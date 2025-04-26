#include <iostream>

#include "set/Set.hpp"

using namespace std;

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Set<int> tree;

    for (int i = 1; i <= 15; i++)
    {
        tree.insert(i);
        tree.bshow();
        cout << "_________________________" << endl;
    }

    cout << "InOrder: ";
    tree.printInOrder();
    cout << endl;

    cout << "PreOrder: ";
    tree.printPreOrder();
    cout << endl;

    cout << "PostOrder: ";
    tree.printPostOrder();
    cout << endl;

    cout << "Level Order: ";
    tree.printLarge();
    cout << endl;

    cout << "Tamanho: " << tree.size() << endl;

    cout << "Contains 5: " << (tree.contains(5) ? "true" : "false") << endl;

    cout << "max: " << tree.maximum() << endl;

    cout << "min: " << tree.minimum() << endl;

    //    cout << tree << endl;

    return 0;
}