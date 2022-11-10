#include <iostream>

class Base {
public:
    int b;
    virtual void fun_base() {}
};

class Drived1 : public Base {
public:
    int d;
    virtual void fun_d1(){};
};

class Drived2 : public Base {
public:
    int d;
    virtual void fun_d2(){};
};

int main() {
    Base base1;
    Drived1 drived1;
    Drived2 drived2;
    Drived1* p1 = &drived1;
    Drived2* p2 = &drived2;
    p1->fun_d1();
    p2->fun_d2();

    std::cout << "finished." << std::endl;
    return 0;
}
