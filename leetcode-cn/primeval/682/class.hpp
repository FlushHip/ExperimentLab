class Solution {
public:
    int calPoints(vector<string>& ops) {
        std::vector<int> cores;
        for (const auto &op : ops) {
            if (op == "C") {
                cores.pop_back();
                continue;
            }
            if (op == "D") {
                cores.push_back(cores.back() * 2);
                continue;
            }
            if (op == "+") {
                cores.push_back(cores.back() + *std::next(cores.rbegin()));
                continue;
            }
            cores.push_back(std::stoi(op));
        }
        return std::accumulate(cores.begin(), cores.end(), 0);
    }
};
