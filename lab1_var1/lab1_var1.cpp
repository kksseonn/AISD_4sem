#include <iostream>
#include <stdexcept>


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
		else {
			return node;
		}
		return node;
	}

	Node* erase(Node* root, int key) {
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

	Node* minValueNode(Node* node) {
		Node* current = node;
		while (current && current->left != nullptr)
			current = current->left;
		return current;
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

	void deleteTree(Node* root) {
		if (root != nullptr) {
			deleteTree(root->left);
			deleteTree(root->right);
			delete root;
		}
	}

	void print(Node* node) {
		if (node == nullptr)
			return;
		print(node->left);
		std::cout << node->data << " ";
		print(node->right);
	}

public:
	BinarySearchTree() : root(nullptr) {}

	BinarySearchTree(const BinarySearchTree& other) {
		root = copyTree(other.root);
	}

	~BinarySearchTree() {
		deleteTree(root);
	}

	BinarySearchTree& operator=(const BinarySearchTree& other) {
		if (this != &other) {
			deleteTree(root);
			root = copyTree(other.root);
		}
		return *this;
	}

	bool insert(int key) {
		if (!contains(key)) {
			root = insert(root, key);
			return true;
		}
		return false;
	}

	bool contains(int key) {
		return contains(root, key);
	}

	bool erase(int key) {
		if (contains(key)) {
			root = erase(root, key);
			return true;
		}
		return false;
	}

	void print() {
		print(root);
		std::cout << std::endl;
	}
};

int main() {
	BinarySearchTree set1;

	set1.insert(5);
	set1.insert(3);
	set1.insert(7);
	set1.insert(2);
	set1.insert(4);
	set1.insert(6);
	set1.insert(8);

	std::cout << "Tree contents: ";
	set1.print();

	std::cout << "Contains 3: " << std::boolalpha << set1.contains(3) << std::endl;
	std::cout << "Contains 9: " << std::boolalpha << set1.contains(9) << std::endl;

	BinarySearchTree set2(set1);
	std::cout << "copyTree contents: ";
	set2.print();
	BinarySearchTree set3 = set1;
	std::cout << "Tree_3 = Tree_1 contents: ";
	set3.print();

	set1.erase(3);

	std::cout << "After erasing 3:" << std::endl;
	std::cout << "Tree contents: ";
	set1.print();
	std::cout << "Contains 3: " << std::boolalpha << set1.contains(3) << std::endl;

	set2 = set1;

	std::cout << "Tree contents of set2 after assignment: ";
	set2.print();

	return 0;
}