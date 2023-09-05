#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>

int main() {
    for (std::string ip; std::cin >> ip;) {
        int n = static_cast<int>(ip.size());
        std::array<int, 4> ips{0, 0, 0, 0};
        bool valid = true;
        do {
            int begin = 0;
            auto pos = ip.find('.', begin);
            if (pos != std::string::npos &&
                std::all_of(ip.begin() + begin, ip.begin() + pos, ::isdigit) &&
                (pos - begin == 1 || (pos - begin > 1 && ip[begin] != '0'))) {
                ips[0] = std::stoi(
                    std::string{ip.begin() + begin, ip.begin() + pos});
            } else {
                valid = false;
                break;
            }
            begin = pos + 1;
            pos = ip.find('.', begin);
            if (pos != std::string::npos &&
                std::all_of(ip.begin() + begin, ip.begin() + pos, ::isdigit) &&
                (pos - begin == 1 || (pos - begin > 1 && ip[begin] != '0'))) {
                ips[1] = std::stoi(
                    std::string{ip.begin() + begin, ip.begin() + pos});
            } else {
                valid = false;
                break;
            }
            begin = pos + 1;
            pos = ip.find('.', begin);
            if (pos != std::string::npos &&
                std::all_of(ip.begin() + begin, ip.begin() + pos, ::isdigit) &&
                (pos - begin == 1 || (pos - begin > 1 && ip[begin] != '0'))) {
                ips[2] = std::stoi(
                    std::string{ip.begin() + begin, ip.begin() + pos});
            } else {
                valid = false;
                break;
            }
            begin = pos + 1;
            pos = n;
            if (std::all_of(ip.begin() + begin, ip.begin() + pos, ::isdigit) &&
                (pos - begin == 1 || (pos - begin > 1 && ip[begin] != '0'))) {
                ips[3] = std::stoi(
                    std::string{ip.begin() + begin, ip.begin() + pos});
            } else {
                valid = false;
                break;
            }

            if (!std::all_of(ips.begin(), ips.end(),
                    [](int a) { return a == std::clamp(a, 0, 255); })) {
                valid = false;
                break;
            }
        } while (false);
        if (!valid) {
            std::cout << "invalid" << std::endl;
            continue;
        }

        if (ips[0] == std::clamp(ips[0], 1, 125) ||
            (ips[0] == 126 &&
                std::accumulate(ips.begin(), ips.end(), 0) == 126)) {
            std::cout << "A_address" << std::endl;
        } else if (ips[0] == std::clamp(ips[0], 128, 191)) {
            std::cout << "B_address" << std::endl;
        } else if (ips[0] == std::clamp(ips[0], 192, 223)) {
            std::cout << "C_address" << std::endl;
        } else {
            std::cout << "other" << std::endl;
        }
    }
    return 0;
}
