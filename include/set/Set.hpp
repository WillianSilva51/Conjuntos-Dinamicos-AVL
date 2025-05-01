#pragma once

#include "node/Node.hpp"

#include <iostream>
#include <initializer_list>
#include <queue>
#include <stack>

template <class T>
class Set
{
    using NodePtr = Node<T> *;

private:
    Node<T> *root{nullptr};

    size_t size_m{0};

    Node<T> *insert(NodePtr p, const T &key);

    Node<T> *remove(NodePtr p, const T &key);

    Node<T> *clear(NodePtr root);

    int updateHeight(NodePtr node);

    int height(NodePtr node);

    int balance(NodePtr node);

    Node<T> *rightRotation(NodePtr p);

    Node<T> *leftRotation(NodePtr p);

    bool contains(NodePtr root, const T &key) const;

    Node<T> *fixup_node(NodePtr p);

    void insertUnion(Set<T> &result, const NodePtr &node) const;

    void printInOrder(NodePtr node);

    void printPreOrder(NodePtr node);

    void printPostOrder(NodePtr node);

    void printLarge(NodePtr node);

    void bshow(NodePtr node, std::string heranca);

public:
    Set() = default;

    Set(const Set &other) : Set()
    {
        insertUnion(*this, other.root);
    }

    Set(std::initializer_list<T> list);

    ~Set();

    size_t size() const;

    bool empty() const;

    void clear();

    void swap(Set<T> &other);

    void insert(const T &key);

    void erase(const T &key);

    bool contains(const T &key) const;

    T minimum() const;

    T maximum() const;

    T successor(const T &key) const;

    T predecessor(const T &key) const;

    Set Union(const Set &other) const;

    Set Intersection(const Set &other) const;

    Set Difference(const Set &other) const;

    Set operator+(const Set &other) const
    {
        return Union(other);
    }

    Set operator*(const Set &other) const
    {
        return Intersection(other);
    }

    Set operator-(const Set &other) const
    {
        return Difference(other);
    }

    // Funções de impressão

    void printInOrder();

    void printPreOrder();

    void printPostOrder();

    void printLarge();

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
Set<T>::~Set()
{
    clear();
}

template <class T>
size_t Set<T>::size() const
{
    return size_m;
}

template <class T>
bool Set<T>::empty() const
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
Node<T> *Set<T>::remove(NodePtr p, const T &key)
{
    return p;
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
Node<T> *Set<T>::fixup_node(NodePtr p)
{
    p->height = updateHeight(p);

    int bal = balance(p);

    if (bal < -1 and height(p->left->left) > height(p->left->right))
    {
        return rightRotation(p);
    }
    else if (bal < -1 and height(p->left->left) < height(p->left->right))
    {
        p->left = leftRotation(p->left);
        return rightRotation(p);
    }
    else if (bal > 1 and height(p->right->right) > height(p->right->left))
    {
        return leftRotation(p);
    }
    else if (bal > 1 and height(p->right->right) < height(p->right->left))
    {
        p->right = rightRotation(p->right);
        return leftRotation(p);
    }

    return p;
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

    std::queue<NodePtr> nodes;
    nodes.push(node);

    while (!nodes.empty())
    {
        NodePtr atual = nodes.front();
        nodes.pop();

        if (atual == nullptr)
            continue;

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
        std::cout << "Nao ha nodes" << std::endl;

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