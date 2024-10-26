#include "Onibus.hpp"
#include "Empresa.hpp"
#include <iostream>

using namespace std;

int main()
{
    Empresa *empresa = new Empresa();
    empresa->adicionar_onibus("ABC-1234", 40);
    
    empresa->busca_onibus("ABC-1234")->subir_passageiros(10);


    empresa->adicionar_onibus("ABC-1234", 80);
    empresa->imprimir_estado(); 

}
