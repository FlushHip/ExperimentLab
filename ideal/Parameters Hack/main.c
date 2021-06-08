#include <stdio.h>
#include <stdlib.h>

cmp(int *a)
{
    return *a - *1[&a];
}

int main(int argc, char **argv)
{
    int n = argc - 1;
    int arr[1 << 4] = { 0 };
    for (int i = 1; i < argc; ++i) {
        arr[i - 1] = atoi(argv[i]);
    }
    qsort(arr, n, sizeof(arr[0]), cmp);

    for (int i = 0; i < n; ++i) {
        printf("%d%c", arr[i], " \n"[i + 1 == n]);
    }
    return 0;
}