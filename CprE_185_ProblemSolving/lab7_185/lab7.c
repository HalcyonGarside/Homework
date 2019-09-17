// 185 Lab 7
#include <stdio.h>


#define MAXPOINTS 10000

// compute the average of the first num_items of buffer
double avg(double buffer[], int num_items);

//update the max and min of the first num_items of array
void maxmin(double array[], int num_items, double* max, double* min);

//shift length-1 elements of the buffer to the left and put the 
//new_item on the right.
void updatebuffer(double buffer[], int length, double new_item);



int main(int argc, char* argv[]) {
	
	/* DO NOT CHANGE THIS PART OF THE CODE */

	double x[MAXPOINTS], y[MAXPOINTS], z[MAXPOINTS];
	int lengthofavg = 0;
	if (argc>1) {
		sscanf(argv[1], "%d", &lengthofavg );
		printf("You entered a buffer length of %d\n", lengthofavg);
	}
	else {
		printf("Enter a length on the command line\n");
		return -1;
	}
	if (lengthofavg <1 || lengthofavg >MAXPOINTS) {
		printf("Invalid length\n");
		return -1;
	}


	
	/* PUT YOUR CODE HERE */
	double gx, gy, gz;
	int bS, bT, bX, bC;

	double maxX, minX, maxY, minY, maxZ, minZ, aveX, aveY, aveZ;
	int i;

	//Fills each array to its indicated length
	for (i = 0; i < lengthofavg; i++) {
		scanf("%lf, %lf, %lf, %d, %d, %d, %d", &gx, &gy, &gz, &bT, &bC, &bX, &bS);

		x[i] = gx;
		y[i] = gy;
		z[i] = gz;
	}

	do {
		scanf("%lf, %lf, %lf, %d, %d, %d, %d", &gx, &gy, &gz, &bT, &bC, &bX, &bS);

		updatebuffer(x, lengthofavg, gx);
		updatebuffer(y, lengthofavg, gy);
		updatebuffer(z, lengthofavg, gz);

		aveX = avg(x, lengthofavg);
		aveY = avg(y, lengthofavg);
		aveZ = avg(z, lengthofavg);

		maxmin(x, lengthofavg, &maxX, &minX);
		maxmin(y, lengthofavg, &maxY, &minY);
		maxmin(z, lengthofavg, &maxZ, &minZ);

		printf("x, %lf, %lf, %lf, %lf, y, %lf, %lf, %lf, %lf, z, %lf, %lf, %lf, %lf\n", gx, aveX, maxX, minX, gy, aveY, maxY, minY, gz, aveZ, maxZ, minZ);

		fflush(stdout);
	} while (bS == 0);
}

double avg(double buffer[], int num_items) {
	double sum = 0.0;
	int i;

	for (i = 0; i < num_items; i++) {
		sum = sum + buffer[i];
	}

	return sum / num_items;
}

void maxmin(double array[], int num_items, double* max, double* min) {
	int i;
	*max = array[0];
	*min = array[0];

	for (i = 0; i < num_items; i++) {
		if (array[i] > *max) {
			*max = array[i];
		}
		if (array[i] < *min) {
			*min = array[i];
		}
	}
}

void updatebuffer(double buffer[], int length, double new_item) {
	int i;

	for (i = length; i > 0; i--) {
		buffer[i] = buffer[i - 1];
	}

	buffer[0] = new_item;

}
