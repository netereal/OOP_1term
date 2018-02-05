#include <iostream>
#include <string>
using namespace std;

int main(void) {
	string str1, str2, longest;
	getline(cin, str1);
	getline(cin, str2);
	for (int i = 0; str1[i]; i++)
		for (int j = 0; str2[j]; j++) {
			if (str2[j] == str1[i]) {
				longest += str2[j];
				str2.erase(j, 1);
				break;
			}
		}
	cout << longest;
	cout << endl;
	system("pause");
}