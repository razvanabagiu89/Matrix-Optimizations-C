/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
*/
 
double *multiply_matrices(int N, double *A, double *B, int operation_no) {
	register double *result = calloc(N * N, sizeof(double));

	for (register int i = 0; i < N; i++) {

		register double *orig_pa = &A[i * N];	

		for (register int j = 0; j < N; j++) {
			register double current_res = 0;

			register double *pa;
			register double *pb;
			if	(operation_no == 2) {
				pa = orig_pa + j;
				pb = &B[j * N + j];
			}
			else {
				pa = orig_pa;
				pb = &B[j];
			}
			for (register int k = 0; k < N; k++) {

				if (operation_no == 0) { /* classic */
					current_res += *pa * *pb;
					pa++;
					pb += N;

				} else if (operation_no == 1) { /* upper triangular */
					if (k <= j) {
						current_res += *pa * *pb;
						pa++;
						pb += N;
					}
				} 
				else if (operation_no == 2) { /* lower triangular */
					if (k >= j) {
						current_res += *pa * *pb;
						pa++;
						pb += N;
					}
				}
				else return NULL;
			}
			result[i * N + j] = current_res;
		}
	}

	return result;
}

double *add_matrices(int N, register double *A, register double *B) {

	for (register int i = 0; i < N; i++) {
		for (register int j = 0; j < N; j++) {
			A[i * N + j] += B[i * N + j];
		}
	}
	return A;
}

double *compute_transpose(int N, register double *matrix, int operation_no) {
	register double *transpose = calloc(N * N, sizeof(double));

	for (register int i = 0; i < N; i++) {
		for (register int j = 0; j < N; j++) {
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
	printf("OPT SOLVER\n");

	/* C = B * A * A_t + B_t * B = (B * A) * A_t + (B_t * B) */

	/* (B * A) where A = upper triangular */
	register double *D = multiply_matrices(N, B, A, 1);

	/* (D * A_t) where A_t = lower triangular */
	register double *A_tr = compute_transpose(N, A, 1); 
	register double *E = multiply_matrices(N, D, A_tr, 2);

	/* (B_t * B) */
	register double *B_tr = compute_transpose(N, B, 0);
	register double *F = multiply_matrices(N, B_tr, B, 0);
	
	/* (E + F) */
	register double *final = add_matrices(N, E, F);

	free(D);
	free(A_tr);
	free(B_tr);
	free(F);
	return final;
}

