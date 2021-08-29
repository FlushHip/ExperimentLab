#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    std::vector<int> vA{ 1 };
    std::vector<int> vB{ 1, 3 };
    std::vector<int> vC{ 1, 10, 5, 1};

    auto solA = std::make_unique<Solution>(vA);
    auto solB = std::make_unique<Solution>(vB);
    auto solC = std::make_unique<Solution>(vC);

    auto fn = [](std::unique_ptr<Solution> ptr) {
        std::vector<int> ans;
        std::generate_n(std::back_inserter(ans), 30, [ptr = std::move(ptr)]
        {
            return ptr->pickIndex();
        });
        return ans;
    };

    std::cout << fn(std::move(solA)) << std::endl;
    std::cout << fn(std::move(solB)) << std::endl;
    std::cout << fn(std::move(solC)) << std::endl;

    return 0;
}
