#include <iostream>
#include <queue>
using namespace std;

typedef int Vertex;
struct ENode {
	Vertex V1, V2;
	bool Check;
};

ENode* InitializeMap(int N);
void BFS(ENode* Map, int N, int D);

int main()
{
	int N, D;

	cin >> N >> D;

	if (N <= 0)
		return 0;

	ENode* map = InitializeMap(N);

	BFS(map, N, D);

	delete[] map;
	return 0;
}

ENode* InitializeMap(int N) {

	ENode* map = new ENode[N];
	for (int i = 0; i < N; i++) {
		cin >> map[i].V1 >> map[i].V2;
		map[i].Check = false;
	}
	return map;
}

void BFS(ENode* Map, int N, int D) {
	queue<ENode> Q = queue<ENode>();
	ENode start;
	start.V1 = 0;
	start.V2 = 0;
	start.Check = true;
	Q.push(start);

	while (!Q.empty())
	{
		ENode node = Q.front();

		if (node.V1 <= 15
			&& node.V1 >= -15
			&& node.V2 <= 15
			&& node.V2 >= -15)
		{
			if (50 - node.V1 <= D
				|| 50 - node.V2 <= D
				|| node.V1 + 50 <= D
				|| node.V2 + 50 <= D) {
				cout << "Yes";
				return;
			}

			for (int i = 0; i < N; i++)
				if (!Map[i].Check
					&& (Map[i].V1 - node.V1) * (Map[i].V1 - node.V1)
					+ (Map[i].V2 - node.V2) * (Map[i].V2 - node.V2)
					<= D * D + 30 * D + 225)
				{
					Map[i].Check = true;
					Q.push(Map[i]);
				}
		}
		else {
			if (50 - node.V1 <= D
				|| 50 - node.V2 <= D
				|| node.V1 + 50 <= D
				|| node.V2 + 50 <= D) {
				cout << "Yes";
				return;
			}

			for (int i = 0; i < N; i++)
				if (!Map[i].Check
					&& (Map[i].V1 - node.V1) * (Map[i].V1 - node.V1)
					+ (Map[i].V2 - node.V2) * (Map[i].V2 - node.V2)
					<= D * D)
				{
					Map[i].Check = true;
					Q.push(Map[i]);
				}
		}

		Q.pop();
	}

	cout << "No";
}