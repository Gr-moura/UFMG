Esse é um exercício que tem como objetivo praticar o tratamento de exceções. Mais do que a implementação em si, que é relativamente simples, é importante que você observe e entenda o que está acontecendo no seu código.

Você deverá criar uma classe de exceção personalizada chamada "NegativeResultException", herdando da classe Exception. Sua classe deve ter um atributo chamado valor, que armazena um valor inteiro. Esse valor deve ser inicializado com um parâmetro passado no construtor da classe. Você deverá redefinir o método What() para retornar o texto: "Erro: Resultado Negativo."

Você deverá implementar um programa que cria um vector<int> inicializado com os valores {-20, -10, 0, 10, 20}. Após a inicialização do vetor, você deverá entrar em um bloco try onde você vai ler um valor de entrada e acessar o conteúdo do seu vetor na posição fornecida como entrada (obs. acesse a posição do vetor usando o método at( ). O que acontece caso o acesso for feito usando [ ]?).  Se o valor fornecido pelo usuário não é uma posição válida do vector<int> que você criou anteriormente, você devera lançar uma exceção do tipo std::out_of_range com a mensagem "Erro: Parametro invalido".

Se o conteúdo do vetor na posição fornecida pelo usuário for negativo, você deverá lançar uma exceção do tipo NegativeResultException. Se for 0, você deverá lançar uma exceção do tipo logic_error com a mensagem "Erro: O resultado não deve ser zero". Se nenhum desses casos é alcançado, você deverá imprimir o conteúdo do vetor na posição fornecida.

Após o bloco try, você deverá capturar as possíveis exceções. No caso de uma exceção do tipo NegativeResultException, você deverá imprimir a mensagem do método what em uma linha e o valor que gerou a exceção na linha seguinte. Caso aconteçam outras exceções, você deve apenas imprimir a mensagem do método what.

Faça diferentes testes e observe as saídas. As exceções estão sendo tratadas de forma adequada?