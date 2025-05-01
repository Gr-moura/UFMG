#include "listaEncadeada.hpp" // Include the header file with your class definition
#include <cassert>            // For assert()
#include <iostream>
#include <stdexcept> // For std::out_of_range
#include <string>    // For testing with strings

// --- Test Functions ---

// Test inserting into an empty list
void test_InsereFim_ListaVazia()
{
    std::cout << "Running test_InsereFim_ListaVazia..." << std::endl;
    ListaEncadeada<int> lista;
    assert(lista.getQuantidade() == 0); // Ensure list starts empty

    lista.InsereFim(10);
    assert(lista.getQuantidade() == 1); // Check quantity after first insertion
    // Access the element to verify (using the operator[] which will be tested separately)
    // We assume operator[] works for this basic check, or we could traverse manually
    try
    {
        assert(lista[0] == 10);
    }
    catch (const char *msg)
    {                  // Catch the specific exception type thrown
        assert(false); // Should not throw for index 0
    }
    catch (...)
    {
        assert(false); // Catch any other unexpected exception
    }

    std::cout << "test_InsereFim_ListaVazia PASSED." << std::endl;
}

// Test inserting into a non-empty list
void test_InsereFim_ListaNaoVazia()
{
    std::cout << "Running test_InsereFim_ListaNaoVazia..." << std::endl;
    ListaEncadeada<std::string> lista;
    lista.InsereFim("primeiro");
    assert(lista.getQuantidade() == 1);

    lista.InsereFim("segundo");
    assert(lista.getQuantidade() == 2);

    lista.InsereFim("terceiro");
    assert(lista.getQuantidade() == 3);

    // Verify the elements (assuming operator[] works)
    try
    {
        assert(lista[0] == "primeiro");
        assert(lista[1] == "segundo");
        assert(lista[2] == "terceiro");
    }
    catch (const char *msg)
    {
        assert(false); // Should not throw for valid indices
    }
    catch (...)
    {
        assert(false); // Catch any other unexpected exception
    }

    std::cout << "test_InsereFim_ListaNaoVazia PASSED." << std::endl;
}

// Test the getQuantidade method
void test_GetQuantidade()
{
    std::cout << "Running test_GetQuantidade..." << std::endl;
    ListaEncadeada<double> lista;
    assert(lista.getQuantidade() == 0);

    lista.InsereFim(1.1);
    assert(lista.getQuantidade() == 1);

    lista.InsereFim(2.2);
    lista.InsereFim(3.3);
    assert(lista.getQuantidade() == 3);

    lista.Limpa(); // Test after clearing
    assert(lista.getQuantidade() == 0);

    std::cout << "test_GetQuantidade PASSED." << std::endl;
}

// Test the Limpa method
void test_Limpa()
{
    std::cout << "Running test_Limpa..." << std::endl;
    ListaEncadeada<int> lista;
    lista.InsereFim(1);
    lista.InsereFim(2);
    lista.InsereFim(3);
    assert(lista.getQuantidade() == 3);

    lista.Limpa();
    assert(lista.getQuantidade() == 0);

    // Try accessing after Limpa (should throw if attempted, but checking size is sufficient here)
    // Also, try inserting again after Limpa
    lista.InsereFim(100);
    assert(lista.getQuantidade() == 1);
    try
    {
        assert(lista[0] == 100);
    }
    catch (const char *msg)
    {
        assert(false); // Should not throw for index 0 after re-insertion
    }
    catch (...)
    {
        assert(false); // Catch any other unexpected exception
    }

    std::cout << "test_Limpa PASSED." << std::endl;
}

// Test accessing valid indices with non-const operator[]
void test_OperatorColchetes_AcessoValido()
{
    std::cout << "Running test_OperatorColchetes_AcessoValido..." << std::endl;
    ListaEncadeada<char> lista;
    lista.InsereFim('a');
    lista.InsereFim('b');
    lista.InsereFim('c');

    try
    {
        assert(lista[0] == 'a');
        assert(lista[1] == 'b');
        assert(lista[2] == 'c');
    }
    catch (const char *msg)
    {
        std::cerr << "Unexpected exception: " << msg << std::endl;
        assert(false); // Should not throw for valid indices
    }
    catch (...)
    {
        assert(false); // Catch any other unexpected exception
    }

    std::cout << "test_OperatorColchetes_AcessoValido PASSED." << std::endl;
}

// Test modifying elements using non-const operator[]
void test_OperatorColchetes_Modificacao()
{
    std::cout << "Running test_OperatorColchetes_Modificacao..." << std::endl;
    ListaEncadeada<int> lista;
    lista.InsereFim(1);
    lista.InsereFim(2);
    lista.InsereFim(3);

    try
    {
        lista[0] = 10;
        lista[1] = 20;
        lista[2] = 30;

        assert(lista[0] == 10);
        assert(lista[1] == 20);
        assert(lista[2] == 30);
    }
    catch (const char *msg)
    {
        std::cerr << "Unexpected exception: " << msg << std::endl;
        assert(false); // Should not throw during modification or access
    }
    catch (...)
    {
        assert(false); // Catch any other unexpected exception
    }

    std::cout << "test_OperatorColchetes_Modificacao PASSED." << std::endl;
}

// Test accessing invalid indices with non-const operator[] (should throw)
void test_OperatorColchetes_AcessoInvalido()
{
    std::cout << "Running test_OperatorColchetes_AcessoInvalido..." << std::endl;
    ListaEncadeada<int> lista;
    lista.InsereFim(5);

    bool threw_neg = false;
    try
    {
        int val = lista[-1]; // Access negative index
        (void)val;           // Avoid unused variable warning
    }
    catch (const char *msg)
    {
        threw_neg = true; // Expected throw
        std::cout << "  Caught expected exception for negative index: " << msg << std::endl;
    }
    catch (...)
    {
        assert(false); // Should only throw the specific char* exception
    }
    assert(threw_neg);

    bool threw_oot = false;
    try
    {
        int val = lista[1]; // Access index equal to size
        (void)val;          // Avoid unused variable warning
    }
    catch (const char *msg)
    {
        threw_oot = true; // Expected throw
        std::cout << "  Caught expected exception for out-of-bounds index: " << msg << std::endl;
    }
    catch (...)
    {
        assert(false); // Should only throw the specific char* exception
    }
    assert(threw_oot);

    bool threw_oot_large = false;
    try
    {
        int val = lista[100]; // Access index way out of bounds
        (void)val;            // Avoid unused variable warning
    }
    catch (const char *msg)
    {
        threw_oot_large = true; // Expected throw
        std::cout << "  Caught expected exception for large out-of-bounds index: " << msg << std::endl;
    }
    catch (...)
    {
        assert(false); // Should only throw the specific char* exception
    }
    assert(threw_oot_large);

    // Test on empty list
    ListaEncadeada<int> lista_vazia;
    bool threw_empty = false;
    try
    {
        int val = lista_vazia[0]; // Access index 0 on empty list
        (void)val;                // Avoid unused variable warning
    }
    catch (const char *msg)
    {
        threw_empty = true; // Expected throw
        std::cout << "  Caught expected exception for empty list access: " << msg << std::endl;
    }
    catch (...)
    {
        assert(false); // Should only throw the specific char* exception
    }
    assert(threw_empty);

    std::cout << "test_OperatorColchetes_AcessoInvalido PASSED." << std::endl;
}

// Helper function to test const operator[]
void testConstAccess(const ListaEncadeada<std::string> &constLista)
{
    std::cout << "  Running const access tests..." << std::endl;
    // Valid access
    try
    {
        assert(constLista[0] == "const_um");
        assert(constLista[1] == "const_dois");
    }
    catch (const char *msg)
    {
        std::cerr << "Unexpected exception during const access: " << msg << std::endl;
        assert(false);
    }
    catch (...)
    {
        assert(false); // Catch any other unexpected exception
    }
    std::cout << "  Const valid access PASSED." << std::endl;

    // Invalid access (negative)
    bool threw_neg_const = false;
    try
    {
        const std::string &val = constLista[-1];
        (void)val;
    }
    catch (const char *msg)
    {
        threw_neg_const = true;
        std::cout << "    Caught expected const exception for negative index: " << msg << std::endl;
    }
    catch (...)
    {
        assert(false); // Should only throw the specific char* exception
    }
    assert(threw_neg_const);

    // Invalid access (out of bounds)
    bool threw_oot_const = false;
    try
    {
        const std::string &val = constLista[2]; // Index equal to size
        (void)val;
    }
    catch (const char *msg)
    {
        threw_oot_const = true;
        std::cout << "    Caught expected const exception for out-of-bounds index: " << msg << std::endl;
    }
    catch (...)
    {
        assert(false); // Should only throw the specific char* exception
    }
    assert(threw_oot_const);
    std::cout << "  Const invalid access PASSED." << std::endl;
}

// Test accessing elements using const operator[]
void test_OperatorColchetesConst()
{
    std::cout << "Running test_OperatorColchetesConst..." << std::endl;
    ListaEncadeada<std::string> lista;
    lista.InsereFim("const_um");
    lista.InsereFim("const_dois");

    // Call helper function with a const reference to the list
    testConstAccess(lista);

    std::cout << "test_OperatorColchetesConst PASSED." << std::endl;
}

// --- Main Function to Run Tests ---
// int main()
// {
//     std::cout << "--- Starting ListaEncadeada Unit Tests ---" << std::endl;

//     test_InsereFim_ListaVazia();
//     std::cout << "-----------------------------------------" << std::endl;
//     test_InsereFim_ListaNaoVazia();
//     std::cout << "-----------------------------------------" << std::endl;
//     test_GetQuantidade();
//     std::cout << "-----------------------------------------" << std::endl;
//     test_Limpa();
//     std::cout << "-----------------------------------------" << std::endl;
//     test_OperatorColchetes_AcessoValido();
//     std::cout << "-----------------------------------------" << std::endl;
//     test_OperatorColchetes_Modificacao();
//     std::cout << "-----------------------------------------" << std::endl;
//     test_OperatorColchetes_AcessoInvalido();
//     std::cout << "-----------------------------------------" << std::endl;
//     test_OperatorColchetesConst(); // This implicitly tests const invalid access too via helper

//     std::cout << "--- All ListaEncadeada Unit Tests Completed ---" << std::endl;

//     return 0;
// }
