O objetivo desse exercício é começar a praticar alguns conceitos básicos de classes e também aplicar utilizar containers, iteradores e algoritmos da STL. 

Você foi contratado pela UFMG para fazer um controle dos alunos matriculados. Para isso você vai ter que implementar uma classe com os dados e as operações sobre alunos e um programa (main) que faz a leitura dos dados e emite um relatório. 

Classe Aluno:

Você deverá implementar uma classe "Aluno" que armazena o nome (string), número de matrícula (int), e um vetor de tamanho indeterminado com notas obtidas pelo aluno (notas com valores inteiros). O seu TAD deverá possuir métodos para calcular a média das notas, retornar a nota máxima e mínima, além de métodos acessórios, como construtor, métodos para acesso aos dados, etc.  Use um container do tipo vector e algoritmos da STL para encontrar a maior e menor nota. 

Main: 

No seu arquivo main, você deverá ler dos dados de um conjunto de alunos e depois imprimir um relatório. Mais especificamente, você deverá ler, para cada aluno, o nome, número de matrícula e o conjunto de notas. Você não tem informação sobre o número de notas de cada aluno, portanto use o flag -1 para terminar a leitura das notas. Da mesma forma, você não tem informações sobre o número de alunos. Portanto, use o flag "END" para terminar a entrada de dados. Você pode considerar que o nome será fornecido em uma linha, o número de matrícula na linha seguinte e as notas na terceira linha, separadas por espaço (ver exemplo abaixo). 

Como saída, você deverá imprimir para cada aluno: na primeira linha, o número de matrícula, nome e o vetor de notas. Na segunda linha, a média das notas (com duas casas decimais) a maior nota e menor nota. Os alunos deveram ser impressos em ordem alfabética (use o algoritmo sort da STL para isso). 

Exemplo

Entrada:

Luiz
2021153
60 75 90 80 75 -1
Joao
2022098
85 95 90 -1
Maria
2022051
90 100 100 90 -1
END

Saída:

2022098 Joao 85 95 90 
90.00 95 85
2021153 Luiz 60 75 90 80 75 
76.00 90 75
2022051 Maria 90 100 100 90 
95.00 100 90

Você deverá submeter 3 arquivos: aluno.hpp, aluno.cpp, e main.cpp. No seu programa principal, você não deverá acessar diretamente os atributos dos seu TAD. Todo o acesso deverá ser feito através dos métodos implementados.