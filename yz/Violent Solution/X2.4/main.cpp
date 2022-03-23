#include <iostream>
#include <vector>
#include <string>
#include <cmath>

char get_char_aux(const int n, const std::vector<std::string> &matrix, int x, int y, int depth)
{
    if (depth == 1)
        return matrix[x][y];
    int single = static_cast<int>(std::pow(n, depth - 1));
    if (matrix[x / single][y / single] == ' ')
        return ' ';
    return get_char_aux(n, matrix, x % single, y % single, depth - 1);
}

int main(int argc, char **argv)
{
    for (int n, q; std::cin >> n && n; ) {
        std::vector<std::string> matrix(n, std::string(n, ' '));
        std::getline(std::cin, matrix[0]);
        for (int i = 0; i < n; ++i) {
            std::getline(std::cin, matrix[i]);
            matrix[i].resize(n, ' ');
        }
        std::cin >> q;
        int edge = static_cast<int>(std::pow(n, q));

        for (int x = 0; x < edge; ++x) {
            for (int y = 0; y < edge; ++y) {
                std::cout << get_char_aux(n, matrix, x, y, q);
            }
            std::cout << std::endl;
        }
    }
    return 0;
}