#include <iostream>
using namespace std;

#define MaxSize 30
typedef int ElementType;
typedef struct TreeNode {
	ElementType Data;
	struct TreeNode* Left;
	struct TreeNode* Right;
} TreeNode;

TreeNode* Build(int pre[], int min[], int n);
void LevelOrderReverse(TreeNode* T);

int main() {
	int num;
	cin >> num;
	int pre[MaxSize];
	int min[MaxSize];
	for (int i = 0; i < num; i++) {
		cin >> min[i];
	}
	for (int i = 0; i < num; i++) {
		cin >> pre[i];
	}

	TreeNode* TN = Build(pre, min, num);
	LevelOrderReverse(TN);
}

TreeNode* Build(int pre[], int min[], int n) {
	if (!n)
		return NULL;

	TreeNode* T = new struct TreeNode;
	T->Data = pre[0];
	T->Left = T->Right = NULL;

	int index;
	for (index = 0; index < n; index++)
	{
		if (min[index] == pre[0]) break;
	}
	T->Left = Build(pre + 1, min, index);
	T->Right = Build(pre + index + 1, min + index + 1, n - index - 1);
	return T;
}

void LevelOrderReverse(TreeNode* T) {
	if (!T)
	{
		return;
	}

	TreeNode* queue[MaxSize];
	int left = 0, right = 0;
	queue[right++] = T;
	while (left < right)
	{
		TreeNode* bt = queue[left++];
		if (bt == T)
			cout << bt->Data;
		else
			cout << " " << bt->Data;
		if (bt->Right)
			queue[right++] = bt->Right;
		if (bt->Left)
			queue[right++] = bt->Left;
	}
}