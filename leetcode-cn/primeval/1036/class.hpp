template<class F, class S>
std::pair<F, S> operator+(const std::pair<F, S> &lhs, std::pair<F, S> &rhs) {
    return std::make_pair<F, S>(lhs.first + rhs.first, lhs.second + rhs.second);
}

class Solution {
public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        if (blocked.size() < 2) {
            return true;
        }
        auto [n, m] = init(blocked, source, target);

        std::queue<std::pair<int, int>> que;
        mp[src.first][src.second] = 1;
        for (que.push(src); !que.empty(); ) {
            auto point = que.front();
            que.pop();

            static std::pair<int, int> dir[] = {
                { 0, 1 },
                { 0, -1 },
                { 1, 0 },
                { -1, 0 },
            };
            for (int i = 0; i < 4; ++i) {
                std::pair<int, int> to = point + dir[i];
                if (to.first < 0 || to.first > n || to.second < 0 || to.second > m || mp[to.first][to.second] == 1) {
                    continue;
                }
                if (to == des) {
                    return true;
                }
                mp[to.first][to.second] = 1;
                que.push(std::move(to));
            }
        }
        return false;
    }

    std::pair<int, int> init(const vector<vector<int>>& blocked, const vector<int>& source, const vector<int>& target) {
        static const int EdgeMax = (int)1e6;
        std::vector<int> mapX, mapY;
        std::unordered_map<int, int> columns, rows;

        for (const auto block : blocked) {
            mapX.push_back(block[0]);
            mapY.push_back(block[1]);
        }
        mapX.push_back(0);
        mapY.push_back(0);
        mapX.push_back(EdgeMax - 1);
        mapY.push_back(EdgeMax - 1);
        mapX.push_back(source[0]);
        mapY.push_back(source[1]);
        mapX.push_back(target[0]);
        mapY.push_back(target[1]);
        std::sort(mapX.begin(), mapX.end());
        std::sort(mapY.begin(), mapY.end());
        mapX.erase(std::unique(mapX.begin(), mapX.end()), mapX.end());
        mapY.erase(std::unique(mapY.begin(), mapY.end()), mapY.end());

        int n = (int)mapX.size(), m = (int)mapY.size();
        int index = 0;
        columns[mapX[0]] = index;
        for (int i = 1; i < n; ++i) {
            index += mapX[i] == mapX[i - 1] + 1 ? 1 : 2;
            columns[mapX[i]] = index;
        }
        n = index;
        index = 0;
        rows[mapY[0]] = index;
        for (int i = 1; i < m; ++i) {
            index += mapY[i] == mapY[i - 1] + 1 ? 1 : 2;
            rows[mapY[i]] = index;
        }
        m = index;

        mp.clear();
        mp.resize(n + 1, std::vector<int>(m + 1, 0));
        for (const auto block : blocked) {
            mp[columns[block[0]]][rows[block[1]]] = 1;
        }
        src = { columns[source[0]], rows[source[1]] };
        des = { columns[target[0]], rows[target[1]] };

        return { n, m };
    }

private:
    std::vector<std::vector<int>> mp;
    std::pair<int, int> src, des;
};
