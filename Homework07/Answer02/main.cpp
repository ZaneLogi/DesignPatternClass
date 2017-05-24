#include "gtest/gtest.h"
#include <vector>



class Employee
{
public:
    static int _count;

protected:
    std::string _name;
public:
    Employee(const std::string& name)
        : _name(name)
    {
        _count++;
    }

    virtual ~Employee()
    {
        _count--;
    }

    virtual void manage(Employee*) = 0;
    virtual std::string who() = 0;
};

int Employee::_count = 0;

class Worker : public Employee
{
public:
    Worker(const std::string& name)
        : Employee(name)
    {}

    void manage(Employee*) // can't manage others
    {}

    std::string who() override
    {
        return _name;
    }
};

class Manager : public Employee
{
    std::vector<Employee*> _members;

public:
    Manager(const std::string& name)
        : Employee(name)
    {}

    ~Manager() override
    {
        for (auto& m : _members)
            delete m;
    }

    void manage(Employee* x)
    {
        _members.push_back(x);
    }

    std::string who() override
    {
        std::string who = _name;
        for (auto& m : _members)
        {
            who += " " + m->who();
        }
        return who;
    }
};

class Director : public Employee
{
    std::vector<Employee*> _members;

public:
    Director(const std::string& name)
        : Employee(name)
    {}

    ~Director() override
    {
        for (auto& m : _members)
            delete m;
    }

    void manage(Employee* x)
    {
        _members.push_back(x);
    }

    std::string who() override
    {
        std::string who = _name;
        for (auto& m : _members)
        {
            who += " " + m->who();
        }
        return who;
    }
};




//
// TEST CASE
//
TEST(Composite, Test)
{
    Employee* A = new Worker("Mary");
    Employee* B = new Worker("Jean");
    Employee* C = new Manager("John Doe");
    Employee* D = new Director("Gin");
    C->manage(A);
    C->manage(B);
    D->manage(C);
    EXPECT_STREQ("Gin John Doe Mary Jean", D->who().c_str());
    //delete...
    delete D;
}

TEST(Composite, memory_leak_test)
{
    EXPECT_EQ(Employee::_count, 0);
}

//
// main
//
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
