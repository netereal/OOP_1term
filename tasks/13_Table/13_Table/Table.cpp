#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Matrix;

Matrix input(string path) {
	int m = 0, n = 0;
	ifstream in(path);
	in >> m >> n;
	Matrix matr(m);
	for (int i = 0; i < m; i++) 
	{
		matr[i].resize(n);
		for (int j = 0; j < n; j++) 
		{
			in >> matr[i][j];
		}
	}
	in.close();
	return matr;
}
void output(Matrix matr) {
	for (size_t i = 0; i < matr.size(); i++) {
		for (size_t j = 0; j < matr[i].size(); j++) {
			cout << matr[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}
void function(Matrix matr) {
	int sum = 0;
	pair<int, int> first(0,0), second(0,0);
	for (size_t first_i = 0; first_i < matr.size(); first_i++) {
		for (size_t first_j = 0; first_j < matr[first_i].size(); first_j++) {
			for (size_t second_i = 0; second_i < matr.size(); second_i++) {
				for (size_t second_j = 0; second_j < matr[second_i].size(); second_j++) {
					if (first_i == second_i || first_j == second_j) continue;
					int temp = matr[first_i][first_j] + matr[first_i][second_j] + matr[second_i][first_j] + matr[second_i][second_j];
					if (temp > sum) {
						sum = temp;
						first.first = first_i;
						first.second = first_j;
						second.first = second_i;
						second.second = second_j;
					}
				}
			}
		}
	}
	cout << "(" << first.first + 1 << "," << first.second + 1 << ") - " << matr[first.first][first.second] << endl;  // f_i f_j
	cout << "(" << second.first + 1 << "," << first.second + 1 << ") - " << matr[second.first][first.second] << endl;// s_i f_j
	cout << "(" << second.first + 1 << "," << second.second + 1 << ") - " << matr[second.first][second.second] << endl;// s_i s
	cout << "(" << first.first + 1 << "," << second.second + 1 << ") - " << matr[first.first][second.second] << endl;// f_i s_j
	cout << "Sum = " << sum << endl << endl;
}
int main() 
{
	Matrix matr = input("kaka.txt");
	output(matr);
	function(matr);
	system("pause");
}
