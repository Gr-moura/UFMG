import random
import subprocess
import os

nomes = ["Antonio", "Bernardo", "Carlos", "Daniel", "Eduardo", "Fernando", "Gustavo", "Henrique", "Igor", "Joao", "Kleber", "Leonardo", "Marcelo", "Nelson", "Oscar", "Paulo", "Quiteria", "Ricardo", "Sergio", "Thiago", "Ulisses", "Vitor", "Wagner", "Xavier", "Yuri", "Zeca"]
comandos = ["Inserir", "Alterar", "Excluir", "Exibir"]

# Gere um arquivo de teste com comandos aleatórios
input_file = "dados.bin"

with open(input_file, "wb") as file:
    for _ in range(random.randint(15, 100)):
        comando = random.choice(comandos)
        nome = random.choice(nomes)

        if comando == "Exibir":
            file.write(f"{comando}\n{nome}\n".encode())

        if comando == "Inserir":
            idade = random.randint(1, 100)
            telefone = random.randint(10000000, 99999999)
            file.write(f"{comando}\n{nome} {idade} {telefone}\n".encode())

        if comando == "Alterar":
            idade = random.randint(1, 100)
            telefone = random.randint(10000000, 99999999)
            file.write(f"{comando}\n{nome} {idade} {telefone}\n".encode())

        if comando == "Excluir":
            file.write(f"{comando}\n{nome}\n".encode())

# Defina o nome do arquivo fonte e o nome do executável
source_file = "Main.c"
executable = "main"

# Compile o arquivo .c
compile_command = ["gcc", source_file, "-o", executable]
compile_process = subprocess.run(compile_command, capture_output=True, text=True)

# Verifique se a compilação foi bem-sucedida
if compile_process.returncode != 0:
    print("Erro na compilação:")
    print(compile_process.stderr)
else:
    print("Compilação bem-sucedida.")
    
    # Verifique se o arquivo dados.bin existe
    if not os.path.isfile(input_file):
        print("Erro: O arquivo de input não foi encontrado.")
    else:
        # Execute o programa compilado e passe dados.bin como argumento
        run_command = ["./" + executable, input_file]
        run_process = subprocess.run(run_command, capture_output=True, text=True)
        
        # Verifique se a execução foi bem-sucedida
        if run_process.returncode != 0:
            print("Erro na execução:")
            print(run_process.stderr)

        # Remova o executável após a execução
        os.remove(executable)