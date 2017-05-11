#include "gtest/gtest.h"
#include "FromAnswer02.h"


class NewShape
{
public:
    virtual ~NewShape() {}
    virtual std::string newdraw() const = 0;
};


class AdapterTriangle : public NewShape
{
    Triangle* _triangle;
public:
    AdapterTriangle(Triangle* triangle) : _triangle(triangle) {}
    ~AdapterTriangle() { delete _triangle; }
    std::string newdraw() const override { return _triangle->draw(); }
};


//
// TEST
//
TEST(NewShape, Draw)
{
    NewShape* newtriangle = new AdapterTriangle(new Triangle(new OpenGL_api));
    EXPECT_EQ(newtriangle->newdraw(), "using OpenGL to draw");
    delete newtriangle;
}


//
// main
//
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
