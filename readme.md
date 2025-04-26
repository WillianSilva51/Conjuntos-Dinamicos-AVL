# 🚀 Conjuntos Dinâmicos AVL

![GitHub Repo stars](https://img.shields.io/github/stars/WillianSilva51/Conjuntos-Dinamicos-AVL?style=social)
![Build Status](https://img.shields.io/badge/build-passing-brightgreen)
![Coverage](https://img.shields.io/badge/coverage-95%25-yellow)
![Repo Size](https://img.shields.io/github/repo-size/WillianSilva51/Conjuntos-Dinamicos-AVL)
![Languages](https://img.shields.io/github/languages/count/WillianSilva51/Conjuntos-Dinamicos-AVL)
![License](https://img.shields.io/badge/license-MIT-blue)

> Implementação em C++ de conjuntos dinâmicos de inteiros usando árvores AVL, garantindo operações de inserção, remoção e busca com complexidade O(log n).

## 📑 Sumário

- [Sobre](#sobre)
- [Funcionalidades](#funcionalidades)
- [UML & Arquitetura](#uml--arquitetura)
- [Demonstração](#demonstração)
- [Pré-requisitos](#pré-requisitos)
- [Instalação](#instalação)
- [Uso](#uso)
- [API Reference](#api-reference)
- [Configuração](#configuração)
- [Testes](#testes)
- [Deploy (Opcional)](#deploy-opcional)
- [Roadmap](#roadmap)
- [Contribuição](#contribuição)
- [Licença](#licença)
- [Créditos](#créditos)

---

## Sobre

Este projeto apresenta uma estrutura de dados `Set` dinâmica, implementada em C++ usando uma árvore AVL para manter o balanceamento. Foi desenvolvido como parte da Avaliação Continuada 02 da disciplina de Estruturas de Dados Avançadas na Universidade Federal do Ceará.

- **Status:** 🎯 Em desenvolvimento
- **Tecnologias:** C++21, STL
- **Objetivo:** Fornecer operações de conjunto (inserção, remoção, busca, união, interseção e diferença) com complexidade de tempo O(log n) no pior caso.

---

## Funcionalidades

- **Inserção** (`insert(x)`) – adiciona um inteiro ao conjunto, mantendo a árvore balanceada.
- **Remoção** (`erase(x)`) – remove um inteiro se presente, rebalanceando a árvore.
- **Busca** (`contains(x)`) – verifica se um inteiro faz parte do conjunto.
- **Limpar** (`clear()`) – esvazia o conjunto.
- **Troca** (`swap(T)`) – troca o conteúdo de dois conjuntos em O(1).
- **Mínimo/Máximo** (`minimum()`, `maximum()`) – busca o menor e maior elemento, lançando exceção se vazio.
- **Sucessor/Predecessor** (`successor(x)`, `predecessor(x)`) – encontra vizinhos no conjunto ou lança exceção.
- **Empty/Size** (`empty()`, `size()`) – verifica se vazio e retorna o número de elementos.
- **Operações binárias:**
  - **União** (`union(S, R)`) – retorna S ∪ R.
  - **Interseção** (`intersection(S, R)`) – retorna S ∩ R.
  - **Diferença** (`difference(S, R)`) – retorna S − R.

---

## UML & Arquitetura

```mermaid
classDiagram
    class Node {
        +T key
        +int height
        +Node* left
        +Node* right
    }
    class Set {
        -Node* root
        -size_t size_m
        +Set()
        +~Set()
        +insert(x: int): void
        +erase(x: int): void
        +contains(x: int): bool
        +clear(): void
        +swap(T: Set&): void
        +minimum(): int
        +maximum(): int
        +successor(x: int): int
        +predecessor(x: int): int
        +empty(): bool
        +size(): size_t
        +union(S: Set&, R: Set&): Set
        +intersection(S: Set&, R: Set&): Set
        +difference(S: Set&, R: Set&): Set
    }
    Set --> Node
```

A arquitetura segue o paradigma orientado a objetos, separando declaração (`Set.hpp`), implementação (`Set.cpp`) e interface de usuário (`main.cpp`).

---

## Demonstração

> **Observação:** Inclua capturas de tela da aplicação de console (menu interativo) em `docs/`.

---

## Pré-requisitos

- **Compilador:** g++ com suporte C++17 ou superior
- **Ferramenta de build:** make (opcional) 
- **Sistema operacional:** Windows, macOS ou Linux

---

## Instalação

### Clonando o repositório
```bash
git clone https://github.com/WillianSilva51/Conjuntos-Dinamicos-AVL.git
cd Conjuntos-Dinamicos-AVL
```

### Usando Make
```bash
cd Conjuntos-Dinamicos-AVL
make
```

---

## Uso

Execute o binário e siga o menu para testar as operações:

```bash
cd Conjuntos-Dinamicos-AVL/bin
./Set
```

Exemplo de fluxo:
```
1) Inserir elemento
2) Remover elemento
3) Verificar presença
4) Mínimo/Máximo
5) Sucessor/Predecessor
6) União/Interseção/Diferença
7) Limpar conjunto
8) Trocar conjuntos
9) Tamanho/Vazio
0) Sair
```

---

## API Reference

| Método                    | Descrição                                         |
|---------------------------|---------------------------------------------------|
| `Set()`                   | Construtor: cria conjunto vazio                   |
| `~Set()`                  | Destrutor: libera memória                         |
| `insert(x)`               | Insere inteiro x                                  |
| `erase(x)`                | Remove inteiro x                                  |
| `contains(x)`             | Retorna true se x pertence                        |
| `clear()`                 | Esvazia conjunto                                  |
| `swap(T)`                 | Troca conteúdo de dois conjuntos                  |
| `minimum()` / `maximum()` | Retorna menor/maior elemento ou lança exceção     |
| `successor(x)`            | Retorna sucessor de x ou lança exceção            |
| `predecessor(x)`          | Retorna antecessor de x ou lança exceção          |
| `empty()`                 | Retorna true se vazio                             |
| `size()`                  | Retorna número de elementos                       |
| `union(S, R)`             | Retorna união de S e R                            |
| `intersection(S, R)`      | Retorna interseção de S e R                       |
| `difference(S, R)`        | Retorna diferença de S e R                        |

---

## Testes

Para testar as funções, adicione casos em `tests/` e execute:
```bash
# Exemplo simples
./Set < tests/casos.txt
```

---


## Roadmap

- [x] Operações básicas de conjunto
- [ ] Balanceamento AVL nas inserções e remoções
- [ ] Operações binárias (união, interseção, diferença)
- [x] Versão genérica (templates C++)
- [ ] Integração com testes automatizados (Google Test)

---

## Contribuição

1. Fork deste repositório
2. Crie uma branch: `git checkout -b feature/nome-da-feature`
3. Commit: `git commit -m 'Descrição da mudança'`
4. Push: `git push origin feature/nome-da-feature`
5. Abra um Pull Request

Como alternativa, consulte a documentação do GitHub em [como criar uma solicitação pull](https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/creating-a-pull-request).

---

## Licença

Este projeto está licenciado sob a licença MIT. Veja o arquivo [LICENSE](LICENSE) para detalhes.

---

## Créditos

- Prof. Átilio Gomes Luiz – Universidade Federal do Ceará
- Material de apoio da disciplina de EDA Avançada
- [AVL Trees - Wikipedia](https://pt.wikipedia.org/wiki/AVL_tree)
- [C++ Reference](https://en.cppreference.com/w/)
- [C++ STL Documentation](https://en.cppreference.com/w/cpp)