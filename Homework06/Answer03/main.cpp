#include "gtest/gtest.h"
#include <functional>


class Command
{
public:
    virtual void execute() = 0;
};

void divide(int* var1, int var2)
{
    *var1 /= var2;
}

void add(int* var1, int var2)
{
    *var1 += var2;
}

class SimpleCommand : public Command
{
    int* _receiver;
    std::function<void(int*)> _action;

public:
    SimpleCommand(int* num, std::function<void(int*)> f)
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
    int variableA(10);
    int variableB(5);
    std::vector<Command*> commands;

    commands.emplace_back(new SimpleCommand(&variableA, std::bind(&divide, std::placeholders::_1, variableB)));
    commands.emplace_back(new SimpleCommand(&variableA, std::bind(&add, std::placeholders::_1, variableB)));

    EXPECT_EQ(variableA, 10);

    for (auto& c : commands)
        c->execute();

    EXPECT_EQ(variableA, 7);
}

TEST(CommandDesignPattern, Test2)
{
    int variableA(10);
    int variableB(5);
    MacroCommand commands;

    commands.push_back(new SimpleCommand(&variableA, std::bind(&divide, std::placeholders::_1, variableB)));
    commands.push_back(new SimpleCommand(&variableA, std::bind(&add, std::placeholders::_1, variableB)));

    EXPECT_EQ(variableA, 10);
    commands.execute();
    EXPECT_EQ(variableA, 7);
}





//
// main
//
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
