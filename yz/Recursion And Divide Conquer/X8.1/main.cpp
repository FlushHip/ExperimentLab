#include <iostream>
#include <vector>

int main(int argc, char **argv)
{
    for (int n; std::cin >> n; ) {
        std::vector<std::vector<int>> ans;
        for (int i = 0; i < n; ++i) {
            std::vector<int> item(i + 1);
            item.front() = item.back() = 1;
            for (int j = 1; j < i; ++j)
                item[j] = ans[i - 1][j - 1] + ans[i - 1][j];
            ans.push_back(std::move(item));
        }

        for (int i = 0; i < n; ++i) {
            std::cout << ans[i][0];
            for (int j = 1; j < i + 1; ++j)
                std::cout << " " << ans[i][j];
            std::cout << std::endl;
        }
    }
    return 0;
}