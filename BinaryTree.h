#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED
#include <vector>

template<typename T, typename Comparator> class BinaryTree;
#include "Node.h"

template<typename T, typename Comparator>
class BinaryTree
{
protected:
    std::shared_ptr<Node<T, Comparator>> _root;
    int _size;
    void _inorder_walk(std::shared_ptr<Node<T, Comparator>> startNode, std::vector<T>& vector);
public:
    BinaryTree();
    void push(const T& element);
    int getSize() const;
    void push(std::vector<T>& elements);
    T front();
    T back();
    std::vector<T> to_vector();
};

template<typename T, typename Comparator>
BinaryTree<T, Comparator>::BinaryTree()
{
    _root = nullptr;
    _size = 0;
}

template<typename T, typename Comparator>
void BinaryTree<T, Comparator>::push(const T& element)
{
    std::shared_ptr<Node<T, Comparator>> current = _root;
    std::shared_ptr<Node<T, Comparator>> parrent = nullptr;

    while (current != nullptr)
    {
        parrent = current;
        if (Comparator::compare(element, current -> _data) == -1)
            current = current -> _left;
        else
            current = current -> _right;
    }

    std::shared_ptr<Node<T, Comparator>> node(new Node<T, Comparator>(element));
    if (parrent == nullptr)
        _root = node;
    else
    {
        node -> _parrent = parrent;
        if (Comparator::compare(element, parrent -> _data) == -1)
            parrent -> _left = node;
        else
            parrent -> _right = node;
    }
        _size++;
}

template<typename T, typename Comparator>
int BinaryTree<T, Comparator>::getSize() const
{
    return _size;
}

template<typename T, typename Comparator>
void BinaryTree<T, Comparator>::push(std::vector<T>& elements)
{
    for (int i = 0; i < elements.size(); i++)
    {
        push(elements[i]);
    }
}

template<typename T, typename Comparator>
T BinaryTree<T, Comparator>::front()
{
    if (_size > 0)
    {
        std::shared_ptr<Node<T, Comparator>> current = _root;
        while (current -> _left != nullptr)
            current = current -> _left;
        return current -> _data;
    }
}

template<typename T, typename Comparator>
T BinaryTree<T, Comparator>::back()
{
    if (_size > 0)
    {
        std::shared_ptr<Node<T, Comparator>> current = _root;
        while (current -> _right != nullptr)
            current = current -> _right;
        return current -> _data;
    }
}

template<typename T, typename Comparator>
std::vector<T> BinaryTree<T, Comparator>::to_vector()
{
    std::vector<T> result;
    _inorder_walk(_root, result);
    return result;
}

template<typename T, typename Comparator>
void BinaryTree<T, Comparator>::_inorder_walk(std::shared_ptr<Node<T, Comparator>> startNode, std::vector<T>& vector)
{
    if (startNode != nullptr)
    {
        _inorder_walk(startNode -> _left, vector);
        vector.push_back(startNode -> _data);
        _inorder_walk(startNode -> _right, vector);
    }
}
#endif // BINARYTREE_H_INCLUDED


/* TODO By Serg Gerasimov
add(T element) +
add(std::vector<T> elements) +
get(std::function<bool(T)> f)
iterator()
to_string +
remove(std::function<bool(T)> f)
exists(T element)
remove(T element)
*/
