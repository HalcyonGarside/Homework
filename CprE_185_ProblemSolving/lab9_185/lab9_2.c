// Lab 9 DS4Talker Skeleton Code

#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXWORDS 100
#define WORDLEN 11
#define DEBUG 1   // set to 0 to disable debug output
#define CURSOR '>'
#define WHITESPACE ' '
#define SENT_LEN 80

// reads words from the file
// into wl and trims the whitespace off of the end of each word
// DO NOT MODIFY THIS Prototype
int readWords(char* wl[MAXWORDS], char* filename); 

//modifies s to trim white space off the right side
// DO NOT MODIFY THIS Prototype
void trimws(char* s) ;

int tolerance(int target, int tol, int num);

void draw_character(int x, int y, char use);

int main(int argc, char* argv[]) {
	char* wordlist[MAXWORDS], addedWd[WORDLEN];
	char* sentance = malloc(SENT_LEN * sizeof(char));
	char capWord[WORDLEN];
	int elementLengths[SENT_LEN];
	int sentElement = 0;
	int wordCount, selectWd;
	int i;
	int x = 1;
	int y = 0;
	int t, bS, bT, bX, bC, JSr, JSl, a, b, c, d, e, f;
	int JSlx, JSly, JSrx, JSry;
	int lastT;
	int cursX = 0;
	int cursY = 0;
	int prevX, prevY;
	int length = 0;
	int wasSpace = 0;
	int cap = 0;


	wordCount = readWords(wordlist, argv[1]);
	initscr();

// most of your code for part 2 goes here. Don't forget to include the ncurses library 
	for (i = 0; i < wordCount - 1; i++) {
		mvprintw(y, x, "%s", wordlist[i]);
		refresh();
		x = x + 15;
		if (x > 75) {
			x = 1;
			y = y + 1;
		}
	}

	//Initializes time, character position, and the word being indicated by the cursor
	scanf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", &t, &bT, &bC, &bX, &bS, &JSr, &JSl, &a, &b, &c, &d, &e, &f, &JSlx, &JSly, &JSrx, &JSry);
	lastT = t;
	draw_character(cursX, cursY, CURSOR);
	selectWd = 0;
	strcpy(sentance, "");

	do {
		scanf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", &t, &bT, &bC, &bX, &bS, &JSr, &JSl, &a, &b, &c, &d, &e, &f, &JSlx, &JSly, &JSrx, &JSry);
		if ((t - lastT) >= 150) {
			prevX = cursX;
			prevY = cursY;

			//Moves cursor accross words according to input, moves specified word in array.

			//DEBUG: There's something up with the tolerance values here.  Check 'em out.
			if (tolerance(-128, 15, JSlx) && (cursX != 0)) {
				cursX = cursX - 15;
				selectWd = selectWd - 1;
			}
			if ((JSlx >= 117) && (cursX < 60)) {
				cursX = cursX + 15;
				selectWd = selectWd + 1;
			}
			if (tolerance(-128, 10, JSly) && (cursY != 0)) {
				cursY = cursY - 1;
				selectWd = selectWd - 5;
			}
			if (tolerance(127, 10, JSly) && ((selectWd + 5) <= (wordCount - 1))) {
				cursY = cursY + 1;
				selectWd = selectWd + 5;
			}

			//Assigns different tasks to different buttons.

			//Triangle appends space and word to string.  DONE
			if (bT == 1) {
				strcpy(capWord, wordlist[selectWd]);
				if (cap == 1) {
					capWord[0] = toupper(capWord[0]);
					cap = 0;
				}
				strcpy(addedWd, " ");
				strcat(addedWd, capWord);
				strcat(sentance, addedWd);
				length = length + strlen(addedWd);

				elementLengths[sentElement] = strlen(addedWd);
				sentElement = sentElement + 1;
			}
			//X undoes the last action.
			if (bX == 1 && sentElement > 0) {
				
				length = length - elementLengths[sentElement - 1];
				strcpy(&sentance[length], "");
				for (i = 0; i <= elementLengths[sentElement - 1]; i++) {
					mvprintw(17, length + i, " ");
				}
				sentElement = sentElement - 1;
			}
			//Square appends word without space.
			if (bS == 1) {
				strcpy(capWord, wordlist[selectWd]);
				if (cap == 1) {
					capWord[0] = toupper(capWord[0]);
					cap = 0;
				}
				strcpy(addedWd, capWord);
				strcat(sentance, addedWd);
				length = length + strlen(addedWd);

				elementLengths[sentElement] = strlen(addedWd);
				sentElement = sentElement + 1;
			}
			
			if (bC == 1) {
				cap = 1;
			}

			//Pressing down on the joystick clears sentance at the bottom.
			if ((JSr) || (JSl)) {
				strcpy(sentance, "");
				for (i = 0; i <= length; i++) {
					mvprintw(17, i, " ");
				}
				length = 0;
				sentElement = 0;
			}


			//Deletes last place character was and draws it in its new designated position.
			draw_character(prevX, prevY, WHITESPACE);
			draw_character(cursX, cursY, CURSOR);

			if (sentElement >= 0) {
				mvprintw(17, 0, "%s", sentance);
			}
			
			lastT = t;
			refresh();
		}

		refresh();

	} while(a == 0);

    return 0;
	}

int readWords(char* wl[MAXWORDS], char* filename) {
	int i = 0;
	char word[WORDLEN];

	FILE* f = fopen(filename, "r");
	while (!feof(f)) {
		fscanf(f, "%s", word);
		trimws(word);
		wl[i] = (char *) malloc(strlen(word) + 1);
		strcpy(wl[i], word);
		i++;
	}

	fclose(f);

	return i;
}

void trimws(char* s) {
	int i = 0;

	for (i = 0; i < WORDLEN; i++) {
		if (isspace(s[i])) {
			s[i] = '\0';
		}
	}

}

int tolerance(int target, int tol, int num) {
	if ((num < (target + tol)) && (num >(target - tol))) {
		return 1;
	}
	else {
		return 0;
	}
}

void draw_character(int x, int y, char use)
{
	mvaddch(y, x, use);
	refresh();
}