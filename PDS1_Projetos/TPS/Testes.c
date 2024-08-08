#include <stdio.h>

typedef void (*functype)();
typedef int (*functype2)(int, int);

int add(int a, int b)
{
    return a + b;
}

int add2(int a, int b)
{
    return a + b;
}

void fun2()
{
    printf("8\n");
}

void fun()
{
    static int dafdafa;
    printf("%d", dafdafa + 1);
}

int main()
{
    functype array[] = {fun, fun2};

    functype2 array2[] = {add, add2};

    array[1]();

    printf("%d", array2[1](3, 4));

    printf("\n%p\n", array);
    printf("\n%p\n", &array);

    return 0;
}
