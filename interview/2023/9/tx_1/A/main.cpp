#include <algorithm>
#include <limits>
#include <vector>

#include <dbg.h>

int min = std::numeric_limits<int>::max();
std::vector<int> ans_path;
void dfs(int index,
    const std::vector<std::vector<unsigned>>& matrix,
    int n,
    int sum,
    std::vector<bool>& visit,
    std::vector<int>& path) {
    if (path.size() == n) {
        if (min > sum) {
            min = sum;
            ans_path = path;
        }
        return;
    }
    for (int i = 0; i < n; ++i) {
        int to = i;
        if (to != index && !visit[to]) {
            visit[to] = true;
            path.push_back(to);

            dfs(to, matrix, n, sum + matrix[index][to], visit, path);

            visit[to] = false;
            path.pop_back();
        }
    }
}

int main() {
    std::vector<std::vector<unsigned>> matrix{
        {0, 20, 30, 10, 11},
        {20, 0, 16, 4, 2},
        {30, 16, 0, 6, 7},
        {10, 4, 6, 0, 12},
        {11, 2, 7, 12, 0},
    };

    int n = static_cast<int>(matrix.size());
    std::vector<bool> visit(n, false);
    std::vector<int> path;
    int begin = 0;
    dfs(begin, matrix, n, 0, visit, path);
    ans_path.insert(ans_path.begin(), begin);
    std::cout << min << std::endl;
    dbg(ans_path);
}
