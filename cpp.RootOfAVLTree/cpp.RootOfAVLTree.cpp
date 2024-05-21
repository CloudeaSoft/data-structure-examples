#include <iostream>
using namespace std;

typedef int ElementType;
typedef struct AVLNode* Position;
typedef Position AVLTree;
struct AVLNode {
	ElementType Data;
	AVLTree Left;
	AVLTree Right;
	int Height;
};

int Max(int a, int b);
int GetHeight(AVLTree A);
AVLTree SingleLeftRotation(AVLTree A);
AVLTree SingleRightRotation(AVLTree A);
AVLTree DoubleLeftRightRotation(AVLTree A);
AVLTree DoubleRightLeftRotation(AVLTree A);
AVLTree Insert(AVLTree T, ElementType X);

int main() {
	int size, value;
	cin >> size;

	AVLTree T = NULL;
	while (size--) {
		cin >> value;
		T = Insert(T, value);
	}
	if (T)
		cout << T->Data;

	return 0;
}

int Max(int a, int b)
{
	return a > b ? a : b;
}

int GetHeight(AVLTree A) {
	if (!A)
		return -1;
	else
		return A->Height;
}

AVLTree SingleLeftRotation(AVLTree A)
{
	AVLTree B = A->Left;
	A->Left = B->Right;
	B->Right = A;
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
	B->Height = Max(GetHeight(B->Left), A->Height) + 1;

	return B;
}

AVLTree SingleRightRotation(AVLTree A)
{
	AVLTree B = A->Right;
	A->Right = B->Left;
	B->Left = A;
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
	B->Height = Max(GetHeight(B->Left), A->Height) + 1;

	return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A)
{ 
	/* 将B与C做右单旋，C被返回 */
	A->Left = SingleRightRotation(A->Left);
	/* 将A与C做左单旋，C被返回 */
	return SingleLeftRotation(A);
}

AVLTree DoubleRightLeftRotation(AVLTree A) {
	A->Right = SingleLeftRotation(A->Right);
	return SingleRightRotation(A);
}

AVLTree Insert(AVLTree T, ElementType X)
{
	if (!T) {
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		T->Data = X;
		T->Height = 0;
		T->Left = T->Right = NULL;
	}
	else if (X < T->Data) {
		/* 插入T的左子树 */
		T->Left = Insert(T->Left, X);
		/* 如果需要左旋 */
		if (GetHeight(T->Left) - GetHeight(T->Right) == 2)
			if (X < T->Left->Data)
				T = SingleLeftRotation(T);
			else
				T = DoubleLeftRightRotation(T);
	}
	else if (X > T->Data) {
		/* 插入T的右子树 */
		T->Right = Insert(T->Right, X);
		/* 如果需要右旋 */
		if (GetHeight(T->Left) - GetHeight(T->Right) == -2)
			if (X > T->Right->Data)
				T = SingleRightRotation(T);
			else
				T = DoubleRightLeftRotation(T);
	}

	T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;

	return T;
}