// Answer03.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class Car;

class Engine
{
    friend Car;
    friend void check_engine(Car&);

private:
    int CC;
    int type;
    int weight;

public:
    Engine() : CC(0), type(0), weight(0)
    {}

    ~Engine()
    {}

    Engine(int c, int t, int w) : CC(c), type(t), weight(w)
    {}

    Engine(const Engine& x) : CC(x.CC), type(x.type), weight(x.weight)
    {}

    Engine(Engine&& x) : CC(x.CC), type(x.type), weight(x.weight)
    {
        x.CC = 0;
        x.type = 0;
        x.weight = 0;
    }

    Engine& operator= (const Engine& x)
    {
        CC = x.CC;
        type = x.type;
        weight = x.weight;

        return *this;
    }

    Engine& operator= (Engine&& x)
    {
        CC = x.CC;
        type = x.type;
        weight = x.weight;

        x.CC = 0;
        x.type = 0;
        x.weight = 0;

        return *this;
    }

    Engine compare(const Engine& x)
    {
        return Engine(*this); // copy construcotr
    }

};


class Car
{
    friend void check_engine(Car&);

private:
    Engine my_engine;

public:
    Car() : my_engine(2000,1,3000)
    {
    }

    Car& operator = (const Car& x)
    {
        my_engine = x.my_engine;
        return *this;
    }

    void check_my_engine(void)
    {
        std::cout << "Car::check_my_engine() =>\r\n";
        std::cout << "CC: " << my_engine.CC
            << ", type: " << my_engine.type
            << ", weight: " << my_engine.weight
            << std::endl;
    }
};


void check_engine(Car& car)
{
    std::cout << "check_engine() =>\r\n";
    std::cout << "CC: " << car.my_engine.CC
        << ", type: " << car.my_engine.type
        << ", weight: " << car.my_engine.weight
        << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
    Car my_car;
    check_engine(my_car);
    my_car.check_my_engine();
	return 0;
}

