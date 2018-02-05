﻿//36.  На стол кладется кучка из N спичек, затем Игрок 1 с Игроком 2 по очереди 
//берут спички из кучки.Первым берет Игрок 1, ему разрешается взять от 1 до К спичек.
//Затем игрок может взять любое количество спичек, не более чем на 1 превышающее 
//то количество, которое взял игрок перед ним(можно взять меньше  или столько же, 
//но обязательно хотя бы одну).Например, если N = 10, К = 5, то на первом ходу 
//Игрок 1 может взять 1, 2, 3, 4 или 5 спичек; если Игрок 1 возьмет 3, то на следующем 
//ходу Игрок 2 может взять 1. 2, 3 или 4; и если Игрок 2 возьмет 1, то Игрок 1 затем 
//может взять 1 или 2, и т.д.Проигрывает тот, кто возьмет последнюю спичку.Рассчитать, 
//какое количество спичек должен взять на первом ходу Игрок 1, чтобы выиграть при любой игре Игрока 2.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int check_move(int all, int maxAllowed) {
	if (maxAllowed >= all - 1) return all - 1;

	for (int i = 1; i < maxAllowed; i++) {
		int leftOnBoard = all - i;
		int nextMoveAllowed = i + 1;

		if (check_move(leftOnBoard, nextMoveAllowed) == 0) {
			return i;
		}

	}
	return 0;
}

int main() {
	int n, k;
	cout << "N: ";
	cin >> n;
	cout << "k: ";
	cin >> k;

	int res = check_move(n, k);
	if (res) cout << res << " match(es)" << endl;
	else cout << "You Lose \n";

	system("Pause");
	return 0;
}