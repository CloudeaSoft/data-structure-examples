#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;

// Vertex Type
typedef int Vertex;

// Edge Node
struct ENode {
	Vertex V1, V2;
};
typedef ENode* Edge;

// Adjacent Node
struct AdjVNode {
	Vertex AdjV;
	AdjVNode* Next;
};

// Head Element of adjacent node list
typedef struct VNode {
	AdjVNode* FirstEdge;
} AdjList[1001];

// Graph Node
struct GNode {
	int Nv;
	int Ne;
	AdjList Map;
};
typedef GNode* Graph;

Graph BuildGraph();
Graph CreateGraph(int VertexNum);
void InsertEdge(Graph G, Edge E);
void SDS(Graph G);
int SDS_BFS(Graph G, Vertex V);

int main()
{
	Graph G = BuildGraph();
	SDS(G);
}

Graph BuildGraph()
{
	Graph G;
	int Nv;

	cin >> Nv;
	G = CreateGraph(Nv);

	cin >> G->Ne;
	Edge E = new struct ENode;
	for (int i = 0; i < G->Ne; i++) {
		cin >> E->V1 >> E->V2;
		InsertEdge(G, E);
	}

	return G;
}

Graph CreateGraph(int VertexNum)
{
	Graph G = new struct GNode;
	G->Nv = VertexNum;
	G->Ne = 0;
	for (Vertex V = 1; V <= G->Nv; V++)
		G->Map[V].FirstEdge = NULL;

	return G;
}

void InsertEdge(Graph G, Edge E)
{
	AdjVNode* NewNode1 = new struct AdjVNode;
	NewNode1->AdjV = E->V2;
	NewNode1->Next = G->Map[E->V1].FirstEdge;
	G->Map[E->V1].FirstEdge = NewNode1;

	AdjVNode* NewNode2 = new struct AdjVNode;
	NewNode2->AdjV = E->V1;
	NewNode2->Next = G->Map[E->V2].FirstEdge;
	G->Map[E->V2].FirstEdge = NewNode2;
}

void SDS(Graph G)
{
	bool isFirst = true;
	for (int i = 1; i <= G->Nv; i++) {
		int count = SDS_BFS(G, i);
		if (!isFirst) {
			cout << endl;
		}
		else {
			isFirst = false;
		}
		cout << i << ": " << fixed << setprecision(2) << 1.0000f * count * 100 / G->Nv << "%";
	}
}

int SDS_BFS(Graph G, Vertex V)
{
	bool* visited = new bool[G->Nv + 1];
	for (int i = 1; i <= G->Nv; i++) {
		visited[i] = false;
	}
	queue<int> Q = queue<int>();

	int level = 0, count = 0;
	Vertex last = V, tail = V;

	Q.push(V);

	AdjVNode* ptr;
	while (!Q.empty()) {
		V = Q.front();
		Q.pop();

		ptr = G->Map[V].FirstEdge;
		while (ptr) {
			if (!visited[ptr->AdjV]) {
				visited[ptr->AdjV] = true;
				Q.push(ptr->AdjV);
				count++;
				tail = ptr->AdjV;
			}
			ptr = ptr->Next;
		}

		if (V == last) {
			level++;
			last = tail;
		}

		if (level == 6) {
			break;
		}
	}
	return count;
}