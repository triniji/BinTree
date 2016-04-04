#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED
#include <vector>
#include <memory>
#include <functional>

template<typename T, typename Comparator>
class BinaryTree
{
protected:
    struct Node;
    std::shared_ptr<Node> _root;
    int _size;
    void _to_vector(const std::shared_ptr<Node>& startNode, std::vector<T>& vector) const;
    void _copySubTree(const std::shared_ptr<Node>& fromTree, std::shared_ptr<Node>& toTree);
    std::shared_ptr<Node>& _search(const T& element) const
    {
        std::shared_ptr<Node> current = _root;
        while (current != nullptr)
        {
            if (Comparator::compare(element, current->_data) == -1)
                current = current->_left;
            else
                if (Comparator::compare(element, current->_data) == 1)
                    current = current->_right;
                else
                    if (Comparator::equals(element, current->_data))
                        return current;
                    else
                        current = current->_right;
        }
        return current;
    };
    void _filter(BinaryTree<T, Comparator>& result, const std::shared_ptr<Node>& ptr, std::function<bool(T)>& f) const;

public:
    BinaryTree();
    BinaryTree(const BinaryTree<T, Comparator>& tree);
    ~BinaryTree();
    void push(const T& element);
    int getSize() const;
    void push(const std::vector<T>& elements);
    T getMinimal() const;
    T getMaximal() const;
    std::vector<T> to_vector() const;
    bool exists(const T& element) const;
    BinaryTree<T, Comparator>& operator=(const BinaryTree& tree);
    void erase();
    void pop(const T& element);
    BinaryTree<T, Comparator> filter(std::function<bool(T)> f) const;
    void pop(std::function<bool(T)> f);
};

template<typename T, typename Comparator>
BinaryTree<T, Comparator>::~BinaryTree()
{
    _root = nullptr;
}

template <typename T, typename Comparator>
struct BinaryTree<T, Comparator>::Node
{
    T _data;
    std::shared_ptr<Node> _left;
    std::shared_ptr<Node> _right;
    std::shared_ptr<Node> _parent;
};

template<typename T, typename Comparator>
BinaryTree<T, Comparator>::BinaryTree()
{
    _root = nullptr;
    _size = 0;
}
template<typename T, typename Comparator>
BinaryTree<T, Comparator>::BinaryTree(const BinaryTree<T, Comparator>& tree)
{
    *this = tree;
}

template<typename T, typename Comparator>
void BinaryTree<T, Comparator>::push(const T& element)
{
    std::shared_ptr<Node> current = _root;
    std::shared_ptr<Node> parent = nullptr;

    while (current != nullptr)
    {
        parent = current;
        if (Comparator::compare(element, current->_data) == -1)
            current = current->_left;
        else
            if (Comparator::compare(element, current->_data) == 1)
                current = current->_right;
            else
                if (!Comparator::equals(element, current->_data))
                    current = current->_right;
                else
                    return;
    }

    std::shared_ptr<Node> node(new Node);
    node->_data = element;
    if (parent == nullptr)
        _root = node;
    else
    {
        node->_parent = parent;
        if (Comparator::compare(element, parent->_data) == -1)
            parent->_left = node;
        else
            parent->_right = node;
    }
        _size++;
}

template<typename T, typename Comparator>
int BinaryTree<T, Comparator>::getSize() const
{
    return _size;
}

template<typename T, typename Comparator>
void BinaryTree<T, Comparator>::push(const std::vector<T>& elements)
{
    for (int i = 0; i < elements.size(); i++)
    {
        push(elements[i]);
    }
}

template<typename T, typename Comparator>
T BinaryTree<T, Comparator>::getMinimal() const
{
    if (_size > 0)
    {
        std::shared_ptr<Node> current = _root;
        while (current->_left != nullptr)
            current = current->_left;
        return current->_data;
    }
}

template<typename T, typename Comparator>
T BinaryTree<T, Comparator>::getMaximal() const
{
    if (_size > 0)
    {
        std::shared_ptr<Node> current = _root;
        while (current->_right != nullptr)
            current = current->_right;
        return current->_data;
    }
}

template<typename T, typename Comparator>
std::vector<T> BinaryTree<T, Comparator>::to_vector() const
{
    std::vector<T> result;
    _to_vector(_root, result);
    return result;
}

template<typename T, typename Comparator>
void BinaryTree<T, Comparator>::_to_vector(const std::shared_ptr<Node>& startNode, std::vector<T>& vector) const
{
    if (startNode != nullptr)
    {
        _to_vector(startNode->_left, vector);
        vector.push_back(startNode->_data);
        _to_vector(startNode->_right, vector);
    }
}

template<typename T, typename Comparator>
bool BinaryTree<T, Comparator>::exists(const T& element) const
{
    if (_search(element) == nullptr)
        return false;
    return true;
}


template<typename T, typename Comparator>
BinaryTree<T, Comparator>& BinaryTree<T, Comparator>::operator=(const BinaryTree& tree)
{
    if (&tree == this)
        return *this;
    erase();
    if (tree._size != 0)
    {
        _size = tree._size;
        std::shared_ptr<Node> node(new Node);
        node->_data = tree._root->_data;
        _root = node;
        _copySubTree(tree._root, _root);
    }
    return *this;
}

template<typename T, typename Comparator>
void BinaryTree<T, Comparator>::erase()
{
    _root = nullptr;
    _size = 0;
}

template<typename T, typename Comparator>
void BinaryTree<T, Comparator>::_copySubTree(const std::shared_ptr<Node>& fromTree, std::shared_ptr<Node>& toTree)
{
    if (fromTree->_left != nullptr)
    {
        std::shared_ptr<Node> node(new Node);
        node->_data = fromTree->_left->_data;
        node->_parent = toTree;
        toTree->_left = node;
        _copySubTree(fromTree->_left, node);
    }


    if (fromTree->_right != nullptr)
    {
        std::shared_ptr<Node> node(new Node);
        node->_data = fromTree->_right->_data;
        node->_parent = toTree;
        toTree->_right = node;
        _copySubTree(fromTree->_right, node);
    }
}

template<typename T, typename Comparator>
void BinaryTree<T, Comparator>::pop(const T& element)
{
    std::shared_ptr<Node> forDeleting = _search(element);
    if (forDeleting == nullptr)
        return;

    _size--;

    // There're no childrens
    if ((forDeleting->_left == nullptr) && (forDeleting->_right == nullptr))
    {
        if (forDeleting == _root)
            _root = nullptr;
        else
            if (forDeleting->_parent->_left == forDeleting)
                forDeleting->_parent->_left = nullptr;
            else
                forDeleting->_parent->_right = nullptr;
    }

    //There is only one children
    else
        if ((forDeleting->_left == nullptr) ^ (forDeleting->_right == nullptr))
        {
            if (forDeleting == _root)
            {
                _root = forDeleting->_left == nullptr ? forDeleting->_right : forDeleting->_left;
                _root->_parent = nullptr;
            }
            else
            {
                std::shared_ptr<Node> newChildren = forDeleting->_left == nullptr ? forDeleting->_right : forDeleting->_left;
                newChildren->_parent = forDeleting->_parent;
                if (forDeleting->_parent->_left == forDeleting)
                    forDeleting->_parent->_left = newChildren;
                else
                    forDeleting->_parent->_right = newChildren;
            }
        }

        //There are two childrens
        else
        {
            std::shared_ptr<Node> replacement = forDeleting->_right;
            while (replacement->_left != nullptr)
                replacement = replacement->_left;
            if (replacement->_parent->_left == replacement)
            {
                replacement->_parent->_left = replacement->_right;
                if (replacement->_right != nullptr)
                    replacement->_right->_parent = replacement->_parent;
            }
            replacement->_parent = forDeleting->_parent;
            if (forDeleting == _root)
            {
                _root = replacement;
                _root->_left = forDeleting->_left;
                _root->_left->_parent = replacement;
                if (forDeleting->_right != replacement)
                {
                    _root->_right = forDeleting->_right;
                    forDeleting->_right->_parent = replacement;
                }
            }
            else
            {
                if (forDeleting->_parent->_left == forDeleting)
                    forDeleting->_parent->_left = replacement;
                else
                    forDeleting->_parent->_right = replacement;
                replacement->_left = forDeleting->_left;
                forDeleting->_left->_parent = replacement;
                if (forDeleting->_right != replacement)
                {
                    replacement->_right = forDeleting->_right;
                    forDeleting->_right->_parent = replacement;
                }
            }
        }
}

template<typename T, typename Comparator>
BinaryTree<T, Comparator> BinaryTree<T, Comparator>::filter(std::function<bool(T)> f) const
{
    BinaryTree<T, Comparator> result;
    _filter (result, _root, f);
    return result;
}

template<typename T, typename Comparator>
void BinaryTree<T, Comparator>::_filter(BinaryTree<T, Comparator>& result, const std::shared_ptr<Node>& ptr, std::function<bool(T)>& f) const
{
    if (ptr != nullptr)
    {
        if (f(ptr->_data))
            result.push(ptr->_data);
        _filter(result, ptr->_left, f);
        _filter(result, ptr->_right, f);
    }
}

template<typename T, typename Comparator>
void BinaryTree<T, Comparator>::pop(std::function<bool(T)> f)
{
    std::vector<T> tmp = filter(f).to_vector();
    for (int i = 0; i < tmp.size(); i++)
        pop(tmp[i]);
}

#endif // BINARYTREE_H_INCLUDED


/* TODO By Serg Gerasimov
add(T element) +
add(std::vector<T> elements) +
get(std::function<bool(T)> f) +
iterator()
to_string +
remove(std::function<bool(T)> f)
exists(T element) +
remove(T element) +
*/
