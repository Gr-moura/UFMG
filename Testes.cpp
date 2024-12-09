#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Verifica se o nome do arquivo foi passado como argumento
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <nome_do_arquivo>\n", argv[0]);
        return 1;
    }

    // Abre o arquivo para leitura
    FILE *arquivo = fopen(argv[1], "r");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Conta o número de letras 'a' no arquivo
    int contador = 0;
    char caractere;
    while ((caractere = fgetc(arquivo)) != EOF)
    {
        if (caractere == 'a')
        {
            contador++;
        }
    }

    // Exibe o resultado
    printf("%d\n", contador);

    // Fecha o arquivo
    fclose(arquivo);
    return 0;
}
