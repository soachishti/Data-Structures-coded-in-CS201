#include <iostream>
#include <windows.h>
#include <queue> 
using namespace std;

class Graph {
public:
	int TotalVertice = 10;
	int **AdjacencyMatrix;
	int **VerticeInfo;

	Graph(int tv) {
		TotalVertice = tv;
		AdjacencyMatrix = new int*[TotalVertice];
		for (int i = 0; i < TotalVertice; i++) {
			AdjacencyMatrix[i] = new int[TotalVertice];
			for (int j = 0; j < TotalVertice; j++) {
				AdjacencyMatrix[i][j] = 0;
			}
		}

		VerticeInfo = new int*[TotalVertice];
		for (int i = 0; i < TotalVertice; i++) {
			VerticeInfo[i] = new int[2];
			VerticeInfo[i][0] = i;		// Vertice Info 
			VerticeInfo[i][1] = 0;		// Flag: set to 0
			
		}
	}

	bool AddEdge(int vertice1, int vertice2) {
		if (vertice1 >= 0 && vertice2 >= 0 && vertice1 < TotalVertice && vertice2 < TotalVertice) {
			AdjacencyMatrix[vertice1][vertice2]++;
			return true;
		}
		return false;
	}

	void print() {
		for (int i = 0; i < TotalVertice; i++) {
			for (int j = 0; j < TotalVertice; j++) {
				cout << AdjacencyMatrix[i][j] << "\t";
			}
			cout << endl;
		}
	}

	bool bfs(int key) {
		queue<int> q;
		q.push(0);
		while (!q.empty()) {
			int vertice = q.front();
			q.pop();
			for (int i = 0; i < TotalVertice; i++) {
				// Check Flag
				if (VerticeInfo[vertice][1] == 0) {
					// Found data
					if (VerticeInfo[vertice][0] == key) {
						for (int i = 0; i < TotalVertice; i++) VerticeInfo[i][1] = 0; // Reset flags
						return true;
					}
					VerticeInfo[vertice][1] = 1;
				}
					
				// Is there edge, Then add to queue.	
				if (VerticeInfo[i][1] == 0 && AdjacencyMatrix[vertice][i] != 0) {
					q.push(i);
				}
			}
		}
		for (int i = 0; i < TotalVertice; i++) VerticeInfo[i][1] = 0; // Reset flags
		return false;
	}
};

int main() {
	int TotalVertice = 5;
	Graph g(TotalVertice);
	// Each vertice are named after their index 0-(TotalVertice-1)

	g.AddEdge(0, 1);
	g.AddEdge(1, 2);
	g.AddEdge(2, 0);

	cout << g.bfs(1) << endl;
	cout << g.bfs(2) << endl;
	cout << g.bfs(3) << endl; // No edge to 3

	g.AddEdge(2, 3);			// Adding edge to 3
	cout << g.bfs(3) << endl; 

	g.print();

	return 0;
}