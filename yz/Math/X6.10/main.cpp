#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct Matrix
{
public:
    Matrix(int n, int m)
        : n_(n)
        , m_(m)
        , data_(n_, std::vector<int>(m_, 0))
    {}
    int get_n() const
    {
        return n_;
    }
    int get_m() const
    {
        return m_;
    }

    std::vector<int>& operator[](const int i)
    {
        return data_[i];
    }
    const std::vector<int>& operator[](const int i) const
    {
        return data_[i];
    }
private:
    int n_, m_;
    std::vector<std::vector<int>> data_;
};

Matrix operator+(const Matrix &a, const Matrix &b)
{
    assert(a.get_n() == b.get_n() && a.get_m() == b.get_m());

    Matrix ans(a.get_n(), a.get_m());
    for (int i = 0; i < ans.get_n(); ++i) {
        for (int j = 0; j < ans.get_m(); ++j) {
            ans[i][j] = a[i][j] + b[i][j];
        }
    }
    return ans;
}

std::istream& operator>>(std::istream& in, Matrix &matrix)
{
    for (int i = 0; i < matrix.get_n(); ++i) {
        for (int j = 0; j < matrix.get_m(); ++j) {
            in >> matrix[i][j];
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Matrix &matrix)
{
    for (int i = 0; i < matrix.get_n(); ++i) {
        out << matrix[i][0];
        for (int j = 1; j < matrix.get_m(); ++j)
            out << " " << matrix[i][j];
        if (i + 1 != matrix.get_m())
            out << std::endl;
    }
    return out;
}

int main(int argc, char **argv)
{
    for (int n, m; std::cin >> n && n; ) {
        std::cin >> m;

        Matrix a(n, m), b = a;
        std::cin >> a >> b;
        Matrix sum = a + b;
        int ans = 0;
        for (int i = 0; i < n; ++i)
            ans += std::all_of(sum[i].begin(), sum[i].end(), [](const auto &value) { return value == 0; });
        for (int j = 0; j < m; ++j) {
            int c = 1;
            for (int i = 0; i < n; ++i)
                if (sum[i][j]) {
                    c = 0;
                    break;
                }
            ans += c;
        }
        std::cout << ans << std::endl;
    }
    return 0;
}