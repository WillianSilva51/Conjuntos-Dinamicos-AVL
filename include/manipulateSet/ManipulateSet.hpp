#pragma once

#include "set/Set.hpp"

template <typename T>
void funcsExtra(Set<T> &set)
{
    while (true)
    {
        int funcaoEspecial;

        std::cout
            << "Escolha uma função especial:" << std::endl;
        std::cout << "[1] - Max" << std::endl;
        std::cout << "[2] - Min" << std::endl;
        std::cout << "[3] - Sucessor" << std::endl;
        std::cout << "[4] - Predecessor" << std::endl;
        std::cout << "[5] - Voltar" << std::endl;

        std::cin >> funcaoEspecial;

        switch (funcaoEspecial)
        {
        case 1:
        {
            std::cout << "Max: " << set.maximum() << std::endl;
            break;
        }
        case 2:
        {
            std::cout << "Min: " << set.minimum() << std::endl;
            break;
        }
        case 3:
        {
            T elemento;
            std::cout << "Digite o elemento para encontrar o sucessor: ";
            std::cin >> elemento;
            std::cout << "Sucessor de " << elemento << ": " << set.successor(elemento) << std::endl;
            break;
        }
        case 4:
        {
            T elemento;
            std::cout << "Digite o elemento para encontrar o predecessor: ";
            std::cin >> elemento;
            std::cout << "Predecessor de " << elemento << ": " << set.predecessor(elemento) << std::endl;
            break;
        }
        case 5:
        {
            return; // Voltar para o menu de manipulação
        }
        default:
            std::cout << "Opção inválida. Tente novamente." << std::endl;
            break;
        }
    }
}

template <typename T>
void manipulate(Set<T> &set)
{
    while (true)
    {
        int opcao;

        std::cout << "-----------------------------------------------------------" << std::endl;
        std::cout << "Conjunto atual: { ";
        set.printInOrder();
        std::cout << "}" << std::endl;
        std::cout << "-----------------------------------------------------------" << std::endl;

        std::cout << "Escolha uma opção: " << std::endl;
        std::cout << "[1] - Adicionar elemento" << std::endl;
        std::cout << "[2] - Remover elemento" << std::endl;
        std::cout << "[3] - Verificar se contém elemento" << std::endl;
        std::cout << "[4] - Limpar conjunto" << std::endl;
        std::cout << "[5] - Funções Especiais" << std::endl;
        std::cout << "[6] - Sair" << std::endl;

        std::cin >> opcao;

        switch (opcao)
        {
        case 1:
        {
            T elemento;
            std::cout << "Digite o elemento a ser adicionado: ";
            std::cin >> elemento;
            set.insert(elemento);
            std::cout << "Elemento " << elemento << " adicionado." << std::endl;
            break;
        }
        case 2:
        {
            T elemento;
            std::cout << "Digite o elemento a ser removido: ";
            std::cin >> elemento;
            set.erase(elemento);
            std::cout << "Elemento " << elemento << " removido." << std::endl;
            break;
        }
        case 3:
        {
            T elemento;
            std::cout << "Digite o elemento a ser verificado: ";
            std::cin >> elemento;
            if (set.contains(elemento))
                std::cout << "O conjunto contém o elemento." << std::endl;
            else
                std::cout << "O conjunto não contém o elemento." << std::endl;
            break;
        }
        case 4:
        {
            cout << "Tem certeza que deseja limpar o conjunto? (s/n): ";
            char resposta;

            std::cin >> resposta;
            if (tolower(resposta) == 's')
            {
                set.clear();
                std::cout << "Conjunto limpo." << std::endl;
            }
            else if (tolower(resposta) == 'n')
            {
                std::cout << "Operação cancelada." << std::endl;
                break;
            }
            else
            {
                std::cout << "Opção inválida. Operação cancelada." << std::endl;
                break;
            }

            set.clear();
            break;
        }
        case 5:
        {
            funcsExtra(set);
            break;
        }
        case 6:
        {
            return; // Sair do loop
        }
        default:
            std::cout << "Opção inválida. Tente novamente." << std::endl;
            break;
        }
    }
}