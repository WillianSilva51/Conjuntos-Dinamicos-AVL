#pragma once

#include "node/Node.hpp"
#include <iostream>
#include <queue>

template <class T>
class Set
{
    using NodePtr = Node<T> *;

private:
    Node<T> *root{nullptr};

    size_t size_m{0};

    Node<T> *clear(NodePtr root);

    int updateHeight(NodePtr node);

    int height(NodePtr node);

    int balance(NodePtr node);

    Node<T> *rightRotation(NodePtr p);

    Node<T> *leftRotation(NodePtr p);

    Node<T> *insert(NodePtr p, const T &key);

    bool contains(NodePtr root, const T &key) const;

    Node<T> *fixup_node(NodePtr p);

    void printInOrder(NodePtr node);

    void printPreOrder(NodePtr node);

    void printPostOrder(NodePtr node);

    void printLarge(NodePtr node);

    void bshow(NodePtr node, std::string heranca);

public:
    Set() = default;

    ~Set();

    size_t size() const;

    bool empty() const;

    void clear();

    void swap(Set<T> &other);

    void insert(const T &key);

    bool contains(const T &key) const;

    T minimum() const;

    T maximum() const;

    T successor() const;

    T predecessor() const;

    // Funções de impressão

    void printInOrder();

    void printPreOrder();

    void printPostOrder();

    void printLarge();

    /*  friend std::ostream &operator<<(std::ostream &os, const Set<T> &set)
      {
          os << "[";
          set.printInOrder();
          os << "]";
          return os;
      }
  */
    void bshow();
};

// -------------------------------------------Implementação da classe Set.------------------------------------------------------------------

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

    if (bal < -1 && height(p->left->left) > height(p->left->right))
    {
        return rightRotation(p);
    }
    else if (bal < -1 && height(p->left->left) < height(p->left->right))
    {
        p->left = leftRotation(p->left);
        return rightRotation(p);
    }
    else if (bal > 1 && height(p->right->right) > height(p->right->left))
    {
        return leftRotation(p);
    }
    else if (bal > 1 && height(p->right->right) < height(p->right->left))
    {
        p->right = rightRotation(p->right);
        return leftRotation(p);
    }

    return p;
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

    std::cout << std::endl;
}

template <class T>
void Set<T>::bshow()
{
    bshow(root, "");
}

template <class T>
void Set<T>::bshow(NodePtr node, std::string heranca)
{
    if (node != nullptr && (node->left != nullptr || node->right != nullptr))
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
    if (node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->left, heranca + "l");
}