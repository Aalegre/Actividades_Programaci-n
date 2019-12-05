#pragma once
#include <iostream>
#include <stack>

template <typename T>
class BinaryTree
{
	struct BinaryNode
	{
		BinaryNode* left = nullptr;
		BinaryNode* right = nullptr;
		T data;
	};
	BinaryNode * root;

public:
	BinaryTree();
	~BinaryTree();

	void Delete(BinaryNode* node_);
	const void PreOrder();
	const void PreOrder(const BinaryNode* node_);
	const void PreOrderI();
	const void InOrder();
	const void InOrder(const BinaryNode* node_);
	const void PostOrder();
	const void PostOrder(const BinaryNode* node_);
	const int GetNumberNodes();
	const int GetNumberNodes(const BinaryNode * node_);
	const int GetNumberNodesI();
	const int Height();
	const int Height(const BinaryNode* node_);
};


template<typename T>
BinaryTree<T>::BinaryTree()
{
	BinaryNode * temp = new BinaryNode;
	BinaryNode * temp2 = new BinaryNode;
	root = temp;
	temp = new BinaryNode;
	root->left = temp;
	temp = new BinaryNode;
	root->right = temp;
	temp->left = new BinaryNode;
	temp->right = temp2;
	temp2->left = new BinaryNode;
}

template<>
BinaryTree<char>::BinaryTree()
{
	BinaryNode * temp = new BinaryNode;
	BinaryNode * temp2 = new BinaryNode;
	root = temp;
	root->data = 'A';
	temp = new BinaryNode;
	temp->data = 'B';
	root->left = temp;
	temp = new BinaryNode;
	temp->data = 'C';
	root->right = temp;
	temp->left = new BinaryNode;
	temp->left->data = 'D';
	temp->right = temp2;
	temp->right->data = 'E';
	temp2->left = new BinaryNode;
	temp2->left->data = 'F';
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
	Delete(root);
	root = nullptr;
}

template<typename T>
inline void BinaryTree<T>::Delete(BinaryNode* node_)
{
	if (node_ == nullptr)
		return;
	Delete(node_->left);
	Delete(node_->right);
	delete node_;
	node_ = nullptr;
}

template<typename T>
const void BinaryTree<T>::PreOrder()
{
	std::cout << "Printing tree PreOrder:" << std::endl;
	PreOrder(root);
	std::cout << std::endl;
	return void();
}
template<typename T>
const void BinaryTree<T>::PreOrder(const BinaryNode* node_)
{
	if (node_ == nullptr)
		return void();

	std::cout << node_->data;
	PreOrder(node_->left);
	PreOrder(node_->right);


	return void();
}

template<typename T>
const void BinaryTree<T>::PreOrderI()
{
	std::cout << "Printing tree PreOrder Iterative:" << std::endl;


	if (root == nullptr)
		return void();

	std::stack<BinaryNode* > nodes;
	BinaryNode* temp;
	nodes.push(root);
	while (!nodes.empty()) {
		temp = nodes.top();
		std::cout << temp->data;
		nodes.pop();
		if (temp->right != nullptr)
			nodes.push(temp->right);
		if (temp->left != nullptr)
			nodes.push(temp->left);
	}

	std::cout << std::endl;
	return void();
}

template<typename T>
const void BinaryTree<T>::InOrder()
{
	std::cout << "Printing tree InOrder:" << std::endl;
	InOrder(root);
	std::cout << std::endl;
	return void();
}
template<typename T>
const void BinaryTree<T>::InOrder(const BinaryNode* node_)
{
	if (node_ == nullptr)
		return void();

	InOrder(node_->left);
	std::cout << node_->data;
	InOrder(node_->right);


	return void();
}

template<typename T>
const void BinaryTree<T>::PostOrder()
{
	std::cout << "Printing tree PostOrder:" << std::endl;
	PostOrder(root);
	std::cout << std::endl;
	return void();
}
template<typename T>
const void BinaryTree<T>::PostOrder(const BinaryNode* node_)
{
	if (node_ == nullptr)
		return void();

	PostOrder(node_->left);
	PostOrder(node_->right);

	std::cout << node_->data;

	return void();
}

template<typename T>
const int BinaryTree<T>::GetNumberNodes()
{
	return GetNumberNodes(root);
}

template<typename T>
const int BinaryTree<T>::GetNumberNodes(const BinaryNode* node_)
{
	if (node_ == nullptr)
		return 0;

	return GetNumberNodes(node_->left) + GetNumberNodes(node_->right) + 1;
}

template<typename T>
const int BinaryTree<T>::GetNumberNodesI()
{
	if (root == nullptr)
		return 0;

	int count = 0;
	std::stack<BinaryNode* > nodes;
	BinaryNode* temp;
	nodes.push(root);
	while (!nodes.empty()) {
		temp = nodes.top();
		nodes.pop();
		count++;
		if (temp->left != nullptr)
			nodes.push(temp->left);
		if (temp->right != nullptr)
			nodes.push(temp->right);
	}
	return count;
}

template<typename T>
const int BinaryTree<T>::Height()
{
	return Height(root);
}
template<typename T>
const int BinaryTree<T>::Height(const BinaryNode* node_)
{
	if (node_ == nullptr)
		return 0;
	int lH = Height(node_->left);
	int rH = Height(node_->right);
	if (lH > rH)
		return lH + 1;
	else return rH + 1;
}