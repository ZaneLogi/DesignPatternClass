#include "gtest/gtest.h"
#include <vector>

//
// Mediator, make sure you allow communication between mediator and colleague.
//

class Dialog
{
public:
    virtual ~Dialog() {}
    virtual void send(const std::string& msg, class Component* c) = 0;
};

class Component
{
    Dialog* _dlg;

public:
    Component(Dialog* dlg) : _dlg(dlg)
    {}

    Dialog* get_dialog()
    {
        return _dlg;
    }

    virtual void submit(const std::string& msg) = 0;
    virtual void receive(const std::string& msg) = 0;
    virtual const char* get_response() = 0;
};



class FileSelectionDialog : public Dialog
{
    std::vector<Component*> _all_components;

public:
    ~FileSelectionDialog()
    {
        for (auto& c : _all_components)
        {
            delete c;
        }
    }

    void add(Component* c)
    {
        _all_components.push_back(c);
    }

    void handleEvent(int id, const std::string& msg)
    {
        _all_components[id]->submit(msg);
    }

    const char* get_response(int id)
    {
        return _all_components[id]->get_response();
    }

    void send(const std::string& msg, class Component* c) override
    {
        for (auto& ac : _all_components)
        {
            if (ac == c)
            {
                ac->receive(msg);
                return;
            }
        }
    }
};

class ButtonComponent : public Component
{
    std::string _response;

public:
    ButtonComponent(Dialog* dlg) : Component(dlg)
    {}

    void submit(const std::string& msg) override
    {
        get_dialog()->send(msg, this);
    }

    void receive(const std::string& msg) override
    {
        _response = "Button received " + msg;
    }

    const char* get_response() override
    {
        return _response.c_str();
    }
};

class ScrollComponent : public Component
{
    std::string _response;

public:
    ScrollComponent(Dialog* dlg) : Component(dlg)
    {}

    void submit(const std::string& msg) override
    {
        get_dialog()->send(msg, this);
    }

    void receive(const std::string& msg) override
    {
        _response = "Scroll received " + msg;
    }

    const char* get_response() override
    {
        return _response.c_str();
    }
};

class TextboxComponent : public Component
{
    std::string _response;

public:
    TextboxComponent(Dialog* dlg) : Component(dlg)
    {}

    void submit(const std::string& msg) override
    {
        get_dialog()->send(msg, this);
    }

    void receive(const std::string& msg) override
    {
        _response = "Textbox received " + msg;
    }

    const char* get_response() override
    {
        return _response.c_str();
    }
};




//
// main
//

int main()
{
    FileSelectionDialog fileDialog;
    fileDialog.add(new ButtonComponent(&fileDialog)); // colleague 0
    fileDialog.add(new ScrollComponent(&fileDialog)); // colleague 1
    fileDialog.add(new TextboxComponent(&fileDialog)); // colleague 2

    fileDialog.handleEvent(0, "Hello"); // send "Hello" to colleague 0
    fileDialog.handleEvent(2, "Hi"); // send "Hi" to colleague 2 
    EXPECT_STREQ(fileDialog.get_response(0), "Button received Hello");
    EXPECT_STREQ(fileDialog.get_response(2), "Textbox received Hi");
}
