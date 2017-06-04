#include <string>
#include <map>
#include <functional>
#include <iostream>

class State
{
public:
    virtual float to_state1(class HMM* hmm) = 0;
    virtual float to_state2(class HMM* hmm) = 0;
    virtual float get_output_probability(int o) = 0;
};


class HMM
{
    State* _current_state;

    std::map<char, std::function<float(State&, HMM*)>> _mapState;
    std::map<char, int> _mapOutput;

public:
    HMM(State* initial) : _current_state(initial)
    {
        _mapState['1'] = std::mem_fn(&State::to_state1); // for vs2013
        _mapState['2'] = std::mem_fn(&State::to_state2); // for vs2013
        _mapOutput['A'] = 0;
        _mapOutput['C'] = 1;
        _mapOutput['G'] = 2;
        _mapOutput['T'] = 3;
    }

    ~HMM()
    {
        delete _current_state;
    }

    void set_current(State* s)
    {
        _current_state = s;
    }

    float get_probability(const std::string& states, const std::string& symbols)
    {
        float prob = 1;

        for (unsigned i = 0; i < states.size(); i++)
        {
            // transition probability
             prob *= _mapState[states[i]](*_current_state, this);

             // output probability
             float output_probability = _current_state->get_output_probability(_mapOutput[symbols[i]]);
             std::cout << symbols[i] << " - output probability = " << output_probability << "\n";
             prob *= output_probability;
        }
        return prob;
    }



};


class InitialState : public State
{
public:
    float to_state1(HMM*) override;
    float to_state2(HMM*) override;
    float get_output_probability(int o);
};


class State1 : public State
{
    static float _transition_probability[2];
    static float _output_probability[4];

public:
    float to_state1(HMM*) override;
    float to_state2(HMM*) override;
    float get_output_probability(int o) override;
};

float State1::_transition_probability[2] = { 0.99f, 0.01f }; 
float State1::_output_probability[4] = { 0.4f, 0.1f, 0.1f, 0.4f }; 


class State2 : public State
{
    static float _transition_probability[2];
    static float _output_probability[4];

public:
    float to_state1(HMM*) override;
    float to_state2(HMM*) override;
    float get_output_probability(int o) override;
};

float State2::_transition_probability[2] = { 0.1f, 0.9f };
float State2::_output_probability[4] = { 0.05f, 0.4f, 0.5f, 0.05f };


float InitialState::to_state1(HMM* hmm)
{
    std::cout << "From InitialState to State1, _transition_probability = 1\n";
    hmm->set_current(new State1);
    delete this;
    return 1;
}


float InitialState::to_state2(HMM* hmm)
{
    std::cout << "From InitialState to State2, _transition_probability = 1\n";
    hmm->set_current(new State2);
    delete this;
    return 1;
}


float InitialState::get_output_probability(int o)
{
    return 1;
}


float State1::to_state1(HMM* hmm)
{
    std::cout << "From State1 to State1, _transition_probability = " << _transition_probability[0] << "\n";
    hmm->set_current(new State1);
    delete this;
    return _transition_probability[0];
}


float State1::to_state2(HMM* hmm)
{
    std::cout << "From State1 to State2, _transition_probability = " << _transition_probability[1] << "\n";
    hmm->set_current(new State2);
    delete this;
    return _transition_probability[1];
}


float State1::get_output_probability(int o)
{
    return _output_probability[o];
}


float State2::to_state1(HMM* hmm)
{
    std::cout << "From State2 to State1, _transition_probability = " << _transition_probability[0] << "\n";
    hmm->set_current(new State1);
    delete this;
    return _transition_probability[0];
}


float State2::to_state2(HMM* hmm)
{
    std::cout << "From State2 to State2, _transition_probability = " << _transition_probability[1] << "\n";
    hmm->set_current(new State2);
    delete this;
    return _transition_probability[1];
}


float State2::get_output_probability(int o)
{
    return _output_probability[o];
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
    // Please just show the results without the calculation process. You might want to add the begin and end states for the start and end of the symbol string (with prob. = 1).
    HMM hmm(new InitialState);
    float prob = hmm.get_probability(state, symbol);
    std::cout << "probability = " << prob << "\n";
}
