/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
 
double *multiply_matrices(int N, double *A, double *B, int operation_no) {
	double *result = (double*)calloc(N * N, sizeof(double));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				if (operation_no == 0) { /* classic */
					result[i * N + j] += A[i * N + k] * B[k * N + j];
				} else if (operation_no == 1) { /* upper triangular */
					if (k <= j) {
						result[i * N + j] += A[i * N + k] * B[k * N + j];
					}
				} else if (operation_no == 2) { /* lower triangular */
					if (k >= j) {
						result[i * N + j] += A[i * N + k] * B[k * N + j];
					}
				}
				else return NULL;
			}
		}
	}
	return result;
}

double *add_matrices(int N, double *A, double *B) {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			A[i * N + j] += B[i * N + j];
		}
	}
	return A;
}

double *compute_transpose(int N, double *matrix, int operation_no) {
	double *transpose = (double *) calloc(N * N, sizeof(double));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (operation_no == 0) {
				transpose[j * N + i] = matrix[i * N + j];
			} else if (operation_no == 1) { /* upper triangular */
				if (i <= j) {
					transpose[j * N + i] = matrix[i * N + j];
				}
			}
			else return NULL;
		}
	}
	return transpose;
}


double* my_solver(int N, double *A, double* B) {

	/*
	* C = B * A * A_t + B_t * B = (B * A) * A_t + (B_t * B)
	*/

	/* (B * A) where A = upper triangular */
	double *D = multiply_matrices(N, B, A, 1);

	/* (D * A_t) where A_t = lower triangular */
	double *A_tr = compute_transpose(N, A, 1);
	double *E = multiply_matrices(N, D, A_tr, 2);

	/* (B_t * B) */
	double *B_tr = compute_transpose(N, B, 0);
	double *F = multiply_matrices(N, B_tr, B, 0);
	
	/* (E + F) */
	double *final = add_matrices(N, E, F);
	free(D);
	free(F);
	free(A_tr);
	free(B_tr);
	return final;
}

