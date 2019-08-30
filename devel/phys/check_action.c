/*******************************************************************************
*
* File check_action.c
*
* This program checks that action implements the basic algorithm
* correctly
*
* AUTHOR: Beatrice Giudici <b.giudici1@campus.unimib.it>
* CREATED: 14/04/2019
*
*******************************************************************************/

#define MAIN_PROGRAM

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "global.h"
#include "random.h"
#include "phys.h"

int main(void)
{
	/*Declaring the variables */
	double S;
	int i;
	float r_vector[1]; /*For this check, only one random number is needed*/
	double delta = 2.;
	double alpha;

	rlxs_init(0, 3452);

	/*Initializing the entries of the vector in a clever way, in order to compute 
	the action both analitically and numerically without much trouble */
	for (i = 0; i < N; i++)
	{
		xx[i] = 1.;
	}

	S = action();
	fprintf(stdout, "PARAMETERS: M = 1, W = 1, N = 64\n\n");
	fprintf(stdout, "Expected action: 32\n");
	fprintf(stdout, "Action: %f\n", S);

	/*Computing the variation of the action for a chosen index */
	ranlxs(r_vector, 1); /*generation of 2*N random values*/
	i = 4;
	alpha = 2 * delta * (r_vector[0] - 0.5);
	fprintf(stdout, "alpha: %f\n", alpha);
	fprintf(stdout, "delta_S: %f\n", delta_S(i, alpha));

	return 0;
}
