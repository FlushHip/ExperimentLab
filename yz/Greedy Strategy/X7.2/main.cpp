#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

int main(int argc, char **argv)
{
    for (int cmax, d, davg, n; std::cin >> cmax >> d >> davg >> n; ) {
        std::vector<std::pair<int, double>> stations(n);
        for (int i = 0; i < n; ++i)
            std::cin >> stations[i].second >> stations[i].first;
        stations.emplace_back(d, 0);
        std::sort(stations.begin(), stations.end());
        if (stations.front().first) {
            std::cout << "The maximum travel distance = 0.00" << std::endl;
            continue;
        }
        
        double costs = 0, cnow = 0;
        bool f = true;
        for (int i = 0; i < n; ++i) {
            if (stations[i + 1].first - stations[i].first > davg * cmax) {
                std::cout << "The maximum travel distance = " << std::fixed << std::setprecision(2) << stations[i].first + davg * cmax + 0.0 << std::endl;
                f = false;
                break;
            }
            auto pos = std::find_if(stations.begin() + i + 1, stations.end(), [&](const auto &p)
            {
                return p.first - stations[i].first <= davg * cmax
                    && p.second <= stations[i].second;
            });
            if (pos == stations.end()) {
                costs += (cmax - cnow) * stations[i].second;
                cnow += cmax - cnow;
                cnow -= (stations[i + 1].first - stations[i].first) * 1.0 / davg;
            } else {
                double need = (pos->first - stations[i].first) * 1.0 / davg;
                if (need > cnow) {
                    costs += (need - cnow) * stations[i].second;
                    cnow = 0;
                } else {
                    cnow = cnow - need;
                }
                i = pos - stations.begin() - 1;
            }
        }
        if (f)
            std::cout << std::fixed << std::setprecision(2) << costs << std::endl;
    }
    return 0;
}