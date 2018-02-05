#include <iostream>
#include <conio.h>
#include <time.h>

using namespace std;

double func(double x, double y) {
	return x*x + y*y;
}

double randDigs(double up, double low) {
	return low + (up - low)*(double(rand()) / RAND_MAX);
}

int main() {
	srand(time(NULL));
	double x;
	double y;
	double upX = 1;
	double upY = 2 * upX - 1;
	double lowX = 0.5;
	double lowY = 0;
	double checkUpY = 0;
	double sum = 0;
	double integral = 0;

	int N;
	cout << "Enter N = ";
	cin >> N;

	for (int i = 0; i < N; i++) {
		x = randDigs(upX, lowX);
		y = randDigs(upY, lowY);

		checkUpY = 2 * x - 1;
		if ((y > lowY) && (y < checkUpY))
			sum += func(x, y);
	}
	integral = sum*(upX - lowX)*(upY - lowY) / N;
	cout << "Integral: " << integral << endl;
	system("pause");
}