#include <string>
#include <map>
#include <functional>
#include <iostream>
#include <cassert>


const int STATE1_INDEX = 0;
const int STATE2_INDEX = 1;


//
// virtual class State
//
class State
{
public:
    virtual float go_to_state1(class HMM* hmm, std::ostream&) = 0;          // return the transition probability
    virtual float go_to_state2(class HMM* hmm, std::ostream&) = 0;          // return the transition probability
    virtual float get_output_probability(int idx, char ch, std::ostream&) = 0; // return the output probability
};


//
// concrete class InitialState
//
class InitialState : public State
{
public:
    float go_to_state1(HMM*, std::ostream&) override;
    float go_to_state2(HMM*, std::ostream&) override;
    float get_output_probability(int idx, char ch, std::ostream&);
};


//
// concrete class State1
//
class State1 : public State
{
    static const float _transition_probability[2];
    static const float _output_probability[4];

public:
    float go_to_state1(HMM*, std::ostream&) override;
    float go_to_state2(HMM*, std::ostream&) override;
    float get_output_probability(int idx, char ch, std::ostream&) override;
};


//
// concrete class State2
//
class State2 : public State
{
    static const float _transition_probability[2];
    static const float _output_probability[4];

public:
    float go_to_state1(HMM*, std::ostream&) override;
    float go_to_state2(HMM*, std::ostream&) override;
    float get_output_probability(int idx, char ch, std::ostream&) override;
};


//
// Hidden Markov Model 
//
class HMM
{
    State* _current_state;

    std::map<char, std::function<float(State&, HMM*, std::ostream&)>> _transitionFn;
    std::map<char, int> _outputIdx;

public:
    HMM(State* initial) : _current_state(initial)
    {
        assert(initial);

        _transitionFn['1'] = std::mem_fn(&State::go_to_state1); // using std::mem_fn for vs2013
        _transitionFn['2'] = std::mem_fn(&State::go_to_state2); // using std::mem_fn for vs2013
        _outputIdx['A'] = 0;
        _outputIdx['C'] = 1;
        _outputIdx['G'] = 2;
        _outputIdx['T'] = 3;
    }

    ~HMM()
    {
        delete _current_state;
    }

    void set_current(State* s)
    {
        _current_state = s;
    }

    float get_probability(const std::string& states, const std::string& symbols, std::ostream& log)
    {
        assert(states.size() == symbols.size());

        float prob = 1;
        log << "1 ";

        auto symbolItr = symbols.cbegin();
        for (const auto& to_state : states)
        {
            assert(_transitionFn.find(to_state) != _transitionFn.end());
            assert(_outputIdx.find(*symbolItr) != _outputIdx.end());

            log << "* ";

            // transition probability
            prob *= _transitionFn[to_state](*_current_state, this, log);

            log << "* ";

            // output probability
            prob *= _current_state->get_output_probability(_outputIdx[*symbolItr], *symbolItr, log);

            ++symbolItr;
        }

        log << "\n";

        return prob;
    }

};





//
// probability settings
//
const float State1::_transition_probability[] = { 0.99f, 0.01f }; 
const float State1::_output_probability[] = { 0.4f, 0.1f, 0.1f, 0.4f }; 

const float State2::_transition_probability[] = { 0.1f, 0.9f };
const float State2::_output_probability[] = { 0.05f, 0.4f, 0.5f, 0.05f };


//
// the implementatoin of InitialState
//
float InitialState::go_to_state1(HMM* hmm, std::ostream& log)
{
    log << "1(initial) ";
    hmm->set_current(new State1);
    delete this;
    return 1; // always 1
}


float InitialState::go_to_state2(HMM* hmm, std::ostream& log)
{
    log << "1(initial) ";
    hmm->set_current(new State2);
    delete this;
    return 1; // always 1
}


float InitialState::get_output_probability(int idx, char ch, std::ostream&)
{
    assert(false); // should not be here
    return 1;
}


//
// the implementatoin of State1
//
float State1::go_to_state1(HMM* hmm, std::ostream& log)
{
    log << _transition_probability[STATE1_INDEX] << " (state1->state1) ";
    hmm->set_current(new State1);
    delete this;
    return _transition_probability[STATE1_INDEX];
}


float State1::go_to_state2(HMM* hmm, std::ostream& log)
{
    log << _transition_probability[STATE2_INDEX] << " (state1->state2) ";
    hmm->set_current(new State2);
    delete this;
    return _transition_probability[STATE2_INDEX];
}


float State1::get_output_probability(int idx, char ch, std::ostream& log)
{
    log << _output_probability[idx] << " (state1 emits " << ch << ") ";
    return _output_probability[idx];
}


//
// the implementatoin of State2
//
float State2::go_to_state1(HMM* hmm, std::ostream& log)
{
    log << _transition_probability[STATE1_INDEX] << " (state2->state1) ";
    hmm->set_current(new State1);
    delete this;
    return _transition_probability[STATE1_INDEX];
}


float State2::go_to_state2(HMM* hmm, std::ostream& log)
{
    log << _transition_probability[STATE2_INDEX] << " (state2->state2) ";
    hmm->set_current(new State2);
    delete this;
    return _transition_probability[STATE2_INDEX];
}


float State2::get_output_probability(int idx, char ch, std::ostream& log)
{
    log << _output_probability[idx] << " (state2 emits " << ch << ") ";
    return _output_probability[idx];
}



//
// main
//
int main(int argc, char **argv)
{
    std::string symbol = "ATCGTACG";
    std::string state = "11221121";
    // calculate the probability of getting the symbol sequence by the given states using the HMM above.
    // The answer should be the product of that as follows:
    // 1(initial) * 0.4(state1 emits A) * 0.99 (state1->state1) * 0.4 (state1 emits T) * 0.01 (state1->state2) * 0.4 (state2 emits C) …;
    // Please just show the results without the calculation process.
    // You might want to add the begin and end states for the start and end of the symbol string (with prob. = 1).
    HMM hmm(new InitialState);
    float prob = hmm.get_probability(state, symbol, std::cout);
    std::cout << "probability = " << prob << "\n";

/*
======
RESULT
======
1 * 1(initial) * 0.4 (state1 emits A) * 0.99 (state1->state1) * 0.4 (state1 emit
s T) * 0.01 (state1->state2) * 0.4 (state2 emits C) * 0.9 (state2->state2) * 0.5
(state2 emits G) * 0.1 (state2->state1) * 0.4 (state1 emits T) * 0.99 (state1->
state1) * 0.4 (state1 emits A) * 0.01 (state1->state2) * 0.4 (state2 emits C) *
0.1 (state2->state1) * 0.1 (state1 emits G)
probability = 1.80652e-010
*/

}
