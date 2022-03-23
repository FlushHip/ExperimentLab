#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char **argv)
{
    for (std::string str; std::cin >> str && str != "-1"; ) {
        std::vector<int> ans;
        for (int k = 2; k < 10; ++k) {
            int sum = 0, up = 0;
            for (auto i = 0u; i < str.size(); ++i) {
                int t = up * 10 + str[i] - '0';
                up = t % k;
            }

            if (!up)
                ans.push_back(k);
        }
        if (ans.empty())
            std::cout << "none";
        else {
            std::cout << ans.front();
            for (auto it = std::next(ans.begin()); it != ans.end(); ++it)
                std::cout << " " << *it;
        }
        std::cout << std::endl;
    }
    return 0;
}