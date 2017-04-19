// Answer02.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class Engine
{
private:
    int CC;
    int type;
    int weight;

public:
    Engine() : CC(0), type(0), weight(0)
    {
        std::cout << "invoking the default constructor!" << std::endl;
    }

    ~Engine()
    {
        std::cout << "invoking the destructor!" << std::endl;
    }

    Engine(int c, int t, int w) : CC(c), type(t), weight(w) 
    {
        std::cout << "invoking the non-default constructor!" << std::endl;
    }

    Engine(const Engine& x) : CC(x.CC), type(x.type), weight(x.weight)
    {
        std::cout << "invoking the copy constructor!" << std::endl;
    }

    Engine(Engine&& x) : CC(x.CC), type(x.type), weight(x.weight)
    {
        std::cout << "invoking the move constructor!" << std::endl;

        x.CC = 0;
        x.type = 0;
        x.weight = 0;
    }

    Engine& operator= (const Engine& x)
    {
        std::cout << "invoking the copy assignment!" << std::endl;

        CC = x.CC;
        type = x.type;
        weight = x.weight;

        return *this;
    }

    Engine& operator= (Engine&& x)
    {
        std::cout << "invoking the move assignment!" << std::endl;

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

int _tmain(int argc, _TCHAR* argv[])
{
    std::cout << "Engine a:" << std::endl;
    Engine a; // default constructor

    std::cout << "Engine b:" << std::endl;
    Engine b(1000, 2, 3000); // non-default constructor

    std::cout << "Engine c:" << std::endl;
    Engine c(b); // copy constructor

    std::cout << "Engine d:" << std::endl;
    Engine d; // default constructor
    
    std::cout << "Engine d = b" << std::endl;
    d = b; // copy assignment

    std::cout << "Engine d = b.compare(a):" << std::endl;
    d = b.compare(a); // move assignment

    std::cout << "Engine e:" << std::endl;
    Engine e(std::move(d));

	return 0;
}

