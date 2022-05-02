/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"
#include "cblas.h"

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	printf("BLAS SOLVER\n");

	/* C = B * A * A_t + B_t * B 
	= (B * A) * A_t + (B_t * B)
	*/

	/* D = B_t * B */
	double *D = calloc(N * N, sizeof(double));
	cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, N, N, N, 1.0, B, N, B, N, 1.0, D, N);

	/* B = B * A*/
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1, A, N, B, N);

	/* D = B * A_t + D */
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1.0, B, N, A, N, 1.0, D, N);

	return D;
}
