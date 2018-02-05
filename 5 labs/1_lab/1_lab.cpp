#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <vector>
using namespace std;

#define M 20 //maximum no. of constraints
#define N 20 //maximum no. of variables

struct Table {
	int rows, columns; // m is no. of rows, n is no. of columns (note the difference to input m and n)
	double matrix[M][N]; //the tableau
	vector<int> basic; // contains index of basic variable;
};

int check_result;

static const double epsilon = 0.0001;

int equal(double a, double b)
{
	return fabs(a - b) < epsilon;
}


//read in data from file to tab
bool read_table(Table *tab, const char * filename)
{
	ifstream file(filename);
	if (!file) {
		cout << "Cannot read " << filename;
		return false;
	}

	file >> tab->rows;
	file >> tab->columns;

	tab->rows++; tab->columns++;//row 0 and column 0
	for (int i = 0; i < tab->rows; i++) {
		for (int j = 0; j < tab->columns; j++) {
			file >> tab->matrix[i][j];
		}
	}
	for (int i = 1; i < tab->rows; i++)
		if (tab->matrix[i][0] < 0) {
			cout << "There isn't any results in this system." << endl;
			return false;
		}

	//create canonic form
	for (int j = tab->columns; j < 2 * (tab->columns - 1) + 1; j++) {
		tab->matrix[0][j] = 0;
	}

	int check = tab->columns;

	for (int i = 1; i < tab->rows; i++) {
		tab->matrix[i][check] = 1;
		check++;
		for (int j = tab->columns; j < 2 * (tab->columns - 1) + 1; j++) {
			if (tab->matrix[i][j] != 1) tab->matrix[i][j] = 0;
			else tab->basic.push_back(j);
		}
	}

	tab->columns = tab->rows - 1 + tab->columns;
	//
	printf("Read tableau [%d rows x %d columns] from file '%s'.\n",
		tab->rows, tab->columns, filename);
	file.close();
	return true;

}

// create line for display of tableau
void line(int k)
{
	for (int j = 0; j < k; j++)
		cout << '-';
	cout << endl;
}


void print_table(Table *tab, const char* mes) {
	int counter = 0;

	cout << endl << ++counter << ". Tableau " << mes << endl;

	cout << "    b[i]";
	for (int j = 1; j < tab->columns; j++)
		cout << "    x" << j << " ";
	cout << endl;
	line(tab->columns * 7);

	for (int i = 0; i < tab->rows; i++) {
		if (counter > 2) {// only for tableaux in shortened form
			if (i == 0)
				cout << "min ";
			else
				cout << "x" << tab->basic[i] << "  ";
		}
		for (int j = 0; j < tab->columns; j++) {
			if (equal((int)tab->matrix[i][j], tab->matrix[i][j]))
				printf(" %6d", (int)tab->matrix[i][j]);
			else
				printf(" %6.2lf", tab->matrix[i][j]);
		}
		cout << endl;
	}
}


void print_solution(Table *tab, int l)
{
	double* var = new double[tab->rows];

	for (int j = 0; j < tab->rows; j++)
		var[j] = tab->matrix[j][0];

	cout << "The maximal value " << tab->matrix[0][0] << " is attained for:" << endl;

	for (int k = 1; k < tab->rows; k++) {
		if (tab->matrix[k][1] == 1)
			printf("     x_%i = %f\n", 1, var[k]);
		if (tab->matrix[k][2] == 1)
			printf("     x_%i = %f\n", 2, var[k]);
	}
	line(80);
}

bool simplex_first(Table *tab)
{
	bool check_if_negative = true;
	double min_F = INFINITY, min = INFINITY, cross_num;
	int min_column, min_row;
	while (check_if_negative != false) {

		check_if_negative = false;
		for (int j = 0; j < tab->columns; j++) {
			if (tab->matrix[0][j] < 0)
				check_if_negative = true;
		}
		if (check_if_negative == false)
			return true;

		for (int j = 1; j < tab->columns; j++) {
			if (tab->matrix[0][j] < min_F) {
				min_F = tab->matrix[0][j];
				min_column = j;
			}
		}

		for (int i = 1; i < tab->rows; i++) {
			if ((tab->matrix[i][0] / tab->matrix[i][min_column] < min) && (tab->matrix[i][0] > 0) && (tab->matrix[i][min_column] > 0)) {
				min_row = i;
				min = tab->matrix[i][0] / tab->matrix[i][min_column];
			}
		}
		cross_num = tab->matrix[min_row][min_column];
		tab->basic[min_row - 1] = min_column;

		for (int j = 0; j < tab->rows; j++) {
			if (j != min_row)
				for (int i = 0; i < tab->columns; i++)
					if (i != min_column)
						tab->matrix[j][i] = tab->matrix[j][i] - tab->matrix[j][min_column] * tab->matrix[min_row][i] / cross_num;
		}

		for (int i = 0; i < tab->columns; i++)
			tab->matrix[min_row][i] = tab->matrix[min_row][i] / cross_num;

		for (int j = 0; j < tab->rows; j++)
			if (j != min_row) tab->matrix[j][min_column] = tab->matrix[j][min_column] / cross_num;


		for (int i = 0; i < tab->rows; i++) {
			if (i != min_row) tab->matrix[i][min_column] = 0;
			else tab->matrix[i][min_column] = 1;
		}

		print_table(tab, "simplex first");
		min_F = 0;
		min = INFINITY;

		if (tab->matrix[1][0] == check_result) {
			cout << "No result of system!" << endl;
			return false;
		}
	}
}

void simplex_move(Table *tab, int min_column, int min_row)
{
	double cross_num;

	cross_num = tab->matrix[min_row][min_column];
	for (size_t i = 0; i < tab->basic.size(); i++)
		if (tab->basic[i] == (tab->columns - 1)) {
			tab->basic[i] = min_column;
			break;
		}

	for (int j = 0; j < tab->rows; j++) {
		if (j != min_row)
			for (int i = 0; i < tab->columns; i++)
				if (i != min_column)
					tab->matrix[j][i] = tab->matrix[j][i] - tab->matrix[j][min_column] * tab->matrix[min_row][i] / cross_num;
	}

	for (int i = 0; i < tab->columns; i++)
		tab->matrix[min_row][i] = tab->matrix[min_row][i] / cross_num;

	for (int j = 0; j < tab->rows; j++)
		if (j != min_row) tab->matrix[j][min_column] = tab->matrix[j][min_column] / cross_num;

	for (int i = 0; i < tab->rows; i++) {
		if (i != min_row) tab->matrix[i][min_column] = 0;
		else tab->matrix[i][min_column] = 1;
	}

	print_table(tab, "simplex_move");

}

double max_data(double *array, int n)
{
	double max_d = -1;
	int max_index;
	for (int i = 0; i < (n - 1); i++)
		if (array[i] >(max_d + epsilon)) {
			max_d = array[i];
			max_index = i;
		}
	return (max_index);
}

bool gomory(Table *tab)
{
	/*
	for (int i = 0; i < tab->columns; i++)
	tab->matrix[0][i] = -tab->matrix[0][i];
	*/

	while (true) {
		bool if_finally = true;
		double* array = new double[tab->rows];
		for (int i = 1; i < tab->rows; i++) {
			array[i - 1] = tab->matrix[i][0] - (int)(tab->matrix[i][0] + epsilon);
			cout << array[i - 1] << " ";
		}
		cout << endl;
		for (int i = 0; i < tab->rows; i++)
			if (array[i] > epsilon) {
				if_finally = false;
				break;
			}

		if (if_finally == true) {
			cout << "Getting result..." << endl;
			return true;
		}

		int max_remaining_index = max_data(array, tab->rows);

		tab->matrix[tab->rows][tab->columns] = 1;

		for (int j = 0; j < tab->rows; j++)
			tab->matrix[j][tab->columns] = 0;

		tab->matrix[tab->rows][0] = -array[max_remaining_index];

		double max_timetable = 0, min_timetable = INFINITY;
		int max_index_row = 0, min_index_column = 0;

		for (int j = 1; j < tab->columns; j++) {
			if ((fabs(tab->matrix[max_remaining_index + 1][j] - (int)tab->matrix[max_remaining_index + 1][j]) > epsilon)
				&& (fabs(tab->matrix[max_remaining_index + 1][j] - (int)(tab->matrix[max_remaining_index + 1][j]) + epsilon) > epsilon)) {
				if (tab->matrix[max_remaining_index + 1][j] > 0)
					tab->matrix[tab->rows][j] = (int)tab->matrix[max_remaining_index + 1][j] - tab->matrix[max_remaining_index + 1][j];
				if (tab->matrix[max_remaining_index + 1][j] < 0)
					tab->matrix[tab->rows][j] = -1 - (int)fabs(tab->matrix[max_remaining_index + 1][j]) - tab->matrix[max_remaining_index + 1][j];
			}
			else (tab->matrix[tab->rows][j] = 0);
		}
		tab->columns = tab->columns + 1;
		tab->rows = tab->rows + 1;

		for (int i = 1; i < tab->rows; i++) {
			if ((fabs(tab->matrix[i][0]) > max_timetable) && (tab->matrix[i][0] < 0)) {
				max_index_row = i;
				max_timetable = fabs(tab->matrix[i][0]);
			}
		}

		for (int j = 1; j < tab->columns; j++) {
			if (fabs(fabs(tab->matrix[0][j]) / tab->matrix[max_index_row][j] - epsilon) < min_timetable && tab->matrix[0][j] != 0 && tab->matrix[max_index_row][j] != 0) {
				min_timetable = fabs(tab->matrix[0][j]) / fabs(tab->matrix[max_index_row][j] - epsilon);
				min_index_column = j;
			}
		}

		tab->basic.push_back(tab->columns - 1);

		print_table(tab, "Gomory");

		simplex_move(tab, min_index_column, max_index_row);
	}
}

int main() {
	//read in data
	Table *tab = new Table;
	bool check_simplex;
	bool check_gomory;
	if (read_table(tab, "matrix.txt")) {
		print_table(tab, "Initial");

		check_result = tab->matrix[1][0];
		int l = tab->columns - tab->rows - 1;// l is original number of variables

		check_simplex = simplex_first(tab);
		if (check_simplex)
			check_gomory = gomory(tab);
		else
			cout << "No result after simplex method." << endl;
		if (check_gomory)
			print_solution(tab, l);
		else
			cout << "No solution." << endl;
	}
	system("pause");
	return 0;
}
