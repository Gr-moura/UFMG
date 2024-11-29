#include <stdio.h>
#include <stdlib.h>

void txt_to_bin(const char *txt_file, const char *bin_file)
{
    FILE *txt = fopen(txt_file, "r");
    if (txt == NULL)
    {
        perror("Erro ao abrir o arquivo de texto");
        exit(EXIT_FAILURE);
    }

    FILE *bin = fopen(bin_file, "wb");
    if (bin == NULL)
    {
        perror("Erro ao criar o arquivo binário");
        fclose(txt);
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    size_t bytes_read;

    // Lê o arquivo de texto em blocos e escreve os dados no binário
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), txt)) > 0)
    {
        fwrite(buffer, 1, bytes_read, bin);
    }

    fclose(txt);
    fclose(bin);

    printf("Conversão concluída: %s -> %s\n", txt_file, bin_file);
}

int main()
{
    const char *input_txt = "entrada.txt"; // Nome do arquivo de texto
    const char *output_bin = "saida.bin";  // Nome do arquivo binário

    txt_to_bin(input_txt, output_bin);

    return 0;
}
