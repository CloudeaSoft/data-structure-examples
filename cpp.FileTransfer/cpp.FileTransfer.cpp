#include <iostream>
using namespace std;

typedef int ElementType;
typedef ElementType SetName;
typedef ElementType SetType[10000];

void Initialize(SetType S, int N);
SetName Find(SetType S, ElementType X);
void Union(SetType S, SetName R1, SetName R2);
void InputConnection(SetType S);
void CheckConnection(SetType S);
void CheckNetWork(SetType S, int N);

int main()
{
	SetType S;
	int n;
	char in;

	cin >> n;
	Initialize(S, n);

	do {
		cin >> in;
		switch (in) {
		case 'I':
			InputConnection(S);
			break;
		case 'C':
			CheckConnection(S);
			break;
		case 'S':
			CheckNetWork(S, n);
			break;
		}
	} while (in != 'S');

	return 0;
}

void Initialize(SetType S, int X) {
	for (int i = 0; i < X; i++) {
		S[i] = -1;
	}
}

SetName Find(SetType S, ElementType X) {
	if (S[X] < 0)
		return X;
	else
		return S[X] = Find(S, S[X]);
}

void Union(SetType S, SetName R1, SetName R2) {
	if (S[R1] < S[R2]) {
		S[R1] += S[R2];
		S[R2] = R1;
	}
	else {
		S[R2] += S[R1];
		S[R1] = R2;
	}
}

void InputConnection(SetType S) {
	ElementType a, b;
	cin >> a >> b;
	SetName r1 = Find(S, a - 1);
	SetName r2 = Find(S, b - 1);
	if (r1 != r2)
		Union(S, r1, r2);
}

void CheckConnection(SetType S) {
	ElementType a, b;
	cin >> a >> b;
	SetName r1 = Find(S, a - 1);
	SetName r2 = Find(S, b - 1);
	if (r1 == r2)
		cout << "yes" << endl;
	else
		cout << "no" << endl;
}

void CheckNetWork(SetType S, int n) {
	int counter = 0;
	for (int i = 0; i < n; i++) {
		if (S[i] < 0)
			counter++;
	}
	if (counter == 1)
		cout << "The network is connected." << endl;
	else
		cout << "There are " << counter << " components." << endl;
}