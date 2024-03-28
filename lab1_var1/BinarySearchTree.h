#pragma once
class BinarySearchTree {
	struct Node {
		int data;
		Node* left;
		Node* right;
		Node(int value) : data(value), left(nullptr), right(nullptr) {}
	};
	Node* root;
	Node* copyTree(Node* root);
	Node* insert(Node* node, int key);
	Node* erase(Node* root, int key);
	Node* minValueNode(Node* node);
	bool contains(Node* node, int key);
	void deleteTree(Node* root);
	void print(Node* node);
public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree& other);
	~BinarySearchTree();
	BinarySearchTree& operator=(const BinarySearchTree& other);
	bool insert(int key);
	bool contains(int key);
	bool erase(int key);
	void print();
};