#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <ctime>
using namespace std;
typedef vector<vector<int>> Matrix;
#define min(a,b) ((a)>(b) ? (b) : (a))
const int INF = 100000000;

Matrix Input(string path)
{
	ifstream fin(path);
	Matrix res;
	int vertices;
	fin >> vertices;
	res.resize(vertices);
	for (int i = 0;i < vertices;i++)
	{
		res[i].resize(vertices);
		for (int j = 0;j < vertices;j++)
		{
			fin >> res[i][j];
			if (!res[i][j]) res[i][j] = INF;
		}
	}
	fin.close();
	return res;
}
void Output(Matrix m)
{
	size_t n = m.size();
	for (size_t i = 0; i < n;i++)
	{
		for (size_t j = 0; j < n; j++) cout << m[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
	cout << endl;
}

Matrix UsualFloid(Matrix d)
{
	int n = d.size();
	for (int k = 0; k < n; ++k)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	return d;
}

void func(Matrix &d, int k1, int k2, int n)
{
	for (int k = min(k1, n); k < min(k2, n); k++)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}
Matrix ParallelFloid(Matrix m, int thread_count)
{
	if (thread_count > m.size()) thread_count = m.size();
	vector<thread> thrds(thread_count);
	int n = (m.size() % thread_count ? m.size() / thread_count + 1 : m.size() / thread_count);
	for (int i = 0; i < thread_count; i++)
		thrds[i] = thread(func, ref(m), n*i, n*(i + 1), m.size());
	for (int i = 0; i < thread_count; i++) if (thrds[i].joinable()) thrds[i].join();
	return m;
}

int main()
{
	Matrix matrix = Input("input.txt");
	int thread_count;
	cin >> thread_count;

	unsigned long long t1, t2;

	t1 = clock();
	Matrix usual = UsualFloid(matrix);
	//Output(usual);
	t2 = clock();
	t2 -= t1;
	cout << " Time 1: " << t2 << endl;

	t1 = clock();
	Matrix parall = ParallelFloid(matrix, thread_count);
	//Output(parall);
	t2 = clock();
	t2 -= t1;
	cout << " Time 2: " << t2 << endl;


	system("pause");
	return 0;
}