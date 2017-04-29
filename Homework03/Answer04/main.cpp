#include "gtest/gtest.h"

#include <iterator>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include <random>
#include <chrono>


template<
    typename ValueType,
    template <typename, typename...> class ContainerType,
    typename... Args>
class BackInserter
{
private:
    ContainerType<ValueType, Args...> list;

public:
    void insert(const ValueType& d)
    {
        *std::back_inserter(list) = d;
    }
};


TEST(backinserter_test1, test_vector)
{
    BackInserter<int, std::vector, std::allocator<int>> data; // noted the use of a template template parameter

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 65535);
    std::chrono::steady_clock::time_point start =
        std::chrono::steady_clock::now();
    for (int i = 0; i<100000; ++i)
    {
        data.insert(dis(gen));
    }
    std::chrono::steady_clock::time_point end
        = std::chrono::steady_clock::now();
    std::cout << "Time elapsed : "
        << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
        << "us\n";
}

#if 0
//
// error C2039: 'push_back' : is not a member of 'std::queue<ValueType,std::deque<int,std::allocator<_Ty>>>'
//
TEST(backinserter_test1, test_queue)
{
    BackInserter<int, std::queue, std::deque<int>> data; // noted the use of a template template parameter

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 65535);
    std::chrono::steady_clock::time_point start =
        std::chrono::steady_clock::now();
    for (int i = 0; i<100000; ++i)
    {
        data.insert(dis(gen));
    }
    std::chrono::steady_clock::time_point end
        = std::chrono::steady_clock::now();
    std::cout << "Time elapsed : "
        << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
        << "us\n";
}
#endif


TEST(backinserter_test1, test_deque)
{
    BackInserter<int, std::deque, std::allocator<int>> data; // noted the use of a template template parameter

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 65535);
    std::chrono::steady_clock::time_point start =
        std::chrono::steady_clock::now();
    for (int i = 0; i<100000; ++i)
    {
        data.insert(dis(gen));
    }
    std::chrono::steady_clock::time_point end
        = std::chrono::steady_clock::now();
    std::cout << "Time elapsed : "
        << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
        << "us\n";
}


TEST(backinserter_test1, test_list)
{
    BackInserter<int, std::list, std::allocator<int>> data; // noted the use of a template template parameter

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 65535);
    std::chrono::steady_clock::time_point start =
        std::chrono::steady_clock::now();
    for (int i = 0; i<100000; ++i)
    {
        data.insert(dis(gen));
    }
    std::chrono::steady_clock::time_point end
        = std::chrono::steady_clock::now();
    std::cout << "Time elapsed : "
        << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
        << "us\n";
}


#if 0
//
// error C2039: 'push_back' : is not a member of 'std::set<ValueType,std::less<int>,std::allocator<_Ty>>'
//
TEST(backinserter_test1, test_set)
{
    BackInserter<int, std::set, std::less<int>, std::allocator<int>> data; // noted the use of a template template parameter

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 65535);
    std::chrono::steady_clock::time_point start =
        std::chrono::steady_clock::now();
    for (int i = 0; i<100000; ++i)
    {
        data.insert(dis(gen));
    }
    std::chrono::steady_clock::time_point end
        = std::chrono::steady_clock::now();
    std::cout << "Time elapsed : "
        << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
        << "us\n";
}
#endif


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
