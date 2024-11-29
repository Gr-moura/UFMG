O Objetivo desse projeto é praticar os conceitos de Tipos Abstratos de Dados (TAD) e Modularização.

Você foi contratado por uma empresa de transporte publico para implementar um sistema de forma a monitorar as suas operações. Basicamente, na central de ônibus os operadores podem cadastrar novos ônibus, subir e descer pessoas no ônibus e fazer transferência de pessoas entre os ônibus. Para implementar o seu sistema você vai criar 2 TADs e um arquivo main: 

TAD Onibus

O TAD Empresa armazena os dados da conta: placa (string), capacidade máxima (int), e lotação atual (int) e possui as seguintes operações:

- Construtor: inicializa um novo ônibus com uma placa (string) e capacidade máxima de passageiros (int) como parâmetro.
- subir_passageiros: recebe um valor inteiro como parâmetro e adiciona esses passageiros no total de passageiros.
- descer_passageiros: recebe um valor como parâmetro e subtrai do saldo da conta.
- transfere_passageiros: recebe um ponteiro a outro ônibus e um valor inteiro como parâmetros. O valor inteiro representa a quantidade de passageiros que vão ser transferidos entre o ônibus atual e segundo próximo ônibus.
- imprimir_estado: imprime em uma linha a placa, a lotação atual e o total máximo de passageiros, com um endl no final no seguinte formato: <PLACA> (<LOTACAO_ATUAL>/<MAX_LOTACAO>). Exemplo: "AAA123 (10/20)".

TAD Empresa

O TAD empresa é usada para armazenar os registros dos ônibus. Basicamente, ele vai ter como atributos um número inteiro que armazena o número total de ônibus cadastrados e um vetor com apontadores para os ônibus. (Para simplificar, você pode considerar que o número máximo de ônibus é 20, e usar um vetor simples com alocação estática). O TAD Empresa possui as seguintes operações:

- Construtor: inicializa o TAD colocado o valor 0 no número de ônibus cadastrados e inicializando todos os elementos do vetor de veículos com nullptr.
- adicionar_onibus: registra um novo ônibus no sistema com a placa e lotação máxima passados como parâmetro e a coloca no vetor de veículos, incrementando também o número de ônibus. Note que não pode haver veículos com placas repetidas, portanto o seu método deve retornar um apontador para o novo ônibus registrado ou, em caso de falhas, nullptr.  
- busca_onibus: recebe a placa de um veículo e faz uma pesquisa por um ônibus com essa placa no vetor de ônibus, retornando um apontador para o veículo encontrada ou nullptr caso não exista.
- imprimir_estado: imprime as informações de todos os ônibus cadastrados na empresa (placa, lotação atual, lotação máxima), um ônibus por linha.

  Main:

O seu programa principal faz a gerência das operações da empresa. Ele vai ser um basicamente um loop que lê comandos da entrada (C, S, D, T, I, F) juntamente com os parâmetros e faz as operações de acordo. Para cada comando, o sistema imprime uma mensagem com uma quebra de linha (endln) no final. Importante: as mensagens devem ser exatamente como especificadas abaixo para evitar erros na correção automática. As operações são: 

- C <placa> <lotação>: cadastra um novo ônibus com a placa e lotação máxima indicados. Deve ser impresso: “novo onibus cadastrado” em caso de sucesso ou “ERRO : onibus repetido” em caso de falha.
- S <placa> <num pessoas>: registra que X pessoas subiram no onibus com a placa sinalizada. Você poderá considerar que os valores fornecidos serão sempre positivos. Considerar a lotação máxima do veiculo: se o numero de pessoas que entrar agora supera a lotação máxima, não deixar ninguém novo subir e vai precisar mostrar a mensagem “ERRO : onibus lotado”. Deve ser impresso: “passageiros subiram com sucesso” em caso de sucesso ou “ERRO : onibus inexistente” caso a placa do veiculo seja inválida.
- D <placa> <num pessoas>: registra que X pessoas desceram no onibus com a placa sinalizada. Você poderá considerar que os valores fornecidos serão sempre positivos. Considerar que a lotação atual não pode ser menor a 0: se o numero de pessoas que sair agora faz a lotação do veiculo ficar menor a zero, não deixar ninguém descer e vai precisar mostrar a mensagem “ERRO : faltam passageiros”. Deve ser impresso: “passageiros desceram com sucesso” em caso de sucesso ou “ERRO : onibus inexistente” caso a placa do veiculo seja inválida.
- T <placa1> <placa2> <num pessoas>: transfere pessoas de um ônibus <placa1> a outro <placa2>. Você poderá considerar que os valores fornecidos serão sempre positivos. Deve ser impresso: “transferencia de passageiros efetuada” em caso de sucesso ou “ERRO : onibus inexistente” caso um das placas dos onibus indicadas sejam inválidas ou “ERRO : transferencia cancelada” se tem alguma situação de lotação invalida.
- I: lista as informações de todos os ônibus cadastrados (placa, lotação atual, lotação máxima), um ônibus por linha.
- T: termina a execução do programa.



Segue abaixo um exemplo de uma execução do Sistema:

C OLX123 11
novo onibus cadastrado
C OLX123 12
ERRO : onibus repetido
I
OLX123 (0/11)
S OLX123 10
passageiros subiram com sucesso
D OLX123 5
passageiros desceram com sucesso
I
OLX123 (5/11)
C BBB222 10
novo onibus cadastrado
S BBB222 2
passageiros subiram com sucesso
I
OLX123 (5/11)
BBB222 (2/10)
F 

Você deverá submeter 5 arquivos: Onibus.hpp, Onibus.cpp, Empresa.hpp, Empresa.cpp e main.cpp. No seu programa principal, você não deverá acessar diretamente os atributos dos seus TADs. Todo o acesso deverá ser feito através dos métodos implementados.
