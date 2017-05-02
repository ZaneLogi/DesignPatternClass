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
    template <typename...> class ContainerType>
class BackInserter
{
private:
    ContainerType<ValueType, std::allocator<ValueType>> list;

public:
    void insert(const ValueType& d)
    {
        *std::back_inserter(list) = d;
    }
};


// Partial template specialization for specific type 'std::queue'
template<typename ValueType>
class BackInserter<ValueType, std::queue>
{
private:
    std::queue<ValueType> list;

public:
    void insert(const ValueType& d)
    {
        list.push(d);
    }
};


// Partial template specialization for specific type 'std::set'
template<typename ValueType>
class BackInserter<ValueType, std::set>
{
private:
    std::set<ValueType> list;

public:
    void insert(const ValueType& d)
    {
        list.insert(d);
    }
};


TEST(backinserter_test1, test_vector)
{
    BackInserter<int, std::vector> data; // noted the use of a template template parameter

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


TEST(backinserter_test1, test_queue)
{
    BackInserter<int, std::queue> data; // noted the use of a template template parameter

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


TEST(backinserter_test1, test_deque)
{
    BackInserter<int, std::deque> data; // noted the use of a template template parameter

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
    BackInserter<int, std::list> data; // noted the use of a template template parameter

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


TEST(backinserter_test1, test_set)
{
    BackInserter<int, std::set> data; // noted the use of a template template parameter

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


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
