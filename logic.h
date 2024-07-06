#ifndef LOGIC_H
#define LOGIC_H

#include <string>
#include "graphics.h"
#include <vector>

int min(int a, int b);

class BinaryFunction {
public:

    virtual bool compute(bool a, bool b);
    virtual ~BinaryFunction();

};

class AndFunction : public BinaryFunction {
public:
    AndFunction() {};
    bool compute(bool a, bool b) override;
};
class OrFunction : public BinaryFunction {
public:
    OrFunction() {};
    bool compute(bool a, bool b) override;
};
class XorFunction : public BinaryFunction {
public:
    XorFunction() {};
    bool compute(bool a, bool b) override;
};

class NandFunction : public BinaryFunction {
public:
    NandFunction() {};
    bool compute(bool a, bool b) override;
};
class NorFunction : public BinaryFunction {
public:
    NorFunction() {};
    bool compute(bool a, bool b) override;
};
class XnorFunction : public BinaryFunction {
public:
    XnorFunction() {};
    bool compute(bool a, bool b) override;
};



// ------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
class Rectangle {
protected:
    int x1 = 0, y1 = 0, x2= 0, y2 = 0;
    int border_width = 0;
    std::string insideText = "";

public:
    Rectangle(int x1, int y1, int x2, int y2, std::string str, int border_width);
    virtual ~Rectangle() {};
    void draw(int r, int g, int b);
    std::string getString() const;
    void setString(std::string text);

};

class Button : public Rectangle {
public:
    Button(int x1, int y1, int x2, int y2, std::string str, int border_width) : Rectangle(x1, y1, x2, y2, str, border_width) {}
    bool handle_click(int x, int y);
    

};

class FunctionContainer {
private:
    std::vector<BinaryFunction*> functions;
    std::vector<std::string> names;
    std::vector<Button*> buttons;
public:
    void addFunction(BinaryFunction* function);
    void addName(std::string str);
    bool computeAll(bool a, bool b) const;
    std::vector<BinaryFunction*> getFunctions() const;
    std::vector<std::string> getNames() const;
    std::vector<Button*>  getButtons() const;
    void deleteAtPosition(int index);
    FunctionContainer() {};
    ~FunctionContainer() {};

    void draw(int mouseX, int mouseY);
};


class Program {

private:
    std::vector<Button*> defaultButtons;
    Rectangle* userInput;
    FunctionContainer container;
    Button* userInputAFalse;
    Button* userInputATrue;
    Button* userInputBFalse;
    Button* userInputBTrue;
    bool A = false;
    bool B = false;
public:
    Program();
    ~Program();
    void handleEvent(int mouseX, int mouseY);
    void draw(int mouseX, int mouseY);
    void compute(bool a, bool b) const;
};


#endif