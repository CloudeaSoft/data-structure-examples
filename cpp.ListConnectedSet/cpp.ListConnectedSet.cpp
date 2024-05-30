#include <iostream>
#include <queue>
using namespace std;

#define MaxVertexNum 10
#define INFINITY 0

typedef int Vertex;
typedef int DataType;

typedef struct ENode* PtrToENode;
struct ENode {
	Vertex V1, V2;
};
typedef PtrToENode Edge;

typedef struct GNode* PtrToGNode;
struct GNode {
	int Nv;
	int Ne;
	int G[MaxVertexNum][MaxVertexNum];
	DataType Data[MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph CreateGraph(int VertexNum);
void InsertEdge(MGraph Graph, Edge E);
MGraph BuildGraph();
void ResetVisit(MGraph Graph);
void BFS(MGraph Graph);
int FindHead(MGraph Graph);
void BFSSingle(MGraph Graph, int index);
void DFS(MGraph Graph);
void DFSSingle(MGraph Graph, int index);

int main()
{
	MGraph m = BuildGraph();
	DFS(m);
	ResetVisit(m);
	BFS(m);
}

MGraph CreateGraph(int VertexNum)
{ /* 初始化一个有VertexNum个顶点但没有边的图 */
	Vertex V, W;
	MGraph Graph;

	Graph = new struct GNode; /* 建立图 */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;

	for (V = 0; V < Graph->Nv; V++)
		for (W = 0; W < Graph->Nv; W++)
			Graph->G[V][W] = INFINITY;

	return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
	/* 插入边 <V1, V2> */
	Graph->G[E->V1][E->V2] = 1;
	/* 插入边 <V2, V1> */
	Graph->G[E->V2][E->V1] = 1;
}

MGraph BuildGraph()
{
	MGraph Graph;
	Edge E;
	int Nv, i;

	cin >> Nv; // Number of Vertex
	Graph = CreateGraph(Nv);

	cin >> Graph->Ne; // Number of Edge
	if (Graph->Ne != 0) {
		E = new struct ENode;
		for (i = 0; i < Graph->Ne; i++) {
			cin >> E->V1 >> E->V2;
			InsertEdge(Graph, E);
		}
	}

	return Graph;
}

void ResetVisit(MGraph Graph) {
	for (int i = 0; i < Graph->Nv; i++)
		Graph->Data[i] = 0;
}

int FindHead(MGraph Graph) {
	for (int i = 0; i < Graph->Nv; i++) {
		if (Graph->Data[i] == 0) {
			return i;
		}
	}
	return -1;
}

void BFS(MGraph Graph) {
	if (Graph->Nv <= 0) {
		return;
	}

	bool notFirst = false;

	while (true)
	{
		int head = FindHead(Graph);

		if (head == -1) {
			return;
		}
		else if (notFirst)
			cout << endl;
		else
			notFirst = true;

		BFSSingle(Graph, head);
	}
}

void BFSSingle(MGraph Graph, int index) {
	queue<int> outputQueue = queue<int>();

	outputQueue.push(index);

	Graph->Data[index] = 1;

	cout << "{ ";

	while (!outputQueue.empty()) {
		int a = outputQueue.front();
		outputQueue.pop();
		cout << a << " ";

		for (int i = 0; i < Graph->Nv; i++) {
			if (Graph->G[a][i] == 1 // Node is connected
				&& Graph->Data[i] == 0) // Node hasn't been visited
			{
				outputQueue.push(i);
				Graph->Data[i] = 1;
			}
		}
	}

	cout << "}";
}

void DFS(MGraph Graph) {
	if (Graph->Nv <= 0) {
		return;
	}

	while (true)
	{
		int head = FindHead(Graph);

		if (head == -1)
			return;

		cout << "{ ";
		DFSSingle(Graph, head);
		cout << "}" << endl;
	}
}

void DFSSingle(MGraph Graph, int index) {
	Graph->Data[index] = 1;

	cout << index << " ";
	for (int i = 0; i < Graph->Nv; i++)
		if (Graph->G[index][i] == 1 // Node is connected
			&& Graph->Data[i] == 0) // Node hasn't been visited
			DFSSingle(Graph, i);
}