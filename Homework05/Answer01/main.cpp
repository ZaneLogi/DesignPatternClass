#include "gtest/gtest.h"
#include <functional>
#include <cassert>




class Dough
{
public:
    virtual ~Dough() {}
    virtual std::string brand() const = 0;
};

class Topping
{
public:
    virtual ~Topping() {}
    virtual std::string name() const = 0;
};

class Sauce
{
public:
    virtual ~Sauce() {}
    virtual std::string type() const = 0;
};

class Pizza
{
public:
    virtual ~Pizza() {}
    virtual Dough* get_dough() = 0;
    virtual Topping* get_topping() = 0;
    virtual Sauce* get_sauce() = 0;
};



class CrisspyFlower : public Dough
{
public:
    std::string brand() const override { return "CrisspyFlower"; }
};


class ToughFlower : public Dough
{
public:
    std::string brand() const override { return "ToughFlower"; }
};


class Pineapple : public Topping
{
public:
    std::string name() const override { return "Pineapple"; }
};


class ChiliPepper : public Topping
{
public:
    std::string name() const override { return "chili pepper"; }
};


class Mayo : public Sauce
{
public:
    std::string type() const override { return "mayo"; }
};


class SourSauce : public Sauce
{
public:
    std::string type() const override { return "sour sauce"; }
};


//
// class HawaiianPizzaBuilder
//
class HawaiianPizzaBuilder : public Pizza
{
private:
    CrisspyFlower _dough;
    Pineapple _topping;
    Mayo _sauce;

public:
    static Pizza* create()
    {
        return new HawaiianPizzaBuilder();
    }

    Dough* get_dough() override { return &_dough; }
    Topping* get_topping() override { return &_topping; }
    Sauce* get_sauce() override { return &_sauce; }

private:
    HawaiianPizzaBuilder() = default;
};


//
// class ChiliPizzaBuilder
//
class ChiliPizzaBuilder : public Pizza
{
private:
    ToughFlower _dough;
    ChiliPepper _topping;
    SourSauce _sauce;

public:
    static Pizza* create()
    {
        return new ChiliPizzaBuilder();
    }

    Dough* get_dough() override { return &_dough; }
    Topping* get_topping() override { return &_topping; }
    Sauce* get_sauce() override { return &_sauce; }

private:
    ChiliPizzaBuilder() = default;
};


//
// class pizza_director
//
class pizza_director
{
public:
    static pizza_director *get_instance()
    {
        static pizza_director director;
        return &director;
    }

    static void register_pizza_builder(const std::string &type, std::function<Pizza*()> createFunc)
    {
        builderMap[type] = createFunc;
    }

    static void unregister_pizza_builder(const std::string& name)
    {
        builderMap.erase(name);
    }

    Pizza* getPizza(const std::string& name)
    {
        auto itr = builderMap.find(name);
        if (itr != builderMap.end())
            return itr->second();
        else
            return nullptr;
    }

private:
    pizza_director() = default;
    pizza_director(const pizza_director&) = delete;
    const pizza_director& operator = (const pizza_director&) = delete;

private:
    static std::map<std::string, std::function<Pizza*()>> builderMap;
};

std::map<std::string, std::function<Pizza*()>> pizza_director::builderMap;




//
// TEST1
//
TEST(HawaiianPizzaBuilder, Hawaii)
{
    pizza_director::register_pizza_builder("Hawaii", &HawaiianPizzaBuilder::create);
    Pizza* pizza = pizza_director::get_instance()->getPizza("Hawaii");
    Dough* my_dough = pizza->get_dough();
    Topping* my_topping = pizza->get_topping();
    Sauce* my_sauce = pizza->get_sauce();
    EXPECT_EQ(my_dough->brand(), "CrisspyFlower");
    EXPECT_EQ(my_topping->name(), "Pineapple");
    EXPECT_EQ(my_sauce->type(), "mayo");
}


//
// TEST2
//
TEST(ChiliPizzaBuilder, SpicyCraz)
{
    pizza_director::register_pizza_builder("SpicyCraz", &ChiliPizzaBuilder::create);
    Pizza* pizza = pizza_director::get_instance()->getPizza("SpicyCraz");
    Dough* my_dough = pizza->get_dough();
    Topping* my_topping = pizza->get_topping();
    Sauce* my_sauce = pizza->get_sauce();
    EXPECT_EQ(my_dough->brand(), "ToughFlower");
    EXPECT_EQ(my_topping->name(), "chili pepper");
    EXPECT_EQ(my_sauce->type(), "sour sauce");
}


//
// main
//
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
