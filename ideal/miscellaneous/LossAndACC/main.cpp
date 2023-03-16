#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char* argv[]) {
    std::ifstream ifs(
        R"(D:\FlushHip\experimentlab\ideal\miscellaneous\LossAndACC\origin.txt)");
    if (!ifs.is_open()) {
        std::cerr << "can't open file." << std::endl;
        return 1;
    }

    std::ofstream ofs[3]{
        std::ofstream(
            R"(D:\FlushHip\experimentlab\ideal\miscellaneous\LossAndACC\loss.dat)"),
        std::ofstream(
            R"(D:\FlushHip\experimentlab\ideal\miscellaneous\LossAndACC\ar.dat)"),
        std::ofstream(
            R"(D:\FlushHip\experimentlab\ideal\miscellaneous\LossAndACC\er.dat)"),
    };
    for (int i = 0; i < 3; ++i) {
        ofs[i] << "x\tf(x)\n\n";
    }
    int epoch = 1;
    double pre_y = 4.0;
    for (std::string line; std::getline(ifs, line); ++epoch) {
        std::getline(ifs, line);
        double loss = 0.0, acc = 0.0;
        std::string ignore;
        std::istringstream iss(line);
        iss >> ignore >> ignore >> ignore >> ignore >> loss >> ignore >> acc;
        for (int i = 0; i < 10; ++i) {
            double y = pre_y + i * 1.0 / 10 * (loss - pre_y) +
                (loss - pre_y) * ((rand() % 5) - 2);
            if (y > 0.0) {
                ofs[0] << (epoch - 1 + i * 1.0 / 10) << "\t" << y << std::endl;
            }
        }
        ofs[1] << epoch << "\t" << acc << std::endl;
        ofs[2] << epoch << "\t" << 1 - acc << std::endl;

        pre_y = loss;
    }
    return 0;
}
