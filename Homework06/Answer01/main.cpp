#include "gtest/gtest.h"


//
// Coffee
//
class Coffee
{
public:
    static int __count;

public:
    Coffee() { __count++; }
    virtual ~Coffee() { __count--; }
    virtual int get_cost() = 0;
    virtual std::string get_content() = 0;
};

int Coffee::__count = 0;

//
// Black Coffee
//
class BlackCoffee : public Coffee
{
public:
    int get_cost() override { return 10; }
    std::string get_content() override { return "black coffee"; }
};

//
// Coffee Decorator
//
class CoffeeDecorator : public Coffee
{
private:
    Coffee* _coffee;
public:
    CoffeeDecorator(Coffee* d) : _coffee(d) {}
    ~CoffeeDecorator() override { delete _coffee; }

    int get_cost() override { return _coffee->get_cost(); }
    std::string get_content() override { return _coffee->get_content(); }
};

//
// Milk Decorator
//
class MilkDecorator : public CoffeeDecorator
{
public:
    MilkDecorator(Coffee* d) : CoffeeDecorator(d) {}
    
    int get_cost() override { return 5 + CoffeeDecorator::get_cost(); }
    std::string get_content() override { return CoffeeDecorator::get_content() + " with milk"; }
};

//
// Sugar Decorator
//
class SugarDecorator : public CoffeeDecorator
{
public:
    SugarDecorator(Coffee* d) : CoffeeDecorator(d) {}
    int get_cost() override { return 1 + CoffeeDecorator::get_cost(); }
    std::string get_content() override { return CoffeeDecorator::get_content() + " with sugar"; }
};





TEST(DecoratorDesignPattern, Test1)
{
    Coffee *mycoffee = new BlackCoffee;
    EXPECT_EQ(mycoffee->get_cost(), 10);
    EXPECT_STREQ(mycoffee->get_content().c_str(), "black coffee");

    mycoffee = new MilkDecorator(mycoffee);
    EXPECT_EQ(mycoffee->get_cost(), 15);
    EXPECT_STREQ(mycoffee->get_content().c_str(), "black coffee with milk");

    mycoffee = new SugarDecorator(mycoffee);
    EXPECT_EQ(mycoffee->get_cost(), 16);
    EXPECT_STREQ(mycoffee->get_content().c_str(), "black coffee with milk with sugar");

    delete mycoffee;
}

TEST(DecoratorDesignPattern, Test2)
{
    Coffee *mycoffee = new BlackCoffee;
    mycoffee = new SugarDecorator(mycoffee);
    EXPECT_EQ(mycoffee->get_cost(), 11);
    EXPECT_STREQ(mycoffee->get_content().c_str(), "black coffee with sugar");

    delete mycoffee;
}

TEST(DecoratorDesignPattern, memory_leak_test)
{
    EXPECT_EQ(Coffee::__count, 0);
}





//
// main
//
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
