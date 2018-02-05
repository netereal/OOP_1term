#include <iostream>
#include <iomanip>
using namespace std;
typedef long double lg;

lg EsIstMeinCos(double x)
{
	lg EPS = 1e-18;
	lg pi = 3.141592;
	if (abs(x) > pi / 4) return 0;

	lg res = 1;
	int n = 0;
	lg temp1 = 0;
	lg temp2 = 1;
	do
	{
		temp1 = temp2;
		temp2 *= (-x*x) / ((2 * n + 1)*(2 * n + 2));
		n++;
		res += temp2;
	} while (abs(temp2 - temp1) >= EPS);
	return res;
}

int main()
{
	lg x;
	cin >> x;
	cout << "cos(" << x << ") = " << fixed << setprecision(20) << EsIstMeinCos(x) << endl;
	system("pause");
}