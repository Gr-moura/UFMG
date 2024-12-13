import turtle

def ler_arquivo(nome_arquivo):
    try:
        with open(nome_arquivo, 'r') as arquivo:
            conteudo = arquivo.read()
            return conteudo
    except FileNotFoundError:
        return "Arquivo não encontrado."

def desenhar_comandos(comandos, angulo):
    turtle.up()  # Levanta a caneta (turtle)
    turtle.speed(0)  # Aumenta a velocidade do turtle (0 é a velocidade máxima)
    turtle.hideturtle()  # Esconde a caneta (turtle)
    turtle.setup(width=1000, height=1000)  # Define o tamanho da janela do turtle
    turtle.setpos(-700, -200)  # Move a caneta para o canto inferior esquerdo
    turtle.down()  # Abaixa a caneta (turtle)
    for comando in comandos:
        if comando == 'F':
            turtle.forward(5)
        elif comando == '+':
            turtle.right(angulo)
        elif comando == '-':
            turtle.left(angulo)

# Exemplo de uso
nome_arquivo = 'i.txt'
conteudo = ler_arquivo(nome_arquivo)
if conteudo != "Arquivo não encontrado.":
    angulo = 60  # Defina o ângulo desejado aqui
    desenhar_comandos(conteudo, angulo)
    turtle.done()
else:
    print(conteudo)
print(conteudo)