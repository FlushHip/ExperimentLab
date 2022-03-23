#include <iostream>
#include <vector>
#include <cassert>
#include <cctype>
#include <algorithm>

struct BigInteger
{
public:
    BigInteger() = default;
    BigInteger(const std::string &str)
    {
        data_.resize(str.size(), 0);
        for (auto i = 0u; i < str.size(); ++i) {
            assert(std::isdigit(str[i]));
            data_[i] = str[i] - '0';
        }
        std::reverse(data_.begin(), data_.end());
    }

private:
    friend BigInteger operator+(const BigInteger& a, const BigInteger& b);
    friend std::ostream& operator<<(std::ostream& out, const BigInteger &bigInteger);

    std::vector<int> data_;
};

BigInteger operator+(const BigInteger& A, const BigInteger& B)
{
    BigInteger ans;
    auto a = A.data_, b = B.data_;
    int n = std::max(a.size(), b.size());
    a.resize(n, 0);
    b.resize(n, 0);
    
    std::vector<int> data;
    int up = 0;
    for (int i = 0; i < n; ++i) {
        int t = a[i] + b[i] + up;
        data.push_back(t % 10);
        up = t / 10;
    }
    if (up)
        data.push_back(up);
    ans.data_ = std::move(data);
    return ans;
}

std::ostream& operator<<(std::ostream& out, const BigInteger &bigInteger)
{
    for (auto it = bigInteger.data_.crbegin(); it != bigInteger.data_.crend(); ++it)
        out << *it;
    return out;
}

int main(int argc, char **argv)
{
    for (int a, n; std::cin>> a >> n; ) {
        BigInteger ans("0");
        for (int i = 1; i <= n; ++i)
            ans = ans + std::string(i, '0' + a);
        std::cout << ans << std::endl;
    }
    return 0;
}