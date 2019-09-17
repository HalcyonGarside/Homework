// WII-MAZE Skeleton code written by Jason Erbskorn 2007
// Edited for ncurses 2008 Tom Daniels
// Updated for Esplora 2013 TeamRursch185
// Updated for DualShock 4 2016 Rursch


// Headers
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses/ncurses.h>
#include <unistd.h>
#include <time.h>

// Mathematical constants
#define PI 3.14159

// Screen geometry
// Use ROWS and COLS for the screen height and width (set by system)
// MAXIMUMS
#define NUMCOLS 100
#define NUMROWS 72

// Character definitions taken from the ASCII table
#define AVATAR 'A'
#define WALL '*'
#define EMPTY_SPACE ' '


// 2D character array which the maze is mapped into
char MAZE[NUMROWS][NUMCOLS];


// POST: Generates a random maze structure into MAZE[][]
//You will want to use the rand() function and maybe use the output %100.  
//You will have to use the argument to the command line to determine how 
//difficult the maze is (how many maze characters are on the screen).
void generate_maze(int difficulty);

// PRE: MAZE[][] has been initialized by generate_maze()
// POST: Draws the maze to the screen 
void draw_maze(void);

// PRE: 0 < x < COLS, 0 < y < ROWS, 0 < use < 255
// POST: Draws character use to the screen and position x,y
void draw_character(int x, int y, char use);

// PRE: -1.0 < x_mag < 1.0
// POST: Returns tilt magnitude scaled to -1.0 -> 1.0
// You may want to reuse the roll function written in previous labs.  
float calc_roll(float x_mag);

int tolerance(double target, double tol, double num);

// Main - Run with './ds4rd.exe -t -g -b' piped into STDIN
int main(int argc, char* argv[])
{
	if (argc <2) { printf("You forgot the difficulty\n"); return 1;}
	int difficulty = atoi(argv[1]); // get difficulty from first command line arg
	// setup screen    
	initscr();
	refresh();

	int lastT, t, bT, bC, bX, bS;
	double gx, gy, gz;

	int avatarX = NUMCOLS / 2;
	int avatarY = 0;

	int lose = 0;
	int i;

	// Generate and draw the maze, with initial avatar
	generate_maze(difficulty);
	draw_maze();
	draw_character(avatarX, avatarY, AVATAR);

	// Read gyroscope data to get ready for using moving averages.  
	scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d", &t, &gx, &gy, &gz, &bT, &bC, &bX, &bS);
	lastT = t;

	// Event loop
	do
	{
		// Avatar Placed & Waiting

		// Read data, update average
		scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d", &t, &gx, &gy, &gz, &bT, &bC, &bX, &bS);
		
		// Begin Move?
		if ((t - lastT) >= 1000) {
			int prevX = avatarX;
			int prevY = avatarY;

			//Right Move? Yes --> Update X
			if (tolerance(-0.9, 0.4, gx) && MAZE[avatarY][avatarX + 1] != WALL) {
				avatarX = avatarX + 1;
			}
			//Left Move? Yes --> Update X
			else if (tolerance(0.9, 0.4, gx) && MAZE[avatarY][avatarX - 1] != WALL) {
				avatarX = avatarX - 1;
			}

			//Begin Fall

			//Check -> Can I fall? Yes --> Update Y
			if (MAZE[avatarY + 1][avatarX] != WALL) {
				avatarY = avatarY + 1;
			}

			//Erase Previous Avatar
			draw_character(prevX, avatarY - (avatarY - prevY), EMPTY_SPACE);

			//Place New Avatar
			draw_character(avatarX, avatarY, AVATAR);
			lastT = t;
		}

		//If the character is covered side-to-side and under with walls, you lose
		if (MAZE[avatarY][avatarX + 1] == WALL && MAZE[avatarY][avatarX - 1] == WALL && MAZE[avatarY + 1][avatarX] == WALL) {
			lose = 1;
		}

		//If the character can move side to side, but there aren't any holes in that interval, you lose
		if (MAZE[avatarY + 1][avatarX] == WALL) {
			int mazeRight = 0;
			int mazeLeft = 0;
			for (i = 1; MAZE[avatarY][avatarX + i] != WALL; i++) {
				if (MAZE[avatarY + 1][avatarX + i] != WALL) {
					mazeRight = 1;
				}
			}
			for (i = 1; MAZE[avatarY][avatarX - i] != WALL; i++) {
				if (MAZE[avatarY + 1][avatarX - i] != WALL) {
					mazeLeft = 1;
				}
			}

			if (mazeRight != 1 && mazeLeft != 1) {
				lose = 1;
			}
		}
		//Check -> Did I Win? Yes --> Announce and Exit; No --> Repeat Loop

	} while(avatarY != NUMROWS && lose == 0);

	// Print the win message
	endwin();

	if (avatarY == NUMROWS) {
		printf("YOU WIN!\n");
	}
	else {
		printf("YOU LOSE!\n");
	}

	return 0;
}



// PRE: 0 < x < COLS, 0 < y < ROWS, 0 < use < 255
// POST: Draws character use to the screen and position x,y
//THIS CODE FUNCTIONS FOR PLACING THE AVATAR AS PROVIDED.
//
//    >>>>DO NOT CHANGE THIS FUNCTION.<<<<
void draw_character(int x, int y, char use)
{
	mvaddch(y,x,use);    
	refresh();
}

void generate_maze(int difficulty) {
	int i, j;
	unsigned int t = time(0);

	srand(t);

	for (i = 0; i < NUMROWS; i++) {
		for (j = 0; j < NUMCOLS; j++) {
			if ((rand() % 100) < difficulty) {
				MAZE[i][j] = WALL;
			}
			else {
				MAZE[i][j] = EMPTY_SPACE;
			}
		}
	}
}

void draw_maze(void) {
	int i, j;

	for (i = 0; i < NUMROWS; i++) {
		for (j = 0; j < NUMCOLS; j++) {
			mvaddch(i, j, MAZE[i][j]);
		}
	}
}

int tolerance(double target, double tol, double num) {
	if ((num < (target + tol)) && (num > (target - tol))) {
		return 1;
	}
	else {
		return 0;
	}
}