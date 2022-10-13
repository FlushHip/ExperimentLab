#include <sstream>
#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<MyCircularQueue>(3);

    std::ostringstream oss;
    oss.setf(std::ios::boolalpha);

    oss << sol->enQueue(1) << std::endl;
    oss << sol->enQueue(2) << std::endl;
    oss << sol->enQueue(3) << std::endl;
    oss << sol->enQueue(4) << std::endl;
    oss << sol->Rear() << std::endl;
    oss << sol->isFull() << std::endl;
    oss << sol->deQueue() << std::endl;
    oss << sol->enQueue(4) << std::endl;
    oss << sol->Rear() << std::endl;

    std::cout << oss.str() << std::endl;

    return 0;
}
