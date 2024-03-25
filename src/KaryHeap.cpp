#include "KaryHeap.h"
#include <iostream>
#include <iomanip>
#include <vector>

KaryHeap::KaryHeap(int kValue, int maxSizeValue) : k(kValue), size(0), maxSize(maxSizeValue) {
    heap = new int[maxSize];
}

void KaryHeap::insert(int element) {
    if (size >= maxSize) {
        std::cerr << "Heap is full. Cannot insert element." << std::endl;
        return;
    }
    heap[size] = element;
    heapifyUp(size);
    size++;
}

int KaryHeap::extractMin() {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty");
    }
    int minElement = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);
    return minElement;
}

int KaryHeap::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty");
    }
    return heap[0];
}
bool KaryHeap::isEmpty() const {
    return size == 0;
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
        if (cIndex < size && heap[cIndex] < heap[smallest]) {
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
    if (isEmpty()) {
        std::cout << "(empty heap)" << std::endl;
        return;
    }

    int depth = static_cast<int>(std::ceil(std::log(size * (k - 1) + 1) / std::log(k))) - 1;
    int maxNodes = std::pow(k, depth + 1) - 1;
    int maxNodeWidth = std::to_string(heap[0]).size(); // Assuming the root is at index 0
    int index = 0;

    for (int level = 0; level <= depth; level++) {
        int levelNodes = std::pow(k, level);
        int space = (maxNodes / levelNodes) * maxNodeWidth;
        for (int node = 0; node < levelNodes && index < size; node++, index++) {
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