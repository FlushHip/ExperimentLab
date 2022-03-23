#include <iostream>
#include <vector>
#include <cassert>

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
    assert(a.get_n() == b.get_n());

    Matrix ans(a.get_n());
    for (int i = 0; i < ans.get_n(); ++i) {
        for (int j = 0; j < ans.get_n(); ++j) {
            for (int k = 0; k < ans.get_n(); ++k)
                ans[i][j] += a[i][k] * b[k][j];
        }
    }
    return ans;
}

std::ostream& operator<<(std::ostream& out, const Matrix &matrix)
{
    for (int i = 0; i < matrix.get_n(); ++i) {
        out << matrix[i][0];
        for (int j = 1; j < matrix.get_n(); ++j)
            out << " " << matrix[i][j];
        if (i + 1 != matrix.get_n())
            out << std::endl;
    }
    return out;
}

int main(int argc, char **argv)
{
    std::freopen("in.dat", "r", stdin);

    for (int n, k; std::cin >> n >> k; ) {
        Matrix x(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> x[i][j];
            }
        }

        Matrix ans(n, true);
        while (k) {
            if (k % 2)
                ans = ans * x;
            x = x * x;
            k /= 2;
        }
        
        std::cout << ans << std::endl;
    }
    return 0;
}