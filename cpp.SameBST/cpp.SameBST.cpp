#include <iostream>
using namespace std;

typedef struct TreeNode
{
	int data;
	bool flag;
	TreeNode* Left;
	TreeNode* Right;
	TreeNode(int d) {
		data = d;
		flag = false;
		Left = Right = NULL;
	}
}*tree;

void insertNode(tree& root, int x);
bool findNode(tree root, int x);
void clearTree(tree root);

int main()
{
	int N, Value;
	while (cin >> N && N) {
		int L;
		cin >> L;

		tree head = NULL;
		for (int i = 0; i < N; i++) {
			cin >> Value;
			insertNode(head, Value);
		}
		while (L--) {
			bool res = true;
			for (int i = 0; i < N; i++) {
				cin >> Value;
				res = res && findNode(head, Value);
			}

			if (res) {
				cout << "Yes\n";
			}
			else
				cout << "No\n";
			clearTree(head);
		}
	}

	return 0;
}

void insertNode(tree& root, int x) {
	if (root == NULL) {
		root = new TreeNode(x);
	}
	else {
		if (x < root->data)
			insertNode(root->Left, x);
		else
			insertNode(root->Right, x);
	}
}

bool findNode(tree root, int x) {
	if (root == NULL) {
		return false;
	}

	if (root->data == x) {
		root->flag = true;
		return true;
	}

	if (root->flag == false) {
		return false;
	}

	if (root->data < x) {
		return findNode(root->Right, x);
	}
	else {
		return findNode(root->Left, x);
	}
}

void clearTree(tree root) {
	if (root == NULL) return;
	root->flag = false;
	clearTree(root->Left);
	clearTree(root->Right);
}