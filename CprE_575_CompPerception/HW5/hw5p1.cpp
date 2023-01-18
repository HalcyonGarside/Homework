//Implementation of the forward algorithm (slow)

#include <stdio.h>

//DO NOT DEFINE THESE OVER...
//N = 4
//M = 5
//T = 5
#define N 2
#define M 3
#define T 3

int main()
{
	float A[N][N];
	float B[N][M];

	float pi[N];

	int inputSeq[T];

	//Input array values here:
	A[0][0] = 0.5; A[0][1] = 0.5; //A[0][2] = 0; A[0][3] = 0;
	A[1][0] = 0; A[1][1] = 1; //A[1][2] = 0; A[1][3] = 0;
	//A[2][0] = 0; A[2][1] = 0; A[2][2] = 0; A[2][3] = 0;
	//A[3][0] = 0; A[3][1] = 0; A[3][2] = 0; A[3][3] = 0;

	B[0][0] = 0.5; B[0][1] = 0; B[0][2] = 0.5; //B[0][3] = 0; B[0][4] = 0;
	B[1][0] = 0; B[1][1] = 1; B[1][2] = 0; //B[1][3] = 0;	B[1][4] = 0;
	//B[2][0] = 0; B[2][1] = 0; B[2][2] = 0; B[2][3] = 0;	B[2][4] = 0;
	//B[3][0] = 0; B[3][1] = 0; B[3][2] = 0; B[3][3] = 0;	B[3][4] = 0;

	pi[0] = 1; pi[1] = 0; //pi[2] = 0; pi[3] = 0;

	inputSeq[0] = 0; inputSeq[1] = 2; inputSeq[2] = 1; //inputSeq[3] = 0; inputSeq[4] = 0;


	//Init sequence array
	int curSeq[T + 1];
	float totProb, curProb;

	totProb = 0;

	for (int i = 0; i < T + 1; i++)
	{
		curSeq[i] = 0;
	}

	//While there hasn't been any overflow in the sequence numbers
	while(curSeq[T] == 0)
	{
		curProb = pi[curSeq[0]];
		for (int o = 0; o < T - 1; o++)
		{
			curProb *= B[curSeq[o]][inputSeq[0]];
			curProb *= A[curSeq[o]][curSeq[o + 1]];
		}

		curProb *= B[curSeq[T - 1]][inputSeq[T - 1]];

		totProb += curProb;

		//DEBUG: Print current sequence
		//printf("%d %d %d\n", curSeq[0], curSeq[1], curSeq[2]);

		//Update states...
		bool iter = true;
		int curPos = 0;
		while (iter)
		{
			iter = false;
			curSeq[curPos]++;
			if (curSeq[curPos] >= N)
			{
				curSeq[curPos] = 0;
				iter = true;
				curPos++;
			}
		}
	}

	printf("%f\n", totProb);
}