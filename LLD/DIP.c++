#include <bits/stdc++.h>
using namespace std;

class Keyboard
{
public:
    virtual ~Keyboard() = default;
    virtual void getSpecifications() const = 0;
};

class Mouse
{
public:
    virtual ~Mouse() = default;
    virtual void getSpecifications() const = 0;
};

class WiredKeyboard : public Keyboard
{
    string connectionType, company, modelVersion, color;

public:
    WiredKeyboard(string connectionType, string company, string modelVersion, string color)
        : connectionType(std::move(connectionType)),
          company(std::move(company)),
          modelVersion(std::move(modelVersion)),
          color(std::move(color)) {}

    void getSpecifications() const override
    {
        cout << "===> Wired Keyboard\n"
             << "Connection type: " << connectionType << '\n'
             << "Company: " << company << '\n'
             << "Model Version: " << modelVersion << '\n'
             << "Color: " << color << '\n';
    }
};

class BluetoothKeyboard : public Keyboard
{
    string connectionType, company, modelVersion, color;

public:
    BluetoothKeyboard(string connectionType, string company, string modelVersion, string color)
        : connectionType(std::move(connectionType)),
          company(std::move(company)),
          modelVersion(std::move(modelVersion)),
          color(std::move(color)) {}

    void getSpecifications() const override
    {
        cout << "===> Bluetooth Keyboard\n"
             << "Connection type: " << connectionType << '\n'
             << "Company: " << company << '\n'
             << "Model Version: " << modelVersion << '\n'
             << "Color: " << color << '\n';
    }
};

class WiredMouse : public Mouse
{
    string connectionType, company, modelVersion, color;

public:
    WiredMouse(string connectionType, string company, string modelVersion, string color)
        : connectionType(std::move(connectionType)),
          company(std::move(company)),
          modelVersion(std::move(modelVersion)),
          color(std::move(color)) {}

    void getSpecifications() const override
    {
        cout << "===> Wired Mouse\n"
             << "Connection type: " << connectionType << '\n'
             << "Company: " << company << '\n'
             << "Model Version: " << modelVersion << '\n'
             << "Color: " << color << '\n';
    }
};

class BluetoothMouse : public Mouse
{
    string connectionType, company, modelVersion, color;

public:
    BluetoothMouse(string connectionType, string company, string modelVersion, string color)
        : connectionType(std::move(connectionType)),
          company(std::move(company)),
          modelVersion(std::move(modelVersion)),
          color(std::move(color)) {}

    void getSpecifications() const override
    {
        cout << "===> Bluetooth Mouse\n"
             << "Connection type: " << connectionType << '\n'
             << "Company: " << company << '\n'
             << "Model Version: " << modelVersion << '\n'
             << "Color: " << color << '\n';
    }
};

class MacBook
{
    unique_ptr<Keyboard> keyboard;
    unique_ptr<Mouse> mouse;

public:
    MacBook(unique_ptr<Mouse> m, unique_ptr<Keyboard> k)
        : keyboard(std::move(k)), mouse(std::move(m)) {}

    const Keyboard &getKeyboard() const { return *keyboard; }
    const Mouse &getMouse() const { return *mouse; }
};

int main()
{
    auto wiredKeyboard = make_unique<WiredKeyboard>("USB", "Dell", "F602", "Grey");
    auto wiredMouse = make_unique<WiredMouse>("USB", "Dell", "M90", "Grey");
    auto btKeyboard = make_unique<BluetoothKeyboard>("Bluetooth", "Logitech", "G102", "Black");
    auto btMouse = make_unique<BluetoothMouse>("Bluetooth", "Logitech", "M185", "Black");

    MacBook wiredMacBook(std::move(wiredMouse), std::move(wiredKeyboard));
    wiredMacBook.getKeyboard().getSpecifications();
    wiredMacBook.getMouse().getSpecifications();

    MacBook btMacBook(std::move(btMouse), std::move(btKeyboard));
    btMacBook.getKeyboard().getSpecifications();
    btMacBook.getMouse().getSpecifications();

    return 0;
}