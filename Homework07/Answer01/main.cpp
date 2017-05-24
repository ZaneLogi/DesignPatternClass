#include "gtest/gtest.h"
#include <functional>
#include <sstream>

//
// CarPart (virtual base)
//
class CarPart
{
public:
    virtual const char* get_info() = 0;
};

//
// Wheel (CarPart-derived)
//
class Wheel : public CarPart
{
    std::string _info;
public:
    Wheel(const std::string& type)
    {
        std::stringstream ss;
        ss << "CarPart: " << type << " wheel";
        _info = ss.str();
    }

    const char* get_info() override
    {
        return _info.c_str();
    }
};

//
// Frame (CarPart-derived)
//
class Frame : public CarPart
{
    std::string _info;
public:
    Frame(const std::string& type)
    {
        std::stringstream ss;
        ss << "CarPart: " << type << " frame";
        _info = ss.str();
    }

    const char* get_info() override
    {
        return _info.c_str();
    }
};

//
// Factory (virtual base)
//
class Factory
{
public:
    virtual CarPart* create_wheel() = 0;
    virtual CarPart* create_frame() = 0;
};

//
// Wooden Factory (Factory-drived)
//
class WoodenFactory : public Factory
{
public:
    static WoodenFactory* get_instance()
    {
        static WoodenFactory theFactory;
        return &theFactory;
    }

    CarPart* create_wheel() override
    {
        return new Wheel("wooden");
    }

    CarPart* create_frame() override
    {
        return new Frame("wooden");
    }


private:
    WoodenFactory() = default;
    WoodenFactory(const WoodenFactory&) = delete;
    const WoodenFactory& operator = (const WoodenFactory&) = delete;
};

//
// Steel Factory (Factory-drived)
//
class SteelFactory : public Factory
{
public:
    static SteelFactory* get_instance()
    {
        static SteelFactory theFactory;
        return &theFactory;
    }

    CarPart* create_wheel() override
    {
        return new Wheel("steel");
    }

    CarPart* create_frame() override
    {
        return new Frame("steel");
    }


private:
    SteelFactory() = default;
    SteelFactory(const SteelFactory&) = delete;
    const SteelFactory& operator = (const SteelFactory&) = delete;
};

//
// Cart Part Factory
//
class CartPartFactory
{
public:
    static CartPartFactory* get_instance()
    {
        static CartPartFactory theFactory;
        return &theFactory;
    }

    static void register_factory(const std::string& type, Factory* factory)
    {
        _factoryMap[type] = factory;
    }

    CarPart* create_wheel(const std::string& type)
    {
        return _factoryMap[type]->create_wheel();
    }

    CarPart* create_frame(const std::string& type)
    {
        return _factoryMap[type]->create_frame();
    }

private:
    CartPartFactory() = default;
    CartPartFactory(const CartPartFactory&) = delete;
    const CartPartFactory& operator = (const CartPartFactory&) = delete;

private:
    static std::map<std::string, Factory*> _factoryMap;
};

std::map<std::string, Factory*> CartPartFactory::_factoryMap;





//
// TEST CASE
//
TEST(AbstractFactory, Test)
{        
    CartPartFactory::get_instance()->register_factory("wooden", WoodenFactory::get_instance());
    CartPartFactory::get_instance()->register_factory("steel", SteelFactory::get_instance());
    CarPart* wooden_wheel = CartPartFactory::get_instance()->create_wheel("wooden");
    CarPart* steel_wheel = CartPartFactory::get_instance()->create_wheel("steel");
    CarPart* wooden_frame = CartPartFactory::get_instance()->create_frame("wooden");
    CarPart* steel_frame = CartPartFactory::get_instance()->create_frame("steel");

    EXPECT_STREQ("CarPart: wooden wheel", wooden_wheel->get_info());
    EXPECT_STREQ("CarPart: wooden frame", wooden_frame->get_info());
    EXPECT_STREQ("CarPart: steel wheel", steel_wheel->get_info());
    EXPECT_STREQ("CarPart: steel frame", steel_frame->get_info());
}





//
// main
//
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
