#include <iostream>

class BinarySearchTree {
	struct Node {
		int data;
		Node* left;
		Node* right;
		Node(int value) : data(value), left(nullptr), right(nullptr) {}
	};
	Node* root;

	Node* copyTree(Node* root) {
		if (root == nullptr) {
			return nullptr;
		}
		Node* newNode = new Node(root->data);
		newNode->left = copyTree(root->left);
		newNode->right = copyTree(root->right);
		return newNode;
	}

	Node* insert(Node* node, int key) {
		if (node == nullptr) {
			return new Node(key);
		}
		if (key < node->data) {
			node->left = insert(node->left, key);
		}
		else if (key > node->data) {
			node->right = insert(node->right, key);
		}
		return node;
	}

	bool contains(Node* node, int key) {
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

public:
	BinarySearchTree() : root(nullptr) {}

	BinarySearchTree(const BinarySearchTree& other) {
		root = copyTree(other.root);
	}

	void insert(int key) {
		root = insert(root, key);
	}

	bool contains(int key) {
		return contains(root, key);
	}
};

int main() {
	BinarySearchTree set;
	set.insert(5);
	set.insert(3);
	set.insert(7);
	set.insert(2);
	set.insert(4);
	set.insert(6);
	set.insert(8);

	std::cout << "Contains 3: " << std::boolalpha << set.contains(3) << std::endl;
	std::cout << "Contains 9: " << std::boolalpha << set.contains(9) << std::endl;

	return 0;
}