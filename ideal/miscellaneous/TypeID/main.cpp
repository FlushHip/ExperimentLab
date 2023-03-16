#include <iostream>
#include <vector>

#include <boost/type_index.hpp>

struct Widget{};

std::vector<Widget> createVec()
{
    return { Widget{} };
}

template<typename T>
void f(const T& param)
{
    std::cout << "T=\t"
        << boost::typeindex::type_id_with_cvr<T>().pretty_name()
        << std::endl;
    std::cout << "param=\t"
        << boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name()
        << std::endl;
}

int main(int argc, char **argv)
{
    const auto vw = createVec();
    f(vw);
    if (!vw.empty()) {
        f(&vw[0]);
    }
    return 0;
}
