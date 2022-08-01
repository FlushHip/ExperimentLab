#include <iostream>
#include <iomanip>

template<typename F, typename T, typename... Args>
void fold_left(F&& f, T&& t, Args&&... args) {
    // <init> op <...> op <args>
    ((f(std::string(sizeof...(Args), '(')), f(t)), ..., ((f(" + "), f(args), f(')')))), f('\n');
}

template<typename F, typename T, typename... Args>
void fold_right(F&& f, T&& t, Args&&... args) {
    // <args> op <...> op <init>
    ((f('('), f(args), f(" + ")), ..., (f(t), f(std::string(sizeof...(Args), ')')))), f('\n');
}

auto f = [] (auto && x) {
    std::cout << x;
};

int main(int argc, char* argv[]) {
    // ((((1 + 2) + 3) + 4) + 5)
    fold_left(f, 1, 2, 3, 4, 5);
    // (2 + (3 + (4 + (5 + 1))))
    fold_right(f, 1, 2, 3, 4, 5);
    return 0;
}
