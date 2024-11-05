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
	double x = 0, y = 0;
	for(double i=1000;i>=0;i--){
		double **output=createMat(2,1);
		output[0][0]+=i/125;
		x = output[0][0];
		y = sqrt(x*4);
		output[1][0]=y;
		fprintf(file,"%lf,%lf\n",output[0][0],output[1][0]);
		freeMat(output,2);
	}
	x = 0; y = 0;
	for(double i=0;i<=1000;i++){
		double **output=createMat(2,1);
		output[0][0]+=i/125;
		x = output[0][0];
		y = -sqrt(x*4);
		output[1][0]=y;
		fprintf(file,"%lf,%lf\n",output[0][0],output[1][0]);
		freeMat(output,2);
	}

	x = 0; y = 0;
	for(double i=1000;i>=0;i--){
		double **output=createMat(2,1);
		output[0][0]+=i/125;
		x = output[0][0];
		y = sqrt(8*x-x*x);
		output[1][0]=y;
		fprintf(file,"%lf,%lf\n",output[0][0],output[1][0]);
		freeMat(output,2);
	}
	x = 0; y = 0;
	for(double i=0;i<=1000;i++){
		double **output=createMat(2,1);
		output[0][0]+=i/125;
		x = output[0][0];
		y = -sqrt(8*x-x*x);
		output[1][0]=y;
		fprintf(file,"%lf,%lf\n",output[0][0],output[1][0]);
		freeMat(output,2);
	}

	printf("Results have been written to values.dat\n");

	return 0;
}
