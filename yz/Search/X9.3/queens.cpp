#include <vector>
#include <array>
#include <string>
#include <algorithm>

static std::vector<std::string> ans;
static std::array<std::array<bool, 8>, 8> matrix;

bool rc_valid(int row, int col)
{
    for (int i = 0; i < row; ++i)
        if (matrix[i][col])
            return false;
    for (int r = row - 1, c = col - 1; r >= 0 && c >= 0; --r, --c)
        if (matrix[r][c])
            return false;
    for (int r = row - 1, c = col + 1; r >= 0 && c < 8; --r, ++c)
        if (matrix[r][c])
            return false;
    return true;
}

void get_queens_aux(int row)
{
    if (row == 8) {
        std::string str;
        for (int i = 0; i < 8; ++i)
            str.push_back('0' + 1 + (std::find(matrix[i].begin(), matrix[i].end(), true) - matrix[i].begin()));
        ans.push_back(std::move(str));
        return ;
    }
    for (int col = 0; col < 8; ++col) {
        if (rc_valid(row, col)) {
            matrix[row][col] = true;
            get_queens_aux(row + 1);
            matrix[row][col] = false;
        }
    }
}

std::vector<std::string> get_queens()
{
    get_queens_aux(0);
    return ans;
}