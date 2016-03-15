#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <memory>

template<typename T, typename Comparator>
class Node
{
    friend class BinaryTree<T, Comparator>;
protected:
    Node(const T& data);
    T _data;
    std::shared_ptr<Node> _left;
    std::shared_ptr<Node> _right;
    std::shared_ptr<Node> _parrent;
public:
    T getData();
};

template<typename T, typename Comparator>
Node<T, Comparator>::Node(const T& data)
{
    _data = data;
    _left = nullptr;
    _right = nullptr;
    _parrent = nullptr;
}

template<typename T, typename Comparator>
T Node<T, Comparator>::getData()
{
    return _data;
}
#endif // NODE_H_INCLUDED
