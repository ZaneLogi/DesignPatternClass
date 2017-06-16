#include "gtest/gtest.h"
#include <vector>
#include <random>

/*
Flyweight, make sure you only create and delete two instances of TILE.
You can prepare some prompts on the screen when TILE is created or deleted.
*/

class TILE
{
    std::string _name;

public:
    TILE(const char* n) : _name(n)
    {}

    void print_basic_info()
    {
        std::cout << "Tile type: " << _name << "\n";
    }

    void print_position_info(int x, int y)
    {
        std::cout << "Tile type: " << _name << ", x = " << x << ", y = " << y << "\n";
    }
};

class Terrain_Factory
{
    std::map<std::string, TILE*> _tileMap;

public:
    static Terrain_Factory* get_instance()
    {
        static Terrain_Factory tf;
        return &tf;
    }

    ~Terrain_Factory()
    {
        for (auto& t : _tileMap)
        {
            std::cout << "delete tile: ";
            t.second->print_basic_info();
            std::cout << "\n";
            delete t.second;
        }
    }

    TILE* create_hill()
    {
        return create_tile("hill");
    }

    TILE* create_grass()
    {
        return create_tile("grass");
    }

private:
    Terrain_Factory() = default;
    Terrain_Factory(const Terrain_Factory&) = delete;
    Terrain_Factory& operator = (const Terrain_Factory&) = delete;

    TILE* create_tile(const char* name)
    {
        auto& itr = _tileMap.find(name);
        if (itr != _tileMap.end())
        {
            return itr->second;
        }
        else
        {
            std::cout << "create new tile: " << name << "\n";
            auto t = new TILE(name);
            _tileMap[name] = t;
            return t;
        }
    }
};

int random(int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, max - 1);
    return dis(gen);
}

TEST(Flyweight, TILE)
{
    std::vector< std::vector<TILE*> > mytiles(100, std::vector<TILE*>(100));
    for (auto& x : mytiles)
    {
        for (auto& y : x)
        {
            // Sprinkle some hills.
            if (random(10) == 0) // 1/10 chance
            {
                y = Terrain_Factory::get_instance()->create_hill();
            }
            else
            {
                y = Terrain_Factory::get_instance()->create_grass();
            }
        }
    }

    for (int x = 0; x< 100; x++)
    {
        for (int y = 0; y<100; y++)
        {
            mytiles[x][y]->print_basic_info();
            mytiles[x][y]->print_position_info(x, y);
        }
    }
}

//
// main
//
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
