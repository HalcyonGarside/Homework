/* 185 Lab 3 Template */

#include <stdio.h>
#include <math.h>

/* Put your function prototypes here */
int buttonsPressed(int t, int c, int x, int s);

int main(void) {
    /* DO NOT MODIFY THESE VARIABLE DECLARATIONS */
    int t;
    double  ax, ay, az;   

	int tr, c, ex, sq;


    /* This while loop makes your code repeat. Don't get rid of it. */
    while (1) {
		scanf("%d,%d,%d,%d", &tr, &c, &ex, &sq);
		printf("There are %d buttons pressed\n", buttonsPressed(tr, c, ex, sq));
		fflush(stdout);
    }
return 0;
}

/* Put your functions here */
int buttonsPressed(int t, int c, int x, int s){	
	return t + c + x + s;
}
