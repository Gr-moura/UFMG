import random
import subprocess
import os
import sys
from typing import Dict, Any, List, Callable, Union

# --- Configurações ---

# 1. Defina a estrutura das suas entradas randomizadas aqui
#    Use listas para escolher um item aleatório.
#    Use funções (lambda ou def) para gerar valores dinamicamente.
#    A ordem das chaves IMPORTA - define a ordem em que os dados
#    serão escritos no arquivo de input (um valor por linha por padrão).
ENTRADA_CONFIG: Dict[str, Union[List[Any], Callable[[], Any]]] = {
    "nome": [
        "Antonio",
        "Bernardo",
        "Carlos",
        "Daniel",
        "Eduardo",
        "Fernando",
        "Gustavo",
        "Henrique",
        "Igor",
        "Joao",
        "Kleber",
        "Leonardo",
        "Marcelo",
        "Nelson",
        "Oscar",
        "Paulo",
        "Quiteria",
        "Ricardo",
        "Sergio",
        "Thiago",
        "Ulisses",
        "Vitor",
        "Wagner",
        "Xavier",
        "Yuri",
        "Zeca",
    ],
    "idade": lambda: random.randint(1, 100),
    "telefone": lambda: random.randint(100000000, 999999999),  # Ajustado para 9 dígitos
    # Adicione mais campos conforme necessário para seu código C++
    # Exemplo: "quantidade_itens": lambda: random.randint(1, 50),
}

# 2. Caminho para o seu arquivo de código C++
ARQUIVO_CPP = "seu_codigo.cpp"  # <<< MUDE AQUI para o nome do seu arquivo .cpp

# 3. Nome desejado para o arquivo executável após a compilação
NOME_EXECUTAVEL = "programa_teste"  # No Windows, pode ser "programa_teste.exe"

# 4. Quantidade de casos de teste a serem gerados
NUM_CASOS_TESTE = 10

# 5. Diretórios para salvar os casos de teste
DIR_BASE = "casos_teste"
DIR_INPUT = os.path.join(DIR_BASE, "input")
DIR_OUTPUT = os.path.join(DIR_BASE, "output")

# 6. Compilador C++ e flags (ajuste se necessário)
COMPILADOR = "g++"
FLAGS_COMPILACAO = ["-std=c++17", "-O2"]  # Exemplo: C++17, otimização O2

# --- Funções Auxiliares ---


def gerar_valor(config_item: Union[List[Any], Callable[[], Any]]) -> Any:
    """Gera um valor aleatório baseado no tipo de configuração."""
    if isinstance(config_item, list):
        return random.choice(config_item)
    elif callable(config_item):
        return config_item()
    else:
        # Se precisar de outros tipos (ex: float, bool), adicione aqui
        # Por segurança, retornamos None ou levantamos um erro se o tipo for inesperado
        print(
            f"AVISO: Tipo de configuração não suportado: {type(config_item)}. Retornando None.",
            file=sys.stderr,
        )
        return None
        # raise TypeError(f"Tipo de configuração não suportado: {type(config_item)}")


def gerar_input_str(config: Dict[str, Union[List[Any], Callable[[], Any]]]) -> str:
    """
    Gera uma string formatada para o arquivo de input.
    Por padrão, coloca cada valor em uma nova linha, na ordem das chaves do dict.
    """
    valores_gerados = []
    for key in config:
        valor = gerar_valor(config[key])
        valores_gerados.append(str(valor))  # Converte para string para escrita
    return "\n".join(valores_gerados) + "\n"  # Adiciona nova linha no final


def compilar_cpp(arquivo_fonte: str, nome_saida: str) -> bool:
    """Compila o código C++ usando o compilador definido."""
    comando = [COMPILADOR] + FLAGS_COMPILACAO + [arquivo_fonte, "-o", nome_saida]
    print(f"--- Compilando: {' '.join(comando)} ---")
    try:
        processo = subprocess.run(comando, check=True, capture_output=True, text=True)
        if processo.stderr:
            print("--- Warnings da Compilação ---")
            print(processo.stderr)
            print("------------------------------")
        print("--- Compilação bem-sucedida! ---")
        return True
    except FileNotFoundError:
        print(
            f"ERRO: Compilador '{COMPILADOR}' não encontrado. Verifique se ele está instalado e no PATH.",
            file=sys.stderr,
        )
        return False
    except subprocess.CalledProcessError as e:
        print("--- ERRO DE COMPILAÇÃO ---", file=sys.stderr)
        print(f"Comando falhou: {' '.join(e.cmd)}", file=sys.stderr)
        print(f"Código de retorno: {e.returncode}", file=sys.stderr)
        print("--- Saída de Erro (stderr) ---", file=sys.stderr)
        print(e.stderr, file=sys.stderr)
        print("----------------------------", file=sys.stderr)
        return False
    except Exception as e:
        print(f"ERRO inesperado durante a compilação: {e}", file=sys.stderr)
        return False


def executar_e_capturar(executavel: str, arquivo_input: str) -> str | None:
    """Executa o programa C++ com um input e captura o output."""
    # Garante que o caminho do executável seja relativo ao script ou absoluto
    caminho_executavel = os.path.abspath(executavel)
    if sys.platform == "win32" and not caminho_executavel.endswith(".exe"):
        caminho_executavel += ".exe"  # Adiciona .exe no Windows se não tiver

    # Se o executável não estiver no diretório atual, prefixa com ./ no Linux/macOS
    if sys.platform != "win32" and not os.path.dirname(caminho_executavel):
        caminho_executavel = "./" + caminho_executavel

    print(f"Executando: {caminho_executavel} < {arquivo_input}")
    try:
        with open(arquivo_input, "r", encoding="utf-8") as f_in:
            processo = subprocess.run(
                [caminho_executavel],
                stdin=f_in,
                capture_output=True,
                text=True,
                check=True,  # Levanta exceção se o programa C++ retornar erro
                encoding="utf-8",  # Assume UTF-8 para input/output
            )
        if processo.stderr:
            print(f"  -> Programa C++ emitiu avisos (stderr):")
            print(processo.stderr, end="")  # Mostra stderr do programa C++
        return processo.stdout
    except FileNotFoundError:
        print(
            f"ERRO: Executável '{caminho_executavel}' não encontrado. A compilação falhou ou o nome está incorreto.",
            file=sys.stderr,
        )
        return None
    except subprocess.CalledProcessError as e:
        print(
            f"--- ERRO DURANTE EXECUÇÃO do C++ (Input: {arquivo_input}) ---",
            file=sys.stderr,
        )
        print(f"Comando: {' '.join(e.cmd)}", file=sys.stderr)
        print(f"Código de retorno: {e.returncode}", file=sys.stderr)
        print("--- Saída de Erro (stderr) do C++ ---", file=sys.stderr)
        print(e.stderr or "Nenhuma saída de erro específica.", file=sys.stderr)
        print("------------------------------------", file=sys.stderr)
        return None  # Retorna None para indicar falha na execução
    except Exception as e:
        print(
            f"ERRO inesperado durante a execução de {caminho_executavel} com {arquivo_input}: {e}",
            file=sys.stderr,
        )
        return None


# --- Função Principal ---


def main():
    print(">>> Iniciando Gerador de Casos de Teste <<<")

    # 1. Criar diretórios se não existirem
    os.makedirs(DIR_INPUT, exist_ok=True)
    os.makedirs(DIR_OUTPUT, exist_ok=True)
    print(f"Diretórios '{DIR_INPUT}' e '{DIR_OUTPUT}' prontos.")

    # 2. Compilar o código C++
    if not compilar_cpp(ARQUIVO_CPP, NOME_EXECUTAVEL):
        print("Falha na compilação. Abortando.", file=sys.stderr)
        sys.exit(1)  # Termina o script com código de erro

    # 3. Gerar casos de teste (Input e Output)
    print(f"\n--- Gerando {NUM_CASOS_TESTE} Casos de Teste ---")
    falhas_execucao = 0
    for i in range(NUM_CASOS_TESTE):
        print(f"\nProcessando Caso de Teste #{i+1}...")

        # Nome dos arquivos
        nome_base_arquivo = f"caso_{i+1}"
        arquivo_input_path = os.path.join(DIR_INPUT, f"{nome_base_arquivo}_input.txt")
        arquivo_output_path = os.path.join(
            DIR_OUTPUT, f"{nome_base_arquivo}_output.txt"
        )

        # Gerar conteúdo do input
        input_data = gerar_input_str(ENTRADA_CONFIG)

        # Salvar arquivo de input
        try:
            with open(arquivo_input_path, "w", encoding="utf-8") as f:
                f.write(input_data)
            print(f"  -> Input salvo em: {arquivo_input_path}")
        except IOError as e:
            print(
                f"ERRO ao salvar arquivo de input {arquivo_input_path}: {e}",
                file=sys.stderr,
            )
            continue  # Pula para o próximo caso de teste

        # Executar o programa C++ com o input gerado e capturar output
        output_data = executar_e_capturar(NOME_EXECUTAVEL, arquivo_input_path)

        # Salvar arquivo de output (se a execução foi bem-sucedida)
        if output_data is not None:
            try:
                # Normalizar finais de linha (útil entre Windows/Linux)
                output_data_normalized = output_data.replace("\r\n", "\n")
                with open(arquivo_output_path, "w", encoding="utf-8") as f:
                    f.write(output_data_normalized)
                print(f"  -> Output salvo em: {arquivo_output_path}")
            except IOError as e:
                print(
                    f"ERRO ao salvar arquivo de output {arquivo_output_path}: {e}",
                    file=sys.stderr,
                )
        else:
            # Marca que houve falha, mas continua para outros casos
            print(
                f"  -> Falha ao executar C++ para {arquivo_input_path}. Output não gerado."
            )
            falhas_execucao += 1

    print("\n--- Processo Concluído ---")
    if falhas_execucao > 0:
        print(
            f"ATENÇÃO: {falhas_execucao} caso(s) de teste falharam durante a execução do C++.",
            file=sys.stderr,
        )
    else:
        print("Todos os casos de teste foram gerados e executados com sucesso!")
    print(
        f">>> Verifique os arquivos nos diretórios '{DIR_INPUT}' e '{DIR_OUTPUT}'. <<<"
    )


if __name__ == "__main__":
    main()
