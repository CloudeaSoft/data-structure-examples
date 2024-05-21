#include <iostream>
using namespace std;

typedef int ElementType;
typedef struct HNode* Heap;
struct HNode {
	ElementType* Data;
	int Size;
	int Capacity;
};
typedef Heap MinHeap;

#define MINDATA -50000

MinHeap CreateMinHeap(int MaxSize);
bool IsFull(MinHeap H);
bool Insert(MinHeap H, ElementType X);
void PrintPath(MinHeap H, int index);

int main()
{
	int size, m;
	int checkValue;
	ElementType value;
	cin >> size >> m;

	MinHeap minH = CreateMinHeap(size);
	for (int i = 0; i < size; i++) {
		cin >> value;
		Insert(minH, value);
	}

	for (int i = 0; i < m; i++) {
		cin >> checkValue;
		PrintPath(minH, checkValue);
		if (i + 1 > m)
			continue;
		cout << endl;
	}

	free(minH);
}

MinHeap CreateMinHeap(int MaxSize) {
	MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
	H->Data = (ElementType*)malloc((MaxSize + 1) * sizeof(ElementType));
	H->Size = 0;
	H->Capacity = MaxSize;
	H->Data[0] = MINDATA;

	return H;
}

bool IsFull(MinHeap H) {
	return (H->Size == H->Capacity);
}

bool Insert(MinHeap H, ElementType X) {
	// Check
	if (IsFull(H)) {
		return false;
	}

	int i = ++H->Size; // One after the last node position
	for (; H->Data[i / 2] > X; i /= 2)
		H->Data[i] = H->Data[i / 2]; // Exchange data between parent node and child node
	H->Data[i] = X; // Place data to final position
	return true;
}

void PrintPath(MinHeap H, int index) {
	for (; index > 1; index /= 2)
		cout << H->Data[index] << " ";
	cout << H->Data[1];
}