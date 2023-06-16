#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    std::ifstream fin("./in.dat", std::ios::in);
    if (!fin.is_open()) {
        std::cerr << "file isn't open" << std::endl;
        return -1;
    }

    struct info {
        int num = 0;
        std::string label;
        std::string rebar_d;
        std::string name;
        int len = 0;
    };
    std::vector<info> lines;
    while (true) {
        int num = 0;
        std::string label;
        std::string rebar_d;
        std::string name;
        int len = 0;
        int cnt = 0;
        if (!(fin >> num >> label >> rebar_d >> name >> len >> cnt)) {
            break;
        }
        while (cnt--) {
            lines.emplace_back(num, std::move(label), std::move(rebar_d),
                std::move(name), len);
        }
        // std::cout << num << "\t" << label << "\t" << rebar_d << "\t" << name
        //          << "\t" << len << "\t" << cnt << std::endl;
    }

    return 0;
}
