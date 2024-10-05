#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "libs/matfun.h"
#include "libs/geofun.h"

int main() {
	double **k, **l, **M, P, **U, **Q;
	//int ax=-2,ay=0,bx=0,by=8;
	M = createMat(3,1);
	Q = createMat(1,1);
	U = createMat(3,1);/*
	k = createMat(2,1);
	l = createMat(2,1);
	P = createMat(2,1);
	Q = createMat(2,1);*/
	M[0][0] = 2;
	M[1][0] = 2;
	M[2][0] = -1;
	/*
	k[0][0] = (float) 2/3;
	k[1][0] = (float) 1/3;
	l[0][0] = (float) 1/3;
	l[1][0] = (float) 2/3;*/
	P = 1/Matnorm(M,3);
	Q[0][0] = P;
	printf("%f",P);
	U = Matscale(M,3,1,P);
	//Q = Matmul(M,k,2,2,1);
	FILE *file;
	file = fopen("values.dat", "w");

	if (file == NULL) {
		printf("Error opening file!\n");
		return 1;
	}
	fprintf(file, "%.04lf\t", U[0][0]);
	fprintf(file, "%.04lf\t", U[1][0]);                                                                                                
        fprintf(file, "%.04lf\t", U[2][0]);                                                                                                                                                 
        /*fprintf(file, "%.02lf\t\n", Q[1][0]);
	fprintf(file, "%.02lf\t", M[0][1]);                                                                                                                                                 
        fprintf(file, "%.02lf\t\n", M[1][1]);
	fprintf(file, "%.02lf\t", M[0][0]);                                                                                                                                                 
        fprintf(file, "%.02lf\t\n", M[1][0]);*/
	fclose(file);
	printf("Results have been written to values.dat\n");

	freeMat(M,2);/*
	freeMat(k,2);
	freeMat(l,2);
	freeMat(P,2);
	freeMat(Q,2);*/
	return 0;
}
