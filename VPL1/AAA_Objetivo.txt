O objetivo desse exercício é praticar os conceitos de Strings e Streams em C++. 

Você deverá implementar uma versão do Jogo Wordle.  O objetivo do jogo é adivinhar uma palavra de cinco letras dentro em no máximo cinco tentativas. Você insere uma palavra de cinco letras e o jogo indica se as letras estão corretas e se estão na posição correta, na posição errada ou se não estão na palavra. Com base nessas dicas, você tenta adivinhar a palavra correta antes de acabar suas tentativas. 

Mais especificamente, as instruções são as seguintes: 

você deverá inicialmente ler um arquivo chamado "palavras.txt" que contém um conjunto de palavras. A primeira linha contém um inteiro n com o número de palavras do arquivo, seguidas pelas n palavras, uma por linha. Cada palavra possui 5 letras (para simplificar, você pode considerar que a palavra é fornecida em letras maiúsculas e não há caracteres repetidos) .
O próximo passo é ler da entrada padrão um número de 1 a n que vai escolher a palavra a ser adivinhada. Vamos chamar essa palavra de chave.
A partir daí começa o jogo propriamente dito... Você deverá fornecer como entrada uma palavra de 5 letras. (da mesma forma,  você pode considerar que a palavra é fornecida em letras maiúsculas e não há caracteres repetidos).
O seu programa deverá analisar a palavra fornecida como entrada em comparação com a chave e, para cada uma das letras, fornecer uma string de saída da seguinte forma (veja um exemplo em seguida):
- imprimir a letra em maiúscula caso ela esteja presente na chave e esteja na posição correta.
- imprimir a letra em minúscula caso ela esteja presente na chave mas na posição incorreta.
- imprimir um * caso a letra não esteja presente. Além disso, as letras que não estão presentes são impressas depois da palavra entre parênteses.
(devem ser impressas as letras não presentes de todas as tentativas, sem repetição. coloque um espaço depois da palavra).  
Caso a palavra seja igual a chave, você deve imprimir "GANHOU!" e terminar o programa. Senão, deve ler uma nova entrada.
Depois de 5 tentativas, caso você não tenha acertado a palavra, você deve imprimir: "PERDEU!", seguido da palavra correta, separada por um espaço.
Exemplo 1 (E: Entrada, S: Saída)

(E/S)	 Valor	 Explicação
E	7	Palavra #7 do Arquivo. (No caso a palavra é "MUITO")
E	TALCO	Primeira tentativa. Palavra TALCO
S	t***O (ALC)	Saída indicando que a letra T está presente mas no lugar errado, a letra O está presente e no lugar certo e
os caracteres A, L, C não estão presentes
E	PERTO	Segunda tentativa. Palavra PERTO
S	***TO (ALCPER)	Saída indicando que as letras T e O estão presentes e no lugar certo e as letras A, L, C (da primeira tentativa)
e P, E, R da segunda não estão presentes.
E	MISTO	Terceira tentativa. Palavra MISTO
S	Mi*TO (ALCPERS)	Saída indicando que a letra I está presente mas no lugar errado, as letras M, T e O estão presentes e no lugar
certo e as letras A, L, C (da primeira tentativa), P, E, R da segunda e S da terceira não estão presentes.
E	MUITO	Terceira tentativa. Palavra MUITO
S	MUITO (ALCPERS)	Saída indicando que todas as letras estão corretas e no lugar certo e as letras A, L, C (da primeira tentativa),
P, E, R da segunda e S da terceira não estão presentes
S	GANHOU!	Impressão do resultado final

Exemplo 2 (E: Entrada, S: Saída)

(E/S)	 Valor	 Explicação
E	26	Palavra #26 do Arquivo. (No caso a palavra é "ZEBRA")
E	QUILO	Primeira tentativa. Palavra QUILO
S	***** (QUILO)
Saída indicando que nenhuma letra está presente
E	CHAVE	Segunda tentativa. Palavra CHAVE
S	**a*e (QUILOCHV)	Saída indicando que as letras A e E estão presentes mas no lugar errado. C, H, V não estão presentes e foram adicionadas
à lista de erros.
E	ANTES	Terceira tentativa. Palavra ANTES
S	a**e* (QUILOCHVNTS)
Saída indicando que as letras A e E estão presentes mas continuam lugar errado. N, T, S não estão presentes e foram
adicionadas à lista de erros.
E	VERGA	Quarta tentativa. Palavra VERGA
S	*Er*A (QUILOCHVNTSG)
Saída indicando que as letras A e E estão presentes e no lugar e a letra r está presente mas fora do lugar. G não está
presente e foi adicionada à lista de erros. Obs. a letra V já estava presente na lista de erros e não foi adicionada novamente.
E	 PEDRA	Quinta e última tentativa. Palavra PEDRA
S	 *E*RA (QUILOCHVNTSGPD)	Saída indicando que as letras A, E e R estão presentes e no lugar certo. P, D  não estão presentes e foram
adicionadas à lista de erros.
S	PERDEU! ZEBRA
Como não acertou em 5 tentativas, imprimiu a palavra "PERDEU!" seguida de um espaço e a chave correta. 

Observações Finais:
- É obrigatório o uso de Strings e Streams. char *, printf, scanf e similares estão vetados!