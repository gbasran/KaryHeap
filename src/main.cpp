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
    std::cout << "Execution time-> " << duration.count() << " milliseconds" << std::endl;
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

struct ExperimentTimes {
    long long seqTime;
    long long ranTime;
};

ExperimentTimes testHeapPerformance(int k, int N) {
    KaryHeap seqHeap(k, N);
    KaryHeap ranHeap(k, N);
    ExperimentTimes times;

    // Sequential insertion
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < N; ++i) {
        seqHeap.insert(i);
    }
    while (!seqHeap.isEmpty()) {
        seqHeap.extractMin();
    }
    auto end = std::chrono::high_resolution_clock::now();
    times.seqTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // Random insertion
    std::vector<int> elements(N);
    std::iota(elements.begin(), elements.end(), 0);
    std::shuffle(elements.begin(), elements.end(), std::default_random_engine());

    start = std::chrono::high_resolution_clock::now();
    for(int elem : elements) {
        ranHeap.insert(elem);
    }
    while (!ranHeap.isEmpty()) {
        ranHeap.extractMin();
    }
    end = std::chrono::high_resolution_clock::now();
    times.ranTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    return times;
}

int main() {
    int k = 3; // Or any other k value you wish to test
    int l = 1000000; // Number of elements to insert and extract
    ExperimentTimes times = testHeapPerformance(k, l);
    std::cout << "Sequential time: " << times.seqTime << " microseconds" << std::endl;
    std::cout << "Random time: " << times.ranTime << " microseconds" << std::endl;

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

    std::vector<int> ks = {2, 4, 8, 16}; // Different k values to test
    int N = 10000000; // 10 million elements

    for (int k : ks) {
        std::cout << std::endl;
        testEfficiency(k, N);
        std::cout << std::endl;
    }

    return 0;
}
