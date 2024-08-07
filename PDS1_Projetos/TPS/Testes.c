#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int ID;
} oi;

typedef struct
{
    unsigned int ID;
    char nome[50];
    char departamento[50];
    double preco;

} Produto_t;

typedef struct reg
{
    Produto_t produto;

    struct reg *esq;
    struct reg *dir;

} noh_t;

void foo(int x)
{
    int buf[10];

    if (x == 1000)
        buf[x] = 0;
}

int main()
{
    int a[100];

    int x = 200;

    scanf("%d", &x);

    if (x == 100)
        a[x] = 1;

    printf("Noh_t * = %lu\n", sizeof(noh_t *));
    printf("Int * = %lu\n", sizeof(int *));
    printf("Void * = %lu\n", sizeof(void *));
    printf("Void = %lu\n", sizeof(void));

    noh_t *la = calloc(1, sizeof(noh_t));

    int i;
    char c, s[50];

    if (la->esq == NULL)
        printf("cjhsabchja");

    char ori[100];

    sscanf(ori, "%d %c %s", &i, &c, s);

    printf("%d %c %s\n", i, c, s);

    free(la);

    return 0;
}
