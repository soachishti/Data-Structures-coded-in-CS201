#include <iostream>
#include <windows.h>
#include <queue> 
#include <stack> 
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

    void ResetFlags() {
        for (int i = 0; i < TotalVertice; i++) VerticeInfo[i][1] = 0; // Reset flags
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
		            cout << VerticeInfo[vertice][0] << endl;
					// Found data
					if (VerticeInfo[vertice][0] == key) {
                        
                        ResetFlags();
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
		ResetFlags();
		return false;
	}
    
    bool dfs(int key) {
		stack<int> s;
		s.push(0);
		while (!s.empty()) {
			int vertice = s.top();               
			int StackSize = s.size();
            for (int i = 0; i < TotalVertice; i++) {
				// Check Flag
				if (VerticeInfo[vertice][1] == 0) {
                    cout << VerticeInfo[vertice][0] << endl;
                    // Found data
					if (VerticeInfo[vertice][0] == key) {
						ResetFlags();
						return true;
					}
					VerticeInfo[vertice][1] = 1;
				}					
				               
                // Is there edge, Then add to queue.	
				if (VerticeInfo[i][1] == 0 && AdjacencyMatrix[vertice][i] != 0) {
					s.push(i);
                    break;
				}
			}
            // If no new vertice added, Mean it is end
            if (StackSize == s.size()) {
                // Backtracking
                s.pop();
            }
		}
		ResetFlags();
		return false;
	}    
    
    bool HaveLoop() {
		stack<int> s;
		s.push(0);
        bool isBack = false;
		while (!s.empty()) {
			int vertice = s.top();               
			int StackSize = s.size();
            for (int i = 0; i < TotalVertice; i++) {
				// Check Flag
				if (VerticeInfo[vertice][1] == 0) {
                    cout << VerticeInfo[vertice][0] << endl;
					VerticeInfo[vertice][1] = 1;
				}					
				cout << vertice << "\t" << i << endl;   
                // Is there edge, Then add to queue.	
				if (VerticeInfo[i][1] == 0 && AdjacencyMatrix[vertice][i] != 0) {
					s.push(i);
                    break;
				} else if (!isBack && VerticeInfo[i][1] == 1 && AdjacencyMatrix[vertice][i] != 0) {
                    return true;
                }
			}
            // If no new vertice added, Mean it is end
            if (StackSize == s.size()) {
                // Backtracking
                s.pop();
            }
		}
		ResetFlags();
		return false;
	}    
    
    
};

int main() {
    
    // Test three
    int TotalVertice = 3;
    Graph g(TotalVertice);
    //g.AddEdge(0,1); 
    g.AddEdge(2,1);
    g.AddEdge(1,2);
    //g.AddEdge(2,0); 
    g.AddEdge(0,1); // For starting point 

    //g.print();    
    cout << endl << g.HaveLoop(); 
    return 0;  
    
    
    // Test two
/*     int TotalVertice = 8;
    Graph g(TotalVertice);
    g.AddEdge(0,1); // a->b
    g.AddEdge(0,2); // a-c
    g.AddEdge(0,3); // a-d
    g.AddEdge(1,4); // b->e
    g.AddEdge(1,5); // b->f
    g.AddEdge(5,7); // f->h
    g.AddEdge(3,6); // d->g

    cout << "DFS Traversal: \n";
    g.dfs(-1);
    cout << endl; 
    
    cout << "BFS Traversal: \n";
    g.bfs(-1); 
    
    //g.print();    
    cout << endl << g.HaveLoop(); 
    return 0; */
    
    /* 
    // Test One
    int TotalVertice = 5;
	Graph g(TotalVertice);
	// Each vertice are named after their index 0-(TotalVertice-1)

    
	g.AddEdge(0, 1);
	g.AddEdge(1, 2);
	g.AddEdge(2, 0);

	//cout << g.bfs(1) << endl;
	//cout << g.bfs(2) << endl;
	//cout << g.bfs(3) << endl; // No edge to 3

	g.AddEdge(2, 3);			// Adding edge to 3
	g.AddEdge(3, 4);			// Adding edge to 3
	g.AddEdge(4, 2);			// Adding edge to 3
	g.AddEdge(4, 0);			// Adding edge to 3
	//cout << g.bfs(3) << endl; 
        
    cout << "DFS Traversal: \n";
    g.dfs(-1);
    cout << endl; 
    
    cout << "BFS Traversal: \n";
    g.bfs(-1); 

    cout << endl << g.HaveLoop() << endl;    
	g.print();    */ 
	return 0;
}