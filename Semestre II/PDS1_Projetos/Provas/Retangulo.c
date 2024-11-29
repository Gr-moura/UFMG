/*
    Crie uma estrutura chamada Retângulo.

    Essa estrutura deverá conter o ponto superior esquerdo e o ponto inferior direito do retângulo.
    Cada ponto é definido por uma estrutura Ponto, a qual contém as posições X e Y.

    Faça um programa que declare e leia uma estrutura Retângulo e um ponto,
    exiba a área, o comprimento da diagonal e o perímetro desse retângulo e se o ponto está dentro desse retângulo.

    O programa deve conter 4 funções que retornam os valores solicitados, com as seguintes assinaturas :

        double area_retângulo(struct Retangulo r);
        double comprimento_diagonal(struct Retangulo r);
        double perimetro_retangulo(struct Retangulo r);
        int ponto_dentro(struct Retangulo r, struct Ponto p);

    Você está livre para criar outras funções, mas as 4 descritas acima são obrigatórias.

    Os argumentos serão passados na seguinte ordem :

        abscissa x do ponto superior esquerdo do retângulo,
        ordenada y do ponto superior esquerdo do retângulo,

        abscissa x do ponto inferior direito do retângulo,
        ordenada y do ponto inferior direito do retângulo,

        abscissa x do ponto,
        ordenada y do ponto.

    Os resultados devem ser apresentados com 2 casas decimais.
*/

#include <math.h>
#include <stdio.h>

struct Ponto
{
    double x;
    double y;
};

struct Retangulo
{
    struct Ponto sup_esquerdo;
    struct Ponto inf_direito;
};

double area_retangulo(struct Retangulo r)
{
    double altura = r.sup_esquerdo.y - r.inf_direito.y;

    double largura = r.inf_direito.x - r.sup_esquerdo.x;

    return largura * altura;
}

double comprimento_diagonal(struct Retangulo r)
{
    double altura = r.sup_esquerdo.y - r.inf_direito.y;

    double largura = r.inf_direito.x - r.sup_esquerdo.x;

    double ans = sqrt((altura * altura + largura * largura));
    return ans;
}

double perimetro_retangulo(struct Retangulo r)
{
    double altura = r.sup_esquerdo.y - r.inf_direito.y;

    double largura = r.inf_direito.x - r.sup_esquerdo.x;

    return (2 * altura + 2 * largura);
}

int ponto_dentro(struct Retangulo r, struct Ponto p)
{
    if ((p.x >= r.sup_esquerdo.x && p.x <= r.inf_direito.x) && (p.y <= r.sup_esquerdo.y && p.y >= r.inf_direito.y))
        return 1;

    return 0;
}

int main()
{

    struct Retangulo ret;
    struct Ponto pt;

    /* abscissa x do ponto superior esquerdo do retângulo,
     *  ordenada y do ponto superior esquerdo do retângulo, */

    scanf("%lf%lf", &ret.sup_esquerdo.x, &ret.sup_esquerdo.y);

    /* abscissa x do ponto inferior direito do retângulo,
     *  ordenada y do ponto inferior direito do retângulo, */

    scanf("%lf%lf", &ret.inf_direito.x, &ret.inf_direito.y);

    /* abscissa x do ponto, ordenada y do ponto.*/

    scanf("%lf%lf", &pt.x, &pt.y);

    printf("area do retangulo: %.2lf\n", area_retangulo(ret));
    printf("diagonal do retangulo: %.2lf\n", comprimento_diagonal(ret));
    printf("perimetro do retangulo: %.2lf\n", perimetro_retangulo(ret));

    if (ponto_dentro(ret, pt))
        printf("Ponto dentro: Sim\n");

    else
        printf("Ponto dentro: Nao\n");

    return 0;
}
