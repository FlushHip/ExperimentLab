#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "config.h"
#include "maths.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << argv[0] << " Version " << VERSION_MAJOR << "."
            << VERSION_MINOR << "." << VERSION_PATCH << std::endl;
        std::cerr << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }

    const double input_value = std::stod(argv[1]);
    const double output_value = math::sqrt(input_value);
    std::cout << output_value << std::endl;

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);

    return 0;
}