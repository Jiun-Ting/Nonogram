#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

vector <vector <int> > temp;
vector <int> vec;
vector <int> vecx;
int n_row;
int n_column;

//////// ------ find possible blanks locations in each row  -///////////////////////////////////////////////////
void blank(int m, int n, int g) {
	int i, j;
	if (m == g) {
		for (i = 0; i < g; ++i) {
			vec.push_back(vecx[i]);
		}
		vec.push_back(n);
		temp.push_back(vec);
		vec.clear();
		return;
	}

	for (i = 0; i <= n; ++i) {
		vecx.insert(vecx.begin() + m, i);
		blank(m + 1, n - i, g);
	}
}

///////// ------ initial guess ----------------- ///////////////////////////////////////////////////////////////////
vector <int> guess(int n, vector <int> x, vector <int> guess_temp) {
	int i, j, u, k;
	vector <vector<int> > maps{ {} };
	vector <int> B;

	for (i = 0; i < temp.size(); i++) {
		for (j = 0; j < x.size(); j++) {
			for (k = 0; k < temp[i][j]; k++) {
				maps[i].push_back(0);
			}

			for (k = 0; k < x[j]; k++) {
				maps[i].push_back(-1);
			}
			if (j < (x.size() - 1)) {
				maps[i].push_back(0);
			}
		}
		if (maps[i].size() < n) {
			for (k = 0; k < temp[i][x.size()]; k++) {
				maps[i].push_back(0);
			}
		}
		maps.push_back(B);
	}

	int sum;

	vector <int> row;
	for (k = 0; k < n; k++) {
		sum = 0;
		for (i = 0; i < maps.size() - 1; i++) {
			if (maps[i][k] == -1) {
				sum++;
			}
		}
		if (sum == maps.size() - 1) {
			row.push_back(-1);
		}
		else {
			row.push_back(0);
		}
	}
	int black = 0;
	for (i = 0; i < row.size(); i++) {
		if (row[i] == -1) {
			black++;
		}
	}

	int x_sum = 0;
	for (i = 0; i < x.size(); i++) {
		x_sum += x[i];
	}

	if (black == x_sum) {
		for (i = 0; i < row.size(); i++) {
			if (row[i] == 0) {
				row[i] = 1;
			}
		}
	}
	for (i = 0; i < row.size(); i++) {
		if ((row[i] == 0) && (guess_temp[i] != 0)) {
			row[i] = guess_temp[i];
		}
	}


	return row;
}

//////// ------- all possibe rows/ colunms  -------- //////////////////////////////////////////
vector <vector<int> > certain_row(int n, int n_c, vector <vector<int> > clue, vector <vector<int> > guess_matrix) {
	int i, j, u, N;
	int x_sum;
	vector <int> x;
	vector <vector<int> > maps;
	for (i = 0; i < n; i++) {
		x = clue[i];
		u = x.size();
		x_sum = 0;
		for (j = 0; j < u; j++) {
			x_sum += x[j];
		}
		N = n_c - x_sum - (u - 1);
		blank(0, N, u);
		maps.push_back(guess(n_c, clue[i], guess_matrix[i]));
		temp.clear();
		vecx.clear();
		x.clear();
	}

	return maps;
}


vector <vector<int> > certain_colunm(int n, int n_c, vector <vector<int> > clue, vector <vector<int> > guess_matrix) {
	int i, j, u, N;
	int x_sum;
	vector <int> x;
	vector <vector<int> > maps;
	vector <vector<int> > inv;
	vector <vector<int> > inv_maps{ {} };
	vector <int> fake;
	for (i = 0; i < n; i++) {
		x = clue[i];
		u = x.size();
		x_sum = 0;
		for (j = 0; j < u; j++) {
			x_sum += x[j];
		}
		N = n_c - x_sum - (u - 1);
		blank(0, N, u);

		maps.push_back(guess(n_c, clue[i], guess_matrix[i]));
		temp.clear();
		vecx.clear();
		x.clear();
	}
	for (i = 0; i < n_c; i++) {
		for (j = 0; j < n; j++) {
			inv_maps[i].push_back(0);
		}
		if (i != (n_c - 1)) {
			inv_maps.push_back(fake);
		}
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n_c; j++) {
			inv_maps[j][i] = maps[i][j];
		}
	}
	return inv_maps;
}
//////////////////////////////////////////////////////////////////////////
int main() {
	int i, j, u, k, n, N, n_c;
	int input_temp;
	string input;
	vector <vector<int> > clue_r;
	vector <vector<int> > clue_c;
	vector <int> clue;
	cout << "enter" << endl;
	cin >> n_row >> n_column;
	cin.ignore();
	for (i = 0; i < (n_row + n_column); i++) {
		getline(cin, input);
		stringstream ssin(input);
		while (ssin.good()) {
			ssin >> input_temp;
			clue.push_back(input_temp);
		}
		if (i < n_row) {
			clue_r.push_back(clue);
		}
		else {
			clue_c.push_back(clue);
		}
		clue.clear();
	}

	vector <vector<int> > maps;
	vector <vector<int> > z;
	vector <vector<int> > z2;
	vector <int> p;
	int number = 0;
	bool stop = 0;
	vector <vector<int> > guess_temp{ {} };
	vector <vector<int> > guess_temp_mid{ {} };
	vector <vector<int> > guess_temp_inv{ {} };

	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_column; j++) {
			guess_temp[i].push_back(0);
		}
		if (i != n_row - 1) {
			guess_temp.push_back(p);
		}
	}
	while (stop == 0) {
		z = certain_row(n_row, n_column, clue_r, guess_temp);
		guess_temp_mid = z;

		for (i = 0; i < n_column; i++) {
			for (j = 0; j < n_row; j++) {
				guess_temp_inv[i].push_back(0);
			}
			if (i != n_column - 1) {
				guess_temp_inv.push_back(p);
			}
		}

		for (i = 0; i < n_row; i++) {
			for (j = 0; j < n_column; j++) {
				guess_temp_inv[j][i] = guess_temp_mid[i][j];
			}
		}

		z2 = certain_colunm(n_column, n_row, clue_c, guess_temp_inv);
		if (z2 == guess_temp) {
			stop = 1;
		}
		guess_temp = z2;
		number++;
	}

	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_column; j++) {
			cout << guess_temp[i][j] << " ";
		}
		cout << endl;
	}
	cout << number << endl;


	return 0;
}