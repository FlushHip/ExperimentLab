#include <iostream>
#include <algorithm>

int main(int argc, char **argv)
{
    {
        std::string strA = "FlushHip";
        std::string strB(strA);
        std::reverse(strB.begin(), strB.end());

        std::cout << strA << " <-> " << strB << std::endl;
    }
    {
        std::string strA = "FlushHip";
        std::string strB(strA.rbegin(), strA.rend());

        std::cout << strA << " <-> " << strB << std::endl;
    }
    {
        char strA[] = "FlushHip";
        std::string strB(std::rbegin(strA), std::rend(strA));

        std::cout << strA << " <-> " << strB << std::endl;
    }
    {
        enum { MAX_LEN = 9 };
        std::unique_ptr<char[]> strA(new char[MAX_LEN]{ "FlushHip" });
        std::string strB(strA.get());
        std::reverse(strB.begin(), strB.end());

        std::cout << strA << " <-> " << strB << std::endl;
    }
    return 0;
}
