#include <stdio.h>

int main()
{
    int qt_navios, extremo, mudarlinha, mudarcoluna;
    char tipo_navio, orientacao;

    int coords_centro[2];

    char p1_matriz[20][20];
    char p2_matriz[20][20];

    // Preencher o mar
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            p1_matriz[i][j] = '~';
            p2_matriz[i][j] = '~';
        }
    }

    scanf("%d", &qt_navios);

    // Pegar os navios do player 1
    for (int i = 0; i < qt_navios; i++)
    {
        scanf("%d %d ", &coords_centro[0], &coords_centro[1]);
        scanf("%c %c", &tipo_navio, &orientacao);

        if (tipo_navio == 'C')
            extremo = 1;
        else if (tipo_navio == 'E')
            extremo = 2;
        else if (tipo_navio == 'P')
            extremo = 3;

        // Percorre e soma os valores até os extremos (-3, -2, -1, 0, 1, 2, 3)
        for (int j = -extremo; j < extremo + 1; j++)
        {
            if (orientacao == 'V')
            {
                mudarlinha = j;
                mudarcoluna = 0;
            }
            else
            {
                mudarlinha = 0;
                mudarcoluna = j;
            }

            p1_matriz[coords_centro[0] + mudarlinha][coords_centro[1] + mudarcoluna] = tipo_navio;
        }
    }

    // Pegar os navios do player 2
    for (int i = 0; i < qt_navios; i++)
    {
        scanf("%d %d ", &coords_centro[0], &coords_centro[1]);
        scanf("%c %c", &tipo_navio, &orientacao);

        if (tipo_navio == 'C')
            extremo = 1;
        else if (tipo_navio == 'E')
            extremo = 2;
        else if (tipo_navio == 'P')
            extremo = 3;

        // Percorre e soma os valores até os extremos (-3, -2, -1, 0, 1, 2, 3)
        for (int j = -extremo; j < extremo + 1; j++)
        {
            if (orientacao == 'V')
            {
                mudarlinha = j;
                mudarcoluna = 0;
            }
            else
            {
                mudarlinha = 0;
                mudarcoluna = j;
            }

            p2_matriz[coords_centro[0] + mudarlinha][coords_centro[1] + mudarcoluna] = tipo_navio;
        }
    }

    // Ver ataques
    int rodadas;
    scanf("%d", &rodadas);

    int p1_pontos = 0, p2_pontos = 0;
    int linha_ataque, coluna_ataque;

    for (int i = 0; i < rodadas; i++)
    {
        scanf("%d %d", &linha_ataque, &coluna_ataque);

        if (p2_matriz[linha_ataque][coluna_ataque] == 'C')
            p1_pontos += 2;
        else if (p2_matriz[linha_ataque][coluna_ataque] == 'E')
            p1_pontos += 5;
        else if (p2_matriz[linha_ataque][coluna_ataque] == 'P')
            p1_pontos += 10;

        p2_matriz[linha_ataque][coluna_ataque] = 'O';

        scanf("%d %d", &linha_ataque, &coluna_ataque);

        if (p1_matriz[linha_ataque][coluna_ataque] == 'C')
            p2_pontos += 2;
        else if (p1_matriz[linha_ataque][coluna_ataque] == 'E')
            p2_pontos += 5;
        else if (p1_matriz[linha_ataque][coluna_ataque] == 'P')
            p2_pontos += 10;

        p1_matriz[linha_ataque][coluna_ataque] = 'O';
    }

    // Printar o resultado final
    printf("\nTABULEIRO JOGADOR 1\n");
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            printf("%c ", p1_matriz[i][j]);
        }
        printf("\n");
    }

    printf("\nTABULEIRO JOGADOR 2\n");
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            printf("%c ", p2_matriz[i][j]);
        }
        printf("\n");
    }

    if (p1_pontos == p2_pontos)
    {
        printf("\nO jogo terminou empatado em %d pontos.\n", p1_pontos);
        return 0;
    }

    int vencedor = p1_pontos > p2_pontos ? 1 : 2;
    int maior_pont = p1_pontos > p2_pontos ? p1_pontos : p2_pontos;
    int menor_pont = p1_pontos < p2_pontos ? p1_pontos : p2_pontos;

    printf("\nO jogador %d venceu com %d pontos, contra %d pontos do jogador %d.\n", vencedor, maior_pont, menor_pont,
           3 - vencedor);

    return 0;
}
