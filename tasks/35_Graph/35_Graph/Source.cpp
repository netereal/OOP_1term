#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
typedef vector<vector<int>> Matrix;

int vertices;
Matrix matrix;
vector<char> used;
bool res = true;

void Input(string path)
{
	ifstream fin(path);
	fin >> vertices;
	matrix.resize(vertices);
	for (int i = 0; i < vertices; i++)
	{
		vector<int> tmp(vertices);
		for (int j = 0; j < vertices; j++)
			fin >> tmp[j];
		matrix[i] = tmp;
	}
	fin.close();
	used.resize(vertices);
}
void DFS(int current, int prev = -1)
{
	if (!res) return;
	used[current] = 1;
	for (int i = 0; i < vertices; i++)
		if (matrix[current][i])
		{
			if (!used[i]) DFS(i, current);
			else if (used[i] == 1)
			{
				res = false;
				return;
			}
		}
	used[current] = 2;
}

int main()
{
	Input("Graph.txt");
	DFS(0);
	if (res) cout << "OK" << endl; else cout << "NO" << endl;
	system("pause");
	return 0;
}