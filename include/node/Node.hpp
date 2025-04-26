#pragma once

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