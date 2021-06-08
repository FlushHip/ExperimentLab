#include <iostream>
#include <memory>

#include <boost/core/addressof.hpp>

class nonaddressable
{
public:
    typedef double useless_type;
//public:
private:
    useless_type operator&() const;
};

template <class T>
T * addressof(T & v)
{
  return reinterpret_cast<T *>(& const_cast<char&>(reinterpret_cast<const volatile char &>(v)));
}

int main(int argc, char **argv)
{
    nonaddressable na;
    //nonaddressable * naptr = &na;  // Error: operator & of type nonadressable is private.

    nonaddressable * naptr1 = std::addressof(na);

    nonaddressable * naptr2 = boost::addressof(na);

    nonaddressable * naptr3 = addressof(na);

    std::cout << std::hex << naptr1 << std::endl
        << naptr2 << std::endl
        << naptr3 << std::endl;
    return 0;
}