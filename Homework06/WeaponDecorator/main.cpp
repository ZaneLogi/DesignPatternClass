#include "gtest/gtest.h"
#include <functional>
#include <algorithm>
#include <deque>
#include <cstdarg>



//
// Decorator Design Pattern
//

class Weapon
{
public:
    virtual ~Weapon() {}
    virtual std::string attack() = 0;
    virtual std::string type() const = 0;
    virtual bool hasAttribute(std::string attribute) const = 0;
    virtual void save(std::vector<std::string>& types) const = 0;
};

class Sword : public Weapon
{
    const char* TYPE = "Sword";

public:
    std::string attack() override { return "normal"; }
    std::string type() const override{ return TYPE; }

    bool hasAttribute(std::string attribute) const override { return false; }
    void save(std::vector<std::string>& types) const override { types.push_back(TYPE); }
};

class Bow : public Weapon
{
    const char* TYPE = "Bow";

public:
    std::string attack() override { return "normal"; }
    std::string type() const override{ return TYPE; }

    bool hasAttribute(std::string attribute) const override { return false; }
    void save(std::vector<std::string>& types) const override { types.push_back(TYPE); }
};

class WeaponDecorator : public Weapon
{
    Weapon* _weapon;
public:
    WeaponDecorator(Weapon* w) : _weapon(w) {}
    ~WeaponDecorator() override { delete _weapon; }

    std::string attack() override { return _weapon->attack(); }
    std::string type() const override{ return _weapon->type(); }

    bool hasAttribute(std::string attribute) const override { return _weapon->hasAttribute(attribute); }

    void save(std::vector<std::string>& types) const override { _weapon->save(types); }
};

class FireAttributeDecorator : public WeaponDecorator
{
    const char* ATTRIBUTE = "Fire";

public:
    FireAttributeDecorator(Weapon* w) : WeaponDecorator(w) {}
    std::string attack() override { return std::string("fire_") + WeaponDecorator::attack(); }
    std::string type() const override{ return WeaponDecorator::type(); }

    bool hasAttribute(std::string attribute) const override
    {
        if (attribute == ATTRIBUTE)
            return true;
        return WeaponDecorator::hasAttribute(attribute);
    }

    void save(std::vector<std::string>& types) const override
    {
        types.push_back(ATTRIBUTE);
        WeaponDecorator::save(types);
    }
};

class IceAttributeDecorator : public WeaponDecorator
{
    const char* ATTRIBUTE = "Ice";

public:
    IceAttributeDecorator(Weapon* w) : WeaponDecorator(w) {}
    std::string attack() override { return std::string("ice_") + WeaponDecorator::attack(); }
    std::string type() const override{ return WeaponDecorator::type(); }

    bool hasAttribute(std::string attribute) const override
    {
        if (attribute == ATTRIBUTE)
            return true;
        return WeaponDecorator::hasAttribute(attribute);
    }

    void save(std::vector<std::string>& types) const override
    {
        types.push_back(ATTRIBUTE);
        WeaponDecorator::save(types);
    }    
};


//
// HELPER: createWeapon
//
Weapon* createWeapon(std::string weaponType)
{
    if (weaponType == "Sword")
        return new Sword;
    else if (weaponType == "Bow")
        return new Bow;

    return nullptr;
}

//
// HELPER: enchantWeapon
//
Weapon* enchantWeapon(Weapon* weapon, std::string type)
{
    if (type == "Fire")
    {
        return new FireAttributeDecorator(weapon);
    }
    else if (type == "Ice")
    {
        return new IceAttributeDecorator(weapon);
    }

    return nullptr;
}

//
// HELPER: saveWeapon
//
void saveWeapon(Weapon* weapon, std::vector<std::string>& types)
{
    types.clear();
    weapon->save(types);
    std::reverse(types.begin(), types.end());
}

//
// HELPER: loadWeapon
//
Weapon* loadWeapon(const std::vector<std::string>& types)
{
    auto itr = types.begin();
    Weapon* weapon = createWeapon(*itr);
    ++itr;

    while (itr != types.end())
    {
        weapon = enchantWeapon(weapon, *itr);
        ++itr;
    }

    return weapon;
}

//
// HELPER: isWeaponInfoCorrect
//
bool isWeaponInfoCorrect(const std::vector<std::string> weaponAttributes, ...)
{
    bool correct = true;
    va_list args;
    va_start(args, weaponAttributes);

    for (auto& i : weaponAttributes)
    {
        const char * s = va_arg(args, const char*);
        if (s == nullptr || i != s)
        {
            correct = false;
            break;
        }
    }

    va_end(args);
    return correct;
}



//
// TEST CASE: Create
//
TEST(WeaponCreation, Create)
{
    //
    // no matter what decorator is added, the weapon type should not be changed.
    //
    Weapon* sword = createWeapon("Sword");
    EXPECT_EQ(sword->type(), "Sword");

    sword = enchantWeapon(sword, "Fire");
    EXPECT_EQ(sword->type(), "Sword");

    sword = enchantWeapon(sword, "Ice");
    EXPECT_EQ(sword->type(), "Sword");

    delete sword;


    Weapon* bow = createWeapon("Bow");
    EXPECT_EQ(bow->type(), "Bow");

    bow = enchantWeapon(bow, "Fire");
    EXPECT_EQ(bow->type(), "Bow");

    bow = enchantWeapon(bow, "Ice");
    EXPECT_EQ(bow->type(), "Bow");

    delete bow;
}

//
// TEST CASE: Save
//
TEST(WeaponCreation, Save)
{
    //
    // given a weapon, the attributes of the weapon should be persisted correctly.
    //
    std::vector<std::string> types;

    Weapon* weapon = createWeapon("Sword");
    weapon = enchantWeapon(weapon, "Fire");
    saveWeapon(weapon, types);
    EXPECT_TRUE(isWeaponInfoCorrect(types, "Sword", "Fire", nullptr));

    weapon = enchantWeapon(weapon, "Ice");
    saveWeapon(weapon, types);
    EXPECT_TRUE(isWeaponInfoCorrect(types, "Sword", "Fire", "Ice", nullptr));

    delete weapon;
}

//
// TEST CASE: Load
//
TEST(WeaponCreation, Load)
{
    //
    // given a list of attributes, the weapon should be created corectly.
    //
    std::vector<std::string> types;
    types.push_back("Sword");
    types.push_back("Ice");
    types.push_back("Fire");

    Weapon* weapon = loadWeapon(types);
    saveWeapon(weapon, types);
    EXPECT_TRUE(isWeaponInfoCorrect(types, "Sword", "Ice", "Fire", nullptr));

    delete weapon;
}

//
// TEST CASE: Attack
//
TEST(WeaponCreation, Attack)
{
    //
    // using a weapon to attack, all decorators with the weapon itself should work correctly
    //
    Weapon* weapon = createWeapon("Sword");
    EXPECT_EQ(weapon->attack(), "normal");

    weapon = enchantWeapon(weapon, "Fire");
    EXPECT_EQ(weapon->attack(), "fire_normal");

    weapon = enchantWeapon(weapon, "Ice");
    EXPECT_EQ(weapon->attack(), "ice_fire_normal");

    delete weapon;
}

//
// TEST CASE: Attribute
//
TEST(WeaponCreation, Attribute)
{
    //
    // given a weapon, check its attributes as expected.
    //
    Weapon* weapon = createWeapon("Sword");
    weapon = enchantWeapon(weapon, "Fire");
    weapon = enchantWeapon(weapon, "Ice");
    EXPECT_FALSE(weapon->hasAttribute("Sword")); // it's a type, not an attribute
    EXPECT_TRUE(weapon->hasAttribute("Fire")); // it's an attribute
    EXPECT_TRUE(weapon->hasAttribute("Ice")); // it's an attribute

    delete weapon;
}




//
// Builder Design Pattern
// 

class WeaponsDealer
{
public:
    static WeaponsDealer* getInstance()
    {
        static WeaponsDealer dealer;
        return &dealer;
    }

    static void registerWeaponBuilder(const std::string &type, std::function<Weapon*()> createFunc)
    {
        builderMap[type] = createFunc;
    }

    static void unregisterWeaponBuilder(const std::string& name)
    {
        builderMap.erase(name);
    }

    Weapon* getWeapon(const std::string& name)
    {
        auto itr = builderMap.find(name);
        if (itr != builderMap.end())
            return itr->second();
        else
            return nullptr;
    }

private:
    WeaponsDealer() = default;
    WeaponsDealer(const WeaponsDealer&) = delete;
    const WeaponsDealer& operator = (const WeaponsDealer&) = delete;

private:
    static std::map<std::string, std::function<Weapon*()>> builderMap;
};

std::map<std::string, std::function<Weapon*()>> WeaponsDealer::builderMap;


class FireSwordBuilder
{
public:
    static Weapon* create()
    {
        return new FireAttributeDecorator(new Sword);
    }
};

class IceBowBuilder
{
public:
    static Weapon* create()
    {
        return new IceAttributeDecorator(new Bow);
    }
};


//
// TEST CASE: FireSword
//
TEST(BuilderDesignPattern, FireSword)
{
    WeaponsDealer::registerWeaponBuilder("FireSword", &FireSwordBuilder::create);
    Weapon* weapon = WeaponsDealer::getInstance()->getWeapon("FireSword");
    EXPECT_EQ(weapon->type(), "Sword");
    EXPECT_TRUE(weapon->hasAttribute("Fire"));
    EXPECT_FALSE(weapon->hasAttribute("Ice"));

    delete weapon;
}

//
// TEST CASE: IceBow
//
TEST(BuilderDesignPattern, IceBow)
{
    WeaponsDealer::registerWeaponBuilder("IceBow", &IceBowBuilder::create);
    Weapon* weapon = WeaponsDealer::getInstance()->getWeapon("IceBow");
    EXPECT_EQ(weapon->type(), "Bow");
    EXPECT_TRUE(weapon->hasAttribute("Ice"));
    EXPECT_FALSE(weapon->hasAttribute("Fire"));

    delete weapon;
}




//
// Iterator Design Pattern 
//
class Warehouse
{
    friend class WarehouseIterator;
    std::map<std::string, std::deque<Weapon*>> _list;

public:
    void push(Weapon* weapon)
    {
        _list[weapon->type()].push_back(weapon);
    }

    Weapon* pop(std::string type)
    {
        Weapon* weapon = nullptr;
        auto itr = _list.find(type);
        if (itr != _list.end() && itr->second.size() > 0)
        {
            weapon = itr->second.front();
            itr->second.pop_front();
        }
        return weapon;
    }

    ~Warehouse()
    {
        for (auto& type : _list)
        {
            for (auto& weapon : type.second)
            {
                delete weapon;
            }
        }
    }
};

class WarehouseIterator
{
    const Warehouse &_warehouse;

    std::map<std::string, std::deque<Weapon*>>::const_iterator _itrMap;
    std::deque<Weapon*>::const_iterator _itrDeque;

public:
    WarehouseIterator(const Warehouse& wh) : _warehouse(wh)
    {
        _itrMap = _warehouse._list.begin();
        _itrDeque = _itrMap->second.begin();
    }

    void operator++()
    {
        ++_itrDeque;
        if (_itrDeque == _itrMap->second.end())
        {
            ++_itrMap;
            if (_itrMap != _warehouse._list.end())
            {
                _itrDeque = _itrMap->second.begin();
            }
        }
    }

    bool operator()()
    {
        return _itrMap == _warehouse._list.end();
    }

    Weapon* operator *()
    {
        return *_itrDeque;
    }
};


//
// TEST CASE: Warehouse
//
TEST(IteratorDesignPattern, Warehouse)
{
    Warehouse wh;
    wh.push(FireSwordBuilder::create());
    wh.push(IceBowBuilder::create());

    Weapon* weapon = wh.pop("Sword");
    EXPECT_EQ(weapon->type(), "Sword");
    EXPECT_TRUE(weapon->hasAttribute("Fire"));
}

TEST(IteratorDesignPattern, WarehouseIterator)
{
    Warehouse wh;
    wh.push(FireSwordBuilder::create());
    wh.push(IceBowBuilder::create());

    WarehouseIterator whItr(wh);
    int itemCount = 0;
    while (!whItr())
    {
        Weapon* weapon = *whItr;

        if (weapon->type() == "Sword")
            EXPECT_TRUE(weapon->hasAttribute("Fire"));
        else if (weapon->type() == "Bow")
            EXPECT_TRUE(weapon->hasAttribute("Ice"));

        ++whItr;
        ++itemCount;
    }

    EXPECT_EQ(itemCount, 2);
}




//
// Command Design Pattern 
//

class WeaponShop;

class WeaponOrder
{
    WeaponShop* _shop;
    Weapon*(WeaponShop::*_method)();
public:
    WeaponOrder(WeaponShop* s, Weapon*(WeaponShop::*m)()) : _shop(s), _method(m) {}
    Weapon* execute()
    {
        return (_shop->*_method)();
    }
};

class WeaponShop
{
public:
    Weapon* buyFireSword() { return new FireAttributeDecorator(new Sword); }
    Weapon* buyIceSword() { return new IceAttributeDecorator(new Sword); }
    Weapon* buyFireBow() { return new FireAttributeDecorator(new Bow); }
    Weapon* buyIceBow() { return new IceAttributeDecorator(new Bow); }
};

class WeaponBroker
{
public:
    std::vector<Weapon*> buy(std::vector<WeaponOrder>& list)
    {
        std::vector<Weapon*> result;
        for (auto& i : list)
        {
            result.push_back(i.execute());
        }
        return result;
    }
};

TEST(CommandDesignPattern, orderTest)
{
    WeaponShop shop;
    WeaponOrder order1(&shop, &WeaponShop::buyFireSword);
    WeaponOrder order2(&shop, &WeaponShop::buyIceBow);

    Weapon* weapon1 = order1.execute();
    Weapon* weapon2 = order2.execute();
    EXPECT_EQ(weapon1->type(), "Sword");
    EXPECT_TRUE(weapon1->hasAttribute("Fire"));
    EXPECT_EQ(weapon2->type(), "Bow");
    EXPECT_TRUE(weapon2->hasAttribute("Ice"));
}

TEST(CommandDesignPattern, brokerTest)
{
    WeaponShop shop;
    WeaponOrder order1(&shop, &WeaponShop::buyFireSword);
    WeaponOrder order2(&shop, &WeaponShop::buyIceBow);
    std::vector<WeaponOrder> orderList;
    orderList.push_back(order1);
    orderList.push_back(order2);

    WeaponBroker broker;
    std::vector<Weapon*> weaponList = broker.buy(orderList);
    EXPECT_EQ(weaponList.size(), 2);
}





//
// main
//
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}












#if 0

//
// member function to functor
//

int test()
{
    class Base
    {
    public:
        virtual void test(int) = 0;
    };

    class Derived1 : public Base
    {
    public:
        void test(int i) override { std::cout << "derived1::test " << i << "\n"; }
    };

    class Derived2 : public Base
    {
    public:
        void test(int i) override { std::cout << "derived2::test " << i << "\n"; }
    };

    std::function<void(Base&, int)> cb(&Base::test);

    Derived1 derived1;
    Derived2 derived2;
    cb(derived1, 10);
    cb(derived2, 20);
}

#endif