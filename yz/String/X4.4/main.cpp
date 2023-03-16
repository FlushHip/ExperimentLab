#include <iostream>
#include <string>
#include <algorithm>

int main(int argc, char **argv)
{
    for (std::string a, b; std::cin >> a >> b; ) {
        auto pa = a.find('.'), pb = b.find('.');
        if (pa < pb)
            a.insert(0, pb - pa, '0');
        else
            b.insert(0, pa - pb, '0');
        if (a.size() < b.size())
            a.append(b.size() - a.size(), '0');
        else
            b.append(a.size() - b.size(), '0');
        std::reverse(a.begin(), a.end());
        std::reverse(b.begin(), b.end());

        std::string ans;
        int up = 0;
        for (auto i = 0u; i < a.size(); ++i) {
            if (a[i] == '.') {
                ans.push_back('.');
                continue;
            }
            int num = a[i] + b[i] - '0' - '0' + up;
            ans.push_back((num % 10) + '0');
            up = num / 10;
        }
        if (up)
            ans.push_back(up + '0');
        std::reverse(ans.begin(), ans.end());
        
        std::cout << ans << std::endl;
    }
    return 0;
}