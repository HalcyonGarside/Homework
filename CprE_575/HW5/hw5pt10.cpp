////Implementation of the backward algorithm
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include "nanohmm.h"
//
//void doBaumWelch(baumwelch_t* bw, unsigned int* O, int T, int iter)
//{
//	printf("Log likelihood of this model: %f\n", baumwelch(bw, O, T, iter));
//
//	printf("A:\n");
//	for (int i = 0; i < bw->lambda->N; i++)
//	{
//		for (int j = 0; j < bw->lambda->N; j++)
//		{
//			printf("%f, ", bw->lambda->A[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//
//
//	printf("B:\n");
//	for (int i = 0; i < bw->lambda->N; i++)
//	{
//		for (int j = 0; j < bw->lambda->M; j++)
//		{
//			printf("%f, ", bw->lambda->B[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//
//	printf("pi:\n");
//	for (int i = 0; i < bw->lambda->N; i++)
//	{
//		printf("%f, ", bw->lambda->pi[i]);
//	}
//	printf("\n\n\n");
//}
//
//int main()
//{
//	//Initialize O's
//	unsigned int** O = (unsigned int**)malloc(5 * sizeof(unsigned int*));
//	for (int i = 0; i < 5; i++)
//	{
//		O[i] = (unsigned int*)malloc(20 * sizeof(unsigned int));
//	}
//
//	//Hell.
//	O[0][0] = 4; O[0][1] = 2; O[0][2] = 5; O[0][3] = 1; O[0][4] = 5; O[0][5] = 1; O[0][6] = 5; O[0][7] = 3; O[0][8] = 2; O[0][9] = 3; O[0][10] = 2; O[0][11] = 0; O[0][12] = 1; O[0][13] = 0; O[0][14] = 0; O[0][15] = 4; O[0][16] = 4; O[0][17] = 3; O[0][18] = 0; O[0][19] = 1;
//	O[1][0] = 3; O[1][1] = 2; O[1][2] = 3; O[1][3] = 3; O[1][4] = 5; O[1][5] = 5; O[1][6] = 5; O[1][7] = 5; O[1][8] = 1; O[1][9] = 0; O[1][10] = 1; O[1][11] = 4; O[1][12] = 2; O[1][13] = 4; O[1][14] = 3; O[1][15] = 0; O[1][16] = 5; O[1][17] = 3; O[1][18] = 1; O[1][19] = 0;
//	O[2][0] = 4; O[2][1] = 3; O[2][2] = 0; O[2][3] = 3; O[2][4] = 4; O[2][5] = 0; O[2][6] = 1; O[2][7] = 0; O[2][8] = 2; O[2][9] = 0; O[2][10] = 5; O[2][11] = 3; O[2][12] = 2; O[2][13] = 0; O[2][14] = 0; O[2][15] = 5; O[2][16] = 5; O[2][17] = 3; O[2][18] = 5; O[2][19] = 4;
//	O[3][0] = 3; O[3][1] = 4; O[3][2] = 2; O[3][3] = 0; O[3][4] = 5; O[3][5] = 4; O[3][6] = 4; O[3][7] = 3; O[3][8] = 1; O[3][9] = 5; O[3][10] = 3; O[3][11] = 3; O[3][12] = 2; O[3][13] = 3; O[3][14] = 0; O[3][15] = 4; O[3][16] = 2; O[3][17] = 5; O[3][18] = 2; O[3][19] = 4;
//	O[4][0] = 2; O[4][1] = 0; O[4][2] = 5; O[4][3] = 4; O[4][4] = 4; O[4][5] = 2; O[4][6] = 0; O[4][7] = 5; O[4][8] = 5; O[4][9] = 4; O[4][10] = 4; O[4][11] = 2; O[4][12] = 0; O[4][13] = 5; O[4][14] = 4; O[4][15] = 4; O[4][16] = 5; O[4][17] = 5; O[4][18] = 5; O[4][19] = 5;
//
//
//	//------------------------------------------------------------
//	//						PART A
//	//------------------------------------------------------------
//	hmm_t* my_hmm = (hmm_t*)malloc(hmm_block_size(3, 6));
//	hmm_init_block(my_hmm, 3, 6);
//
//	my_hmm->N = 3;
//	my_hmm->M = 6;
//
//	//---------------------Model 1-------------------------------
//	//Init A matrix
//	my_hmm->A[0][0] = 0.65;	my_hmm->A[0][1] = 0.15;	my_hmm->A[0][2] = 0.2;
//	my_hmm->A[1][0] = 0.22;	my_hmm->A[1][1] = 0.66;	my_hmm->A[1][2] = 0.12;
//	my_hmm->A[2][0] = 0.75;	my_hmm->A[2][1] = 0;	my_hmm->A[2][2] = 0.25;
//
//	//Init B matrix
//	my_hmm->B[0][0] = 0.11;	my_hmm->B[0][1] = 0.11;	my_hmm->B[0][2] = 0.11;	my_hmm->B[0][3] = 0.11;	my_hmm->B[0][4] = 0.33;	my_hmm->B[0][5] = 0.23;
//	my_hmm->B[1][0] = 0.25;	my_hmm->B[1][1] = 0.25;	my_hmm->B[1][2] = 0;	my_hmm->B[1][3] = 0.25;	my_hmm->B[1][4] = 0.25;	my_hmm->B[1][5] = 0;
//	my_hmm->B[2][0] = 0;	my_hmm->B[2][1] = 0;	my_hmm->B[2][2] = 0.5;	my_hmm->B[2][3] = 0;	my_hmm->B[2][4] = 0;	my_hmm->B[2][5] = 0.5;
//
//	//Init pi vector
//	my_hmm->pi[0] = 0.33;	my_hmm->pi[1] = 0.33;	my_hmm->pi[2] = 0.33;
//
//
//	//Init Baum-Welch Alg
//	baumwelch_t* bw = (baumwelch_t*)malloc(baumwelch_block_size(3, 6, 20));
//	baumwelch_init_block(bw, my_hmm, 20, 0);
//
//	doBaumWelch(bw, O[0], 20, 20);
//
//
//	//---------------------Model 2-------------------------------
//	//Init A matrix
//	my_hmm->A[0][0] = 0.33;	my_hmm->A[0][1] = 0.33;	my_hmm->A[0][2] = 0.34;
//	my_hmm->A[1][0] = 0.4;	my_hmm->A[1][1] = 0.6;	my_hmm->A[1][2] = 0;
//	my_hmm->A[2][0] = 0.33;	my_hmm->A[2][1] = 0.22;	my_hmm->A[2][2] = 0.45;
//
//	//Init B matrix
//	my_hmm->B[0][0] = 0.25;	my_hmm->B[0][1] = 0.11;	my_hmm->B[0][2] = 0.20;	my_hmm->B[0][3] = 0;	my_hmm->B[0][4] = 0.1;	my_hmm->B[0][5] = 0.34;
//	my_hmm->B[1][0] = 0.5;	my_hmm->B[1][1] = 0;	my_hmm->B[1][2] = 0;	my_hmm->B[1][3] = 0.5;	my_hmm->B[1][4] = 0;	my_hmm->B[1][5] = 0;
//	my_hmm->B[2][0] = 0;	my_hmm->B[2][1] = 0.34;	my_hmm->B[2][2] = 0.33;	my_hmm->B[2][3] = 0.33;	my_hmm->B[2][4] = 0;	my_hmm->B[2][5] = 0;
//
//	//Init pi vector
//	my_hmm->pi[0] = 0;	my_hmm->pi[1] = 0.5;	my_hmm->pi[2] = 0.5;
//
//	doBaumWelch(bw, O[1], 20, 100);
//
//
//	//---------------------Model 3-------------------------------
//	//Init A matrix
//	my_hmm->A[0][0] = 0;	my_hmm->A[0][1] = 0;	my_hmm->A[0][2] = 1;
//	my_hmm->A[1][0] = 0.6;	my_hmm->A[1][1] = 0.2;	my_hmm->A[1][2] = 0.2;
//	my_hmm->A[2][0] = 0.59;	my_hmm->A[2][1] = 0.21;	my_hmm->A[2][2] = 0.2;
//
//	//Init B matrix
//	my_hmm->B[0][0] = 0;	my_hmm->B[0][1] = 0;	my_hmm->B[0][2] = 0;	my_hmm->B[0][3] = 0.7;	my_hmm->B[0][4] = 0;	my_hmm->B[0][5] = 0.3;
//	my_hmm->B[1][0] = 0;	my_hmm->B[1][1] = 1;	my_hmm->B[1][2] = 0;	my_hmm->B[1][3] = 0;	my_hmm->B[1][4] = 0;	my_hmm->B[1][5] = 0;
//	my_hmm->B[2][0] = 0.16;	my_hmm->B[2][1] = 0.2;	my_hmm->B[2][2] = 0.16;	my_hmm->B[2][3] = 0.16;	my_hmm->B[2][4] = 0.16;	my_hmm->B[2][5] = 0.16;
//
//	//Init pi vector
//	my_hmm->pi[0] = 0.59;	my_hmm->pi[1] = 0.34;	my_hmm->pi[2] = 0.07;
//
//	doBaumWelch(bw, O[2], 20, 100);
//
//
//	//---------------------Model 4-------------------------------
//	//Init A matrix
//	my_hmm->A[0][0] = 0.25;	my_hmm->A[0][1] = 0.25;	my_hmm->A[0][2] = 0.5;
//	my_hmm->A[1][0] = 0.33;	my_hmm->A[1][1] = 0.34;	my_hmm->A[1][2] = 0.33;
//	my_hmm->A[2][0] = 0.69;	my_hmm->A[2][1] = 0.1;	my_hmm->A[2][2] = 0.21;
//
//	//Init B matrix
//	my_hmm->B[0][0] = 0.13;	my_hmm->B[0][1] = 0.43;	my_hmm->B[0][2] = 0.23;	my_hmm->B[0][3] = 0.21;	my_hmm->B[0][4] = 0;	my_hmm->B[0][5] = 0;
//	my_hmm->B[1][0] = 0.01;	my_hmm->B[1][1] = 0.29;	my_hmm->B[1][2] = 0.1;	my_hmm->B[1][3] = 0.5;	my_hmm->B[1][4] = 0.05;	my_hmm->B[1][5] = 0.05;
//	my_hmm->B[2][0] = 0.5;	my_hmm->B[2][1] = 0;	my_hmm->B[2][2] = 0;	my_hmm->B[2][3] = 0;	my_hmm->B[2][4] = 0.5;	my_hmm->B[2][5] = 0;
//
//	//Init pi vector
//	my_hmm->pi[0] = 1;	my_hmm->pi[1] = 0;	my_hmm->pi[2] = 0;
//
//	doBaumWelch(bw, O[3], 20, 100);
//
//
//	//---------------------Model 5-------------------------------
//	//Init A matrix
//	my_hmm->A[0][0] = 0.08;	my_hmm->A[0][1] = 0.7;	my_hmm->A[0][2] = 0.22;
//	my_hmm->A[1][0] = 0.3;	my_hmm->A[1][1] = 0.6;	my_hmm->A[1][2] = 0.1;
//	my_hmm->A[2][0] = 0.01;	my_hmm->A[2][1] = 0.49;	my_hmm->A[2][2] = 0.5;
//
//	//Init B matrix
//	my_hmm->B[0][0] = 0.91;	my_hmm->B[0][1] = 0;	my_hmm->B[0][2] = 0;	my_hmm->B[0][3] = 0.09;	my_hmm->B[0][4] = 0;	my_hmm->B[0][5] = 0;
//	my_hmm->B[1][0] = 0;	my_hmm->B[1][1] = 0;	my_hmm->B[1][2] = 0.25;	my_hmm->B[1][3] = 0.25;	my_hmm->B[1][4] = 0.25;	my_hmm->B[1][5] = 0.25;
//	my_hmm->B[2][0] = 0;	my_hmm->B[2][1] = 0.34;	my_hmm->B[2][2] = 0.33;	my_hmm->B[2][3] = 0;	my_hmm->B[2][4] = 0;	my_hmm->B[2][5] = 0.33;
//
//	//Init pi vector
//	my_hmm->pi[0] = 0.2;	my_hmm->pi[1] = 0.4;	my_hmm->pi[2] = 0.4;
//
//	doBaumWelch(bw, O[4], 20, 100);
//
//	free(my_hmm);
//	free(bw);
//
//
//	//TODO: EDIT MATRICES
//	//------------------------------------------------------------
//	//						PART B
//	//------------------------------------------------------------
//	hmm_t* my_hmm_4 = (hmm_t*)malloc(hmm_block_size(4, 6));
//	hmm_init_block(my_hmm_4, 4, 6);
//
//	my_hmm_4->N = 4;
//	my_hmm_4->M = 6;
//
//	//---------------------Model 1-------------------------------
//	//Init A matrix
//	my_hmm_4->A[0][0] = 0.2;	my_hmm_4->A[0][1] = 0.2;	my_hmm_4->A[0][2] = 0.2;	my_hmm_4->A[0][3] = 0.4;
//	my_hmm_4->A[1][0] = 0.4;	my_hmm_4->A[1][1] = 0.2;	my_hmm_4->A[1][2] = 0.3;	my_hmm_4->A[1][3] = 0.1;
//	my_hmm_4->A[2][0] = 0.75;	my_hmm_4->A[2][1] = 0;	my_hmm_4->A[2][2] = 0.25;		my_hmm_4->A[2][3] = 0.0;
//	my_hmm_4->A[3][0] = 0;		my_hmm_4->A[3][1] = 0.25;	my_hmm_4->A[3][2] = 0;		my_hmm_4->A[3][3] = 0.75;
//
//	//Init B matrix
//	my_hmm_4->B[0][0] = 0.11;	my_hmm_4->B[0][1] = 0.11;	my_hmm_4->B[0][2] = 0.11;	my_hmm_4->B[0][3] = 0.11;	my_hmm_4->B[0][4] = 0.33;	my_hmm_4->B[0][5] = 0.23;
//	my_hmm_4->B[1][0] = 0.25;	my_hmm_4->B[1][1] = 0.25;	my_hmm_4->B[1][2] = 0;	my_hmm_4->B[1][3] = 0.25;	my_hmm_4->B[1][4] = 0.25;	my_hmm_4->B[1][5] = 0;
//	my_hmm_4->B[2][0] = 0;	my_hmm_4->B[2][1] = 0;	my_hmm_4->B[2][2] = 0.5;	my_hmm_4->B[2][3] = 0;	my_hmm_4->B[2][4] = 0;	my_hmm_4->B[2][5] = 0.5;
//	my_hmm_4->B[3][0] = 0.4;	my_hmm_4->B[3][1] = 0.2;	my_hmm_4->B[3][2] = 0.1;	my_hmm_4->B[3][3] = 0.05;	my_hmm_4->B[3][4] = 0.2;	my_hmm_4->B[3][5] = 0.05;
//
//	//Init pi vector
//	my_hmm_4->pi[0] = 0.33;	my_hmm_4->pi[1] = 0.13;	my_hmm_4->pi[2] = 0.21; my_hmm_4->pi[3] = 0.33;
//
//
//	//Init Baum-Welch Alg
//	baumwelch_t* bw4 = (baumwelch_t*)malloc(baumwelch_block_size(4, 6, 20));
//	baumwelch_init_block(bw4, my_hmm_4, 20, 0);
//
//	doBaumWelch(bw4, O[0], 20, 20);
//
//
//	//---------------------Model 2-------------------------------
//	//Init A matrix
//	my_hmm_4->A[0][0] = 0.3;	my_hmm_4->A[0][1] = 0.1;	my_hmm_4->A[0][2] = 0.1;	my_hmm_4->A[0][3] = 0.5;
//	my_hmm_4->A[1][0] = 0.5;	my_hmm_4->A[1][1] = 0.2;	my_hmm_4->A[1][2] = 0.2;		my_hmm_4->A[1][3] = 0.1;
//	my_hmm_4->A[2][0] = 0.25;	my_hmm_4->A[2][1] = 0.33;	my_hmm_4->A[2][2] = 0.35;	my_hmm_4->A[2][3] = 0.07;
//	my_hmm_4->A[3][0] = 0.1;	my_hmm_4->A[3][1] = 0.6;	my_hmm_4->A[3][2] = 0.15;		my_hmm_4->A[3][3] = 0.15;
//
//	//Init B matrix
//	my_hmm_4->B[0][0] = 0.25;	my_hmm_4->B[0][1] = 0.11;	my_hmm_4->B[0][2] = 0.20;	my_hmm_4->B[0][3] = 0;	my_hmm_4->B[0][4] = 0.1;	my_hmm_4->B[0][5] = 0.34;
//	my_hmm_4->B[1][0] = 0.5;	my_hmm_4->B[1][1] = 0;	my_hmm_4->B[1][2] = 0;	my_hmm_4->B[1][3] = 0.5;	my_hmm_4->B[1][4] = 0;	my_hmm_4->B[1][5] = 0;
//	my_hmm_4->B[2][0] = 0;	my_hmm_4->B[2][1] = 0.34;	my_hmm_4->B[2][2] = 0.33;	my_hmm_4->B[2][3] = 0.33;	my_hmm_4->B[2][4] = 0;	my_hmm_4->B[2][5] = 0;
//	my_hmm_4->B[3][0] = 0.9;	my_hmm_4->B[3][1] = 0.02;	my_hmm_4->B[3][2] = 0.02;	my_hmm_4->B[3][3] = 0.02;	my_hmm_4->B[3][4] = 0.02;	my_hmm_4->B[3][5] = 0.02;
//
//	//Init pi vector
//	my_hmm_4->pi[0] = 0.02;	my_hmm_4->pi[1] = 0.5;	my_hmm_4->pi[2] = 0.15; my_hmm_4->pi[3] = 0.33;
//
//	doBaumWelch(bw4, O[1], 20, 100);
//
//
//	//---------------------Model 3-------------------------------
//	//Init A matrix
//	my_hmm_4->A[0][0] = 0;		my_hmm_4->A[0][1] = 0;		my_hmm_4->A[0][2] = 0.5;	my_hmm_4->A[0][3] = 0.5;
//	my_hmm_4->A[1][0] = 0.6;	my_hmm_4->A[1][1] = 0.1;	my_hmm_4->A[1][2] = 0.2;	my_hmm_4->A[1][3] = 0.1;
//	my_hmm_4->A[2][0] = 0.59;	my_hmm_4->A[2][1] = 0.11;	my_hmm_4->A[2][2] = 0.2;	my_hmm_4->A[2][3] = 0.1;
//	my_hmm_4->A[3][0] = 0.75;	my_hmm_4->A[3][1] = 0;		my_hmm_4->A[3][2] = 0.1;	my_hmm_4->A[3][3] = 0.15;
//	//Init B matrix
//	my_hmm_4->B[0][0] = 0;	my_hmm_4->B[0][1] = 0;	my_hmm_4->B[0][2] = 0;	my_hmm_4->B[0][3] = 0.7;	my_hmm_4->B[0][4] = 0;	my_hmm_4->B[0][5] = 0.3;
//	my_hmm_4->B[1][0] = 0;	my_hmm_4->B[1][1] = 1;	my_hmm_4->B[1][2] = 0;	my_hmm_4->B[1][3] = 0;	my_hmm_4->B[1][4] = 0;	my_hmm_4->B[1][5] = 0;
//	my_hmm_4->B[2][0] = 0.16;	my_hmm_4->B[2][1] = 0.2;	my_hmm_4->B[2][2] = 0.16;	my_hmm_4->B[2][3] = 0.16;	my_hmm_4->B[2][4] = 0.16;	my_hmm_4->B[2][5] = 0.16;
//	my_hmm_4->B[3][0] = 0.5;	my_hmm_4->B[3][1] = 0;	my_hmm_4->B[3][2] = 0;	my_hmm_4->B[3][3] = 0;	my_hmm_4->B[3][4] = 0.5;	my_hmm_4->B[3][5] = 0;
//
//	//Init pi vector
//	my_hmm_4->pi[0] = 0.59;	my_hmm_4->pi[1] = 0.04;	my_hmm_4->pi[2] = 0.03; my_hmm_4->pi[3] = 0.34;
//
//	doBaumWelch(bw4, O[2], 20, 100);
//
//
//	//---------------------Model 4-------------------------------
//	//Init A matrix
//	my_hmm_4->A[0][0] = 0.25;	my_hmm_4->A[0][1] = 0.25;	my_hmm_4->A[0][2] = 0.25;	my_hmm_4->A[0][3] = 0.25;
//	my_hmm_4->A[1][0] = 0.33;	my_hmm_4->A[1][1] = 0.33;	my_hmm_4->A[1][2] = 0.33;	my_hmm_4->A[1][3] = 0.01;
//	my_hmm_4->A[2][0] = 0.69;	my_hmm_4->A[2][1] = 0.1;	my_hmm_4->A[2][2] = 0.06;	my_hmm_4->A[2][3] = 0.15;
//	my_hmm_4->A[3][0] = 0.25;	my_hmm_4->A[3][1] = 0;		my_hmm_4->A[3][2] = 0.25;	my_hmm_4->A[3][3] = 0.5;
//
//	//Init B matrix
//	my_hmm_4->B[0][0] = 0.13;	my_hmm_4->B[0][1] = 0.43;	my_hmm_4->B[0][2] = 0.23;	my_hmm_4->B[0][3] = 0.21;	my_hmm_4->B[0][4] = 0;	my_hmm_4->B[0][5] = 0;
//	my_hmm_4->B[1][0] = 0.01;	my_hmm_4->B[1][1] = 0.29;	my_hmm_4->B[1][2] = 0.1;	my_hmm_4->B[1][3] = 0.5;	my_hmm_4->B[1][4] = 0.05;	my_hmm_4->B[1][5] = 0.05;
//	my_hmm_4->B[2][0] = 0.5;	my_hmm_4->B[2][1] = 0;	my_hmm_4->B[2][2] = 0;	my_hmm_4->B[2][3] = 0;	my_hmm_4->B[2][4] = 0.5;	my_hmm_4->B[2][5] = 0;
//	my_hmm_4->B[3][0] = 0.11;	my_hmm_4->B[3][1] = 0.11;	my_hmm_4->B[3][2] = 0.22;	my_hmm_4->B[3][3] = 0.22;	my_hmm_4->B[3][4] = 0.22;	my_hmm_4->B[3][5] = 0.12;
//
//	//Init pi vector
//	my_hmm_4->pi[0] = 0.33;	my_hmm_4->pi[1] = 0;	my_hmm_4->pi[2] = 0.33; my_hmm_4->pi[3] = 0.33;
//
//	doBaumWelch(bw4, O[3], 20, 100);
//
//
//	//---------------------Model 5-------------------------------
//	//Init A matrix
//	my_hmm_4->A[0][0] = 0.08;	my_hmm_4->A[0][1] = 0.45;	my_hmm_4->A[0][2] = 0.22;	my_hmm_4->A[0][3] = 0.25;
//	my_hmm_4->A[1][0] = 0.3;	my_hmm_4->A[1][1] = 0.48;	my_hmm_4->A[1][2] = 0.1;	my_hmm_4->A[1][3] = 0.22;
//	my_hmm_4->A[2][0] = 0.01;	my_hmm_4->A[2][1] = 0.49;	my_hmm_4->A[2][2] = 0.29;	my_hmm_4->A[2][3] = 0.21;
//	my_hmm_4->A[3][0] = 0.33;	my_hmm_4->A[3][1] = 0.44;	my_hmm_4->A[3][2] = 0.01;		my_hmm_4->A[3][3] = 0.22;
//
//	//Init B matrix
//	my_hmm_4->B[0][0] = 0.91;	my_hmm_4->B[0][1] = 0;	my_hmm_4->B[0][2] = 0;	my_hmm_4->B[0][3] = 0.09;	my_hmm_4->B[0][4] = 0;	my_hmm_4->B[0][5] = 0;
//	my_hmm_4->B[1][0] = 0;	my_hmm_4->B[1][1] = 0;	my_hmm_4->B[1][2] = 0.25;	my_hmm_4->B[1][3] = 0.25;	my_hmm_4->B[1][4] = 0.25;	my_hmm_4->B[1][5] = 0.25;
//	my_hmm_4->B[2][0] = 0;	my_hmm_4->B[2][1] = 0.34;	my_hmm_4->B[2][2] = 0.33;	my_hmm_4->B[2][3] = 0;	my_hmm_4->B[2][4] = 0;	my_hmm_4->B[2][5] = 0.33;
//	my_hmm_4->B[3][0] = 0.24;	my_hmm_4->B[3][1] = 0.19;	my_hmm_4->B[3][2] = 0.08;	my_hmm_4->B[3][3] = 0.08;	my_hmm_4->B[3][4] = 0.2;	my_hmm_4->B[3][5] = 0.21;
//
//	//Init pi vector
//	my_hmm_4->pi[0] = 0.2;	my_hmm_4->pi[1] = 0.4;	my_hmm_4->pi[2] = 0.2; my_hmm_4->pi[3] = 0.2;
//
//	doBaumWelch(bw4, O[4], 20, 100);
//
//	return 0;
//}