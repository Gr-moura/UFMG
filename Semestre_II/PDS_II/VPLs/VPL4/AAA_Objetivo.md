O objetivo desse exercício é praticar a manipulação de apontadores usando para isso o TAD Lista Encadeada (List) visto em sala, e praticar a automação da compilação do seu projeto usando Makefiles.

Neste VPL, você vai precisar escrever um método void List::Inverte() que inverte a ordem dos elementos de uma lista encadeada. Para isso, você deverá fazer a manipulação dos apontadores para trocar as nodos de posição na lista. (Obs. Não vale apenas trocar o campo "data" de lugar, criar novos nodos, ou usar uma estrutura auxiliar! A troca dos nodos será conferida na execução).

Estão sendo disponibilizados os arquivos list.hpp, node.hpp, list.cpp e main.cpp (vpl4_listas.zip). 

As suas tarefas serão (1) Implementar o método indicado no TAD e submeter o arquivo list.cpp, e (2) fazer um Makefile para compilar o projeto e submeter o arquivo Makefile. Mas para organizar melhor o código, o projeto foi  estruturado de acordo com a hierarquia de diretórios abaixo:

. Projeto
├── Makefile
├── build/
│  └── [arquivos.o]
├── include/
│  └── list.hpp
│  └── node.hpp
└── src/
│  └── list.cpp
│  └── main.cpp

O arquivo Makefile para esse programa deve seguir as seguintes orientações:

Todas os TADs e o arquivo main devem ser compilados individualmente e os arquivos *.o resultantes devem ser salvos no diretório /build/

Em seguida, os arquivos compilados devem ser linkados em um executável resultante chamado vpl_execution, que deve ser salvo no diretório raiz da aplicação.

Atenção, a formatação (tabs, espaços, etc) do arquivo Makefile impacta no funcionamento. Uma sugestão é fazer as regras no VSCode/Notepad e copiar para o Moodle. Atenção também para os nomes dos arquivos com maiúsculas ou minúsculas.

Obs. Leia com atenção o arquivo main.cpp que está sendo fornecido e tente entender quais os testes que estão sendo efetuados.