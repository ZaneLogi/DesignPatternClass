#include "gtest/gtest.h"


class Complex
{
private:
    double realNumber;
    double imaginaryNumber;

public:
    Complex(double real, double imaginary)
        : realNumber(real)
        , imaginaryNumber(imaginary)
    {}

    inline double getRealNumber() const
    {
        return realNumber;
    }

    inline double getImaginaryNumber() const
    {
        return imaginaryNumber;
    }

    Complex operator * (const Complex& x) const
    {
        return Complex(
            realNumber * x.realNumber - imaginaryNumber * x.imaginaryNumber,
            realNumber * x.imaginaryNumber + imaginaryNumber * x.realNumber);
    }

    bool operator == (const Complex& x) const
    {
        return realNumber == x.realNumber
            && imaginaryNumber == x.imaginaryNumber;
    }
};



TEST(ComplexMultiUnitTests, testMultiply)
{
    Complex x1(10, 9); //10+9i
    Complex x2(5, 4);  // 5+4i
    Complex y(14, 85); //14+85i

    EXPECT_EQ(x1*x2, y);
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
