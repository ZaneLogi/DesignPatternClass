#include "gtest/gtest.h"
#include <vector>

class Image
{
public:
    virtual Image* clone() = 0;
    virtual const char* info() = 0;
};

class DogImage : public Image
{
    std::string _info;

public:
    DogImage(const std::string& size)
    {
        _info = "dog image : " + size;
    }

    Image* clone() override
    {
        return new DogImage(*this);
    }

    const char* info() override
    {
        return _info.c_str();
    }
};

class CatImage : public Image
{
    std::string _info;

public:
    CatImage(const std::string& size)
    {
        _info = "cat image : " + size;
    }

    Image* clone() override
    {
        return new CatImage(*this);
    }

    const char* info() override
    {
        return _info.c_str();
    }
};





TEST(Prototype, Test)
{
    std::vector<Image*> all_image_prototype;
    all_image_prototype.push_back(new DogImage("big"));
    all_image_prototype.push_back(new CatImage("small"));
    all_image_prototype.push_back(new DogImage("huge"));
    Image* my_image = all_image_prototype[1]->clone();
    EXPECT_STREQ("cat image : small", my_image->info());
    my_image = all_image_prototype[2]->clone();
    EXPECT_STREQ("dog image : huge", my_image->info());
    //delete...
    for (auto& i : all_image_prototype)
    {
        delete i;
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
