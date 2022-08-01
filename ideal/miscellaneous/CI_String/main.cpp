// case-insensitive string

#include <iostream>

struct ci_char_traits : public std::char_traits<char>  {
    static bool eq(char c1, char c2) {
        return std::toupper(c1) == std::toupper(c2);
    }
    static bool lt(char c1, char c2) {
        return std::toupper(c1) < std::toupper(c2);
    }
    static int compare(const char* s1, const char* s2, std::size_t n) {
        while (n--) {
            if (lt(*s1, *s2)) {
                return -1;
            }
            if (!eq(*s1, *s2)) {
                return 1;
            }
            ++s1, ++s2;
        }
        return 0;
    }
    static const char* find(const char* s, std::size_t n, char a) {
        const auto ua(std::toupper(a));
        while (n--) {
            if (eq(*s, ua)) {
                return s;
            }
            ++s;
        }
        return nullptr;
    }
};

template<typename DstTraits, typename CharT, typename SrcTraits>
constexpr std::basic_string_view<CharT, ci_char_traits>
    to_ci_string_view(const std::basic_string_view<CharT, SrcTraits>& sv) {
    return {sv.data(), sv.size()};
}

int main(int argc, char* argv[]) {
    using namespace std::literals::string_view_literals;

    constexpr auto sv1 = "Hello, World!"sv;
    constexpr auto sv2 = "hELLO, wORLD!"sv;

    if (to_ci_string_view<ci_char_traits>(sv1) == to_ci_string_view<ci_char_traits>(sv2)) {
        std::cout << "sv1 and sv2 are equal" << std::endl;
    } else {
        std::cout << "sv1 and sv2 are not equal" << std::endl;
    }

    return 0;
}
