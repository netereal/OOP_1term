#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

int **graph;
int* colorArr;
int vertices;


void input() {
	ifstream in("Graph.txt");

	if (!in.is_open())
		cout << "File not found.";
	else {
		in >> vertices;
		graph = new int*[vertices];
		for (int i = 0; i < vertices; i++) graph[i] = new int[vertices];
		for (int i = 0; i < vertices; i++)
			for (int j = 0; j < vertices; j++) {
				in >> graph[i][j];
			}
	}
}
void clean() {
	delete[] colorArr;
	for (int i = 0; i < vertices; i++)
		delete[] graph[i];
}
void show() {
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++)
			cout << graph[i][j] << ' ';
		cout << endl;
	}

}
// This function returns true if graph G[V][V] is Bipartite, else false
bool isBipartite()
{
	int src = 0;
	// Create a color array to store colors assigned to all veritces. Vertex 
	// number is used as index in this array.
	colorArr = new int[vertices];
	for (int i = 0; i < vertices; ++i)
		colorArr[i] = -1;

	// Assign first color to source
	colorArr[src] = 1;

	// BFS traversal
	queue <int> q;
	q.push(src);

	// Run while there are vertices in queue (Similar to BFS)
	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		// Return false if there is a self-loop 
		if (graph[u][u] == 1)
			return false;

		// Find all non-colored adjacent vertices
		for (int v = 0; v < vertices; ++v)
		{
			// An edge from u to v exists and destination v is not colored
			if (graph[u][v] && colorArr[v] == -1)
			{
				// Assign alternate color to this adjacent v of u
				colorArr[v] = 1 - colorArr[u];
				q.push(v);
			}
			//  An edge from u to v exists and destination v is colored with
			// same color as u
			else if (graph[u][v] && colorArr[v] == colorArr[u])
				return false;
		}
	}
	for (int v = 0; v < vertices; ++v)
		if (colorArr[v] == 0)
			cout << v << ' ';
	cout << endl;
	for (int v = 0; v < vertices; ++v)
		if (colorArr[v] == 1)
			cout << v << ' ';
	cout << endl;

	// If we reach here, then all adjacent vertices can be colored with 
	// alternate color
	return true;
}

int main() {

	input();
	show();
	isBipartite() ? cout << "Yes" : cout << "No";
	cout << endl;
	system("pause");
	clean();
	return 0;
}