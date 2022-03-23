#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

constexpr auto kMod = 10000;

struct Matrix
{
public:
    Matrix(int n, bool fe = false)
        : n_(n)
        , data_(n_, std::vector<int>(n_, 0))
    {
        if (!fe)
            return;
        for (int i = 0; i < n_; ++i)
            data_[i][i] = 1;
    }
    int get_n() const
    {
        return n_;
    }
    int get_m() const
    {
        return n_;
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
    int n_;
    std::vector<std::vector<int>> data_;
};

Matrix operator*(const Matrix &a, const Matrix &b)
{
    assert(a.get_m() == b.get_n());
    Matrix ans(a.get_n());
    for (int i = 0; i < ans.get_n(); ++i) {
        for (int j = 0; j < ans.get_m(); ++j) {
            for (int k = 0; k < a.get_n(); ++k) {
                ans[i][j] += a[i][k] * b[k][j] % kMod;
                ans[i][j] %= kMod;
            }
        }
    }
    return ans;
}

int main(int argc, char **argv)
{
    int a[2];
    for (int p, q, k; std::cin >> a[0] >> a[1] >> p >> q >> k; ) {
        if (k < 2) {
            std::cout << a[k] % kMod << std::endl;
            continue;
        }
        Matrix x(2), ans(2, true);
        x[0][0] = p % kMod; x[0][1] = q % kMod;
        x[1][0] = 1; x[1][1] = 0;

        for (int y = k; y; ) {
            if (y % 2)
                ans = ans * x;
            x = x * x;
            y /= 2;
        }
        std::cout << (ans[1][0] * (a[1] % kMod) + ans[1][1] * (a[0] % kMod)) % kMod << std::endl;
    }
    return 0;
}