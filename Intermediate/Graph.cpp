#include <iostream>
#include <vector>
#include <queue> 
using namespace std;

struct GraphNode {
	int data;
	GraphNode *next;
	bool flag = false;
};

class Graph {
public:
	vector<GraphNode*> vertex;

	int AddVertice() {
		int id = vertex.size();
		GraphNode* tmp = new GraphNode;
		tmp->data = id;
		tmp->next = NULL;
		vertex.push_back(tmp);
		return id;
	}

	void AddEdge(int vertice1, int vertice2) {
		for (auto vertice : vertex) {
			if (vertice->data == vertice1) {
				GraphNode* tmp = new GraphNode;
				tmp->data = vertice2;
				tmp->next = NULL;
				GraphNode* edge = vertice;
				while (edge->next != NULL) {
					edge = edge->next;
				}
				edge->next = tmp;
				break;
			}
		}
	}

	void print() {
		for (auto vertice : vertex) {
			cout << vertice->data << "| -> ";
			auto edge = vertice->next;
			while (edge != NULL) {
				cout << edge->data << " -> ";
				edge = edge->next;
			}
			cout << endl;
		}
	}

	GraphNode* getVertice(int key) {
		for (auto vertice : vertex) {
			if (vertice->data == key) {
				return vertice;
			}
		}
		return NULL;
	}

	void bfs(int key) {
		GraphNode *vertice, *edge;
		queue<int> q;
		q.push(0);
		while (!q.empty()) {
			vertice = getVertice(q.front());
			q.pop();
			edge = vertice->next;
			while (edge != NULL) {
				if (getVertice(edge->data)->flag == false) {
					cout << edge->data << endl;
					if (key == edge->data) {
						cout << "Found" << endl;
					}
					getVertice(edge->data)->flag = true;
					q.push(edge->data);
				}
				edge = edge->next;
			}
		}
	}

};

int main() {
	Graph g;
	int v1 = g.AddVertice();
	int v2 = g.AddVertice();
	int v3 = g.AddVertice();
	int v4 = g.AddVertice();
	int v5 = g.AddVertice();

	g.AddEdge(v1, v2);
	g.AddEdge(v1, v3);
	g.AddEdge(v1, v4);
	g.AddEdge(v1, v5);

	g.AddEdge(v2, v1);
	g.AddEdge(v2, v3);

	g.AddEdge(v1, v1);

	g.bfs(v5);

	g.print();

	return 0;
}