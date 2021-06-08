#include <fstream>
#include <string>

int main(int argc, char **argv)
{
    std::string output = R"(
double sqrt_table[] = {
    0,
    1,
    1.414,
    1.732,
    2,
    2.236,
    2.449,
    2.646,
    2.828,
    3
};
    )";
    std::ofstream ofs(argv[1], std::ios::out);
    ofs << output << std::endl;
    return 0;
}