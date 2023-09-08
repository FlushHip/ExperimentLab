#include <iostream>
#include <vector>

#include <dbg.h>

int main() {
    for (int T{}; std::cin >> T;) {
        for (int L = 0; L < T; ++L) {
            std::string str;
            std::cin >> str;
            std::string line;
            for (char c : str) {
                switch (c) {
                case 'b':
                case 'd':
                case 'q':
                case 'p':
                    line.push_back('b');
                    break;
                case 'n':
                case 'u':
                    line.push_back('u');
                    break;
                case 'w':
                    line.append("vv");
                    break;
                case 'm':
                    line.append("uu");
                    break;
                default:
                    line.push_back(c);
                    break;
                }
            }

            dbg(line);

            bool ans = true;
            int n = static_cast<int>(line.size());
            for (int lhs = 0, rhs = n - 1; lhs < rhs; ++lhs, --rhs) {
                if (line[lhs] != line[rhs]) {
                    ans = false;
                    break;
                }
            }
            std::cout << (ans ? "YES" : "NO") << std::endl;
        }
    }
    return 0;
}
