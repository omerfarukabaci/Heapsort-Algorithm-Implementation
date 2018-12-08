#include "Heap.h"
#include <iostream>
#include <math.h>

template <class Data>
Heap<Data>::Heap() {
	heapSize = 0;
	heapType = MAX_HEAP;
	nodes = new Data[MAX_HEAPSIZE + 1];
}

template <class Data>
Heap<Data>::Heap(Type type) {
	heapSize = 0;
	heapType = type;
	nodes = new Data[MAX_HEAPSIZE + 1];
}


template <class Data>
void Heap<Data>::swap(int index1, int index2) {
	Data temp = nodes[index1];
	nodes[index1] = nodes[index2];
	nodes[index2] = temp;
}

template <class Data>
Heap<Data>::~Heap() {
	delete[] nodes;
}

template <class Data>
Data Heap<Data>::extractMax() {
	if (heapSize < 1) {
		std::cout << "Heap underflow!" << std::endl;
		Data error;
		error = -1;
		return error;
	}

	if (heapType == MIN_HEAP) {
		Data error;
		error = -1;
		return error;
	}

	Data max = nodes[1];
	swap(1, heapSize);
	heapSize--;
	maxHeapify(1);

	return max;
}

template <class Data>
Data Heap<Data>::extractMin() {
	if (heapSize < 1) {
		std::cout << "Heap underflow!" << std::endl;
		Data error;
		error = -1;
	}

	if (heapType == MAX_HEAP) {
		Data error;
		error = -1;
		return error;
	}

	Data min = nodes[1];
	swap(1, heapSize);
	heapSize--;
	minHeapify(1);

	return min;
}

template <class Data>
void Heap<Data>::buildMaxHeap() {
	if (heapType == MIN_HEAP)
		return;

	for (int i = heapSize / 2; i > 0; i--) {
		maxHeapify(i);
	}
}

template <class Data>
void Heap<Data>::buildMinHeap() {
	if (heapType == MAX_HEAP)
		return;
	for (int i = heapSize / 2; i > 0; i--) {
		minHeapify(i);
	}
}

template <class Data>
void Heap<Data>::maxHeapify(int index) {
	int leftIndex = leftIndexOf(index);
	int rightIndex = rightIndexOf(index);
	int largest = index;
	
	if (leftIndex <= heapSize && nodes[leftIndex] > nodes[largest])
		largest = leftIndex;

	if (rightIndex <= heapSize && nodes[rightIndex] > nodes[largest])
		largest = rightIndex;

	if (largest != index) {
		swap(index, largest);
		maxHeapify(largest);
	}

}
template <class Data>
void Heap<Data>::minHeapify(int index) {
	int leftIndex = leftIndexOf(index);
	int rightIndex = rightIndexOf(index);
	int smallest = index;

	if (leftIndex <= heapSize && nodes[leftIndex] < nodes[smallest])
		smallest = leftIndex;

	if (rightIndex <= heapSize && nodes[rightIndex] < nodes[smallest])
		smallest = rightIndex;

	if (smallest != index) {
		swap(index, smallest);
		minHeapify(smallest);
	}
}

template <class Data>
void Heap<Data>::increaseKey(int index, Data toAdd) {
	if (toAdd != -1)
		nodes[index] = nodes[index] + toAdd;

	if (heapType == MAX_HEAP) {
		while (index > 1 && nodes[parentIndexOf(index)] < nodes[index]) {
			swap(parentIndexOf(index), index);
			index = parentIndexOf(index);
		}

	}
	else if (heapType == MIN_HEAP) {
		while (index > 1 && nodes[parentIndexOf(index)] > nodes[index]) {
			swap(parentIndexOf(index), index);
			index = parentIndexOf(index);
		}
	}
}

template <class Data>
void Heap<Data>::insert(Data input) {
	heapSize++;
	nodes[heapSize] = input;
}

template <class Data>
void Heap<Data>::heapSort() {
	if (heapType == MAX_HEAP) {
		buildMaxHeap();
		for (int i = heapSize; i > 1; i--) {
			swap(1, i);
			heapSize--;
			maxHeapify(1);
		}
	}
	else if (heapType == MIN_HEAP) {
		buildMinHeap();
		for (int i = heapSize; i > 1; i--) {
			swap(1, i);
			heapSize--;
			minHeapify(1);
		}
	}
}

template <class Data>
int Heap<Data>::nodeIsPresent(Data d) {
	for (int i = 1; i <= heapSize; i++) {
		if (nodes[i] == d) {
			return i;
		}
	}
	return -1;
}

template <class Data>
void Heap<Data>::printMax3() {
	if (heapType == MIN_HEAP)
		return;

	std::cout << extractMax() << ", ";
	std::cout << extractMax() << ", ";
	std::cout << extractMax() << std::endl;

	Data inoperative;
	inoperative = -1;

	heapSize++;
	increaseKey(heapSize, inoperative);
	heapSize++;
	increaseKey(heapSize, inoperative);
	heapSize++;
	increaseKey(heapSize, inoperative);

	return;
}

template <class Data>
void Heap<Data>::printMin3() {
	if (heapType == MAX_HEAP)
		return;

	std::cout << extractMin() << ", ";
	std::cout << extractMin() << ", ";
	std::cout << extractMin() << std::endl;

	Data inoperative;
	inoperative = -1;

	heapSize++;
	increaseKey(heapSize, inoperative);
	heapSize++;
	increaseKey(heapSize, inoperative);
	heapSize++;
	increaseKey(heapSize, inoperative);

	return;
}

template <class Data>
int Heap<Data>::parentIndexOf(int index) {
	return (index / 2);
}

template <class Data>
int Heap<Data>::leftIndexOf(int index) {
	return (2 * index);
}

template <class Data>
int Heap<Data>::rightIndexOf(int index) {
	return ((2 * index) + 1);
}

template <class Data>
int Heap<Data>::getTreeHeight() {
	return floor(log2(heapSize));
}