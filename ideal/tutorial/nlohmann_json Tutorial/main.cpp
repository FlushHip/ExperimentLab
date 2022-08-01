#include <iostream>

#include <nlohmann/json.hpp>

struct person {
    std::string name;
    int age;
    char sale;
    std::tuple<int, std::string> t;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(person, name, age, sale, t)

int main() {
    person p{"flushhip", 18, 'F', {1, "lisi"}};
    using my_tuple =
        std::tuple<int, std::string, std::string, std::tuple<int, int, int>>;
    my_tuple tp{1, "F", "B", {1, 2, 3}};
    nlohmann::json j = tp;
    std::cout << j << std::endl;

    nlohmann::json j2 = p;
    std::cout << j2 << std::endl;

    std::string str_j = j.dump();
    std::cout << str_j << std::endl;
    auto tpp = j.get<my_tuple>();
    assert(tpp == tp);

    return 0;
}
