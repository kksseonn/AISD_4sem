#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "BinarySearchTree.h"

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}
//int main() {
//    const int num_iterations = 1000;
//
//    ////fill bst
//    //std::clock_t start_bst_time = std::clock();
//    //for (int i = 0; i < num_iterations; ++i) {
//    //    BinarySearchTree bst;
//    //    for (int j = 0; j < 100000; ++j) {
//    //        bst.insert(lcg());
//    //    }
//    //}
//    //std::clock_t end_bst_time = std::clock();
//    //std::cout << "Time taken to fill BST: "
//    //    << static_cast<double>(end_bst_time - start_bst_time) / CLOCKS_PER_SEC / num_iterations
//    //    << " seconds" << std::endl;
//
//    ////fill vec
//    //std::clock_t start_vec_time = std::clock();
//    //for (int i = 0; i < num_iterations; ++i) {
//    //    std::vector<int> vec;
//    //    for (int j = 0; j < 100000; ++j) {
//    //        vec.push_back(lcg());
//    //    }
//    //}
//    //std::clock_t end_vec_time = std::clock();
//    //std::cout << "Time taken to fill vector: "
//    //    << static_cast<double>(end_vec_time - start_vec_time) / CLOCKS_PER_SEC / num_iterations
//    //    << " seconds" << std::endl;
//
//    ////search in bst
//    //start_bst_time = std::clock();
//    //for (int i = 0; i < num_iterations; ++i) {
//    //    BinarySearchTree bst;
//    //    for (int j = 0; j < 100000; ++j) {
//    //        bst.insert(lcg());
//    //    }
//    //    for (int j = 0; j < 100000; ++j) {
//    //        bst.contains(lcg());
//    //    }
//    //}
//    //end_bst_time = std::clock();
//    //std::cout << "Time taken to search in BST: "
//    //    << static_cast<double>(end_bst_time - start_bst_time) / CLOCKS_PER_SEC / num_iterations
//    //    << " seconds" << std::endl;
//
//    //search in vec
//    std::clock_t start_vec_time = std::clock();
//    for (int i = 0; i < num_iterations; ++i) {
//        std::vector<int> vec;
//        for (int j = 0; j < 100000; ++j) {
//            vec.push_back(lcg());
//        }
//        for (int j = 0; j < 100000; ++j) {
//            std::find(vec.begin(), vec.end(), lcg());
//        }
//    }
//    std::clock_t end_vec_time = std::clock();
//    std::cout << "Time taken to search in vec: "
//        << static_cast<double>(end_vec_time - start_vec_time) / CLOCKS_PER_SEC / num_iterations
//        << " seconds" << std::endl;
//
//    //insert and erase in bst
//    std::clock_t start_bst_time = std::clock();
//    for (int i = 0; i < num_iterations; ++i) {
//        BinarySearchTree bst;
//        for (int j = 0; j < 100000; ++j) {
//            bst.insert(lcg());
//        }
//        for (int j = 0; j < 100000; ++j) {
//            bst.erase(lcg());
//        }
//    }
//    std::clock_t end_bst_time = std::clock();
//    std::cout << "Time taken to insert and erase in BST: "
//        << static_cast<double>(end_bst_time - start_bst_time) / CLOCKS_PER_SEC / num_iterations
//        << " seconds" << std::endl;
//
//    //insert and erase in vec
//    start_vec_time = std::clock();
//    for (int i = 0; i < num_iterations; ++i) {
//        std::vector<int> vec;
//        for (int j = 0; j < 100000; ++j) {
//            vec.push_back(lcg());
//        }
//        for (int j = 0; j < 100000; ++j) {
//            vec.pop_back();
//        }
//    }
//    end_vec_time = std::clock();
//    std::cout << "Time taken to insert and erase in vec: "
//        << static_cast<double>(end_vec_time - start_vec_time) / CLOCKS_PER_SEC / num_iterations
//        << " seconds" << std::endl;
//
//    return 0;
//}
