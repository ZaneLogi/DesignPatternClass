#include "gtest/gtest.h"
#include <boost/iterator/filter_iterator.hpp>


//
// linked list (first in, last out)
//
template <typename T>
class linked_list
{
    template <typename T> friend class linked_list_iterator;

    class linked_list_node
    {
    public:
        T _value;
        linked_list_node* _next;
    };

    linked_list_node* _head;

public:
    linked_list() : _head(nullptr)
    {}

    ~linked_list()
    {
        clear();
    }

    bool is_empty() const
    {
        return _head == nullptr;
    }

    void clear()
    {
        while (_head != nullptr)
        {
            linked_list_node* next = _head->_next;
            delete _head;
            _head = next;
        }
    }

    int count() const
    {
        int count = 0;
        linked_list_node* node = _head;
        while (node != nullptr)
        {
            ++count;
            node = node->_next;
        }
        return count;
    }

    void push(T value)
    {
        linked_list_node* node = new linked_list_node;
        node->_value = value;
        node->_next = _head,
        _head = node;
    }

    T pop()
    {
        linked_list_node* node = _head;
        _head = _head->_next;
        int value = node->_value;
        delete node;
        return value;
    }
};





//
// Test Case
// 
TEST(LinkedList, empty_test)
{
    linked_list<int> list;
    EXPECT_TRUE(list.is_empty());

    list.push(1);
    EXPECT_FALSE(list.is_empty());

    list.pop();
    EXPECT_TRUE(list.is_empty());

    list.push(1);
    list.clear();
    EXPECT_TRUE(list.is_empty());
}

TEST(LinkedList, value_tset)
{
    linked_list<int> list;
    list.push(0);
    list.push(1);
    list.push(2);
    EXPECT_EQ(list.pop(), 2);
    EXPECT_EQ(list.pop(), 1);
    EXPECT_EQ(list.pop(), 0);
}

TEST(LinkedList, count_test)
{
    linked_list<int> list;
    EXPECT_EQ(list.count(), 0);

    list.push(1);
    EXPECT_EQ(list.count(), 1);

    list.push(1);
    EXPECT_EQ(list.count(), 2);

    list.pop();
    EXPECT_EQ(list.count(), 1);

    list.pop();
    EXPECT_EQ(list.count(), 0);
}




//
// linked list iterator
//
template <typename T>
class linked_list_iterator
    : public boost::iterator_facade<
    linked_list_iterator<T>,
    T,
    boost::forward_traversal_tag>
{
public:
    explicit linked_list_iterator(linked_list<T>& list) : _current(list._head)
    {}

    // test to see if it is the end of the linked list
    bool operator()()
    {
        return _current == nullptr;
    }

private:
    friend class boost::iterator_core_access;

    void increment() { _current = _current->_next; }

    T& dereference() const { return _current->_value; }

    typename linked_list<T>::linked_list_node* _current;
};




//
// Test Case
// 
TEST(LinkedListIterator, Test)
{
    linked_list<int> list;
    list.push(0);
    list.push(1);
    list.push(2);

    linked_list_iterator<int> itr(list);
    EXPECT_EQ(*itr, 2);
    ++itr;
    EXPECT_EQ(*itr, 1);
    ++itr;
    EXPECT_EQ(*itr, 0);
    ++itr;
    EXPECT_TRUE(itr()); // no more items.
}





//
// main
//
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
