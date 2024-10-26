#include "Onibus.hpp"
#include <iostream>

using namespace std;

int main()
{
    Onibus *A = new Onibus("ABC-1234", 40);
    A->imprimir_estado();   
    Onibus *B = new Onibus("DEF-5678", 80);
    B->imprimir_estado();
    A->subir_passageiros(10);
    A->imprimir_estado();
    B->subir_passageiros(20);
    B->transfere_passageiros(A, 5);
    A->imprimir_estado();
    B->imprimir_estado();
}
