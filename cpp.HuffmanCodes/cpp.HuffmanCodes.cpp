#include <iostream>
using namespace std;

#define MINDATA 0
#define ERROR -1

typedef struct TreeNode* HuffmanTree;
struct TreeNode {
	int Weight;
	HuffmanTree Left, Right;
};

typedef HuffmanTree ElementType;
struct Heap {
	ElementType* Data;
	int Size;
	int Capacity;
};
typedef Heap* MinHeap;

MinHeap CreateMinHeap(int size);
bool Insert(MinHeap H, ElementType X);

HuffmanTree DeleteMin(MinHeap H);
HuffmanTree Huffman(MinHeap H);

int CalcWPL(HuffmanTree T, int H = 0);
bool Check(string A, string B);

int main()
{

	int num;
	cin >> num;

	MinHeap mHeap = CreateMinHeap(num);

	// 1. 读入权重数组，并生成最小堆
	int* a = new int[num];
	char symbol; int count;
	for (int i = 0; i < num; i++) {
		cin >> symbol >> count;
		a[i] = count;

		HuffmanTree hTree;
		hTree = new struct TreeNode;
		hTree->Weight = count;
		hTree->Left = hTree->Right = NULL;

		Insert(mHeap, hTree);
	}

	// 2. 将最小堆转化为哈夫曼树
	HuffmanTree huff = Huffman(mHeap);
	// 3. 通过哈夫曼树得到最优值
	int huffWPL = CalcWPL(huff);

	// 4. 将最优值与其他编码做比对，检测前缀，打印结果
	int stuNum;
	cin >> stuNum;

}

MinHeap CreateMinHeap(int MaxSize) {
	MinHeap H = new struct Heap;
	H->Data = new ElementType[MaxSize + 1];
	H->Size = 0;
	H->Capacity = MaxSize;

	ElementType Guard = new struct TreeNode;
	Guard->Weight = MINDATA;
	Guard->Left = Guard->Right = NULL;
	H->Data[0] = Guard;

	return H;
}

bool IsFull(MinHeap H) {
	return (H->Size == H->Capacity);
}

bool Insert(MinHeap H, ElementType X) {
	if (IsFull(H)) {
		return false;
	}

	int i = ++H->Size;
	for (; H->Data[i / 2]->Weight > X->Weight; i /= 2)
		H->Data[i] = H->Data[i / 2];
	H->Data[i] = X;
	return true;
}

HuffmanTree DeleteMin(MinHeap H) {
	int Parent, Child;
	ElementType MinItem, X;

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

HuffmanTree Huffman(MinHeap H) {
	HuffmanTree T;
	for (int i = 1; i < H->Size; i++) {
		T = new TreeNode;
		T->Left = DeleteMin(H);
		T->Right = DeleteMin(H);
		T->Weight = T->Left->Weight + T->Right->Weight;
		Insert(H, T);
	}
	T = DeleteMin(H);
	return T;
}

int CalcWPL(HuffmanTree T, int H = 0) {
	if (!T->Left && !T->Right)
		return T->Weight * H;
	else
		return CalcWPL(T->Left, H + 1) + CalcWPL(T->Right, H + 1);
}