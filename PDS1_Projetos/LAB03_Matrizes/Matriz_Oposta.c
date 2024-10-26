#include <stdio.h>

int main()
{
    int qt_linhas, qt_colunas, maior;

    scanf("%d ", &qt_linhas);
    scanf("%d ", &qt_colunas);

    int matriz[qt_linhas][qt_colunas];

    for (int i = 0; i < qt_linhas; i++)
    {
        for (int j = 0; j < qt_colunas; j++)
        {

            scanf("%d ", &matriz[i][j]);

            if (j != qt_colunas)
                printf("%d ", -1 * matriz[i][j]);
            else
                printf("%d\n", -1 * matriz[i][j]);
        }
    }

    return 0;
}
