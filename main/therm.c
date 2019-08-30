/****************************************************************************************
*
* File therm.c
*
* This main program generates Markov chains and computes the action for every sweep, 
* writing its value and the corresponding sweep indices on a file (both for cold start
* and hot start)
*
* AUTHOR: Beatrice Giudici <b.giudici1@campus.unimib.it>
* CREATED: 21/03/2019
*
****************************************************************************************/

#define MAIN_PROGRAM

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "global.h"
#include "phys.h"
#include "random.h"
#include "extras.h"

#define Nsweep 1000

int main(void)
{
	/*Declaration of variables*/
	double *S;
	int i;
	float r3[N];
	FILE *file;

	/*Initializing the random numbers generator */
	rlxs_init(0, 3452);

	/*Creating a ector to collect the values of the action at each sweep */
	S = malloc(Nsweep * sizeof(double));

	/*Cold start*/
	for (i = 0; i < N; ++i)
	{
		xx[i] = 0.0;
	}

	S[0] = action();
	for (i = 1; i < Nsweep; ++i)
	{
		single_metropolis();
		S[i] = action();
	}

	/*Writing on a file all the results */
	file = fopen("../results/cold_therm.dat", "w");
	for (i = 0; i < Nsweep; ++i)
	{
		fprintf(file, "%d %f\n", i, S[i]);
	}
	fclose(file);

	/*Hot start*/
	ranlxs(r3, N);
	for (i = 0; i < N; ++i)
	{
		/*The initial values are randomly chosen in [-10,10) */
		xx[i] = (double)10 * (r3[i] - 0.5);
	}

	S[0] = action();
	for (i = 1; i < Nsweep; ++i)
	{
		single_metropolis();
		S[i] = action();
	}

	/*Writing the results on a file */
	file = fopen("../results/hot_therm.dat", "w");
	for (i = 0; i < Nsweep; ++i)
	{
		fprintf(file, "%d %f\n", i, S[i]);
	}
	fclose(file);

	fprintf(stderr, "The files 'cold_therm.dat' and 'hot_therm.dat' have been generated in the directory 'results'.\n");

	return 0;
}
