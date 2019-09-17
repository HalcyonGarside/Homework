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
double velocity(double v, double mag, double t);

/*--------------------------------------------------------------
Implementation
--------------------------------------------------------------*/
int main(void) {
	int t, tChng, b1, b2, b3, b4;
	double gx, gy, gz;

	double dist, distAct, t1, t2, tf, v;



	printf("William Blanchard\n");
	printf("wsb\n");

	scanf("%d, %lf, %lf, %lf", &t, &gx, &gy, &gz);
	printf("Ok, I'm now recieving data.\n");
	printf("I'm Waiting.");

	t1 = t;

	while (close_to(0.5, 1, mag(gx, gy, gz))) {
		scanf("%d, %lf, %lf, %lf", &t, &gx, &gy, &gz);
		if ((t - t1) > 1000) {
			printf(".");
			t1 = t;
		}
		fflush(stdout);
	}
	printf("\n \n");

	printf("Help me!  I'm falling!");

	t1 = t;
	tChng = t;
	dist = 0.0;
	v = 0.0;

	while (close_to(0.5, 0, mag(gx, gy, gz))) {
		scanf("%d, %lf, %lf, %lf", &t, &gx, &gy, &gz);
		if (close_to(10, 0, t % 1000)) {
			printf("!");
		}
		fflush(stdout);

		v = velocity(v, mag(gx, gy, gz), (1.0 * (t - tChng)) / 1000.0);

		distAct = distAct + v * ((1.0 * (t - tChng)) / 1000);

		tChng = t;
	}

	t2 = (t - t1) / 1000;
	printf("\n \n");

	/*
	The equation given for fall distance is x0 + vt + (1/2)gt^2, where t is fall time, v is initial velocity,
	and x0 is initial location.  Since initial velocity and location are both 0, they can be eliminated from the
	equation in this definition.  g is the force of gravity, defined as 9.8 m/sec^2.
	*/
	dist = 0.5 * 9.8 * (t2 * t2);

	printf("Compensating for air resistance, the fall was %lf meters.\n", distAct);
	printf("This is %2.0lf%% less than computed before.\n", 100.0 - ((distAct / dist) * 100));

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

double velocity(double v, double mag, double t) {
	return v + (9.8 * (1 - mag) * t);
}