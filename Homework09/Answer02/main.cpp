#include "gtest/gtest.h"
#include <vector>


//
// Memento, implement undo.
//

class Memento
{
    friend class Originator;
private:
    int _state;
    Memento(int s) : _state(s)
    {}
};


class Originator
{
    int _state;
public:
    Originator(int state) : _state(state)
    {}

    void setState(int newState)
    {
        _state = newState;
    }

    int get_state() const
    {
        return _state;
    }

    Memento* save()
    {
        return new Memento(_state);
    }

    void undo(Memento* m)
    {
        _state = m->_state;
    }
};


class Caretaker
{
    std::vector<Memento*> _memento_list;

public:
    void addMemento(Memento* m)
    {
        _memento_list.push_back(m);
    }

    Memento* get_last_memento()
    {
        Memento* m = _memento_list.back();
        _memento_list.pop_back();
        return m;
    }
};




TEST(Memento, Caretaker)
{
    Caretaker* caretaker = new Caretaker; //keep the memento
    Originator* originator = new Originator(0); //state =0
    caretaker->addMemento(originator->save());
    originator->setState(1);
    caretaker->addMemento(originator->save());
    originator->setState(2);
    EXPECT_EQ(originator->get_state(), 2);
    originator->undo(caretaker->get_last_memento());
    EXPECT_EQ(originator->get_state(), 1);

    // You can move on implementing redo.
}


//
// main
//
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
