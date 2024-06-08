#include <iostream>
using namespace std;

#define MaxSize 101
#define INFINITY 65535
#define ERROR 0

typedef int Vertex;
typedef int Weight;

struct ENode {
	Vertex V1, V2;
	Weight Value;
};
typedef ENode* Edge;

struct GNode {
	int Nv;
	int Ne;
	Weight EdgeMap[MaxSize][MaxSize];
};
typedef GNode* Graph;

struct PathNode {
	int dist;
	int path;
};

Graph BuildGraph();
Graph CreateGraph(int N);
void InsertEdge(Graph G, Edge E);
bool Dijkstra(Graph G, Vertex s);
Vertex FindMinDist(Graph G, PathNode P[], bool C[]);

int main()
{
	Graph G = BuildGraph();

	for (Vertex i = 1; i <= G->Nv; i++) {
		cout << i << endl;
		Dijkstra(G, i);
	}
}

Graph BuildGraph()
{
	int N;
	cin >> N;
	Graph G = CreateGraph(N);

	cin >> G->Ne;
	Edge E = new struct ENode;
	for (int i = 0; i < G->Ne; i++) {
		cin >> E->V1 >> E->V2 >> E->Value;
		InsertEdge(G, E);
	}

	return G;
}

Graph CreateGraph(int VertexNum)
{
	Graph G = new struct GNode;
	G->Nv = VertexNum;
	G->Ne = 0;

	for (Vertex i = 1; i <= VertexNum; i++) {
		for (Vertex j = 1; j <= VertexNum; j++) {
			G->EdgeMap[i][j] = INFINITY;
		}
	}

	return G;
}

void InsertEdge(Graph G, Edge E)
{
	G->EdgeMap[E->V1][E->V2] = E->Value;
	G->EdgeMap[E->V2][E->V1] = E->Value;
}

bool Dijkstra(Graph G, Vertex S)
{
	PathNode* pathArr = new PathNode[G->Nv + 1];
	bool* collected = new bool[G->Nv + 1];
	for (Vertex i = 1; i <= G->Nv; i++)
	{
		pathArr[i].dist = G->EdgeMap[S][i];
		if (pathArr[i].dist < INFINITY)
			pathArr[i].path = S;
		else
			pathArr[i].path = -1;
		collected[i] = false;
	}

	pathArr[S].dist = 0;
	collected[S] = true;

	while (true) {
		Vertex V = FindMinDist(G, pathArr, collected);
		cout << V << " ";
		if (V == ERROR)
		{
			break;
		}

		collected[V] = true;

		for (Vertex i = 1; i <= G->Nv; i++) {
			if (collected[i] == false && G->EdgeMap[V][i] < INFINITY) {
				if (G->EdgeMap[V][i] < 0)
					return false;
				if (pathArr[V].dist + G->EdgeMap[V][i] < pathArr[i].dist)
				{
					pathArr[i].dist = pathArr[V].dist + G->EdgeMap[V][i];
					pathArr[i].path = V;
				}
			}
		}
	}

	cout << endl;

	for (Vertex i = 1; i <= G->Nv; i++)
	{
		cout << pathArr[i].dist << " ";
	}

	cout << endl;

	for (Vertex i = 1; i <= G->Nv; i++)
	{
		cout << pathArr[i].path << " ";
	}

	cout << endl;

	return true;
}

Vertex FindMinDist(Graph G, PathNode P[], bool C[])
{
	Vertex MinV;
	int MinDist = INFINITY;

	for (Vertex i = 1; i <= G->Nv; i++) {
		if (C[i] == false && P[i].dist < MinDist) {
			MinDist = P[i].dist;
			MinV = i;
		}
	}

	if (MinDist == INFINITY)
	{
		return ERROR;
	}

	return MinV;
}