#include <iostream>
#include "MinHeap.cpp"
typedef struct TreeNode* HuffmanTree;
struct TreeNode {
	int Weight;
	HuffmanTree Left, Right;
};

HuffmanTree Huffman(MinHeap H) {
	int i; HuffmanTree T;
	BuildMinHeap(H);
	for (i = 1; i < H->Size; i++) {
		T = (HuffmanTree)malloc(sizeof(struct TreeNode));

	}
}