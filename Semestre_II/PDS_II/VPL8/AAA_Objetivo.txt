O objetivo desse exercício é praticar alguns conceitos básicos de classes, herança e composição.

Você foi contratado para auxiliar no desenvolvimento de uma interface gráfica de um novo sistema operacional. Sua tarefa inicial é montar uma hierarquia de classes para representação de figuras geométricas e fazer alguns testes iniciais. 

Você deverá criar uma superclasse chamada FiguraGeometrica, e três classes herdeiras: Retângulo, Triângulo e Círculo. A sua superclasse deve ser uma classe abstrata. Ela possui um atributo chamado "centro" com coordenadas do centro da figura geométrica. Esse atributo deve ser um objeto de outra classe chamada "Ponto", criada para representar um ponto no espaço 2D (implemente a classe com construtores adequados e métodos Get / Set para os atributos. A sua classe base também deve possuir e um método chamado "Desenha" que imprime essas coordenadas e que pode ser redefinido nas classes herdeiras. Além disso, a sua classe possui um método virtual puro chamado "CalculaArea" que calcula a área ocupada pelas figuras geométricas (retornando um valor float) e será implementado nas classes herdeiras.

A classe Retângulo tem como os atributos os dois lados do retângulo. O seu método Desenha chama o método da classe pai e depois imprime a palavra "RETANGULO". Já o seu método CalculaArea retorna a área do retângulo.

A classe Círculo tem como o atributo o raio do círculo. O seu método Desenha chama o método da classe pai e depois imprime a palavra "CIRCULO", e o seu método CalculaArea retorna a área do circulo.

Por fim, a classe Triângulo tem como atributos a base e altura do triangulo. O seu método Desenha chama o método da classe pai e depois imprime a palavra "TRIANGULO", e o seu método CalculaArea retorna a sua área.

Use adequadamente os modificadores de acesso (public, protected e private) em suas classes e implemente os métodos construtores e destrutores conforme necessário. 

O seu programa principal deverá armazenar um vetor de figuras geométricas e receber comandos para a sua manipulação. Mais especificamente, ele vai ser um  loop que lê comandos da entrada (R, C, T, D, A, E) juntamente com eventuais parâmetros e faz as operações de acordo.  Os comandos são:

R <C1> <C2> <L1> <L2>: Cria um retângulo com lados L1 e L2 com centro em C1, C2.

C <C1> <C2> <R>: Cria um círculo de raio R com centro em C1, C2.

T <C1> <C2> <B> <A>: Cria um triângulo de base B e altura A com centro em C1, C2.

D:  "Desenha" todas as figuras geométricas armazenadas, imprimindo as coordenadas do seu centro e o texto especificado para cada tipo.

A: calcula e imprime a área total ocupada por todas as figuras geométricas.

E: termina a execução do programa.

A sequência abaixo mostra um exemplo de entrada com a respectiva saída:

R 10 10 10 20
R 20 20 10 40
T 0 0 20 20
C 50 50 100
D
A
E
10 10 RETANGULO
20 20 RETANGULO
0 0 TRIANGULO
50 50 CIRCULO
32215.93
Para simplificar, você pode colocar a implementação da sua hierarquia de classes e o seu main em um mesmo arquivo. 
