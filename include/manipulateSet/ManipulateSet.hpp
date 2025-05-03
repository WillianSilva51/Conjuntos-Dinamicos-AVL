#pragma once

#include "set/Set.hpp"
#include "manipulateSet/funcsExtras.hpp"

template <typename T>
void manipulate(Set<T> &set)
{
    int opcao;
    do
    {
        std::cout << "-----------------------------------------------------------" << std::endl;
        std::cout << "Conjunto atual: { ";
        set.printInOrder();
        std::cout << "}" << std::endl;
        std::cout << "Tamanho do conjunto: " << set.size() << std::endl;
        std::cout << "Conjunto vazio? " << (set.empty() ? "Sim" : "Não") << std::endl;
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
            promptValue("Digite o elemento a ser adicionado: ", elemento);

            set.insert(elemento);
            std::cout << "Elemento " << elemento << " adicionado." << std::endl;
            break;
        }
        case 2:
        {
            T elemento;
            promptValue("Digite o elemento a ser removido: ", elemento);

            set.erase(elemento);
            std::cout << "Elemento " << elemento << " removido." << std::endl;
            break;
        }
        case 3:
        {
            T elemento;
            promptValue("Digite o elemento a ser verificado: ", elemento);

            if (set.contains(elemento))
                std::cout << "O conjunto contém o elemento." << std::endl;
            else
                std::cout << "O conjunto não contém o elemento." << std::endl;
            break;
        }
        case 4:
        {
            std::cout << "Tem certeza que deseja limpar o conjunto? (s/n): ";
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
            break;
        }
        case 5:
        {
            funcsExtra(set);
            break;
        }
        default:
            std::cout << "Opção inválida. Tente novamente." << std::endl;
            std::cin.clear();
            std::cin.ignore();
            break;
        }
    } while (opcao != 6);
}