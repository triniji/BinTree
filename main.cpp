#include <iostream>
#include "BinaryTree.h"
#include "Comparator.h"
using namespace std;


void displayTree(BinaryTree<int, IntegerComparator>& tree)
{
    vector<int> tmp = tree.to_vector();
    for (int i = 0; i < tmp.size(); i++)
    {
        cout << tmp[i] << " ";
    }
    cout << "\n";
    return;
}

int main()
{
    BinaryTree<int, IntegerComparator> tree;
    vector<int> a;
    for (int i = -6; i < 10; i++)
        a.push_back(i);
    tree.push(a);
    cout << "tree: ";
    displayTree(tree);

    BinaryTree<int, IntegerComparator> secondTree;
    secondTree = tree;
    cout << "secondTree: ";
    displayTree(secondTree);
    secondTree.push(100);
    secondTree.push(-40);
    secondTree.push(200);
    secondTree.push(-50);
    secondTree.push(-25);
    secondTree.push(75);
    cout << "Min: " << secondTree.getMinimal() << "\nMax: " << secondTree.getMaximal() << "\n";
    displayTree( secondTree);
    displayTree(tree);
    tree = secondTree;
    displayTree(secondTree);

    return 0;
}
