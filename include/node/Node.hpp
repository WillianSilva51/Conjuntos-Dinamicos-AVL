#pragma once

/**
 * @brief Estrutura que representa um nó em uma árvore binária, comumente utilizada em árvores AVL.
 *
 * Esta estrutura genérica (template) `Node` é projetada para encapsular os dados
 * de um nó individual dentro de uma estrutura de árvore. Cada nó contém uma chave
 * (o valor armazenado), a altura do nó na árvore (fundamental para algoritmos
 * de balanceamento, como os empregados em árvores AVL), e ponteiros para
 * seus nós filhos, esquerdo e direito.
 *
 * @tparam T O tipo de dado da chave a ser armazenada no nó. Este tipo deve
 *           suportar operações de comparação se o nó for utilizado em árvores
 *           de busca ordenadas.
 *
 * ### Membros:
 *
 * - `key` (do tipo `T`):
 *   Armazena o valor principal ou a chave de identificação do nó.
 *
 * - `height` (do tipo `int`):
 *   Representa a altura do nó dentro da árvore. A altura é definida como a
 *   maior distância (número de arestas) deste nó até uma folha em sua subárvore.
 *   Por convenção, um nó folha tem altura 1. A altura de um subárvore vazia
 *   (representada por um ponteiro `nullptr`) é frequentemente considerada 0
 *   para simplificar os cálculos de balanceamento.
 *
 * - `left` (ponteiro para `Node<T>`):
 *   Aponta para o nó filho à esquerda. Se o nó não possuir um filho esquerdo,
 *   este ponteiro será `nullptr`.
 *
 * - `right` (ponteiro para `Node<T>`):
 *   Aponta para o nó filho à direita. Se o nó não possuir um filho direito,
 *   este ponteiro será `nullptr`.
 *
 * ### Construtor:
 *
 * `Node(const T &key, const int &height = 1, Node<T> *left = nullptr, Node<T> *right = nullptr)`
 *
 *   Constrói uma nova instância de `Node`.
 *
 *   @param key Referência constante para a chave que será armazenada no nó.
 *   @param height (Opcional) Valor inteiro para a altura inicial do nó.
 *                 O valor padrão é `1`, assumindo que um novo nó é, inicialmente,
 *                 uma folha.
 *   @param left (Opcional) Ponteiro para o nó filho esquerdo.
 *                O valor padrão é `nullptr`.
 *   @param right (Opcional) Ponteiro para o nó filho direito.
 *                 O valor padrão é `nullptr`.
 *
 *   O construtor utiliza uma lista de inicialização de membros para definir os
 *   valores `key`, `height`, `left` e `right` com os parâmetros fornecidos.
 */
template <typename T>
struct Node
{
    T key;
    int height;
    Node<T> *left;
    Node<T> *right;

    Node(const T &key, const int &height = 1, Node<T> *left = nullptr, Node<T> *right = nullptr)
        : key(key), height(height), left(left), right(right) {}
};