#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<MyCircularDeque>(3);

    std::ostringstream oss;
    oss.setf(std::ios::boolalpha);

    oss << sol->insertLast(1) << std::endl;
    oss << sol->insertLast(2) << std::endl;
    oss << sol->insertFront(3) << std::endl;
    oss << sol->insertFront(4) << std::endl;
    oss << sol->getRear() << std::endl;
    oss << sol->isFull() << std::endl;
    oss << sol->deleteLast() << std::endl;
    oss << sol->insertFront(4) << std::endl;
    oss << sol->getFront() << std::endl;

    std::cout << oss.str() << std::endl;

    return 0;
}
