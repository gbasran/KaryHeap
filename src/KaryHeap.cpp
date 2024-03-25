#include "KaryHeap.h"
#include <iostream>
#include <iomanip>
#include <vector>

KaryHeap::KaryHeap(int kValue) : k(kValue) {}

void KaryHeap::insert(int element) {
    heap.push_back(element);  // Add the element to the end of the vector
    heapifyUp(heap.size() - 1);  // Adjust the position of the newly added element
}

int KaryHeap::extractMin() {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty");
    }
    int minElement = heap[0];  // Store the minimum element
    heap[0] = heap.back();  // Replace the root of the heap with the last element
    heap.pop_back();  // Remove the last element
    heapifyDown(0);  // Restore the heap property
    return minElement;
}

int KaryHeap::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty");
    }
    return heap[0];  // Return the root element
}

bool KaryHeap::isEmpty() const {
    return heap.empty();
}

void KaryHeap::heapifyUp(int i) {
    while (i != 0 && heap[parentIndex(i)] > heap[i]) {
        std::swap(heap[i], heap[parentIndex(i)]);
        i = parentIndex(i);
    }
}

void KaryHeap::heapifyDown(int i) {
    int smallest = i;
    for (int j = 1; j <= k; ++j) {
        int cIndex = childIndex(i, j);
        if (cIndex < heap.size() && heap[cIndex] < heap[smallest]) {
            smallest = cIndex;
        }
    }
    if (smallest != i) {
        std::swap(heap[i], heap[smallest]);
        heapifyDown(smallest);
    }
}

int KaryHeap::parentIndex(int i) const {
    return (i - 1) / k;
}

int KaryHeap::childIndex(int i, int j) const {
    return k * i + j;
}

void KaryHeap::printHeap() const {
    if (heap.empty()) {
        std::cout << "(empty heap)" << std::endl;
        return;
    }

    int depth = static_cast<int>(std::ceil(std::log(heap.size() * (k - 1) + 1) / std::log(k))) - 1;
    int maxNodes = std::pow(k, depth + 1) - 1;
    int maxNodeWidth = std::to_string(heap.back()).size();
    int index = 0;

    for (int level = 0; level <= depth; level++) {
        int levelNodes = std::pow(k, level);
        int space = (maxNodes / levelNodes) * maxNodeWidth;
        for (int node = 0; node < levelNodes && index < heap.size(); node++, index++) {
            if (node > 0) {
                std::cout << std::setw(space) << std::setfill(' ') << ' ';
            } else {
                std::cout << std::setw((space / 2) + (maxNodeWidth / 2)) << std::setfill(' ') << ' ';
            }
            std::cout << std::setw(maxNodeWidth) << std::setfill(' ') << heap[index];
        }
        std::cout << std::endl;
    }
}