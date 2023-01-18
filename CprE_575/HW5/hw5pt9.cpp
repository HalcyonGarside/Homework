//Implementation of the backward algorithm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nanohmm.h"

int main()
{
	//Initialize O's
	unsigned int** O = (unsigned int**)malloc(5 * sizeof(unsigned int*));
	for (int i = 0; i < 5; i++)
	{
		O[i] = (unsigned int*)malloc(20 * sizeof(unsigned int));
	}

	//Hell.
	O[0][0] = 4; O[0][1] = 2; O[0][2] = 5; O[0][3] = 1; O[0][4] = 5; O[0][5] = 1; O[0][6] = 5; O[0][7] = 3; O[0][8] = 2; O[0][9] = 3; O[0][10] = 2; O[0][11] = 0; O[0][12] = 1; O[0][13] = 0; O[0][14] = 0; O[0][15] = 4; O[0][16] = 4; O[0][17] = 3; O[0][18] = 0; O[0][19] = 1;
	O[1][0] = 3; O[1][1] = 2; O[1][2] = 3; O[1][3] = 3; O[1][4] = 5; O[1][5] = 5; O[1][6] = 5; O[1][7] = 5; O[1][8] = 1; O[1][9] = 0; O[1][10] = 1; O[1][11] = 4; O[1][12] = 2; O[1][13] = 4; O[1][14] = 3; O[1][15] = 0; O[1][16] = 5; O[1][17] = 3; O[1][18] = 1; O[1][19] = 0;
	O[2][0] = 4; O[2][1] = 3; O[2][2] = 0; O[2][3] = 3; O[2][4] = 4; O[2][5] = 0; O[2][6] = 1; O[2][7] = 0; O[2][8] = 2; O[2][9] = 0; O[2][10] = 5; O[2][11] = 3; O[2][12] = 2; O[2][13] = 0; O[2][14] = 0; O[2][15] = 5; O[2][16] = 5; O[2][17] = 3; O[2][18] = 5; O[2][19] = 4;
	O[3][0] = 3; O[3][1] = 4; O[3][2] = 2; O[3][3] = 0; O[3][4] = 5; O[3][5] = 4; O[3][6] = 4; O[3][7] = 3; O[3][8] = 1; O[3][9] = 5; O[3][10] = 3; O[3][11] = 3; O[3][12] = 2; O[3][13] = 3; O[3][14] = 0; O[3][15] = 4; O[3][16] = 2; O[3][17] = 5; O[3][18] = 2; O[3][19] = 4;
	O[4][0] = 2; O[4][1] = 0; O[4][2] = 5; O[4][3] = 4; O[4][4] = 4; O[4][5] = 2; O[4][6] = 0; O[4][7] = 5; O[4][8] = 5; O[4][9] = 4; O[4][10] = 4; O[4][11] = 2; O[4][12] = 0; O[4][13] = 5; O[4][14] = 4; O[4][15] = 4; O[4][16] = 5; O[4][17] = 5; O[4][18] = 5; O[4][19] = 5;

	forward_t *fw = (forward_t*)malloc(forward_block_size(5, 20));

	hmm_t *my_hmm = (hmm_t*)malloc(hmm_block_size(5, 6));
	hmm_init_block(my_hmm, 5, 6);

	my_hmm->N = 5;
	my_hmm->M = 6;

	//Init A matrix
	my_hmm->A[0][0] = 0.5;	my_hmm->A[0][1] = 0.33;	my_hmm->A[0][2] = 0;	my_hmm->A[0][3] = 0.17;	my_hmm->A[0][4] = 0;
	my_hmm->A[1][0] = 0;	my_hmm->A[1][1] = 0;	my_hmm->A[1][2] = 0;	my_hmm->A[1][3] = 0;	my_hmm->A[1][4] = 1;
	my_hmm->A[2][0] = 0.75;	my_hmm->A[2][1] = 0;	my_hmm->A[2][2] = 0.25;	my_hmm->A[2][3] = 0;	my_hmm->A[2][4] = 0;
	my_hmm->A[3][0] = 0;	my_hmm->A[3][1] = 0;	my_hmm->A[3][2] = 0;	my_hmm->A[3][3] = 1;	my_hmm->A[3][4] = 0;
	my_hmm->A[4][0] = 0;	my_hmm->A[4][1] = 0;	my_hmm->A[4][2] = 1;	my_hmm->A[4][3] = 0;	my_hmm->A[4][4] = 0;

	//Init B matrix
	my_hmm->B[0][0] = 0;	my_hmm->B[0][1] = 0;	my_hmm->B[0][2] = 0;	my_hmm->B[0][3] = 0;	my_hmm->B[0][4] = 1;	my_hmm->B[0][5] = 0;
	my_hmm->B[1][0] = 0;	my_hmm->B[1][1] = 0;	my_hmm->B[1][2] = 1;	my_hmm->B[1][3] = 0;	my_hmm->B[1][4] = 0;	my_hmm->B[1][5] = 0;
	my_hmm->B[2][0] = 0;	my_hmm->B[2][1] = 0;	my_hmm->B[2][2] = 0;	my_hmm->B[2][3] = 0;	my_hmm->B[2][4] = 0;	my_hmm->B[2][5] = 1;
	my_hmm->B[3][0] = 0;	my_hmm->B[3][1] = 0;	my_hmm->B[3][2] = 0;	my_hmm->B[3][3] = 0;	my_hmm->B[3][4] = 0;	my_hmm->B[3][5] = 1;
	my_hmm->B[4][0] = 1;	my_hmm->B[4][1] = 0;	my_hmm->B[4][2] = 0;	my_hmm->B[4][3] = 0;	my_hmm->B[4][4] = 0;	my_hmm->B[4][5] = 0;

	//Init pi vector
	my_hmm->pi[0] = 0;	my_hmm->pi[1] = 1;	my_hmm->pi[2] = 0;	my_hmm->pi[3] = 0;	my_hmm->pi[4] = 0;

	
	//Init forward type
	forward_init_block(fw, my_hmm, 20, 0);

	double likelihood = -INFINITY;
	int likelySeq = -1;

	for (int i = 0; i < 5; i++)
	{
		double curLikelihood = forward(fw, O[i], 20);
		printf("Sequence %d likelihood: %f\n", i + 1, curLikelihood);

		if (curLikelihood > likelihood)
		{
			likelihood = curLikelihood;
			likelySeq = i;
		}
	}

	printf("\n");

	if (likelySeq < 0)
		printf("None possible\n");
	else
		printf("The most likely sequence was sequence %d with likelihood %f\n", likelySeq + 1, likelihood);

	free(fw);

	return 0;
}