#ifndef ITER_METHODS
#define ITER_METHODS


#include <iostream>
#include <cmath>
#include "CSR/MatrixOnCSR.hpp"


std::vector<double> JacobiMethod(CSR &A, const std::vector<double> &x_0, const std::vector<double> &b, const double tolerance) {

    int N = A.GetN(); //shape of matrix

    std::vector<double> x = x_0, x_vich(N), x_last, vec(N); // x and x_last for comparison, x_vich for counting x_(i+1)

    double norm; // norm for comparison with tolerance that will be counted on each iteration

    while (norm > tolerance) {
		for (int i = 0; i < N; ++i) {
			x_vich[i] = 0;
		} 

        for (int i = 0; i < N; ++i) {
            x_vich[i] += A(i, i) * x[i];
        }
        
        vec = A*x;

        for (int i = 0; i < N; ++i) {
            vec[i] = (b[i] - vec[i] + x_vich[i]) / A(i, i);
        }

        x_last = x;
        x = vec;
        norm = 0;

        for (int i = 0; i < N; ++i) {
            norm += std::abs(x[i] - x_last[i]);
        }

    }

    return x;


}

std::vector<double> GaussSeidelMethod(CSR &A, const std::vector<double> &x_0, const std::vector<double> &b, const double tolerance) {

	int N = A.GetN();

	double norm, Ux = 0, Lx = 0;
	
	std::vector<double> x = x_0, x_last;

	while (norm > tolerance) {

		x_last = x;

		for (int k = 1; k < N; ++k) {
			Ux += A(0, k) *  x[k];
		}

		x[0] = (b[0] - Ux) / A(0, 0);

		for (int j = 1; j < N; ++j) {

			Ux = 0;

			for (int k = j + 1; k < N; ++k) {
				Ux += A(j, k) * x[k];
			}

			for (int k = 0; k < j; ++k) {
				Lx += A(j, k) * x[k];
			}

			x[j] = (b[j] - Ux - Lx) / A(j, j);

			Lx = 0;
		}


		norm = 0;

        for (int i = 0; i < N; ++i) {
            norm += std::abs(x[i] - x_last[i]);
        }
	}
	return x;
}

std::vector<double> SimpleIterationMethod(CSR &A, const std::vector<double> &x_0, const std::vector<double> &b, const double tolerance, const double tau){

	int N = A.GetN();

	double norm, Ux = 0, Lx = 0;
	
	std::vector<double> x = x_0, x_last, vec(N);

	while(norm > tolerance) {

		x_last = x;

		vec = A * x;

		for (int k = 0; k < N; ++k) {
			x[k] = x[k] - tau * (vec[k] - b[k]);
		}

		norm = 0;

        for (int i = 0; i < N; ++i) {
            norm += std::abs(x[i] - x_last[i]);

	}
	
}
	return x;
}

#endif
