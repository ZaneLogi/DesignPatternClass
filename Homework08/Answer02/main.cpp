#include "gtest/gtest.h"
#include <vector>

class Square;
class Circle;

class visitor
{
public:
    virtual float visit(Square* square) = 0;
    virtual float visit(Circle* circle) = 0;
};


class Visitable_Item
{
public:
    virtual float accept(visitor *v) = 0;
};


class Square : public Visitable_Item
{
    float _length;

public:
    Square(float length) : _length(length)
    {}

    float accept(visitor* v) override
    {
        return v->visit(this);
    }

    float get_length() const
    {
        return _length;
    }
};


class Circle : public Visitable_Item
{
    float _radius;

public:
    Circle(float radius) : _radius(radius)
    {}

    float accept(visitor* v) override
    {
        return v->visit(this);
    }

    float get_radius() const
    {
        return _radius;
    }
};


class get_area_vistor : public visitor
{
public:
    float visit(Square* square) override
    {
        return square->get_length() * square->get_length();
    }

    float visit(Circle* circle) override
    {
        return circle->get_radius() * circle->get_radius() * 3.14f;
    }
};


class get_perimeter_vistor : public visitor
{
public:
    float visit(Square* square) override
    {
        return square->get_length() * 4;
    }

    float visit(Circle* circle) override
    {
        return circle->get_radius() * 2 * 3.14f;
    }
};


TEST(VisitorDesignPattern, get_area_vistor)
{
    std::vector<Visitable_Item*>  items;
    items.push_back(new Square(10));
    items.push_back(new Circle(5));
    visitor* v1 = new get_area_vistor;
    EXPECT_EQ(items[0]->accept(v1), 100);
    EXPECT_EQ(items[1]->accept(v1), 78.5);

    // free memory
    for (auto& i : items)
    {
        delete i;
    }
}

TEST(VisitorDesignPattern, get_perimeter_vistor)
{
    std::vector<Visitable_Item*>  items;
    items.push_back(new Square(10));
    items.push_back(new Circle(5));
    visitor* v1 = new get_perimeter_vistor;
    EXPECT_EQ(items[0]->accept(v1), 40);
    EXPECT_EQ(items[1]->accept(v1), 5.0f * 6.28f);

    // free memory
    for (auto& i : items)
    {
        delete i;
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
