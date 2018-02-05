#include <iostream>
using namespace std;

void Func()
{
	int N;

	int M;
	int S; 
	int K; 
	int L; 
	cout << "N = "; cin >> N;
	cout << "M = "; cin >> M;
	cout << "S = "; cin >> S;
	cout << "K = "; cin >> K;
	cout << "L = "; cin >> L;

	bool *monets = new bool[N + M];
	for (int i = 0; i < M + N; i++) monets[i] = false;

	for (int i = 0; i < K; i++)
	{
		int iter = (i*S) % (M + N);
		monets[iter] = !monets[iter];
	}

	if (N < L)
	{
		int cnt = 0;
		for (int i = 0; i < M + N; i++) if (monets[i]) cnt++;
		if ((M + N - cnt) % 2) { cout << "Impossible" << endl; delete[] monets; return; }
		for (int i = 0; i < cnt; i++) cout << "O" << " ";
		cnt = (M + N - cnt) / 2;
		for (int i = 0; i < cnt; i++) cout << "P" << " ";
		for (int i = 0; i < cnt; i++) cout << "O" << " ";
	}
	else 
	{
		int cnt = 0;
		for (int i = 0; i < M + N; i++) if (monets[i]) cnt++;
		if ((M + N - cnt) % 2) { cout << "Impossible" << endl; delete[] monets; return; }
		for (int i = 0; i < cnt; i++) cout << "P" << " ";
		cnt = (M + N - cnt) / 2;
		for (int i = 0; i < cnt; i++) cout << "P" << " ";
		for (int i = 0; i < cnt; i++) cout << "O" << " ";
	}
	cout << endl << endl;
	delete[] monets;
}

int main()
{
	Func();
	system("pause");
}