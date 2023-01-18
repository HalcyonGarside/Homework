//Implementation of the backward algorithm

#include <stdio.h>

//DO NOT DEFINE THESE OVER...
//N = 4
//M = 5
//T = 5
#define N 3
#define M 3
#define T 7

int main()
{
	float A[N][N];
	float B[N][M];

	float pi[N];

	int inputSeq[T];

	//Input array values here:
	A[0][0] = 0.8; A[0][1] = 0.1; A[0][2] = 0.1; //A[0][3] = 0;
	A[1][0] = 0.4; A[1][1] = 0.2; A[1][2] = 0.4; //A[1][3] = 0;
	A[2][0] = 0; A[2][1] = 0.3; A[2][2] = 0.7; //A[2][3] = 0;
	//A[3][0] = 0; A[3][1] = 0; A[3][2] = 0; A[3][3] = 0;

	B[0][0] = 0.66; B[0][1] = 0.34; B[0][2] = 0; //B[0][3] = 0; B[0][4] = 0;
	B[1][0] = 0; B[1][1] = 0; B[1][2] = 1; //B[1][3] = 0;	B[1][4] = 0;
	B[2][0] = 0.5; B[2][1] = 0.4; B[2][2] = 0.1; //B[2][3] = 0;	B[2][4] = 0;
	//B[3][0] = 0; B[3][1] = 0; B[3][2] = 0; B[3][3] = 0;	B[3][4] = 0;

	pi[0] = 0.6; pi[1] = 0; pi[2] = 0.4; //pi[3] = 0;

	inputSeq[0] = 0; inputSeq[1] = 1; inputSeq[2] = 0; inputSeq[3] = 2; inputSeq[4] = 0; inputSeq[5] = 1; inputSeq[6] = 0;


	//Init sequence arrays
	float prevBetas[N];
	float curBetas[N];

	for (int i = 0; i < N; i++)
	{
		prevBetas[i] = 0;
		curBetas[i] = 1;
	}

	printf("T = %d: ", T - 1);
	for (int i = 0; i < N; i++)
	{
		printf("State %d: %f  ", i, curBetas[i]);
	}
	printf("\n");

	for (int i = T - 2; i >= 0; i--)
	{
		//Move over values
		for (int j = 0; j < N; j++)
		{
			prevBetas[j] = curBetas[j];
			curBetas[j] = 0;
		}

		//For each state at the current time
		for (int curT = 0; curT < N; curT++)
		{
			//Find probability of getting to this point with the observation sequence
			for (int prevT = 0; prevT < N; prevT++)
			{
				curBetas[curT] += prevBetas[prevT] * A[curT][prevT] * B[prevT][inputSeq[i + 1]];
			}
		}

		printf("T = %d: ", i);
		for (int j = 0; j < N; j++)
		{
			printf("State %d: %f  ", j, curBetas[j]);
		}
		printf("\n");
	}

	float finSum = 0;
	for (int i = 0; i < N; i++)
	{
		finSum += curBetas[i];
	}

	return finSum;
}