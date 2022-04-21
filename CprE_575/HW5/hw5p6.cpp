////implementation of the backward algorithm
//
//#include <stdio.h>
//
//#define n 2
//#define m 3
//#define t 7
//
//float forward(float a[n][n], float b[n][m], float pi[n], int inputseq[t], float outtimeline[n][t]);
//float backward(float a[n][n], float b[n][m], float pi[n], int inputseq[t], float outtimeline[n][t]);
//
//int main()
//{
//	float forwardarray[n][t];
//	float backwardarray[n][t];
//
//	float a[n][n];
//	float b[n][m];
//
//	float pi[n];
//
//	int inputseq[t];
//
//	//input array values here:
//	a[0][0] = 0.6; a[0][1] = 0.4; //a[0][2] = 0.1; //a[0][3] = 0;
//	a[1][0] = 1; a[1][1] = 0; //a[1][2] = 0.4; //a[1][3] = 0;
//	//a[2][0] = 0; a[2][1] = 0.3; a[2][2] = 0.7; //a[2][3] = 0;
//	//a[3][0] = 0; a[3][1] = 0; a[3][2] = 0; a[3][3] = 0;
//
//	b[0][0] = 0.7; b[0][1] = 0.3; b[0][2] = 0; //b[0][3] = 0; b[0][4] = 0;
//	b[1][0] = 0.1; b[1][1] = 0.1; b[1][2] = 0.8; //b[1][3] = 0;	b[1][4] = 0;
//	//b[2][0] = 0.5; b[2][1] = 0.4; b[2][2] = 0.1; //b[2][3] = 0;	b[2][4] = 0;
//	//b[3][0] = 0; b[3][1] = 0; b[3][2] = 0; b[3][3] = 0;	b[3][4] = 0;
//
//	pi[0] = 0.7; pi[1] = 0.3; //pi[2] = 0.4; //pi[3] = 0;
//
//	inputseq[0] = 2; inputseq[1] = 2; inputseq[2] = 0; inputseq[3] = 1; inputseq[4] = 1; inputseq[5] = 0; inputseq[6] = 1;
//
//	printf("%f\n\n", forward(a, b, pi, inputseq, forwardarray));
//	printf("%f\n\n", backward(a, b, pi, inputseq, backwardarray));
//
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < t; j++)
//		{
//			printf("%f ", forwardarray[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < t; j++)
//		{
//			printf("%f ", backwardarray[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//
//	float likelihood;
//	for (int i = 0; i < t; i++)
//	{
//		likelihood = 0;
//		for (int j = 0; j < n; j++)
//		{
//			likelihood += forwardarray[j][i] * backwardarray[j][i];
//		}
//		printf("%f\n", likelihood);
//	}
//
//}
//
//
//float forward(float a[n][n], float b[n][m], float pi[n], int inputseq[t], float outtimeline[n][t])
//{
//	//init sequence arrays
//	float prevalphas[n];
//	float curalphas[n];
//
//	for (int i = 0; i < n; i++)
//	{
//		prevalphas[i] = 0;
//		curalphas[i] = pi[i] * b[i][inputseq[0]];
//	}
//
//	printf("t = 0: ");
//	for (int i = 0; i < n; i++)
//	{
//		printf("state %d: %f  ", i, curalphas[i]);
//		outtimeline[i][0] = curalphas[i];
//	}
//	printf("\n");
//
//	for (int i = 1; i < t; i++)
//	{
//		//move over values
//		for (int j = 0; j < n; j++)
//		{
//			prevalphas[j] = curalphas[j];
//			curalphas[j] = 0;
//		}
//
//		//for each state at the current time
//		for (int curt = 0; curt < n; curt++)
//		{
//			//find probability of getting to this point with the observation sequence
//			for (int prevt = 0; prevt < n; prevt++)
//			{
//				curalphas[curt] += prevalphas[prevt] * a[prevt][curt] * b[curt][inputseq[i]];
//			}
//		}
//
//		printf("t = %d: ", i);
//		for (int j = 0; j < n; j++)
//		{
//			printf("state %d: %f  ", j, curalphas[j]);
//			outtimeline[j][i] = curalphas[j];
//		}
//		printf("\n");
//	}
//
//	float finsum = 0;
//	for (int i = 0; i < n; i++)
//	{
//		finsum += curalphas[i];
//	}
//
//	return finsum;
//}
//
//float backward(float a[n][n], float b[n][m], float pi[n], int inputseq[t], float outtimeline[n][t])
//{
//	//init sequence arrays
//	float prevbetas[n];
//	float curbetas[n];
//
//	for (int i = 0; i < n; i++)
//	{
//		prevbetas[i] = 0;
//		curbetas[i] = 1;
//		outtimeline[i][t - 1] = 1;
//	}
//
//	printf("t = %d: ", t - 1);
//	for (int i = 0; i < n; i++)
//	{
//		printf("state %d: %f  ", i, curbetas[i]);
//	}
//	printf("\n");
//
//	for (int i = t - 2; i >= 0; i--)
//	{
//		//move over values
//		for (int j = 0; j < n; j++)
//		{
//			prevbetas[j] = curbetas[j];
//			curbetas[j] = 0;
//		}
//
//		//for each state at the current time
//		for (int curt = 0; curt < n; curt++)
//		{
//			//find probability of getting to this point with the observation sequence
//			for (int prevt = 0; prevt < n; prevt++)
//			{
//				curbetas[curt] += prevbetas[prevt] * a[curt][prevt] * b[prevt][inputseq[i + 1]];
//			}
//		}
//
//		printf("t = %d: ", i);
//		for (int j = 0; j < n; j++)
//		{
//			printf("state %d: %f  ", j, curbetas[j]);
//			outtimeline[j][i] = curbetas[j];
//		}
//		printf("\n");
//	}
//
//	float finsum = 0;
//	for (int i = 0; i < n; i++)
//	{
//		finsum += curbetas[i];
//	}
//
//	return finsum;
//}