#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
#include "BinarySearchTree.h"

// Pseudorandom number generator function
size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

// Function to fill the container with unique random numbers
void fillContainer(BinarySearchTree& bst, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        bst.insert(lcg());
    }
}

// Function to measure the average time taken for filling the container
double measureFillTime(size_t size) {
    BinarySearchTree bst;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i) {
        fillContainer(bst, size);
        bst.deleteTree();
    }
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 100.0;
}

// Function to measure the average time taken for search operations
double measureSearchTime(BinarySearchTree& bst, size_t size) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        bst.contains(lcg() % size);
    }
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1000.0;
}

// Function to measure the average time taken for insertions and deletions
double measureInsertDeleteTime(BinarySearchTree& bst, size_t size) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        bst.insert(lcg() % size);
        bst.erase(lcg() % size);
    }
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1000.0;
}

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

    std::vector<int> container_sizes = { 1000, 10000, 100000 };

    for (size_t i = 0; i < container_sizes.size(); ++i) {
        size_t size = container_sizes[i];
        double fill_time = measureFillTime(size);
        std::cout << "Average fill time for size " << size << ": " << fill_time << " microseconds" << std::endl;

        BinarySearchTree bst;
        fillContainer(bst, size);

        double search_time = measureSearchTime(bst, size);
        std::cout << "Average search time for size " << size << ": " << search_time << " nanoseconds" << std::endl;

        double insert_delete_time = measureInsertDeleteTime(bst, size);
        std::cout << "Average insert and delete time for size " << size << ": " << insert_delete_time << " nanoseconds" << std::endl;

        // Delete all nodes in the tree
        bst.deleteTree(root);
    }

	return 0;
}