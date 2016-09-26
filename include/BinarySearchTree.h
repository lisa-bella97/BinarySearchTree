//
// Created by Liza on 06.09.2016.
//

#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_BINARYSEARCHTREE_H

#include <iostream>
#include <fstream>
#include <limits>

template <typename T>
class BinarySearchTree;

template <typename T> auto operator >> (std::istream& in, BinarySearchTree<T>& tree) -> std::istream&;
template <typename T> auto operator << (std::ostream& out, const BinarySearchTree<T>& tree) -> std::ostream&;
template <typename T> auto operator >> (std::ifstream& in, BinarySearchTree<T>& tree) -> std::ifstream&;
template <typename T> auto operator << (std::ofstream& out, const BinarySearchTree<T>& tree) -> std::ofstream&;

template <typename T>
class BinarySearchTree
{
public:
    BinarySearchTree();
    BinarySearchTree(const std::initializer_list<T>& list);
    BinarySearchTree(const BinarySearchTree& tree);
    BinarySearchTree(BinarySearchTree&& tree);
    ~BinarySearchTree();

    auto size() const noexcept -> size_t;
    auto insert(const T& value) noexcept -> bool;
    auto find(const T& value) const noexcept -> const T*;

    auto operator = (const BinarySearchTree& tree) -> BinarySearchTree&;
    auto operator = (BinarySearchTree&& tree) -> BinarySearchTree&;
    auto operator == (const BinarySearchTree& tree) -> bool;

    friend auto operator >> <> (std::istream& in, BinarySearchTree<T>& tree) -> std::istream&;
    friend auto operator << <> (std::ostream& out, const BinarySearchTree<T>& tree) -> std::ostream&;
    friend auto operator >> <> (std::ifstream& in, BinarySearchTree<T>& tree) -> std::ifstream&;
    friend auto operator << <> (std::ofstream& out, const BinarySearchTree<T>& tree) -> std::ofstream&;

private:
    struct Node
    {
        Node(T value) : value_(value), left_(nullptr), right_(nullptr) {}

        ~Node()
        {
            if (left_)
                delete left_;

            if (right_)
                delete right_;
        }

        auto copy() -> Node *
        {
            auto newNode = new Node(value_);

            if (left_)
                newNode->left_ = left_->copy();

            if (right_)
                newNode->right_ = right_->copy();

            return newNode;
        }

        T value_;
        Node * left_;
        Node * right_;
    };

    Node * root_;
    size_t size_;

    void direct(Node * root, std::ostream & out) const;
    void reverse(Node * root, std::ostream & out) const;
    void symmetric(Node * root, std::ostream & out) const;
    auto equal(Node *firstNode, Node *secondTree) const -> bool;
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree()
{
    root_ = nullptr;
    size_ = 0;
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const std::initializer_list<T>& list) : BinarySearchTree()
{
    for (auto & elem : list)
        insert(elem);
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& tree) : size_(tree.size_)
{
    root_ = tree.root_->copy();
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& tree)
{
    size_ = tree.size_;
    root_ = tree.root_;
    tree.root_ = nullptr;
    tree.size_ = 0;
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    if (root_)
    {
        delete root_;
        size_ = 0;
    }
}

template<typename T>
auto BinarySearchTree<T>::size() const noexcept -> size_t
{
    return size_;
}

template<typename T>
auto BinarySearchTree<T>::insert(const T& value) noexcept -> bool
{
    if (root_ == nullptr)
    {
        root_ = new Node(value);
        size_++;
        return true;
    }

    Node * node = root_, * parent = nullptr;

    while (node)
    {
        parent = node;

        if (value < parent->value_)
            node = parent->left_;
        else if (value > parent->value_)
            node = parent->right_;
        else
            return false;
    }

    if (value < parent->value_)
        parent->left_ = new Node(value);
    else
        parent->right_ = new Node(value);

    size_++;

    return true;
}

template<typename T>
auto BinarySearchTree<T>::find(const T& value) const noexcept -> const T*
{
    Node * node = root_;

    while (node)
    {
        if (value < node->value_)
            node = node->left_;
        else if (value > node->value_)
            node = node->right_;
        else
            return &node->value_;
    }

    return nullptr;
}

template<typename T>
auto BinarySearchTree<T>::operator = (const BinarySearchTree<T>& tree) -> BinarySearchTree<T>&
{
    if (this == &tree)
        return *this;

    delete root_;
    root_ = tree.root_->copy();
    size_ = tree.size_;

    return *this;
}

template<typename T>
auto BinarySearchTree<T>::operator = (BinarySearchTree<T>&& tree) -> BinarySearchTree<T>&
{
    if (this == &tree)
        return *this;

    delete root_;
    size_ = tree.size_;
    root_ = tree.root_;
    tree.root_ = nullptr;
    tree.size_ = 0;

    return *this;
}

template<typename T>
auto BinarySearchTree<T>::operator == (const BinarySearchTree<T>& tree) -> bool
{
    if (this == &tree)
        return true;

    return equal(root_, tree.root_);
}

template<typename T>
auto operator >> (std::istream& in, BinarySearchTree<T>& tree) -> std::istream&
{
    if (tree.root_)
        delete tree.root_;

    size_t size = 0;
    std::cout << "size = ";

    while (!(in >> size))
    {
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "size = ";
    }

    T value;

    for (auto i = 0; i < size; i++)
    {
        do
        {
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << i + 1 << ">>";
        }
        while (!(in >> value));

        tree.insert(value);
    }

    return in;
}

template<typename T>
auto operator << (std::ostream& out, const BinarySearchTree<T>& tree) -> std::ostream&
{
    tree.symmetric(tree.root_, out);

    return out;
}

template<typename T>
auto operator >> (std::ifstream& in, BinarySearchTree<T>& tree) -> std::ifstream&
{
    if (tree.root_)
        delete tree.root_;

    T value;

    while (in >> value)
        tree.insert(value);

    return in;
}

template<typename T>
auto operator << (std::ofstream& out, const BinarySearchTree<T>& tree) -> std::ofstream&
{
    tree.direct(tree.root_, out);

    return out;
}

template<typename T>
void BinarySearchTree<T>::direct(Node * node, std::ostream & out) const
{
    if (!node)
        return;

    out << node->value_ << "  ";
    direct(node->left_, out);
    direct(node->right_, out);
}

template<typename T>
void BinarySearchTree<T>::reverse(Node* node, std::ostream & out) const
{
    if (!node)
        return;

    reverse(node->left_, out);
    reverse(node->right_, out);
    out << node->value_ << "  ";
}

template<typename T>
void BinarySearchTree<T>::symmetric(Node * node, std::ostream & out) const
{
    if (!node)
        return;

    symmetric(node->right_, out);
    out << node->value_ << "  ";
    symmetric(node->left_, out);
}

template<typename T>
auto BinarySearchTree<T>::equal(Node *firstNode, Node *secondNode) const -> bool
{
    if (firstNode)
        return secondNode && firstNode->value_ == secondNode->value_
            && equal(firstNode->left_, secondNode->left_) && equal(firstNode->right_, secondNode->right_);
    else
        return !secondNode;
}

#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_H