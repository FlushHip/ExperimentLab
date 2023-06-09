#include "headers.h"

int rand7() {
    std::random_device rd;
    std::mt19937 gen(rd());
    int ans = std::uniform_int_distribution<>(1, 7)(gen);
    return ans;
}

#include "class.hpp"

int main(int argc, char** argv) {
    const int EN = 2;

    auto sol = std::make_unique<Solution>();

    int n[EN]{
        1000,
        100000 / 3,
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        std::vector<int> ans(11, 0);
        for (int i = 0; i < n[L]; ++i) {
            ++ans[sol->rand10()];
        }
        for (int i = 1; i < 11; ++i) {
            std::cout << i << " : " << ans[i] << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}
