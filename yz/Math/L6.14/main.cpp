#include <iostream>
#include <vector>
#include <cassert>
#include <cctype>
#include <string>
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
    BigInteger(const int n) : BigInteger(std::to_string(n)) {}

private:
    friend BigInteger operator*(const BigInteger& a, const BigInteger& b);
    friend std::ostream& operator<<(std::ostream& out, const BigInteger &bigInteger);

    std::vector<int> data_;
};

BigInteger operator*(const BigInteger& a, const BigInteger& b)
{
    BigInteger ans;
    std::vector<int> data(a.data_.size() + b.data_.size(), 0);
    for (auto i = 0u; i < a.data_.size(); ++i) {
        for (auto j = 0u; j < b.data_.size(); ++j) {
            data[i + j] += a.data_[i] * b.data_[j];
        }
    }
    int up = 0;
    for (auto i = 0u; i < data.size(); ++i) {
        int t = data[i] + up;
        data[i] = t % 10;
        up = t / 10;
    }
    while (up)
    {
        data.push_back(up % 10);
        up /= 10;
    }
    while (!data.empty() && data.back() == 0)
        data.pop_back();
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
    std::freopen("in.dat", "r", stdin);

    for (int n; std::cin >> n; ) {
        BigInteger ans(1);
        for (int i = 2; i <= n; ++i)
            ans = ans * i;
        std::cout << ans << std::endl;
    }
    return 0;
}