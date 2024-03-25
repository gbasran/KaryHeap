#include "KaryHeap.h"
#include <iostream>
#include <chrono>
#include <functional>

void executionTime(const std::function<void()> &function) {
    auto start = std::chrono::high_resolution_clock::now();
    function();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Execution time-> " << duration.count() << " milliseconds" << std::endl;
}

void testCorrectness(KaryHeap& heap) {
    // Insert elements in a random order
    std::vector<int> elements = {5, 2, 8, 6, 1, 4, 7, 3, 9, 0};
    for (int elem : elements) {
        heap.insert(elem);
    }

    // Extract elements and expect them to be in sorted order
    int prev = heap.extractMin();
    while (!heap.isEmpty()) {
        int current = heap.extractMin();
        if (prev > current) {
            std::cout << "Test failed: elements are not in sorted order." << std::endl;
            return;
        }
        prev = current;
    }
    std::cout << "Correctness test passed." << std::endl;
}

void testEfficiency(int k, int N) {
    KaryHeap heap(k);

    std::cout << "Testing efficiency for k = " << k << " with N = " << N << " elements." << std::endl;

    // Measure insertion time
    auto insertAction = [&]() {
        for (int i = 0; i < N; ++i) {
            heap.insert(rand() % N);  // Insert a random number
        }
    };

    std::cout << "Insertion time: ";
    executionTime(insertAction);

    // Measure extraction time
    auto extractAction = [&]() {
        while (!heap.isEmpty()) {
            heap.extractMin();
        }
    };

    std::cout << "Extraction time: ";
    executionTime(extractAction);
}

int main() {

    KaryHeap heap(2); // visualization of the heap

    std::vector<int> elements = {15, 10, 20, 30, 40, 50, 60, 70, 80, 90};

    for (int elem : elements) {
        heap.insert(elem);
        std::cout << "After inserting " << elem << ":" << std::endl;
        heap.printHeap();
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Starting extraction:" << std::endl;

    while (!heap.isEmpty()) {
        std::cout << std::endl;
        std::cout << "Extracted " << heap.extractMin() << std::endl;
        heap.printHeap();
    }
    std::cout << std::endl;

    // Test for correctness with a small, known set of elements
    KaryHeap testHeap(3); // Using a ternary heap for the correctness test
    testCorrectness(testHeap);

    // Test for efficiency with larger values of N and different ks
    std::vector<int> ks = {2, 4, 8, 16};  // Different k values to test
    int N = 10000000;  // 10 million elements

    for (int k : ks) {
        std::cout << std::endl;
        testEfficiency(k, N);
        std::cout << std::endl;
    }


    return 0;
}