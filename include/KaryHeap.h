#ifndef KARYHEAP_H
#define KARYHEAP_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <math.h>

class KaryHeap {
  public:

  explicit KaryHeap(int k, int maxSize);
  void insert(int element);
  int extractMin();
  int peek() const;
  bool isEmpty() const;
  void printHeap() const;

  private:
  int *heap;
  int k; 
  int size;
  int maxSize;
  void heapifyUp(int i);
  void heapifyDown(int i);
  int parentIndex(int i) const;
  int childIndex(int i, int j) const;
};

#endif // KARYHEAP_H
