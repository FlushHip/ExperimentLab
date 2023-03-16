#include <iostream>
#include <iomanip>
#include <array>
#include <cstdio>

#include "prettyprint.hpp"

struct node
{
    int a;
    int b;
    int x;
};

struct Base1 {
    int val1;
};

struct Base2 {
    int val2;
};

struct Derived : Base1, Base2
{
    int valid;
};

int main(int argc, char **argv)
{
    int node::*pA = 0;
    std::array<int node::*, 3> pL{ &node::a, &node::b, &node::x };

    std::cout << "pA : " << pA << std::endl;
    std::cout << "pL : " << pL << std::endl;
    for (auto ptr : pL) {
        printf("\t%p\n", ptr);
    }

    node n{ 1, 2, 3 };
    node *pn = &n;

    std::cout << "node::a : " << pn->*pL[0] << std::endl;
    std::cout << "node::b : " << pn->*pL[1] << std::endl;
    std::cout << "node::x : " << pn->*pL[2] << std::endl;

    printf("&Base1::val1 = %p\n", &Base1::val1);
    printf("&Base2::val2 = %p\n", &Base2::val2);
    printf("&Derived::val1 = %p\n", &Derived::val1);
    printf("&Derived::val2 = %p\n", &Derived::val2);

    printf("&Derived::valid = %p\n", &Derived::valid);

    return 0;
}
