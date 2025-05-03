#include <iostream>
#include <vector>

#include "set/Set.hpp"
#include "manipulateSet/ManipulateSet.hpp"

using namespace std;

enum Opcoes // Enumeração para as opções do menu
{
    CRIAR_SET = 1,
    MANIPULAR_SET,
    IMPRIMIR_SET,
    TROCAR_SET,
    UNIR_SET,
    INTERSECAO_SET,
    DIFERENCA_SET,
    SAIR
};

Set<int> &getConjunto(vector<Set<int>> &conjuntos)
{
    size_t index;
    std::cout << "Escolha o conjunto (1 a " << conjuntos.size() << "): ";
    std::cin >> index;

    if (index < 1 || index > conjuntos.size())
        throw std::out_of_range("Conjunto inválido. Tente novamente.");

    return conjuntos[index - 1];
}

void imprimirConjuntos(vector<Set<int>> &conjuntos)
{
    std::cout << "-----------------------------------------------------------" << std::endl;
    std::cout << "Conjuntos Disponíveis:" << std::endl;
    for (size_t i = 0; i < conjuntos.size(); i++)
    {
        std::cout << "Conjunto " << i + 1 << ": { ";
        conjuntos[i].printInOrder();
        std::cout << "}" << std::endl;
    }
    std::cout << "-----------------------------------------------------------" << std::endl;
}

void printConjunto(Set<int> &conjunto)
{
    while (true)
    {
        std::cout << "Escolha a forma que será impressa: " << std::endl;
        std::cout << "[1] - InOrder" << std::endl;
        std::cout << "[2] - PreOrder" << std::endl;
        std::cout << "[3] - PostOrder" << std::endl;
        std::cout << "[4] - Level Order" << std::endl;
        std::cout << "[5] - Árvore Binária" << std::endl;
        std::cout << "[6] - Voltar" << std::endl;

        int opcao;
        std::cin >> opcao;
        std::cin.ignore();

        switch (opcao)
        {
        case 1:
            cout << "InOrder: ";
            conjunto.printInOrder();
            std::cout << std::endl;
            break;
        case 2:
            std::cout << "PreOrder: ";
            conjunto.printPreOrder();
            std::cout << std::endl;
            break;
        case 3:
            std::cout << "PostOrder: ";
            conjunto.printPostOrder();
            std::cout << std::endl;
            break;
        case 4:
            std::cout << "Level Order: ";
            conjunto.printLarge();
            std::cout << std::endl;
            break;
        case 5:
            std::cout << "Árvore Binária: " << std::endl;
            conjunto.bshow();
            std::cout << std::endl;
            break;
        case 6:
            return; // Voltar para o menu de manipulação
        default:
            std::cout << "Opção inválida. Tente novamente." << std::endl;
            break;
        }
        std::cout << std::endl;
    }
}

void salvarConjunto(const Set<int> &conjunto, vector<Set<int>> &conjuntos)
{
    while (true)
    {
        std::cout << "Deseja salvar o conjunto? (s/n): ";
        char resposta;
        std::cin >> resposta;
        std::cin.ignore();

        switch (tolower(resposta))
        {
        case 'n':
            return;

        case 's':
        {
            conjuntos.push_back(conjunto);

            std::cout << "Conjunto salvo com sucesso" << std::endl;

            return;
        }
        default:
            std::cout << "Opção inválida" << std::endl;
            break;
        }
    }
}

void criarSet(vector<Set<int>> &conjuntos)
{
    std::cout << "Criando novo conjunto..." << std::endl;

    Set<int> novoConjunto;

    while (true)
    {
        std::cout << "Digite um elemento para adicionar ao conjunto (ou 's' para sair): ";
        std::string input;
        std::cin >> input;

        if (input == "s")
            break;

        try
        {
            int elemento = std::stoi(input);
            novoConjunto.insert(elemento);
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "Entrada inválida. Tente novamente." << std::endl;
        }
    }

    salvarConjunto(novoConjunto, conjuntos);
}

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    std::cout << "Bem-vindo ao programa de manipulação de Conjuntos Dinâmicos" << std::endl;

    vector<Set<int>> conjuntos({Set<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}),
                                Set<int>({1, 2, 3, 77, 50, 12}),
                                Set<int>({15, 16, 17, 18, 19, 20, 21})});

    while (true)
    {
        imprimirConjuntos(conjuntos);

        std::cout << "Escolha uma opção:" << std::endl;
        std::cout << "[1] - Criar Conjunto" << std::endl;
        std::cout << "[2] - Manipular Conjunto" << std::endl;
        std::cout << "[3] - Imprimir Conjunto" << std::endl;
        std::cout << "[4] - Trocar Conjuntos" << std::endl;
        std::cout << "[5] - União De Conjuntos" << std::endl;
        std::cout << "[6] - Interseção De Conjuntos" << std::endl;
        std::cout << "[7] - Diferença De Conjuntos" << std::endl;
        std::cout << "[8] - Sair" << std::endl;

        int opcao;
        std::cout << "Digite a opção desejada: ";
        std::cin >> opcao;
        std::cin.ignore();

        switch (opcao)
        {
        case CRIAR_SET:
        {
            criarSet(conjuntos);
            break;
        }

        case MANIPULAR_SET:
        {
            std::cout << "Escolha o conjunto para manipular: " << endl;

            try
            {
                imprimirConjuntos(conjuntos);

                manipulate(getConjunto(conjuntos));
                std::cout << "Conjunto manipulado com sucesso." << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }

            break;
        }

        case IMPRIMIR_SET:
        {
            imprimirConjuntos(conjuntos);

            std::cout << "Escolha o conjunto para imprimir: " << endl;
            try
            {
                printConjunto(getConjunto(conjuntos));
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }

            break;
        }

        case TROCAR_SET:
        {
            try
            {
                imprimirConjuntos(conjuntos);

                std::cout << "Escolha o primeiro conjunto para trocar: " << endl;
                Set<int> &conjunto1 = getConjunto(conjuntos);

                std::cout << "Escolha o segundo conjunto para trocar: " << endl;
                Set<int> &conjunto2 = getConjunto(conjuntos);

                conjunto1.swap(conjunto2);
                std::cout << "Conjuntos trocados com sucesso." << endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }

            break;
        }

        case UNIR_SET:
        {
            try
            {
                imprimirConjuntos(conjuntos);

                std::cout << "Escolha o primeiro conjunto para unir: " << endl;
                Set<int> &conjunto1 = getConjunto(conjuntos);

                std::cout << "Escolha o segundo conjunto para unir: " << endl;
                Set<int> &conjunto2 = getConjunto(conjuntos);

                Set<int> uniao = conjunto1.Union(conjunto2);

                std::cout << "União dos conjuntos: { ";
                uniao.printInOrder();
                std::cout << "}" << std::endl;

                salvarConjunto(uniao, conjuntos);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }

            break;
        }

        case INTERSECAO_SET:
        {
            try
            {
                imprimirConjuntos(conjuntos);

                std::cout << "Escolha o primeiro conjunto para fazer a interseção: " << endl;
                Set<int> &conjunto1 = getConjunto(conjuntos);

                std::cout << "Escolha o segundo conjunto para fazer a interseção: " << endl;
                Set<int> &conjunto2 = getConjunto(conjuntos);

                Set<int> intersec = conjunto1.Intersection(conjunto2);

                std::cout << "Interseção dos conjuntos: { ";
                intersec.printInOrder();
                std::cout << "}" << std::endl;

                salvarConjunto(intersec, conjuntos);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }

            break;
        }

        case DIFERENCA_SET:
        {
            try
            {
                imprimirConjuntos(conjuntos);

                std::cout << "Escolha o primeiro conjunto para fazer a diferença: " << endl;
                Set<int> &conjunto1 = getConjunto(conjuntos);

                std::cout << "Escolha o segundo conjunto para fazer a diferença: " << endl;
                Set<int> &conjunto2 = getConjunto(conjuntos);

                Set<int> diff = conjunto1.Difference(conjunto2);

                std::cout << "Diferença dos conjuntos: { ";
                diff.printInOrder();
                std::cout << "}" << std::endl;

                salvarConjunto(diff, conjuntos);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }

            break;
        }

        case SAIR:
        {
            std::cout << "Saindo do programa..." << std::endl;
            return 0;
        }

        default:
            std::cout << "Opção inválida. Tente novamente." << std::endl;
            std::cin.clear();
            std::cin.ignore();
            break;
        }
    }

    return 0;
}