#include "gtest/gtest.h"

#include <iostream>
#include <string>
#include <functional>

//
// Driver Interface
//
class IDriver
{
public:
    virtual ~IDriver() {}
    virtual bool status_check() const = 0;
};


//
// Driver Factory
//
class DriverFactory
{
public:
    static DriverFactory *get()
    {
        static DriverFactory factory;
        return &factory;
    }

    static void registerDriver(const std::string &type, std::function<IDriver*()> createFunc)
    {
        driverMap[type] = createFunc;
    }

    static void unregisterDriver(const std::string &type)
    {
        driverMap.erase(type);
    }

    IDriver* create(const std::string& type)
    {
        auto itr = driverMap.find(type);
        if (itr != driverMap.end())
            return itr->second();
        else
            return nullptr;
    }

private:
    DriverFactory() = default;
    DriverFactory(const DriverFactory&) = delete;
    const DriverFactory& operator = (const DriverFactory&) = delete;

private:
    static std::map<std::string, std::function<IDriver*()>> driverMap;
};


std::map<std::string, std::function<IDriver*()>> DriverFactory::driverMap;


//
// mouse
//
class mouse : public IDriver
{
public:
    static IDriver* create()
    {
        return new mouse();
    }

    ~mouse() override {}

    bool status_check() const override
    {
        return true;
    }

private:
    mouse() = default;
};


//
// unit test
//
TEST(DriverFactoryTest, Creation)
{
    IDriver *pdriver = nullptr;

    std::string driver_name("mouse");

    DriverFactory::registerDriver(driver_name, &mouse::create);

    pdriver = DriverFactory::get()->create(driver_name);
    if (pdriver)
    {
        EXPECT_EQ(pdriver->status_check(), true);
    }
    else
    {
        std::cout << "creation failed" << std::endl;
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
