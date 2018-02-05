#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef pair<int, int> Element;
typedef pair<int, vector<Element>> Massiv;
typedef vector<Massiv> Matrix;

int val = 0, ind_i = 0, ind_j = 0;

Matrix Input(string path)
{
	ifstream fin(path);
	Matrix matrix;
	int n;
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		Massiv tmp_mas;
		for (int j = 0; j < n; j++)
		{
			int a;
			fin >> a;
			if (a != 0)
			{
				Element el;
				el.first = j;
				el.second = a;
				tmp_mas.second.push_back(el);
			}
		}
		if (!tmp_mas.second.empty())
		{
			tmp_mas.first = i;
			matrix.push_back(tmp_mas);
		}
	}
	fin.close();
	return matrix;
}
void Output(Matrix matrix)
{
	cout << "Matrix: " << endl;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		cout << "[" << matrix[i].first << "]: ";
		for (size_t j = 0; j < matrix[i].second.size(); j++)
		{
			cout << "(" << matrix[i].second[j].first << ", " << matrix[i].second[j].second << ") ";
		}
		cout << endl;
	}
	cout << endl;
}

void FindMax(Matrix matrix)
{
	val = matrix[0].second[0].second;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t j = 0; j < matrix[i].second.size(); j++)
		{
			if (matrix[i].second[j].second > val)
			{
				val = matrix[i].second[j].second;
				ind_i = i;
				ind_j = matrix[i].second[j].first;
			}
		}
	}
}
void Function(Matrix &matrix)
{
	FindMax(matrix);
	for (size_t i = 0; i < matrix.size(); i++)
	{
		if (matrix[i].first == ind_i) { matrix.erase(matrix.begin() + i); i--; continue; }
		for (size_t j = 0; j < matrix[i].second.size(); j++)
		{
			if (matrix[i].second[j].first == ind_j) matrix[i].second.erase(matrix[i].second.begin() + j);
		}
	}
}

int main()
{
	Matrix matrix = Input("matrix.txt");
	Output(matrix);
	Function(matrix);
	Output(matrix);
	system("pause");
}