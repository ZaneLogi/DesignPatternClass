#include "gtest/gtest.h"
#include <functional>
#include <algorithm>

#if 1

//
// Decorator Design Pattern
//
class Denominator
{
public:
    virtual ~Denominator() { std::cout << "Denominator::~Denominator\r\n"; }
    virtual void doSomething() = 0;
};

class Core : public Denominator
{
public:
    void doSomething() override { std::cout << "Core::doSomething\r\n"; }

    ~Core() override {
        std::cout << "Core::~Core\r\n";
    }
};

class Decorator : public Denominator
{
private:
    Denominator* _denominator;
public:
    Decorator(Denominator* d) : _denominator(d) {}
    void doSomething() override { std::cout << "Decorator::doSomething\r\n"; _denominator->doSomething(); }

    ~Decorator() override {
        std::cout << "Decorator::~Decorator\r\n";
        delete _denominator;
    }
};

class A_decorator : public Decorator
{
public:
    A_decorator(Denominator* d) : Decorator(d) {}
    void doSomething() override { std::cout << "A_decorator::doSomething\r\n"; Decorator::doSomething(); }

    ~A_decorator() override {
        std::cout << "A_decorator::~A_decorator\r\n";
    }
};

class B_decorator : public Decorator
{
public:
    B_decorator(Denominator* d) : Decorator(d) {}
    void doSomething() override { std::cout << "B_decorator::doSomething\r\n"; Decorator::doSomething(); }

    ~B_decorator() override {
        std::cout << "B_decorator::~B_decorator\r\n";
    }
};



TEST(DecoratorDesignPattern, A_decorator)
{
    Denominator* myCore = new Core();
    myCore = new A_decorator(myCore);
    myCore->doSomething();
    delete myCore;
}

TEST(DecoratorDesignPattern, B_decorator)
{
    Denominator* myCore = new Core();
    myCore = new B_decorator(myCore);
    myCore->doSomething();
    delete myCore;
}

TEST(DecoratorDesignPattern, A_decorator_AND_B_decorator)
{
    Denominator* myCore = new Core();
    myCore = new A_decorator(myCore);
    myCore = new B_decorator(myCore);
    myCore->doSomething();
    delete myCore;
}

#endif



#if 0

//
// Iterator Design Pattern
//
class Container
{
    friend class ContainerIterator;

    int _capacity;
    int _size;
    int _data[10];

public:
    ContainerIterator *createIterator() const;
};

class ContainerIterator
{
    const Container* _container;
    int _index;
public:
    ContainerIterator(const Container* c) : _container(c) {}
    void first() { _index = 0; }
    void next() { _index++; }
    bool end() { return _index == _container->_size; }
    int current() { return _container->_data[_index]; }
};

ContainerIterator* Container::createIterator() const
{
    return new ContainerIterator(this);
}

#endif


#if 0

class Receiver;

class Command
{
    Receiver* _receiver;
    std::function<void()> _invokedMethod;

public:
    Command(Receiver* r, void (Receiver::*f)()) : _receiver(r)
    {
        _invokedMethod = std::bind(f, _receiver);
    }

    void execute()
    {
        _invokedMethod();
    }
};

class Receiver
{
public:
    void action1() { std::cout << "invoked Receiver::action1\r\n"; }
    void action2() { std::cout << "invoked Receiver::action2\r\n"; }
    void action3() { std::cout << "invoked Receiver::action3\r\n"; }
};

TEST(CommandDesignPattern, action1)
{
    Receiver myReceiver;
    Command myCommand(&myReceiver, &Receiver::action1);
    myCommand.execute();
}

TEST(CommandDesignPattern, action2)
{
    Receiver myReceiver;
    Command myCommand(&myReceiver, &Receiver::action2);
    myCommand.execute();
}

TEST(CommandDesignPattern, action3)
{
    Receiver myReceiver;
    Command myCommand(&myReceiver, &Receiver::action3);
    myCommand.execute();
}

#endif



//
// main
//
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
