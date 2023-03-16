#include <iostream>
#include <string>
#include <algorithm>

void recurse(const std::string &pre, const std::string &mid
                , const std::size_t l_pre, const std::size_t r_pre
                , const std::size_t l_mid, const std::size_t r_mid)
{
    if (l_pre == r_pre)
        return;
    auto root_mid = std::find(mid.begin() + l_mid, mid.begin() + r_mid, pre[l_pre]) - mid.begin();
    recurse(pre, mid, l_pre + 1, l_pre + 1 + root_mid - l_mid, l_mid, root_mid);
    recurse(pre, mid, l_pre + root_mid - l_mid + 1, r_pre, root_mid + 1, r_mid);
    std::cout << pre[l_pre];
}

int main(int argc, char **argv)
{
    for (std::string pre, mid; std::cin >> pre >> mid; ) {
        recurse(pre, mid, 0u, pre.size(), 0u, mid.size());
        std::cout << std::endl;
    }
    return 0;
}