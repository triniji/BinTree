#include <iostream>
#include "BinaryTree.h"
#include "Comparator.h"
using namespace std;

int main()
{
    cout << "В дерево будут добавлены следующие элементы (в порядке добавления)" << endl;
    BinaryTree<int, IntegerComparator> tree;
    for (int i = 0; i < 20; i++)
    {
        if (i & 1)
            tree.push(i - 10);
        else
            tree.push(i * 2);
        cout << (i & 1 == 1? i - 10: i * 2) << "  ";

    }
    cout << endl;
    std::vector<int> a;
    a = tree.to_vector();
    cout << "Получение всех элементов дерева в порядке возрастания" << endl;
    for (int i = 0; i < a.size(); i++)
        cout << a[i] << "  ";
        cout << endl << "Min: " << tree.front() << endl << "Max: " << tree.back();
    return 0;
}
