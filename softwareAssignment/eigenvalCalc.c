/*
   How the input works:
   set n = size of matrix
   random_matrix.txt has values in the format:
   a1 a2 a3 a4 ... an
   b1 b2 b3 b4 ... bn
   .
   .
   .
   ---
   */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double norm(double *vec, int size) {
	double normVal = 0.0;
	for (int i = 0; i < size; i++) {
		normVal += vec[i] * vec[i];
	}
	return sqrt(normVal);
}

void householderReflection(double *vec, double **hMatrix, int n, int startRow, int startCol) {
	int size = n - startRow;
	double normU = norm(vec, size);
	if (normU < 1e-10) return;
	double alpha = (vec[0] <= 0 ? 1 : -1) * norm(vec, size);
	vec[0] -= alpha;
	normU = norm(vec, size);
	for (int i = 0; i < size; i++) {
		vec[i] /= normU;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i < startRow || j < startCol) {
				hMatrix[i][j] = (i == j) ? 1.0 : 0.0;
			} else {
				hMatrix[i][j] = (i == j ? 1.0 : 0.0) - 2.0 * vec[i - startRow] * vec[j - startCol];
			}
		}
	}
}

void matMult(double **mat1, double **mat2, double **res, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			res[i][j] = 0.0; 
		}
	}

	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n; k++) {
			for (int j = 0; j < n; j++) {
				res[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
}

void qrDecomp(double **aMatrix, int n, double **qMatrix, double **rMatrix) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			qMatrix[i][j] = (i == j ? 1.0 : 0.0);
			rMatrix[i][j] = aMatrix[i][j];
		}
	}

	for (int k = 0; k < n - 1; k++) {
		int size = n - k;

		double *vec = (double *)malloc(size * sizeof(double));
		for (int i = 0; i < size; i++) {
			vec[i] = rMatrix[k + i][k];
		}

		double **hMatrix = (double **)malloc(n * sizeof(double *));
		for (int i = 0; i < n; i++) {
			hMatrix[i] = (double *)malloc(n * sizeof(double));
		}
		householderReflection(vec, hMatrix, n, k, k);

		double **temp = (double **)malloc(n * sizeof(double *));
		for (int i = 0; i < n; i++) {
			temp[i] = (double *)malloc(n * sizeof(double));
		}
		matMult(hMatrix, rMatrix, temp, n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				rMatrix[i][j] = temp[i][j];
			}
		}
		matMult(qMatrix, hMatrix, temp, n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				qMatrix[i][j] = temp[i][j];
			}
		}
		free(vec);
		for (int i = 0; i < n; i++) {
			free(hMatrix[i]);
			free(temp[i]);
		}
		free(hMatrix);
		free(temp);
	}
}

void extractEigenvalues(double **aMatrix, int n, double *realPart, double *imagPart) {
	for (int i = 0; i < n; i++) {
		if (i < n - 1 && fabs(aMatrix[i + 1][i]) > 1e-10) {
			double a = aMatrix[i][i];
			double b = aMatrix[i][i + 1];
			double c = aMatrix[i + 1][i];
			double d = aMatrix[i + 1][i + 1];

			double trace = a + d;
			double det = a * d - b * c;
			realPart[i] = realPart[i + 1] = trace / 2.0;
			imagPart[i] = sqrt(fabs(det - trace * trace / 4.0));
			imagPart[i + 1] = -imagPart[i];
			i++;  
		} 
		else {
			realPart[i] = aMatrix[i][i];
			imagPart[i] = 0.0;
		}
	}
}

void printMat(double **matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%lf ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void modifiedQr(double **aMatrix, int n) {
	double **qMatrix = (double **)malloc(n * sizeof(double *));
	double **rMatrix = (double **)malloc(n * sizeof(double *));
	double **temp = (double **)malloc(n * sizeof(double *));
	double *realPrev = (double *)malloc(n * sizeof(double));
	double *realCurr = (double *)malloc(n * sizeof(double));
	double *imagCurr = (double *)malloc(n * sizeof(double));

	for (int i = 0; i < n; i++) {
		temp[i] = (double *)malloc(n * sizeof(double));
		qMatrix[i] = (double *)malloc(n * sizeof(double));
		rMatrix[i] = (double *)malloc(n * sizeof(double));
	}

	const double tol = 1e-10;
	int maxIter = 100000;  
	int iter = 0;

	for (int i = 0; i < n; i++) {
		realPrev[i] = aMatrix[i][i];
	}

	while (iter < maxIter) {
		iter++;
		//printf("%d\n",iter);

		qrDecomp(aMatrix, n, qMatrix, rMatrix);
		matMult(rMatrix, qMatrix, temp, n);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				aMatrix[i][j] = temp[i][j];
			}
		}

		if (iter % 100 == 0) {
			extractEigenvalues(aMatrix, n, realCurr, imagCurr);
			double maxChange = 0.0;
			for (int i = 0; i < n; i++) {
				double change = fabs(realCurr[i] - realPrev[i]);
				if (change > maxChange) {
					maxChange = change;
				}
			}

			for (int i = 0; i < n; i++) {
				realPrev[i] = realCurr[i];
			}

			if (maxChange < tol) {
				break;
			}
		}
	}

	if (iter < maxIter) {
		printf("Converged at around %d iterations\n", iter);
	} else {
		printf("Failed to converge within %d iterations\n", maxIter);
	}

	printf("Eigenvalues:\n");
	for (int i = 0; i < n; i++) {
		printf("%f + %fi\n", realCurr[i], imagCurr[i]);
	}

	for (int i = 0; i < n; i++) {
		free(temp[i]);
		free(qMatrix[i]);
		free(rMatrix[i]);
	}
	free(temp);
	free(qMatrix);
	free(rMatrix);
	free(realPrev);
	free(realCurr);
	free(imagCurr);
}

void hessenbergReduction(double **aMatrix, int n) {
	for (int k = 0; k < n - 2; k++) {
		int size = n - k - 1;

		int isHessenberg = 1;
		for (int i = k + 1; i < n; i++) {
			if (aMatrix[i][k] != 0.0) {
				isHessenberg = 0;
				break;
			}
		}
		if (isHessenberg) continue;
		double *vec = (double *)malloc(size * sizeof(double));
		for (int i = 0; i < size; i++) {
			vec[i] = aMatrix[k + 1 + i][k];
		}

		double **hMatrix = (double **)malloc(n * sizeof(double *));
		for (int i = 0; i < n; i++) {
			hMatrix[i] = (double *)malloc(n * sizeof(double));
		}
		householderReflection(vec, hMatrix, n, k + 1, k + 1);

		double **temp = (double **)malloc(n * sizeof(double *));
		for (int i = 0; i < n; i++) {
			temp[i] = (double *)malloc(n * sizeof(double));
		}
		matMult(hMatrix, aMatrix, temp, n);
		matMult(temp, hMatrix, aMatrix, n);

		free(vec);
		for (int i = 0; i < n; i++) {
			free(hMatrix[i]);
			free(temp[i]);
		}
		free(hMatrix);
		free(temp);
	}
}

#include <time.h>

int main() {
	int n = 3;
	double **aMatrix = (double **)malloc(n * sizeof(double *));

	for (int i = 0; i < n; i++) {
		aMatrix[i] = (double *)malloc(n * sizeof(double));
	}

	FILE *file = fopen("random_matrix.txt", "r");

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fscanf(file, "%lf", &aMatrix[i][j]);
		}
	}

	fclose(file);

	printf("Matrix A:\n");
	printMat(aMatrix, n);

	clock_t start = clock();

	hessenbergReduction(aMatrix, n);
	printf("Hessenberg matrix of A:\n");
	printMat(aMatrix, n);

	modifiedQr(aMatrix, n);
	clock_t end = clock();

	double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Took %f seconds\n", timeTaken);
	for (int i = 0; i < n; i++) {
		free(aMatrix[i]);
	}
	free(aMatrix);

	return 0;
}

