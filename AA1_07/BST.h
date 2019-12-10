#pragma once


struct BinaryNode
{
	int data;
	BinaryNode* left = nullptr;
	BinaryNode* right = nullptr;
};
class BST {
private:
	BinaryNode* root;

public:
	BST();
	~BST();
	void Delete(BinaryNode* node_);

	BinaryNode* Search(int value_);
	BinaryNode* Search(int value_, BinaryNode* node_);
	const bool Exist(int value_);
	void Insert(int value_);
	BinaryNode* Insert(int value_, BinaryNode* node_);
};


BST::BST()
{
}


BST::~BST()
{
	Delete(root);
}


void BST::Delete(BinaryNode* node_)
{
	if (node_ == nullptr)
		return;
	Delete(node_->left);
	Delete(node_->right);
	delete node_;
	node_ = nullptr;
}


BinaryNode* BST::Search(int value_)
{
	return Search(value_, root);
}


BinaryNode* BST::Search(int value_, BinaryNode* node_)
{
	if (node_ == nullptr)
		return nullptr;
	if (node_->data == value_) {
		return node_;
	}
	else if (node_->data > value_) {
		return Search(value_, node_->left);
	}
	else {
		return Search(value_, node_->right);
	}
	return nullptr;
}


const bool BST::Exist(int value_)
{
	return Search(value_, root) != nullptr;
}

void BST::Insert(int value_)
{
	root = Insert(value_, root);
}

BinaryNode* BST::Insert(int value_, BinaryNode* node_)
{
	if (node_ == nullptr) {
		BinaryNode* newNode = new BinaryNode();
		newNode->data = value_;
		return newNode;
	}
	else if (node_->data == value_) {
		return node_;
	}
	else if (node_->data > value_) {
		node_->left = Insert(value_, node_->left);
		return node_;
	}
	else {
		node_->right = Insert(value_, node_->right);
		return node_;
	}
}
