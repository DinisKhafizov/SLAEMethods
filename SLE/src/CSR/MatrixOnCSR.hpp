#ifndef CSRMATRIX
#define CSRMATRIX

#include<iostream>
#include<vector>

class CSR {
	int ROWS;
	int COLS;
	std::vector<double> values;
	std::vector<int> cols;
	std::vector<int> rows;
public:
	CSR(const int n, const int m) {
		std::vector<double> val(m * n);
		values = val;
		cols = {0};
		rows = {0};
 		ROWS = m;
		COLS = n;
		
	}
	CSR(const std::vector<double> &val, const std::vector<int> &col, const std::vector<int> &row, const int Ncols) {
		values = val;
		cols = col;
		rows = row;
		ROWS = size(rows) - 1;
		COLS = Ncols;
	}

	double operator()(int i, int j) const { //Nahojdenie
		for(int k = rows[i]; k < rows[i + 1]; ++k) {
			if (cols[k] == j) {
				return values[k];
			}
		}
		return 0;
	}

	std::vector<double> operator*(std::vector<double> &vec) const {
	    std::vector<double> res(ROWS);	//Umnojenie 2)Mojno pisat tolko rows, po umolchaniyu 0 v double v vectore budet
		for (int i = 0; i < ROWS; ++i) {
			for (int j = rows[i]; j < rows[i + 1]; ++j) {
				res[i] += values[j] * vec[cols[j]];
			}
		}
		return res;
	}
	void operator *(double x) {
		for (int i = 0; i < size(values); ++i) {
			values[i] *= x;
		}
	}
	int GetN() {
		return ROWS;
	}
	
};

#endif //CSRMATRIX