#include <iostream>
#include <string>
#include <cctype>

int main(int argc, char **argv)
{
    for (std::string str; std::cin >> str; ) {
        int ans[26] = { 0 };
        for (auto i = 0u; i < str.size(); ++i)
            if (std::isupper(str[i]))
                ++ans[str[i] - 'A'];
        for (int i = 0; i < 26; ++i)
            std::cout << static_cast<char>(i + 'A') << ":" << ans[i] << std::endl;
    }
    return 0;
}