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
    tree.push(40);
    tree.push(25);
    tree.push(31);
    tree.push(44);
    tree.push(-5);
    tree.push(7);
    tree.push(81);
    tree.push(34);
    tree.push(45);
    tree.push(15);
    tree.push(19);
    tree.push(12);
    tree.push(-2);
    tree.push(18);
    tree.push(4);
    tree.push(8);
    tree.push(28);
    cout << "tree (size = " << tree.getSize() << "):\n"; displayTree(tree);
    BinaryTree<int, IntegerComparator> copyTree = tree;
    cout << "copyTree (size = " << copyTree.getSize() << "):\n"; displayTree(copyTree);
    tree.pop(7);
    tree.pop(25);
    tree.pop(40);
    tree.pop(15);
    tree.pop(-5);
    cout << "tree (size = " << tree.getSize() << "):\n"; displayTree(tree);
    cout << "Test filter. Tree (with size = " << copyTree.getSize() << "):\n"; displayTree(copyTree); cout << "WTF? o_O\n";
    auto func = [](int i){return(!(i & 1));};
    tree = copyTree.filter(func);
    cout << "Filter: x mod 2 = 0\n"; displayTree(tree);
    cout << "Tree:\n"; displayTree(copyTree);
    copyTree.pop(func);
    cout << "Delete elements like 2*z\n";
    cout << "Now tree:\n"; displayTree(copyTree);
    return 0;
}
