#pragma once
#include <vector>
#include <iostream>
#include "BinarySearchTree.h"


class Operations {
public:
    static std::vector<int> intersection(const BinarySearchTree& set1, const BinarySearchTree& set2);
    static std::vector<int> difference(BinarySearchTree& set1, BinarySearchTree& set2);
};

std::vector<int> Operations::intersection(const BinarySearchTree& set1, const BinarySearchTree& set2) {
    std::vector<int> result;
    auto root1 = set1.getRoot();
    auto root2 = set2.getRoot();

    while (root1 && root2) {
        if (root1->data == root2->data) {
            result.push_back(root1->data);
            root1 = root1->right;
            root2 = root2->right;
        }
        else if (root1->data < root2->data) {
            root1 = root1->right;
        }
        else {
            root2 = root2->right;
        }
    }

    return result;
}

std::vector<int> Operations::difference(BinarySearchTree& set1, BinarySearchTree& set2) {
    std::vector<int> result;
    auto root1 = set1.getRoot();
    auto root2 = set2.getRoot();

    while (root1) {
        if (!set2.contains(root1->data)) {
            result.push_back(root1->data);
        }
        root1 = root1->right;
    }

    return result;
}
//int main() {
//    BinarySearchTree set1;
//    set1.insert(1);
//    set1.insert(2);
//    set1.insert(3);
//    set1.insert(4);
//
//    BinarySearchTree set2;
//    set2.insert(2);
//    set2.insert(4);
//    set2.insert(6);
//    set2.insert(8);
//
//    std::vector<int> intersection_result = Operations::intersection(set1, set2);
//    std::cout << "Intersection of sets: ";
//    for (int elem : intersection_result) {
//        std::cout << elem << " ";
//    }
//    std::cout << std::endl;
//
//    std::vector<int> difference_result = Operations::difference(set1, set2);
//    std::cout << "Difference of sets (set1 - set2): ";
//    for (int elem : difference_result) {
//        std::cout << elem << " ";
//    }
//    std::cout << std::endl;
//
//    return 0;
//}