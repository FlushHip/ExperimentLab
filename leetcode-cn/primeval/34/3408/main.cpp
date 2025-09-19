#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto tasks = std::vector<std::vector<int>>{
        {20, 55, 91},
        {30, 94, 511},
        {35, 90, 877},
        {40, 57, 281},
        {33, 11, 408},
        {13, 91, 217},
        {31, 95, 239},
        {8, 51, 132},
        {42, 77, 30},
        {20, 36, 894},
        {12, 15, 43},
        {1, 48, 591},
        {22, 85, 420},
        {21, 83, 767},
        {6, 25, 894},
        {38, 38, 722},
        {42, 65, 579},
        {47, 54, 436},
        {37, 45, 483},
        {27, 74, 712},
        {23, 63, 610},
        {48, 24, 843},
        {26, 81, 742},
        {41, 78, 625},
        {27, 75, 506},
        {13, 70, 121},
        {24, 6, 103},
    };
    auto sol = std::make_unique<TaskManager>(tasks);

    sol->add(12, 71, 260);
    sol->add(26, 30, 626);
    sol->add(1, 68, 206);
    sol->edit(55, 566);
    sol->edit(6, 312);
    sol->edit(36, 919);
    sol->edit(95, 720);
    sol->rmv(55);
    sol->add(9, 29, 635);
    sol->edit(54, 450);
    std::cout << sol->execTop() << '\n';
    sol->rmv(90);
    sol->add(28, 82, 378);
    sol->add(21, 66, 569);
    sol->edit(30, 476);
    sol->edit(48, 500);
    sol->rmv(85);
    sol->edit(6, 246);
    sol->rmv(71);
    std::cout << sol->execTop() << '\n';
    sol->add(40, 37, 335);
    std::cout << sol->execTop() << '\n';
    sol->rmv(95);
    std::cout << sol->execTop() << '\n';
    sol->add(21, 67, 174);
    std::cout << sol->execTop() << '\n';
    std::cout << sol->execTop() << '\n';
    sol->rmv(74);
    sol->rmv(63);
    std::cout << sol->execTop() << '\n';
    std::cout << sol->execTop() << '\n';
    std::cout << sol->execTop() << '\n';
    std::cout << sol->execTop() << '\n';
    // sol->rmv(101);
    // sol->add(50, 101, 8);
    // std::cout << sol->execTop() << '\n';

    return 0;
}
