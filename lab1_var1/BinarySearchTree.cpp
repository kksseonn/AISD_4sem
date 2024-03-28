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

BinarySearchTree::Node* BinarySearchTree::insert(Node* node, int key) {
		if (node == nullptr) {
			return new Node(key);
		}
		if (key < node->data) {
			node->left = insert(node->left, key);
		}
		else if (key > node->data) {
			node->right = insert(node->right, key);
		}
		else {
			return node;
		}
		return node;
	}

BinarySearchTree::Node* BinarySearchTree::erase(Node* root, int key) {
		if (root == nullptr)
			return nullptr;
		if (key < root->data)
			root->left = erase(root->left, key);
		else if (key > root->data)
			root->right = erase(root->right, key);
		else {
			if (root->left == nullptr) {
				Node* temp = root->right;
				delete root;
				return temp;
			}
			else if (root->right == nullptr) {
				Node* temp = root->left;
				delete root;
				return temp;
			}
			Node* temp = minValueNode(root->right);
			root->data = temp->data;
			root->right = erase(root->right, temp->data);
		}
		return root;
	}

BinarySearchTree::Node* BinarySearchTree::minValueNode(Node* node) {
		Node* current = node;
		while (current && current->left != nullptr)
			current = current->left;
		return current;
	}

bool BinarySearchTree::contains(Node* node, int key) {
	if (node == nullptr) {
		return false;
	}
	if (node->data == key) {
		return true;
	}
	else if (key < node->data) {
		return contains(node->left, key);
	}
	else {
		return contains(node->right, key);
	}
}

void BinarySearchTree::deleteTree(Node* root) {
	if (root != nullptr) {
		deleteTree(root->left);
		deleteTree(root->right);
		delete root;
	}
}

void BinarySearchTree::print(Node* node) {
	if (node == nullptr)
		return;
	print(node->left);
	std::cout << node->data << " ";
	print(node->right);
}

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& other) {
	root = copyTree(other.root);
}
BinarySearchTree::~BinarySearchTree() {
	deleteTree(root);
}
BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other) {
	if (this != &other) {
		deleteTree(root);
		root = copyTree(other.root);
	}
	return *this;
}

bool BinarySearchTree::insert(int key) {
	if (!contains(key)) {
		root = insert(root, key);
		return true;
	}
	return false;
}

bool BinarySearchTree::contains(int key) {
	return contains(root, key);
}

bool BinarySearchTree::erase(int key) {
	if (contains(key)) {
		root = erase(root, key);
		return true;
	}
	return false;
}

void BinarySearchTree::print() {
	print(root);
	std::cout << std::endl;
}
