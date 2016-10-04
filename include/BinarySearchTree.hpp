//
// Created by Liza on 06.09.2016.
//

#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_BINARYSEARCHTREE_HPP

#include <iostream>
#include <fstream>
#include <limits>
#include <memory>

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
    auto find(const T& value) const noexcept -> std::shared_ptr<T>;
    auto remove(const T& value) noexcept -> bool;

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
        Node() : left_(nullptr), right_(nullptr) {}
        Node(T value) : value_(value), left_(nullptr), right_(nullptr) {}

        ~Node()
        {
            left_ = nullptr;
            right_ = nullptr;
        }

        void copy(std::shared_ptr<Node>& node) const noexcept
        {
            if (value_ != node->value_)
                node->value_ = value_;

            if (left_)
            {
                if (!node->left_)
                    node->left_ = std::make_shared<Node>(left_->value_);

                left_->copy(node->left_);
            }
            else if (node->left_)
                node->left_ = nullptr;

            if (right_)
            {
                if (!node->right_)
                    node->right_ = std::make_shared<Node>(right_->value_);

                right_->copy(node->right_);
            }
            else if (node->right_)
                node->right_ = nullptr;
        }

        T value_;
        std::shared_ptr<Node> left_;
        std::shared_ptr<Node> right_;
    };

    std::shared_ptr<Node> root_;
    size_t size_;

    void direct(const std::shared_ptr<Node>& root, std::ostream & out) const noexcept;
    void reverse(const std::shared_ptr<Node>& root, std::ostream & out) const noexcept;
    void symmetric(const std::shared_ptr<Node>& root, std::ostream & out) const noexcept;
    auto equal(const std::shared_ptr<Node>& firstNode, const std::shared_ptr<Node>& secondTree) const noexcept -> bool;
    auto remove_r(const T& value, std::shared_ptr<Node>& node) noexcept -> bool;
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree() : root_(nullptr), size_(0) {}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const std::initializer_list<T>& list) : BinarySearchTree()
{
    for (auto & elem : list)
        insert(elem);
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& tree) : size_(tree.size_)
{
    if (tree.root_)
    {
        root_.reset(new Node);
        tree.root_->copy(root_);
    }
    else
        root_ = nullptr;
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
    root_ = nullptr;
    size_ = 0;
}

template<typename T>
auto BinarySearchTree<T>::size() const noexcept -> size_t
{
    return size_;
}

template<typename T>
auto BinarySearchTree<T>::insert(const T& value) noexcept -> bool
{
    if (!root_)
    {
        root_ = std::make_shared<Node>(value);
        size_++;
        return true;
    }

    std::shared_ptr<Node> node = root_, parent = nullptr;

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
        parent->left_ = std::make_shared<Node>(value);
    else
        parent->right_ = std::make_shared<Node>(value);

    size_++;

    return true;
}

template<typename T>
auto BinarySearchTree<T>::find(const T& value) const noexcept -> std::shared_ptr<T>
{
    auto node = root_;

    while (node)
    {
        if (value < node->value_)
            node = node->left_;
        else if (value > node->value_)
            node = node->right_;
        else
            return std::make_shared<T>(node->value_);
    }

    return nullptr;
}

template<typename T>
auto BinarySearchTree<T>::remove(const T& value) noexcept -> bool
{
    if (remove_r(value, root_))
    {
        size_--;
        return true;
    }

    return false;
}

template<typename T>
auto BinarySearchTree<T>::operator = (const BinarySearchTree<T>& tree) -> BinarySearchTree<T>&
{
    if (this == &tree)
        return *this;

    if (tree.root_)
    {
        root_.reset(new Node);
        tree.root_->copy(root_);
    }
    else
        root_ = nullptr;

    size_ = tree.size_;

    return *this;
}

template<typename T>
auto BinarySearchTree<T>::operator = (BinarySearchTree<T>&& tree) -> BinarySearchTree<T>&
{
    if (this == &tree)
        return *this;

    root_ = nullptr;
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
    tree.root_ = nullptr;
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
        } while (!(in >> value));

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
    tree.root_ = nullptr;
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
void BinarySearchTree<T>::direct(const std::shared_ptr<Node>& node, std::ostream & out) const noexcept
{
    if (!node)
        return;

    out << node->value_ << "  ";
    direct(node->left_, out);
    direct(node->right_, out);
}

template<typename T>
void BinarySearchTree<T>::reverse(const std::shared_ptr<Node>& node, std::ostream & out) const noexcept
{
    if (!node)
        return;

    reverse(node->left_, out);
    reverse(node->right_, out);
    out << node->value_ << "  ";
}

template<typename T>
void BinarySearchTree<T>::symmetric(const std::shared_ptr<Node>& node, std::ostream & out) const noexcept
{
    if (!node)
        return;

    symmetric(node->right_, out);
    out << node->value_ << "  ";
    symmetric(node->left_, out);
}

template<typename T>
auto BinarySearchTree<T>::equal(const std::shared_ptr<Node>& firstNode, const std::shared_ptr<Node>& secondNode) const noexcept -> bool
{
    if (firstNode)
        return secondNode && firstNode->value_ == secondNode->value_
               && equal(firstNode->left_, secondNode->left_) && equal(firstNode->right_, secondNode->right_);
    else
        return !secondNode;
}

template<typename T>
auto BinarySearchTree<T>::remove_r(const T& value, std::shared_ptr<Node>& node) noexcept -> bool
{
    if (!node)
        return false;

    if (value < node->value_)
        remove_r(value, node->left_);
    else if (value > node->value_)
        remove_r(value, node->right_);
    else
    {
        if (!node->left_)
        {
            std::shared_ptr<Node> old = node;
            node = old->right_;
        }
        else if (!node->right_)
        {
            std::shared_ptr<Node> old = node;
            node = old->left_;
        }
        else
        {
            auto min = node->right_;

            while (min->left_)
                min = min->left_;

            node->value_ = min->value_;
            remove_r(min->value_, node->right_);
        }

        return true;
    }
}

#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_HPP