#include <iostream>
#include <set>
#include <stack>
#include <vector>

void dfs(const std::string& line,
    int idx,
    const int n,
    std::stack<char> st,
    std::string output,
    std::set<std::string>& ans) {
    if (idx == n) {
        std::string str = output;
        while (!st.empty()) {
            str.push_back(st.top());
            st.pop();
        }
        ans.emplace(std::move(str));
        return;
    }
    st.push(line[idx]);
    dfs(line, idx + 1, n, st, output, ans);
    while (!st.empty()) {
        output.push_back(st.top());
        st.pop();
        dfs(line, idx + 1, n, st, output, ans);
    }
}

int main() {
    for (std::string line; std::cin >> line;) {
        std::set<std::string> ans;
        std::stack<char> st;
        std::string output;

        int n = static_cast<int>(line.size());
        dfs(line, 0, n, st, output, ans);

        for (const auto& str : ans) {
            std::cout << str << std::endl;
        }
    }
    return 0;
}
