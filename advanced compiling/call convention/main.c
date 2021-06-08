int fun_1(char c, int a, int b, int d)
{
    int tmp = c + a + b + d;
}

int fun_2(char c, int a)
{
    int tmp = c - a;
}

int main(int argc, char** argv)
{
    int a = 1, b = 2, c = 0;
    c = a + b;
    char d = 0;
    int used = fun_1(d, a, b, c);
    used = fun_2(d, d);
    return 0;
}