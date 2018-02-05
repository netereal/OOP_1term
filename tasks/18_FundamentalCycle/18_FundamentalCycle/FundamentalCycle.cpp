#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<vector<int>> Matrix;

Matrix graph;
int vertices, edges;
vector<int> weight;

vector<char> used_edges;
vector<char> used_vertices;

vector<char> path;
bool _end;

void Input(string path)
{
	ifstream fin(path);
	fin >> vertices >> edges;
	graph.resize(vertices);
	for (int i = 0; i < vertices; i++)
	{
		graph[i].resize(edges);
		for (int j = 0; j < edges; j++)
			fin >> graph[i][j];
	}
	weight.resize(edges);
	for (int i = 0; i < edges; i++) fin >> weight[i];
	fin.close();
}

bool Compare(int a, int b)
{
	return weight[a] < weight[b];
}
Matrix KruskalFunc(Matrix matrix, vector<int> weight)
{
	vector<char> vertices_tree(matrix.size());
	vector<char> sorted_edges(matrix[0].size());
	for (size_t i = 0; i < vertices_tree.size(); i++) vertices_tree[i] = (char)i;
	for (size_t i = 0; i < sorted_edges.size(); i++) sorted_edges[i] = (char)i;
	sort(sorted_edges.begin(), sorted_edges.end(), Compare);
	vector<char> used_edges(matrix[0].size());
	for (size_t i = 0; i < sorted_edges.size(); i++)
	{
		int a, b = -1;
		for (size_t j = 0; j < matrix.size(); j++)
			if (matrix[j][sorted_edges[i]]) { a = b; b = j; }
		if (vertices_tree[a] != vertices_tree[b])
		{
			for (size_t j = 0; j < vertices_tree.size(); j++)
				if (vertices_tree[j] == vertices_tree[b])
					vertices_tree[j] = vertices_tree[a];
			used_edges[sorted_edges[i]] = 1;
		}
	}
	Matrix res = matrix;
	for (size_t i = 0; i < res[0].size(); i++)
		if (!used_edges[i])
		{
			for (size_t j = 0; j < res.size(); j++)	res[j][i] = 0;
		}
	return res;
}

bool IsAdjacent(int a, int b)
{
	for (int i = 0; i < edges; i++)
		if (graph[a][i])
			for (int j = 0; j < vertices; j++)
				if (graph[j][i] && j == b) return true;
	return false;
}
void DFS(int current, int find)
{
	if (_end) return;
	used_vertices[current] = 1;
	for (int i = 0; i < edges; i++)
		if (graph[current][i])
		{
			for (int j = 0; j < vertices; j++)
				if (graph[j][i] && !used_vertices[j])
				{
					path[j] = current;
					if (j == find) return;
					DFS(j, find);
				}
		}
}
void Func()
{
	for (int i = 0; i < vertices; i++)
		for (int j = 0; j < vertices; j++)
			if (!IsAdjacent(i, j))
			{
				used_edges.assign(edges, 0);
				used_vertices.assign(vertices, 0);
				path.assign(edges, -1);
				_end = false;
				DFS(j, i);
				cout << i << " - ";
				for (size_t k = path[i]; k != -1; k = path[k]) cout << k << ' ';
				cout << "- " << j;
				cout << endl;
			}
}

int main()
{
	Input("matrix.txt");
	graph = KruskalFunc(graph, weight);
	Func();
	system("pause");
	return 0;
}