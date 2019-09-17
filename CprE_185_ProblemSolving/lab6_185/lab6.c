// 185 lab6.c
//
// This is the outline for your program
// Please implement the functions given by the prototypes below and
// complete the main function to make the program complete.
// You must implement the functions which are prototyped below exactly
//  as they are requested.

#include <stdio.h>
#include <math.h>
#define PI 3.141592653589

//NO GLOBAL VARIABLES ALLOWED


//PRE: Arguments must point to double variables or int variables as appropriate
//This function scans a line of DS4 data, and returns
//  True when the square button is pressed
//  False Otherwise
//This function is the ONLY place scanf is allowed to be used
//POST: it modifies its arguments to return values read from the input line.
int read_line(double* g_x, double* g_y, double* g_z, int* time, int* Button_T, int* Button_X, int* Button_S, int* Button_C);

// PRE: -1.0 <= x_mag <= 1.0
// This function computes the roll of the DS4 in radians
// if x_mag outside of -1 to 1, treat it as if it were -1 or 1
// POST: -PI/2 <= return value <= PI/2
double roll(double x_mag);

// PRE: -1.0 <= y_mag <= 1.0
// This function computes the pitch of the DS4 in radians
// if y_mag outside of -1 to 1, treat it as if it were -1 or 1
// POST: -PI/2 <= return value <= PI/2
double pitch(double y_mag);


// PRE: -PI/2 <= rad <= PI/2
// This function scales the roll value to fit on the screen
// POST: -39 <= return value <= 39
int scaleRadsForScreen(double rad);

// PRE: num >= 0
// This function prints the character use to the screen num times
// This function is the ONLY place printf is allowed to be used
// POST: nothing is returned, but use has been printed num times
void print_chars(int num, char use);

//PRE: -39 <= number <=39
// Uses print_chars to graph a number from -39 to 39 on the screen.
// You may assume that the screen is 80 characters wide.
void graph_line(int number);

int main()
{
	double x, y, z;                             // magnitude values of x, y, and z
	int b_Triangle, b_X, b_Square, b_Circle;    // variables to hold the button statuses
	double roll_rad, pitch_rad;                 // value of the roll measured in radians
	int scaled_value;                           // value of the roll adjusted to fit screen display
	int time;									// value of the time
	int rollOrPitch = 0;						// value switches between 0 and 1 when triangle is pressed

	//insert any beginning needed code here

	do
	{
		// Get line of input
		read_line(&x, &y, &z, &time, &b_Triangle, &b_X, &b_Circle, &b_Square);
		//printf("%lf %lf %lf %d %d %d %d %d\n", x, y, z, time, b_Triangle, b_X, b_Square, b_Square);

		// calculate roll and pitch.  Use the buttons to set the condition for roll and pitch
		roll_rad = roll(x);
		pitch_rad = pitch(y);

		// switch between roll and pitch(up vs. down button)
		if (1 == b_Triangle) {
			if (0 == rollOrPitch) {
				rollOrPitch = 1;
			}
			else if (1 == rollOrPitch) {
				rollOrPitch = 0;
			}
		}

		// Scale your output value
		if (0 == rollOrPitch) {
			scaled_value = scaleRadsForScreen(roll_rad);
		}
		else if (1 == rollOrPitch) {
			scaled_value = scaleRadsForScreen(pitch_rad);
		}

		// Output your graph line
		graph_line(scaled_value);

		fflush(stdout);
	} while (0 == b_Square); // Modify to stop when the square button is pressed
	return 0;
}

int read_line(double* g_x, double* g_y, double* g_z, int* time, int* Button_T, int* Button_X, int* Button_S, int* Button_C) {
	scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d", time, g_x, g_y, g_z, Button_T, Button_X, Button_C, Button_S);

	return *Button_S;
}

double roll(double x_mag) {
	if (x_mag < -1) {
		x_mag = -1;
	}
	else if (x_mag > 1) {
		x_mag = 1;
	}

	return x_mag * (PI / 2);
}

double pitch(double y_mag) {
	if (y_mag < -1) {
		y_mag = -1;
	}
	else if (y_mag > 1) {
		y_mag = 1;
	}

	return y_mag * (PI / 2);
}

int scaleRadsForScreen(double rad) {
	return (rad / (PI / 2)) * 39;
}

void print_chars(int num, char use) {
	int i;

	for (i = 0; i < num; i++) {
		printf("%c", use);
	}
}

void graph_line(int number) {
	if (number > 0) {
		print_chars(39 - number, ' ');
		print_chars(number, 'l');
	}
	else if (number < 0) {
		print_chars(39, ' ');
		print_chars(number * -1, 'r');
	}
	else if (0 == number) {
		print_chars(39, ' ');
		print_chars(1, '0');
	}

	print_chars(1, '\n');
}
