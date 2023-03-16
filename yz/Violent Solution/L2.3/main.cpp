#include <iostream>
#include <string>
#include <algorithm>


int main(int argc, char **argv)
{
    for (int n = 0; n <= 256; ++n) {
        int nn = n * n;
        std::string str_origin = std::to_string(nn);
        std::string str_next = str_origin;
        std::reverse(str_next.begin(), str_next.end());
        if (str_origin == str_next)
            std::cout << n << std::endl;
    }
    return 0;
}