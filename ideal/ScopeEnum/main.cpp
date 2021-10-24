#include <iostream>
#include <tuple>
#include <string>

struct UserInfoA {
    using type = std::tuple<int, int, std::string>;
    enum fields {
        one,
        two,
        three,
    };
};

struct UserInfoB {
    using type = std::tuple<int, int, std::string>;
    enum class fields {
        one,
        two,
        three,
    };

    template<typename E>
    static constexpr auto to(E enumerator) noexcept
    {
        return static_cast<std::underlying_type_t<E>>(enumerator);
    }
};

int main(int argc, char **argv)
{
    UserInfoA::type tuA{ 1, 2, "flushhip" };
    std::cout << std::get<UserInfoA::fields::one>(tuA) << std::endl;
    std::cout << std::get<UserInfoA::three>(tuA) << std::endl;

    UserInfoB::type tuB{ 2, 1, "lisi" };
    std::cout << std::get<UserInfoB::to(UserInfoB::fields::one)>(tuB) << std::endl;
    std::cout << std::get<UserInfoB::to(UserInfoB::fields::three)>(tuB) << std::endl;

    return 0;
}
