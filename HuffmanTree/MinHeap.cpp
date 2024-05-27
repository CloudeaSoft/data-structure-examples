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

#define ERROR -1

bool IsEmpty(MinHeap H)
{
    return (H->Size == 0);
}

ElementType DeleteMin(MinHeap H)
{
    int Parent, Child;
    ElementType MinItem, X;

    if (IsEmpty(H)) {
        printf("最小堆已为空");
        return ERROR;
    }

    MinItem = H->Data[1]; 
    X = H->Data[H->Size--];
    for (Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
        Child = Parent * 2;
        if ((Child != H->Size) && (H->Data[Child] > H->Data[Child + 1]))
            Child++;
        if (X <= H->Data[Child]) break;
        else
            H->Data[Parent] = H->Data[Child];
    }
    H->Data[Parent] = X;

    return MinItem;
}

void PercDown(MinHeap H, int p)
{
    int Parent, Child;
    ElementType X;

    X = H->Data[p];
    for (Parent = p; Parent * 2 <= H->Size; Parent = Child) {
        Child = Parent * 2;
        if ((Child != H->Size) && (H->Data[Child] > H->Data[Child + 1]))
            Child++;
        if (X <= H->Data[Child]) break;
        else
            H->Data[Parent] = H->Data[Child];
    }
    H->Data[Parent] = X;
}

void BuildMinHeap(MinHeap H)
{
    int i;
    for (i = H->Size / 2; i > 0; i--)
        PercDown(H, i);
}