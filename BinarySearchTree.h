#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_BINARYSEARCHTREE_H

#include <iostream>
#include <fstream>

template <typename T>
class BinarySearchTree
{
public:
	BinarySearchTree();
	BinarySearchTree(const std::initializer_list<T> & list);
	~BinarySearchTree();
	auto size() const noexcept->size_t;
	auto insert(const T & value) noexcept -> bool;
	auto find(const T & value) const noexcept -> const T *;

	friend std::ostream & operator << (std::ostream & out, const BinarySearchTree<T> & tree)
	{
		out << "Direct:\n";
		tree.direct(tree.root_, out);
		out << "\nReverse:\n";
		tree.reverse(tree.root_, out);
		out << "\nSymmetric:\n";
		tree.symmetric(tree.root_, out);

		return out;
	}

	friend std::istream & operator >> (std::istream & in, BinarySearchTree<T> & tree)
	{
		size_t size;
		std::cout << "Enter the number of added elements: ";
		in >> size;
		T value;

		for (auto i = 0; i < size; i++)
		{
			std::cout << i + 1 << ">>";
			in >> value;
			tree.insert(value);
		}

		return in;
	}

	friend std::ifstream & operator >> (std::ifstream & in, BinarySearchTree<T> & tree)
	{
		size_t size = 0;
		in >> size;
		T value;

		for (auto i = 0; i < size; i++)
		{
			in >> value;
			tree.insert(value);
		}

		return in;
	}

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

		T value_;
		Node * left_;
		Node * right_;
	};

	Node * root_;
	size_t size_;

	void direct(Node* root, std::ostream & out) const;
	void reverse(Node* root, std::ostream & out) const;
	void symmetric(Node* root, std::ostream & out) const;
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree()
{
	root_ = nullptr;
	size_ = 0;
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const std::initializer_list<T>& list)
{
	root_ = nullptr;
	size_ = 0;

	for (auto elem : list)
		insert(elem);
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
auto BinarySearchTree<T>::insert(const T & value) noexcept -> bool
{
	if (find(value) != nullptr)
		return false;

	if (root_ == nullptr)
	{
		root_ = new Node(value);
		size_++;
		return true;
	}

	Node * node = root_, *parent = nullptr;

	while (node)
	{
		parent = node;

		if (value < parent->value_)
			node = parent->left_;
		else
			node = parent->right_;
	}

	if (value < parent->value_)
		parent->left_ = new Node(value);
	else
		parent->right_ = new Node(value);

	size_++;

	return true;
}

template<typename T>
auto BinarySearchTree<T>::find(const T & value) const noexcept -> const T *
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

	symmetric(node->left_, out);
	out << node->value_ << "  ";
	symmetric(node->right_, out);
}

#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_H
