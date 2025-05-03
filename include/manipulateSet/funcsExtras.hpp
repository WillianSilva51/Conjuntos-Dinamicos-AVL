#pragma once

#include "set/Set.hpp"

template <typename U>
bool promptValue(const std::string &msg, U &out)
{
    std::cout << msg;
    if (!(std::cin >> out))
    {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Valor inválido.\n";
        return false;
    }
    return true;
}

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
            promptValue("Digite o elemento para encontrar o sucessor: ", elemento);
            std::cout << "Sucessor de " << elemento << ": " << set.successor(elemento) << std::endl;
            break;
        }
        case 4:
        {
            T elemento;
            promptValue("Digite o elemento para encontrar o predecessor: ", elemento);
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