#include <iostream>
#include <queue>
#include <vector>
#include <string>

int main(int argc, char **argv)
{
    using Pair = std::pair<long long, long long>;
    auto mod = [](const Pair &p)
    {
        return p.first * p.first + p.second * p.second;
    };
    auto cmp = [mod](const Pair &lhs, const Pair &rhs)
    {
        return mod(lhs) == mod(rhs) ? (lhs.second > rhs.second) : (mod(lhs) < mod(rhs));
    };
    using PriorityQueue = std::priority_queue<Pair, std::vector<Pair>, decltype(cmp)>;

    for (int n; std::cin >> n; ) {
        PriorityQueue que(cmp);
        for (std::string cmd, num; n--; ) {
            std::cin >> cmd;
            if (cmd[0] != 'P') {
                std::cin >> num;
                long long a = std::stoll(num.substr(0, num.find('+')));
                long long b = std::stoll(num.substr(num.find('i') + 1, num.size() - num.find('i') - 1));
                que.emplace(a, b);
                std::cout << "SIZE = " << que.size() << std::endl;
            } else {
                if (que.empty()) {
                    std::cout << "empty" << std::endl;
                    continue;
                }
                std::cout << que.top().first << "+i" << que.top().second << std::endl
                    << "SIZE = " << que.size() - 1 << std::endl;
                que.pop();
            }
        }
    }
    return 0;
}