/*--------------------------------------------------------------
					Includes
--------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*---------------------------------------------------------------
					Prototypes
---------------------------------------------------------------*/
double mag(double x, double y, double z);
int close_to(double tolerance, double point, double val);

/*--------------------------------------------------------------
					Implementation
--------------------------------------------------------------*/
int main(void) {
    int t, b1, b2, b3, b4;
    double gx, gy, gz;

	double dist, t1, t2, tf;

	printf("William Blanchard\n");
	printf("wsb\n");

	scanf("%d, %lf, %lf, %lf", &t, &gx, &gy, &gz);
	printf("Ok, I'm now recieving data.\n");
	printf("I'm Waiting.asfd");

	while (close_to(0.5, 1, mag(gx, gy, gz))) {
		scanf("%d, %lf, %lf, %lf", &t, &gx, &gy, &gz);
		if (close_to(100, 0, t % 1000)) {
			printf(".\n");
		}
		fflush(stdout);
	}
	printf("\n \n");

	printf("Help me!  I'm falling!");
	t1 = t;

	while (close_to(1, 0, mag(gx, gy, gz))) {
		scanf("%d, %lf, %lf, %lf", &t, &gx, &gy, &gz);
		if (close_to(10, 0, t % 1000)) {
			printf("!");
		}
		fflush(stdout);
	}
	t2 = (t - t1) / 1000;
	printf("\n \n");

	/*
	The equation given for fall distance is x0 + vt + (1/2)gt^2, where t is fall time, v is initial velocity, 
	and x0 is initial location.  Since initial velocity and location are both 0, they can be eliminated from the
	equation in this definition.  g is the force of gravity, defined as 9.8 m/sec^2.
	*/
	dist = 0.5 * 9.8 * (t2 * t2);

	printf("Ouch!  I fell %lf meters in %lf seconds.\n", dist, t2);

	fflush(stdout);
return 0;
}

/* Put your functions here */
double mag(double x, double y, double z) {
	return sqrt((x * x) + (y * y) + (z * z));
}

int close_to(double tolerance, double point, double val) {
	if (val <= (tolerance + point) && val >= (point - tolerance)) {
		return 1;
	}
	else {
		return 0;
	}
}