#include <iostream>

//https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Friendship_and_the_Attorney-Client#Known_Uses
class Client
{
public:
    class Attorney;
private:
    void A(int a);
    void B(float b);
    void C(double c);

    friend class Attorney;
};

void Client::A(int a)
{
    std::cout << a << std::endl;
}

void Client::B(float b)
{
    std::cout << b << std::endl;
}

void Client::C(double c)
{
    std::cout << c << std::endl;
}

class Client::Attorney {
private:
    static void callA(Client & c, int a) {
        c.A(a);
    }

    static void callB(Client & c, float b) {
        c.B(b);
    }

    friend class Bar;
};

class Bar {
public:
    Bar() {
        // Bar now has access to only Client::A and Client::B through the Attorney.
        Client::Attorney::callA(client, 1);
        Client::Attorney::callB(client, 1.1f);
    }
private:
    Client client;
};

int main(int argc, char **argv)
{
    Bar{};
    return 0;
}