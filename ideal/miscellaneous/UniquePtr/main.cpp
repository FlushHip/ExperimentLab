#include <iostream>
#include <memory>

int main(int argc, char **argv)
{
    auto pA = std::make_unique<int>();
    auto pB = std::make_unique<int[]>(5);

    int iA = 0, iB = 0;
    auto del = [iA, iB](int *) -> void {};
    std::unique_ptr<int, decltype(del)> pC(nullptr, del);

    std::cout << "pA size : " << sizeof(pA) << std::endl;
    std::cout << "pB size : " << sizeof(pB) << std::endl;
    std::cout << "pC size : " << sizeof(pC) << std::endl;
    std::cout << "del size : " << sizeof(del) << std::endl;

    std::shared_ptr<int> pD = std::move(pC);

    return 0;
}
