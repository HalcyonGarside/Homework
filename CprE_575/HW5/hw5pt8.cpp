//Implementation of the backward algorithm

#include <stdio.h>
#include <math.h>

#define N 2
#define M 3
#define T 7
#define SEQ 5

float forward(float A[N][N], float B[N][M], float pi[N], int inputSeq[T], float outTimeline[N][T]);
float backward(float A[N][N], float B[N][M], float pi[N], int inputSeq[T], float outTimeline[N][T]);

int main()
{
	float forwardArray[N][T];
	float backwardArray[N][T];

	float A[N][N];
	float B[N][M];

	float pi[N];

	int inputSeq[SEQ][T];

	//Input array values here:
	A[0][0] = 0; A[0][1] = 1; //A[0][2] = 0.1; //A[0][3] = 0;
	A[1][0] = 1; A[1][1] = 0; //A[1][2] = 0.4; //A[1][3] = 0;
	//A[2][0] = 0; A[2][1] = 0.3; A[2][2] = 0.7; //A[2][3] = 0;
	//A[3][0] = 0; A[3][1] = 0; A[3][2] = 0; A[3][3] = 0;

	B[0][0] = 0.25; B[0][1] = 0.75; B[0][2] = 0; //B[0][3] = 0; B[0][4] = 0;
	B[1][0] = 1; B[1][1] = 0; B[1][2] = 0; //B[1][3] = 0;	B[1][4] = 0;
	//B[2][0] = 0.5; B[2][1] = 0.4; B[2][2] = 0.1; //B[2][3] = 0;	B[2][4] = 0;
	//B[3][0] = 0; B[3][1] = 0; B[3][2] = 0; B[3][3] = 0;	B[3][4] = 0;

	pi[0] = 1; pi[1] = 0; //pi[2] = 0.4; //pi[3] = 0;

	inputSeq[0][0] = 1; inputSeq[0][1] = 0; inputSeq[0][2] = 0; inputSeq[0][3] = 0; inputSeq[0][4] = 1; inputSeq[0][5] = 0; inputSeq[0][6] = 1;
	inputSeq[1][0] = 0; inputSeq[1][1] = 0; inputSeq[1][2] = 0; inputSeq[1][3] = 1; inputSeq[1][4] = 1; inputSeq[1][5] = 2; inputSeq[1][6] = 0;
	inputSeq[2][0] = 1; inputSeq[2][1] = 1; inputSeq[2][2] = 0; inputSeq[2][3] = 1; inputSeq[2][4] = 0; inputSeq[2][5] = 1; inputSeq[2][6] = 2;
	inputSeq[3][0] = 0; inputSeq[3][1] = 1; inputSeq[3][2] = 0; inputSeq[3][3] = 2; inputSeq[3][4] = 0; inputSeq[3][5] = 1; inputSeq[3][6] = 0;
	inputSeq[4][0] = 2; inputSeq[4][1] = 2; inputSeq[4][2] = 0; inputSeq[4][3] = 1; inputSeq[4][4] = 1; inputSeq[4][5] = 0; inputSeq[4][6] = 1;

	float bestLikelihood = 0;
	float likelihood;
	int bestSeq = -1;
	for (int i = 0; i < SEQ; i++)
	{
		likelihood = forward(A, B, pi, inputSeq[i], forwardArray);
		printf("%f\n\n", likelihood);

		if (likelihood > bestLikelihood)
		{
			bestLikelihood = likelihood;
			bestSeq = i;
		}
	}

	if (bestSeq < 0)
		printf("No chance of any sequence from the selection occurring\n");

	else
		printf("Sequence %d is most likely to occur, with a likelihood of %f.\n", bestSeq + 1, bestLikelihood);
}


float forward(float A[N][N], float B[N][M], float pi[N], int inputSeq[T], float outTimeline[N][T])
{
	//Init sequence arrays
	float prevAlphas[N];
	float curAlphas[N];

	for (int i = 0; i < N; i++)
	{
		prevAlphas[i] = 0;
		curAlphas[i] = pi[i] * B[i][inputSeq[0]];
	}

	printf("T = 0: ");
	for (int i = 0; i < N; i++)
	{
		printf("State %d: %f  ", i, curAlphas[i]);
		outTimeline[i][0] = curAlphas[i];
	}
	printf("\n");

	for (int i = 1; i < T; i++)
	{
		//Move over values
		for (int j = 0; j < N; j++)
		{
			prevAlphas[j] = curAlphas[j];
			curAlphas[j] = 0;
		}

		//For each state at the current time
		for (int curT = 0; curT < N; curT++)
		{
			//Find probability of getting to this point with the observation sequence
			for (int prevT = 0; prevT < N; prevT++)
			{
				curAlphas[curT] += prevAlphas[prevT] * A[prevT][curT] * B[curT][inputSeq[i]];
			}
		}

		printf("T = %d: ", i);
		for (int j = 0; j < N; j++)
		{
			printf("State %d: %f  ", j, curAlphas[j]);
			outTimeline[j][i] = curAlphas[j];
		}
		printf("\n");
	}

	float finSum = 0;
	for (int i = 0; i < N; i++)
	{
		finSum += curAlphas[i];
	}

	return finSum;
}

float backward(float A[N][N], float B[N][M], float pi[N], int inputSeq[T], float outTimeline[N][T])
{
	//Init sequence arrays
	float prevBetas[N];
	float curBetas[N];

	for (int i = 0; i < N; i++)
	{
		prevBetas[i] = 0;
		curBetas[i] = 1;
		outTimeline[i][T - 1] = 1;
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
			outTimeline[j][i] = curBetas[j];
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