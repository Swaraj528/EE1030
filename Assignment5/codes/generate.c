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
	FILE *file;
	file = fopen("values.dat", "w");

	if (file == NULL) {
		printf("Error opening file!\n");
		return 1;
	}
	double **vertex, a = 1;
	vertex = createMat(2,1);
	vertex[0][0] = 0; vertex[1][0] = 0;
	for(int i=500;i>=0;i--){
		double t = 3.0*i/500;
		double **output=createMat(2,1);
		output[0][0]=vertex[0][0]+a*t*t;
		output[1][0]=vertex[1][0]+2*a*t;
		fprintf(file,"%lf,%lf\n",output[0][0],output[1][0]);
		freeMat(output,2);
	}
	for(int i=0;i<=500;i++){
		double t = -3.0*i/500;
		double **output=createMat(2,1);
		output[0][0]=a*t*t;
		output[1][0]=2*a*t;
		fprintf(file,"%lf,%lf\n",output[0][0],output[1][0]);
		freeMat(output,2);
	}
	double **A;
	A = createMat(2,1);
	A[0][0] = 4;
	A[1][0] = 0;
	double radius = 4;
	for(int i=0;i<=1000;i++){
		double theta = 2 * M_PI * (double)i / (double)1000;
		//double theta=(double)i/(double)(2*M_PI*num_points);
		double **output=createMat(2,1);
		output[0][0]=A[0][0]+(radius*cos(theta));
		output[1][0]=A[1][0]+(radius*sin(theta));
		fprintf(file,"%lf,%lf\n",output[0][0],output[1][0]);
		freeMat(output,2);
	}
	
	printf("Results have been written to values.dat\n");

	freeMat(vertex,2);
	freeMat(A,2);
	return 0;
}
