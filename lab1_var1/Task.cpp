#pragma once
#include <vector>
#include <iostream>
#include <unordered_set>
#include "BinarySearchTree.h"


std::vector<int> intersection(const BinarySearchTree& bst1, const BinarySearchTree& bst2) {
    std::vector<int> result;
    std::vector<int> vec1 = bst1.treeToVector();
    std::vector<int> vec2 = bst2.treeToVector();

    std::unordered_set<int> set1(vec1.begin(), vec1.end());

    for (int num : vec2) {
        if (set1.count(num))
            result.push_back(num);
    }

    return result;
}

std::vector<int> difference(const BinarySearchTree& bst1, const BinarySearchTree& bst2) {
    std::vector<int> result;
    std::vector<int> vec1 = bst1.treeToVector();
    std::vector<int> vec2 = bst2.treeToVector();

    std::unordered_set<int> set2(vec2.begin(), vec2.end());

    for (int num : vec1) {
        if (!set2.count(num))
            result.push_back(num);
    }

    for (int num : vec2) {
        if (!bst1.contains(num))
            result.push_back(num);
    }

    return result;
}


int main() {
    BinarySearchTree set1;
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    set1.insert(4);
    set1.print();

    BinarySearchTree set2;
    set2.insert(2);
    set2.insert(4);
    set2.insert(6);
    set2.insert(8);
    set2.print();

    std::vector<int> intersection_result = intersection(set1, set2);
    std::cout << "Intersection of sets: ";
    for (int elem : intersection_result) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    std::vector<int> difference_result = difference(set1, set2);
    std::cout << "Difference of sets (set1 - set2): ";
    for (int elem : difference_result) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}