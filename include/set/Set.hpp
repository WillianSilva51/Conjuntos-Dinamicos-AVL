#pragma once

#include "node/Node.hpp"

#include <iostream>
#include <initializer_list>
#include <queue>
#include <stack>

/**
 * @brief Classe que implementa um conjunto dinâmico utilizando uma Árvore AVL.
 *
 * A Árvore AVL é uma árvore de busca binária auto-balanceável, onde a diferença
 * entre as alturas das subárvores esquerda e direita de qualquer nó é no máximo 1.
 * Isso garante que as operações de busca, inserção e remoção tenham complexidade
 * de tempo O(log n) no pior caso, onde n é o número de elementos no conjunto.
 *
 * @tparam T Tipo dos elementos armazenados no conjunto. Deve suportar operadores
 *           de comparação ( `<`, `==`, `>`).
 */
template <class T>
class Set
{
    /**
     * @brief Alias para um ponteiro para um nó da árvore.
     */
    using NodePtr = Node<T> *;

private:
    /**
     * @brief Ponteiro para o nó raiz da Árvore AVL.
     */
    Node<T> *root{nullptr};

    /**
     * @brief Número de elementos atualmente no conjunto.
     */
    size_t size_m{0};

    /**
     * @brief Realiza o balanceamento da árvore AVL após uma inserção ou remoção.
     *
     * Esta função é chamada recursivamente a partir do nó inserido/removido
     * (ou seu pai) até a raiz, verificando e corrigindo desbalanceamentos
     * através de rotações simples ou duplas.
     *
     * @param p Ponteiro para o nó a partir do qual o balanceamento deve ser verificado.
     * @return NodePtr Ponteiro para a raiz da subárvore balanceada.
     */
    Node<T> *fixup_node(NodePtr p);

    /**
     * @brief Função auxiliar recursiva para inserir um elemento na árvore.
     *
     * Percorre a árvore para encontrar a posição correta de inserção da chave.
     * Após a inserção, chama `fixup_node` para garantir o balanceamento da AVL.
     *
     * @param p Ponteiro para o nó raiz da subárvore onde a chave será inserida.
     * @param key A chave a ser inserida.
     * @return NodePtr Ponteiro para a raiz da subárvore modificada.
     */
    Node<T> *insert(NodePtr p, const T &key);

    /**
     * @brief Realiza o balanceamento da árvore AVL após uma remoção.
     *
     * Similar ao `fixup_node`, mas especificamente ajustado para o processo de
     * remoção, que pode exigir diferentes verificações de balanceamento.
     *
     * @param p Ponteiro para o nó a partir do qual o balanceamento deve ser verificado
     *          (geralmente o pai do nó removido ou o nó que o substituiu).
     * @return NodePtr Ponteiro para a raiz da subárvore balanceada.
     */
    Node<T> *fixup_deletion(NodePtr p);

    /**
     * @brief Função auxiliar recursiva para remover um elemento da árvore.
     *
     * Localiza o nó com a chave especificada. Trata os casos de remoção de nó
     * folha, nó com um filho ou nó com dois filhos (neste caso, substituindo
     * pelo sucessor). Após a remoção, chama `fixup_deletion` para balancear a árvore.
     *
     * @param p Ponteiro para o nó raiz da subárvore de onde a chave será removida.
     * @param key A chave a ser removida.
     * @return NodePtr Ponteiro para a raiz da subárvore modificada.
     */
    Node<T> *remove(NodePtr p, const T &key);

    /**
     * @brief Remove o nó sucessor de um dado nó e o retorna.
     *
     * Usado no processo de remoção de um nó com dois filhos. O sucessor é o menor
     * nó na subárvore direita.
     *
     * @param root Ponteiro para a raiz da subárvore onde o sucessor será procurado.
     * @param node O nó cujo sucessor deve ser removido. (Este parâmetro parece ser o nó a ser substituído, e `root` a sua subárvore direita)
     * @return NodePtr Ponteiro para o nó sucessor que foi removido da sua posição original.
     *         A função também modifica a árvore para remover o sucessor de sua posição original.
     */
    Node<T> *remove_successor(NodePtr root, NodePtr node);

    /**
     * @brief Função auxiliar recursiva para remover todos os nós da árvore.
     *
     * Realiza um percurso em pós-ordem para deletar todos os nós.
     *
     * @param root Ponteiro para o nó raiz da subárvore a ser limpa.
     * @return NodePtr Sempre retorna `nullptr` após limpar a subárvore.
     */
    Node<T> *clear(NodePtr root);

    /**
     * @brief Atualiza a altura de um nó.
     *
     * A altura de um nó é calculada como 1 + máximo(altura do filho esquerdo, altura do filho direito).
     * A altura de um nó folha é 0. A altura de `nullptr` é -1.
     *
     * @param node Ponteiro para o nó cuja altura será atualizada.
     * @return int A nova altura do nó.
     */
    int updateHeight(NodePtr node);

    /**
     * @brief Retorna a altura de um nó.
     *
     * @param node Ponteiro para o nó.
     * @return int A altura do nó. Retorna -1 se o nó for `nullptr`.
     */
    int height(NodePtr node);

    /**
     * @brief Calcula o fator de balanceamento de um nó.
     *
     * O fator de balanceamento é a diferença entre a altura da subárvore esquerda
     * e a altura da subárvore direita.
     *
     * @param node Ponteiro para o nó.
     * @return int O fator de balanceamento do nó.
     */
    int balance(NodePtr node);

    /**
     * @brief Realiza uma rotação simples à direita em torno do nó `p`.
     *
     * Usada para balancear a árvore quando ela está desbalanceada à esquerda.
     *
     * @param p Ponteiro para o nó que será a raiz da rotação (o nó desbalanceado).
     * @return NodePtr Ponteiro para a nova raiz da subárvore após a rotação.
     */
    Node<T> *rightRotation(NodePtr p);

    /**
     * @brief Realiza uma rotação simples à esquerda em torno do nó `p`.
     *
     * Usada para balancear a árvore quando ela está desbalanceada à direita.
     *
     * @param p Ponteiro para o nó que será a raiz da rotação (o nó desbalanceado).
     * @return NodePtr Ponteiro para a nova raiz da subárvore após a rotação.
     */
    Node<T> *leftRotation(NodePtr p);

    /**
     * @brief Função auxiliar recursiva para verificar se uma chave está contida na árvore.
     *
     * @param root Ponteiro para o nó raiz da subárvore onde a busca será realizada.
     * @param key A chave a ser procurada.
     * @return true Se a chave for encontrada.
     * @return false Se a chave não for encontrada.
     */
    bool contains(NodePtr root, const T &key) const;

    /**
     * @brief Insere todos os elementos da subárvore rooted em `node` no conjunto `result`.
     *
     * Função auxiliar usada para a operação de União de conjuntos.
     * Percorre a subárvore `node` e insere cada elemento em `result`.
     *
     * @param result O conjunto onde os elementos serão inseridos.
     * @param node O nó raiz da subárvore cujos elementos serão inseridos.
     */
    void insertUnion(Set<T> &result, const NodePtr &node) const;

    /**
     * @brief Função auxiliar recursiva para imprimir os elementos em ordem (in-order).
     *
     * @param node Ponteiro para o nó raiz da subárvore a ser impressa.
     */
    void printInOrder(NodePtr node);

    /**
     * @brief Função auxiliar recursiva para imprimir os elementos em pré-ordem (pre-order).
     *
     * @param node Ponteiro para o nó raiz da subárvore a ser impressa.
     */
    void printPreOrder(NodePtr node);

    /**
     * @brief Função auxiliar recursiva para imprimir os elementos em pós-ordem (post-order).
     *
     * @param node Ponteiro para o nó raiz da subárvore a ser impressa.
     */
    void printPostOrder(NodePtr node);

    /**
     * @brief Função auxiliar recursiva para imprimir os elementos em formato "grande".
     *
     * Provavelmente imprime os elementos em ordem decrescente (reverse in-order).
     *
     * @param node Ponteiro para o nó raiz da subárvore a ser impressa.
     */
    void printLarge(NodePtr node);

    /**
     * @brief Função auxiliar recursiva para exibir a estrutura da árvore.
     *
     * @param node Ponteiro para o nó raiz da subárvore a ser exibida.
     * @param heranca String usada para formatar a indentação e mostrar a hierarquia.
     */
    void bshow(NodePtr node, std::string heranca);

public:
    /**
     * @brief Construtor padrão. Cria um conjunto vazio.
     */
    Set() = default;

    /**
     * @brief Construtor de cópia. Cria um novo conjunto como cópia de `other`.
     *
     * Realiza uma cópia profunda dos elementos.
     *
     * @param other O conjunto a ser copiado.
     */
    Set(const Set &other);

    /**
     * @brief Construtor a partir de uma lista inicializadora.
     *
     * Cria um conjunto e insere todos os elementos da lista.
     *
     * @param list A lista de inicialização (`std::initializer_list<T>`).
     */
    Set(std::initializer_list<T> list);

    /**
     * @brief Destrutor. Libera toda a memória alocada pelos nós da árvore.
     */
    ~Set();

    /**
     * @brief Operador de atribuição por cópia.
     *
     * Substitui o conteúdo do conjunto atual pelo conteúdo de `other`.
     * Garante a autotribuição segura e libera a memória antiga antes de copiar.
     *
     * @param other O conjunto a ser copiado.
     */
    void operator=(const Set &other);

    /**
     * @brief Retorna o número de elementos no conjunto.
     *
     * @return size_t O número de elementos.
     */
    size_t size() const noexcept;

    /**
     * @brief Verifica se o conjunto está vazio.
     *
     * @return true Se o conjunto não contiver elementos.
     * @return false Caso contrário.
     */
    bool empty() const noexcept;

    /**
     * @brief Remove todos os elementos do conjunto.
     *
     * Após esta operação, `size()` retornará 0 e `empty()` retornará `true`.
     */
    void clear();

    /**
     * @brief Troca o conteúdo deste conjunto com o de `other`.
     *
     * Operação eficiente que apenas troca os ponteiros raiz e os tamanhos.
     *
     * @param other O outro conjunto com o qual trocar o conteúdo.
     */
    void swap(Set<T> &other);

    /**
     * @brief Insere uma chave no conjunto.
     *
     * Se a chave já existir, o conjunto não é modificado.
     * A árvore é balanceada após a inserção, se necessário.
     *
     * @param key A chave a ser inserida.
     */
    void insert(const T &key);

    /**
     * @brief Remove uma chave do conjunto.
     *
     * Se a chave não existir, o conjunto não é modificado.
     * A árvore é balanceada após a remoção, se necessário.
     *
     * @param key A chave a ser removida.
     */
    void erase(const T &key);

    /**
     * @brief Verifica se o conjunto contém uma determinada chave.
     *
     * @param key A chave a ser procurada.
     * @return true Se a chave estiver presente no conjunto.
     * @return false Caso contrário.
     */
    bool contains(const T &key) const;

    /**
     * @brief Retorna o menor elemento no conjunto.
     *
     * @return T O menor elemento.
     * @throw std::out_of_range Se o conjunto estiver vazio.
     */
    T minimum() const;

    /**
     * @brief Retorna o maior elemento no conjunto.
     *
     * @return T O maior elemento.
     * @throw std::out_of_range Se o conjunto estiver vazio.
     */
    T maximum() const;

    /**
     * @brief Retorna o sucessor de uma chave no conjunto.
     *
     * O sucessor é o menor elemento no conjunto que é maior que `key`.
     *
     * @param key A chave cujo sucessor é procurado.
     * @return T O sucessor de `key`.
     * @throw std::out_of_range Se `key` não existir no conjunto, ou se `key` for o maior elemento,
     *                          ou se o conjunto estiver vazio.
     */
    T successor(const T &key) const;

    /**
     * @brief Retorna o predecessor de uma chave no conjunto.
     *
     * O predecessor é o maior elemento no conjunto que é menor que `key`.
     *
     * @param key A chave cujo predecessor é procurado.
     * @return T O predecessor de `key`.
     * @throw std::out_of_range Se `key` não existir no conjunto, ou se `key` for o menor elemento,
     *                          ou se o conjunto estiver vazio.
     */
    T predecessor(const T &key) const;

    /**
     * @brief Retorna um novo conjunto que é a união deste conjunto com `other`.
     *
     * A união contém todos os elementos que estão em `this` ou em `other` (ou em ambos).
     *
     * @param other O outro conjunto.
     * @return Set<T> Um novo conjunto resultado da união.
     */
    Set Union(const Set &other) const;

    /**
     * @brief Retorna um novo conjunto que é a interseção deste conjunto com `other`.
     *
     * A interseção contém apenas os elementos que estão presentes em ambos, `this` e `other`.
     *
     * @param other O outro conjunto.
     * @return Set<T> Um novo conjunto resultado da interseção.
     */
    Set Intersection(const Set &other) const;

    /**
     * @brief Retorna um novo conjunto que é a diferença deste conjunto com `other`.
     *
     * A diferença (`this` - `other`) contém os elementos que estão em `this` mas não em `other`.
     *
     * @param other O outro conjunto.
     * @return Set<T> Um novo conjunto resultado da diferença.
     */
    Set Difference(const Set &other) const;

    /**
     * @brief Operador de união de conjuntos. Equivalente a `Union(other)`.
     *
     * @param other O outro conjunto.
     * @return Set<T> Um novo conjunto resultado da união.
     */
    Set operator+(const Set &other) const;

    /**
     * @brief Operador de interseção de conjuntos. Equivalente a `Intersection(other)`.
     *
     * @param other O outro conjunto.
     * @return Set<T> Um novo conjunto resultado da interseção.
     */
    Set operator*(const Set &other) const;

    /**
     * @brief Operador de diferença de conjuntos. Equivalente a `Difference(other)`.
     *
     * @param other O outro conjunto.
     * @return Set<T> Um novo conjunto resultado da diferença.
     */
    Set operator-(const Set &other) const;

    // Funções de impressão

    /**
     * @brief Imprime os elementos do conjunto em ordem crescente (in-order traversal).
     */
    void printInOrder();

    /**
     * @brief Imprime os elementos do conjunto em pré-ordem (pre-order traversal).
     * (Raiz, Esquerda, Direita)
     */
    void printPreOrder();

    /**
     * @brief Imprime os elementos do conjunto em pós-ordem (post-order traversal).
     * (Esquerda, Direita, Raiz)
     */
    void printPostOrder();

    /**
     * @brief Imprime os elementos do conjunto com base na altura de cada, será imprimida por nível.
     */
    void printLarge();

    /**
     * @brief Exibe a estrutura da árvore AVL de forma visual no console.
     *
     * Útil para depuração e visualização do balanceamento da árvore.
     */
    void bshow();
};

// -------------------------------------------Implementação da classe Set.------------------------------------------------------------------

template <class T>
Set<T>::Set(std::initializer_list<T> list) : Set()
{
    for (const auto &key : list)
        insert(key);
}

template <class T>
Set<T>::Set(const Set &other) : Set()
{
    insertUnion(*this, other.root);
}

template <class T>
Set<T>::~Set()
{
    clear();
}

template <class T>
void Set<T>::operator=(const Set &other)
{
    if (this != &other)
    {
        clear();
        insertUnion(*this, other.root);
    }
}

template <class T>
size_t Set<T>::size() const noexcept
{
    return size_m;
}

template <class T>
bool Set<T>::empty() const noexcept
{
    return root == nullptr;
}

template <class T>
Node<T> *Set<T>::clear(NodePtr root)
{
    if (root != nullptr)
    {
        root->left = clear(root->left);
        root->right = clear(root->right);

        delete root;
        return nullptr;
    }

    return root;
}

template <class T>
void Set<T>::clear()
{
    root = clear(root);
    size_m = 0;
}

template <class T>
void Set<T>::swap(Set<T> &other)
{
    std::swap(root, other.root);
    std::swap(size_m, other.size_m);
}

template <class T>
Node<T> *Set<T>::fixup_node(NodePtr p)
{
    p->height = updateHeight(p);

    int bal = balance(p);

    if (bal == -2 and height(p->left->left) > height(p->left->right))
    {
        return rightRotation(p);
    }
    else if (bal == -2 and height(p->left->left) < height(p->left->right))
    {
        p->left = leftRotation(p->left);
        return rightRotation(p);
    }
    else if (bal == 2 and height(p->right->right) > height(p->right->left))
    {
        return leftRotation(p);
    }
    else if (bal == 2 and height(p->right->right) < height(p->right->left))
    {
        p->right = rightRotation(p->right);
        return leftRotation(p);
    }

    return p;
}

template <class T>
Node<T> *Set<T>::insert(NodePtr p, const T &key)
{
    if (p == nullptr)
    {
        size_m++;
        return new Node<T>(key);
    }

    if (key == p->key)
        return p;
    else if (key < p->key)
        p->left = insert(p->left, key);
    else
        p->right = insert(p->right, key);

    p = fixup_node(p);

    return p;
}

template <class T>
void Set<T>::insert(const T &key)
{
    root = insert(root, key);
}

template <class T>
void Set<T>::erase(const T &key)
{
    root = remove(root, key);
}

template <class T>
Node<T> *Set<T>::fixup_deletion(NodePtr p)
{
    int bal = balance(p);

    if (bal == 2 and balance(p->right) >= 0)
        return leftRotation(p);

    if (bal == 2 and balance(p->right) < 0)
    {
        p->right = rightRotation(p->right);
        return leftRotation(p);
    }

    if (bal == -2 and balance(p->left) <= 0)
        return rightRotation(p);

    if (bal == -2 and balance(p->left) > 0)
    {
        p->left = leftRotation(p->left);
        return rightRotation(p);
    }

    p->height = updateHeight(p);

    return p;
}

template <class T>
Node<T> *Set<T>::remove(NodePtr p, const T &key)
{
    if (p == nullptr)
        return p;

    if (key < p->key)
        p->left = remove(p->left, key);
    else if (key > p->key)
        p->right = remove(p->right, key);
    else if (p->right == nullptr)
    {
        NodePtr child = p->left;
        delete p;
        size_m--;
        return child;
    }
    else
        p->right = remove_successor(p, p->right);

    p = fixup_deletion(p);

    return p;
}

template <class T>
Node<T> *Set<T>::remove_successor(NodePtr root, NodePtr node)
{
    if (node->left != nullptr)
        node->left = remove_successor(root, node->left);
    else
    {
        root->key = node->key;
        NodePtr aux = node->right;
        delete node;
        size_m--;
        return aux;
    }

    node = fixup_deletion(node);

    return node;
}

template <class T>
int Set<T>::updateHeight(NodePtr node)
{
    return 1 + std::max(height(node->left), height(node->right));
}

template <class T>
int Set<T>::height(NodePtr node)
{
    return (!node) ? 0 : node->height;
}

template <class T>
int Set<T>::balance(NodePtr node)
{
    return height(node->right) - height(node->left);
}

template <class T>
Node<T> *Set<T>::rightRotation(NodePtr p)
{
    NodePtr aux = p->left;
    p->left = aux->right;
    aux->right = p;

    p->height = updateHeight(p);
    aux->height = updateHeight(aux);

    return aux;
}

template <class T>
Node<T> *Set<T>::leftRotation(NodePtr p)
{
    NodePtr aux = p->right;
    p->right = aux->left;
    aux->left = p;

    p->height = updateHeight(p);
    aux->height = updateHeight(aux);

    return aux;
}

template <class T>
bool Set<T>::contains(NodePtr root, const T &key) const
{
    if (root == nullptr)
        return false;

    if (key == root->key)
        return true;
    else if (key < root->key)
        return contains(root->left, key);
    else
        return contains(root->right, key);
}

template <class T>
bool Set<T>::contains(const T &key) const
{
    return contains(root, key);
}

template <class T>
T Set<T>::minimum() const
{
    if (root == nullptr)
        throw std::runtime_error("Nao ha elementos no Set");

    NodePtr aux = root;
    while (aux->left != nullptr)
        aux = aux->left;

    return aux->key;
}

template <class T>
T Set<T>::maximum() const
{
    if (root == nullptr)
        throw std::runtime_error("Nao ha elementos no Set");

    NodePtr aux = root;
    while (aux->right != nullptr)
        aux = aux->right;

    return aux->key;
}

template <class T>
T Set<T>::successor(const T &key) const
{
    if (root == nullptr)
        throw std::runtime_error("Nao ha elementos no Set");

    NodePtr aux{root};
    NodePtr succ{nullptr};

    while (aux != nullptr)
    {
        if (key < aux->key)
        {
            succ = aux;
            aux = aux->left;
        }
        else if (key > aux->key)
            aux = aux->right;
        else
            break;
    }

    if (aux == nullptr)
        throw std::runtime_error("Elemento nao encontrado");

    if (aux->right != nullptr)
    {
        aux = aux->right;
        while (aux->left != nullptr)
            aux = aux->left;

        return aux->key;
    }

    if (succ == nullptr or succ->key <= key)
        throw std::runtime_error("Nao ha sucessor");

    return succ->key;
}

template <class T>
T Set<T>::predecessor(const T &key) const
{
    if (root == nullptr)
        throw std::runtime_error("Nao ha elementos no Set");

    NodePtr aux{root};
    NodePtr succ{nullptr};

    while (aux != nullptr)
    {
        if (key < aux->key)
            aux = aux->left;

        else if (key > aux->key)
        {
            succ = aux;
            aux = aux->right;
        }
        else
            break;
    }

    if (aux == nullptr)
        throw std::runtime_error("Elemento nao encontrado");

    if (aux->left != nullptr)
    {
        aux = aux->left;
        while (aux->right != nullptr)
            aux = aux->right;

        return aux->key;
    }

    if (succ == nullptr or succ->key >= key)
        throw std::runtime_error("Nao ha predecessor");

    return succ->key;
}

template <class T>
void Set<T>::insertUnion(Set<T> &result, const NodePtr &node) const
{
    if (node == nullptr)
        return;

    std::stack<NodePtr> nodes;
    nodes.push(node);

    while (!nodes.empty())
    {
        NodePtr atual = nodes.top();
        nodes.pop();

        result.insert(atual->key);

        if (atual->left != nullptr)
            nodes.push(atual->left);

        if (atual->right != nullptr)
            nodes.push(atual->right);
    }
}

template <class T>
Set<T> Set<T>::Union(const Set<T> &other) const
{
    Set<T> result;

    insertUnion(result, root);
    insertUnion(result, other.root);

    return result;
}

template <class T>
Set<T> Set<T>::Intersection(const Set<T> &other) const
{
    if (root == nullptr)
        return Set<T>();

    std::stack<NodePtr> nodes;
    nodes.push(root);

    Set<T> result;

    while (!nodes.empty())
    {
        NodePtr aux = nodes.top();
        nodes.pop();

        if (other.contains(aux->key))
            result.insert(aux->key);

        if (aux->left != nullptr)
            nodes.push(aux->left);

        if (aux->right != nullptr)
            nodes.push(aux->right);
    }

    return result;
}

template <class T>
Set<T> Set<T>::Difference(const Set<T> &other) const
{
    if (root == nullptr)
        return Set<T>();

    std::stack<NodePtr> nodes;
    nodes.push(root);

    Set<T> result;

    while (!nodes.empty())
    {
        NodePtr aux = nodes.top();
        nodes.pop();

        if (!other.contains(aux->key))
            result.insert(aux->key);

        if (aux->left != nullptr)
            nodes.push(aux->left);

        if (aux->right != nullptr)
            nodes.push(aux->right);
    }

    return result;
}

template <class T>
Set<T> Set<T>::operator+(const Set &other) const
{
    return Union(other);
}

template <class T>
Set<T> Set<T>::operator*(const Set &other) const
{
    return Intersection(other);
}

template <class T>
Set<T> Set<T>::operator-(const Set &other) const
{
    return Difference(other);
}

template <class T>
void Set<T>::printInOrder()
{
    printInOrder(root);
}

template <class T>
void Set<T>::printInOrder(NodePtr node)
{
    if (node == nullptr)
        return;

    else
    {
        printInOrder(node->left);
        std::cout << node->key << " ";
        printInOrder(node->right);
    }
}

template <class T>
void Set<T>::printPreOrder()
{
    printPreOrder(root);
}

template <class T>
void Set<T>::printPreOrder(NodePtr node)
{
    if (node == nullptr)
        return;

    else
    {
        std::cout << node->key << " ";
        printPreOrder(node->left);
        printPreOrder(node->right);
    }
}

template <class T>
void Set<T>::printPostOrder()
{
    printPostOrder(root);
}

template <class T>
void Set<T>::printPostOrder(NodePtr node)
{
    if (node == nullptr)
        return;

    else
    {
        printPostOrder(node->left);
        printPostOrder(node->right);
        std::cout << node->key << " ";
    }
}

template <class T>
void Set<T>::printLarge()
{
    printLarge(root);
}

template <class T>
void Set<T>::printLarge(NodePtr node)
{
    if (!node)
        return;

    std::queue<NodePtr> nodes;
    nodes.push(node);

    while (!nodes.empty())
    {
        NodePtr atual = nodes.front();
        nodes.pop();

        std::cout << atual->key << " ";

        if (atual->left != nullptr)
            nodes.push(atual->left);

        if (atual->right != nullptr)
            nodes.push(atual->right);
    }
}

template <class T>
void Set<T>::bshow()
{
    bshow(root, "");
}

template <class T>
void Set<T>::bshow(NodePtr node, std::string heranca)
{
    if (node != nullptr and (node->left != nullptr or node->right != nullptr))
        bshow(node->right, heranca + "r");

    for (int i = 0; i < (int)heranca.size() - 1; i++)
        std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");

    if (heranca != "")
        std::cout << (heranca.back() == 'r' ? "┌───" : "└───");

    if (node == nullptr)
    {
        std::cout << "#" << std::endl;
        return;
    }

    std::cout << node->key << std::endl;

    if (node != nullptr and (node->left != nullptr or node->right != nullptr))
        bshow(node->left, heranca + "l");
}