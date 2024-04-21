#pragma once
#include <iomanip>
#include <vector>


class BinarySearchTree {
	struct Node {
		int data;
		Node* left;
		Node* right;
		Node(int value) : data(value), left(nullptr), right(nullptr) {}
	};
	Node* root;
	Node* copyTree(Node* root);
	Node* minValueNode(Node* node);

	void eraseRecursive(Node*& node, const int key);
	void destroyRecursive(Node* node);
	void printRecursive(Node* node, const std::string& prefix = "", bool isLeft = true) const;
	bool containsRecursive(Node* node, const int key) const;
	void fillVector(Node* node, std::vector<int>& result) const;

public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree& other);
	~BinarySearchTree();

	BinarySearchTree& operator=(const BinarySearchTree& other);

	std::vector<int> treeToVector() const;

	void print() const;
	bool insert(int key);
	bool contains(int key) const;
	bool erase(int key);
	
};