#include "gtest/gtest.h"
#include <functional>


class Number
{
    int _value;

public:
    Number(int v) : _value(v)
    {}

    void divide(Number v2)
    {
        _value /= v2._value;
    }

    void add(Number v2)
    {
        _value += v2._value;
    }

    int operator()()
    {
        return _value;
    }
};

class Command
{
public:
    virtual void execute() = 0;
};

class SimpleCommand : public Command
{
    Number* _receiver;
    std::function<void(Number*)> _action;

public:
    SimpleCommand(Number* num, std::function<void(Number*)> f)
        : _receiver(num)
        , _action(f)
    {}

    void execute() override
    {
        _action(_receiver);
    }
};

class MacroCommand : public Command
{
    std::vector<Command*> _list;

public:
    void push_back(Command *cmd)
    {
        _list.push_back(cmd);
    }

    void execute() override
    {
        for (auto& c : _list)
            c->execute();
    }
};





TEST(CommandDesignPattern,Test1)
{
    Number variableA(10);
    Number variableB(5);
    std::vector<Command*> commands;

    commands.emplace_back(new SimpleCommand(&variableA, std::bind(&Number::divide, std::placeholders::_1, variableB)));
    commands.emplace_back(new SimpleCommand(&variableA, std::bind(&Number::add, std::placeholders::_1, variableB)));

    EXPECT_EQ(variableA(), 10);

    for (auto& c : commands)
        c->execute();

    EXPECT_EQ(variableA(), 7);
}

TEST(CommandDesignPattern, Test2)
{
    Number variableA(10);
    Number variableB(5);
    MacroCommand commands;

    commands.push_back(new SimpleCommand(&variableA, std::bind(&Number::divide, std::placeholders::_1, variableB)));
    commands.push_back(new SimpleCommand(&variableA, std::bind(&Number::add, std::placeholders::_1, variableB)));

    EXPECT_EQ(variableA(), 10);
    commands.execute();
    EXPECT_EQ(variableA(), 7);
}





//
// main
//
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
