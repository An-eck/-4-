#include "logic.h"


int min(int a, int b) {
    return (a < b) ? a : b;
}
void FunctionContainer::addFunction(BinaryFunction* function) {
    if (functions.size() == 20) {
        return;
    }
    functions.push_back(function);
    int x = 200 + 170*(functions.size() / 5);
    int y = 460 + 60*(functions.size() % 4 - 1);
    if (functions.size() % 4 == 0) {
        y = 460 + 60*3;
    }
    Button* newButton = new Button(x, y, x+50, y+50, "X", 1);
    buttons.push_back(newButton);
}

std::vector<BinaryFunction*> FunctionContainer::getFunctions() const {
    return functions;
}
std::vector<std::string> FunctionContainer::getNames() const {
    return names;
}

void FunctionContainer::addName(std::string str) {
    names.push_back(str);
}

std::vector<Button*> FunctionContainer::getButtons() const {
    return buttons;
}

bool FunctionContainer::computeAll(bool a, bool b) const {
    for (int i = 0; i < functions.size(); i++) {
        if (functions[i]->compute(a, b) == false) {
            return false;
        }
    }
    return true;
}
void FunctionContainer::deleteAtPosition(int index) {
    functions.erase(functions.begin() + index);
    names.erase(names.begin() + index);
    buttons.pop_back();
}

void FunctionContainer::draw(int mouseX, int mouseY) {
    int xPos = 100;
    int yPos = 460;
    int w = 100;
    int h = 50;
    int size = functions.size();
    int shift = 0;
    int index = 0;
    for (int j = 0; j <= (size / 4); j++) {
        for (int i = 0; i < min(size-shift, 4); i++) {
            drawRectangle(xPos, yPos, xPos+w, yPos+h, names[i+shift], 1, 255, 255, 255);
            buttons[index]->draw(255, 255, 255);
            index++;
            yPos += h + 10;
        }
        yPos = 460;
        shift += 4;
        xPos += w + 70;
    }

    for (Button* button : buttons) {
        if (button->handle_click(mouseX, mouseY)) {
            button->draw(2, 19, 247);
            break;
        }
    }

    return;
}


bool BinaryFunction::compute(bool a, bool b) {
    return false;
}
BinaryFunction::~BinaryFunction() {}

bool AndFunction::compute(bool a, bool b) {
            return a && b;
}
bool OrFunction::compute(bool a, bool b) {
            return a || b;
}
bool XorFunction::compute(bool a, bool b) {
            return a ^ b;
}
bool NandFunction::compute(bool a, bool b) {
            return !(a && b);
}
bool NorFunction::compute(bool a, bool b) {
            return !(a || b);
}
bool XnorFunction::compute(bool a, bool b) {
            return !(a ^ b);
}


Rectangle::Rectangle(int x1, int y1, int x2, int y2, std::string str, int border_width) : x1(x1), y1(y1), x2(x2), y2(y2), insideText(str), border_width(border_width) {}

void Rectangle::draw(int r, int g, int b) {
    drawRectangle(x1, y1, x2, y2, insideText, border_width, r, g, b);
    return;
}
void Rectangle::setString(std::string text) {
    insideText = text;
    return;
}

std::string Rectangle::getString() const {
    return insideText;
}

bool Button::handle_click(int x, int y) {
    if (x > x1 && x < x2 && y > y1 && y < y2) {
        return true;
    }
    return false;
}

Program::Program() {
    Button* buttonAnd =  new Button(175, 200, 275, 250, "AND", 2);
    Button* buttonOr =  new Button(450, 200, 550, 250, "OR", 2);
    Button* buttonXor =  new Button(725, 200, 825, 250, "XOR", 2);

    int space = 30;
    Button* buttonNand =  new Button(175, 250+space, 275, 300+space, "NAND", 2);
    Button* buttonNor =  new Button(450, 250+space, 550, 300+space, "NOR", 2);
    Button* buttonXnor =  new Button(725, 250+space, 825, 300+space, "XNOR", 2);

    Button* buttonCompute = new Button(440, 360, 560, 410, "Compute", 2);

    defaultButtons.push_back(buttonAnd);
    defaultButtons.push_back(buttonOr);
    defaultButtons.push_back(buttonXor);
    defaultButtons.push_back(buttonNand);
    defaultButtons.push_back(buttonNor);
    defaultButtons.push_back(buttonXnor);
    defaultButtons.push_back(buttonCompute);

    userInputAFalse = new Button(50, 45, 125, 95, "A false", 1);
    userInputATrue = new Button(50, 105, 125, 155, "A true", 1);

    userInputBFalse = new Button(800, 45, 875, 95, "B false", 1);
    userInputBTrue = new Button(800, 105, 875, 155, "B true", 1);

    defaultButtons.push_back(userInputAFalse);
    defaultButtons.push_back(userInputATrue);
    defaultButtons.push_back(userInputBFalse);
    defaultButtons.push_back(userInputBTrue);

    userInput = new Rectangle(300, 50, 700, 150, "", 1);

}

Program::~Program() {
    for (Button* button : defaultButtons) {
        delete button;
    }
    defaultButtons.clear();
    if (userInput != nullptr) {
        delete userInput;
    }
}

void Program::handleEvent(int mouseX, int mouseY) {
    for (Button* button : defaultButtons) {
        if (button->handle_click(mouseX, mouseY)) {
            std::string text = button->getString();
            BinaryFunction* temp = nullptr;
            if (text == "AND") {
                temp = new AndFunction;
            } else if (text == "OR") {
                temp = new OrFunction;
            } else if (text == "XOR") {
                temp = new XorFunction;
            } else if (text == "NAND") {
                temp = new NandFunction;
            } else if (text == "NOR") {
                temp = new NorFunction;
            } else if (text == "XNOR") {
                temp = new XnorFunction;
            } else if (text == "Compute") {
                compute(A, B);
                return;
            } else if (text == "A false") {
                A = false;
                return;
            } else if (text == "A true") {
                A = true;
                return;
            } else if (text == "B false") {
                B = false;
                return;
            } else if (text == "B true") {
                B = true;
                return;
            } else {
                return;
            }
        container.addFunction(temp);
        container.addName(text);
        return;
        } 
    }
    std::vector<Button*> deleteButtons = container.getButtons();
    int index = 0;
    for (Button* button : deleteButtons) {
        if (button->handle_click(mouseX, mouseY)) {
            container.deleteAtPosition(index);
        }
        index++;
    }

    return;
}

void Program::draw(int mouseX, int mouseY) {
    userInput->draw(255, 255, 255);
    for (Button* button : defaultButtons) {

        if (button->handle_click(mouseX, mouseY)) {
            button->draw(2, 19, 247);
        } else {
            button->draw(255, 255, 255);
        }
        if (A == true) {
            userInputATrue->draw(55, 247, 2);
        } else {
            userInputAFalse->draw(55, 247, 2);
        }
        if (B == true) {
            userInputBTrue->draw(55, 247, 2);
        } else {
            userInputBFalse->draw(55, 247, 2);
        }
    }
    container.draw(mouseX, mouseY);
    return;
}

void Program::compute(bool a, bool b) const {
    bool result = container.computeAll(a, b);
    std::string str = result ? "true" : "false";
    userInput->setString(str);
    return;
}