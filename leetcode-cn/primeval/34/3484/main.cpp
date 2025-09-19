#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Spreadsheet>(3);

    std::cout << sol->getValue("=5+7") << "\n";
    sol->setCell("A1", 10);
    std::cout << sol->getValue("=A1+6") << "\n";
    sol->setCell("B2", 15);
    std::cout << sol->getValue("=A1+B2") << "\n";
    sol->resetCell("A1");
    std::cout << sol->getValue("=A1+B2") << "\n";
    return 0;
}
