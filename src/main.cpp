#include "KaryHeap.h"
#include <iostream>
#include <chrono>
#include <functional>
#include <vector>
#include <random>
#include <algorithm>
#include <iomanip>

void executionTime(const std::function<void()> &function) {
    auto start = std::chrono::high_resolution_clock::now();
    function();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Execution time-> " << duration.count() << " ms" << std::endl;
}

void testCorrectness(KaryHeap& heap) {
    std::vector<int> elements = {5, 2, 8, 6, 1, 4, 7, 3, 9, 0};
    for (int elem : elements) {
        heap.insert(elem);
    }

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
    KaryHeap heap(k, N);

    std::cout << "Testing efficiency for k = " << k << " with N = " << N << " elements." << std::endl;

    auto insertAction = [&]() {
        for (int i = 0; i < N; ++i) {
            heap.insert(rand() % N);
        }
    };

    std::cout << "Insertion time: ";
    executionTime(insertAction);

    auto extractAction = [&]() {
        while (!heap.isEmpty()) {
            heap.extractMin();
        }
    };

    std::cout << "Extraction time: ";
    executionTime(extractAction);
}

void testSequentialEfficiency(int k, int N) {
    KaryHeap heap(k, N);
    std::cout << "Sequential efficiency for k = " << k << " with N = " << N << " elements." << std::endl;

    auto sequentialInsert = [&]() {
        for (int i = 0; i < N; ++i) {
            heap.insert(i);
        }
    };

    auto extractAll = [&]() {
        while (!heap.isEmpty()) {
            heap.extractMin();
        }
    };

    std::cout << "Sequential insertion time: ";
    executionTime(sequentialInsert);

    std::cout << "Sequential extraction time: ";
    executionTime(extractAll);
}

void testRandomEfficiency(int k, int N) {
    KaryHeap heap(k, N);
    std::cout << "Random efficiency for k = " << k << " with N = " << N << " elements." << std::endl;

    auto randomInsert = [&]() {
        std::vector<int> elements(N);
        std::iota(elements.begin(), elements.end(), 0);
        std::shuffle(elements.begin(), elements.end(), std::default_random_engine());
        for (int elem : elements) {
            heap.insert(elem);
        }
    };

    auto extractAll = [&]() {
        while (!heap.isEmpty()) {
            heap.extractMin();
        }
    };

    std::cout << "Random insertion time: ";
    executionTime(randomInsert);

    std::cout << "Random extraction time: ";
    executionTime(extractAll);
}


int main() {
    int N = 1000000;
    KaryHeap heap(2, 20);
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


    KaryHeap testHeap(3, 10); // Using a ternary heap for the correctness test
    testCorrectness(testHeap);
    std::cout << std::endl;

    std::cout << "Testing efficiency for different k values" << std::endl;
    std::vector<int> ks = {2, 4, 8, 16}; // Different k values to test
    for (int k : ks) {
        testEfficiency(k, N);
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for (int k : ks) {
        testSequentialEfficiency(k, N);
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for (int k : ks) {
        testRandomEfficiency(k, N);
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Now testing efficiency with different sizes of N" << std::endl;
    std::vector<int> sizes = {1000000, 5000000, 10000000, 20000000, 50000000};
    for (int size : sizes) {
        testEfficiency(3, size);
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for(int size : sizes) {
        testSequentialEfficiency(3, size);
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for(int size : sizes) {
        testRandomEfficiency(3, size);
        std::cout << std::endl;
    }

    return 0;
}
