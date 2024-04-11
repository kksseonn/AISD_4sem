#include <iostream>
#include <stdexcept>
#include "BinarySearchTree.h"

BinarySearchTree::Node* BinarySearchTree::copyTree(Node* root) {
		if (root == nullptr) {
			return nullptr;
		}
		Node* newNode = new Node(root->data);
		newNode->left = copyTree(root->left);
		newNode->right = copyTree(root->right);
		return newNode;
	}

BinarySearchTree::Node* BinarySearchTree::minValueNode(Node* node) {
	Node* current = node;
	while (current && current->left != nullptr)
		current = current->left;
	return current;
}

void BinarySearchTree::eraseRecursive(Node*& node, const int key) {
	if (!node) {
		return;
	}
	if (key < node->data) {
		eraseRecursive(node->left, key);
	}
	else if (key > node->data) {
		eraseRecursive(node->right, key);
	}
	else {
		if (node->left == nullptr) {
			Node* temp = node->right;
			delete node;
			node = temp;
		}
		else if (node->right == nullptr) {
			Node* temp = node->left;
			delete node;
			node = temp;
		}
		else {
			node->data = minValueNode(node->right)->data;
			eraseRecursive(node->right, node->data);
		}
	}
}

void BinarySearchTree::destroyRecursive(Node* node) {
	if (node) {
		destroyRecursive(node->left);
		destroyRecursive(node->right);
		delete node;
	}
}

void BinarySearchTree::printRecursive(Node* root, const std::string& prefix, bool isLeft) const {
	if (root) {
		std::cout << prefix;

		std::cout << (isLeft ? "|--" : "\\--");

		std::cout << root->data << std::endl;

		printRecursive(root->left, prefix + (isLeft ? "|   " : "    "), true);
		printRecursive(root->right, prefix + (isLeft ? "|   " : "    "), false);
	}
}

bool BinarySearchTree::containsRecursive(Node* node, const int key) const {
	if (node) {
		if (node->data == key) return true;
		else if (node->data < key) return containsRecursive(node->right, key);
		else return containsRecursive(node->left, key);
	}
	else
		return false;
}

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& other) {
	root = copyTree(other.root);
}

BinarySearchTree::~BinarySearchTree() {
	destroyRecursive(root);
}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other) {
	if (this != &other) {
		destroyRecursive(root);
		root = copyTree(other.root);
	}
	return *this;
}

BinarySearchTree::Node* BinarySearchTree::getRoot() const { return root; }

void BinarySearchTree::print() const {
	std::cout << "Tree: " << std::endl;
	printRecursive(root);
}

bool BinarySearchTree::insert(int key) {
	if (!root) {
		root = new Node(key);
		return true;
	}

	Node* tmp = root;
	while (tmp && tmp->data != key) {
		if (tmp->data > key) {
			if (tmp->left)
				tmp = tmp->left;
			else {
				tmp->left = new Node(key);
				return true;
			}
		}
		else if (tmp->data < key) {
			if (tmp->right)
				tmp = tmp->right;
			else {
				tmp->right = new Node(key);
				return true;
			}
		}
		else
			return false;
	}
}

bool BinarySearchTree::contains(int key) const {
	return containsRecursive(root, key);
}

bool BinarySearchTree::erase(int key) {
	if (contains(key)) {
		eraseRecursive(root, key);
		return true;
	}
	return false;
}