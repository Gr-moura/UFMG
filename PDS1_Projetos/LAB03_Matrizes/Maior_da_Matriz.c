#include <stdio.h>

int main()
{
    int qt_linhas, qt_colunas, maior;

    scanf("%d", &qt_linhas);
    scanf("%d", &qt_colunas);

    int matriz[qt_linhas][qt_colunas];

    for (int i = 0; i < qt_linhas; i++)
    {
        for (int j = 0; j < qt_colunas; j++)
        {

            scanf("%d", &matriz[i][j]);
        }
    }

    maior = matriz[0][0];

    for (int i = 0; i < qt_linhas; i++)
    {
        for (int j = 0; j < qt_colunas; j++)
        {

            if (matriz[i][j] > maior)
                maior = matriz[i][j];
        }
    }

    printf("%d\n", maior);

    return 0;
}
