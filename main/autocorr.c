/****************************************************************************************
*
* File autocorr.c
*
* This main program generates the matrix of the correlators and, for a fixed time 
* interval (chosen to be t = 5), calculates the autocorrelation function
*
* AUTHOR: Beatrice Giudici <b.giudici1@campus.unimib.it>
* CREATED: 28/03/2019
* MODIFIED: 02/08/2019
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

#define Nsweep 100000
#define T_M_MAX 50

int main(void)
{
	/*Declaration of variables*/
	double temp, **c, mean, mean_sq, *gamma;
	int i, t; /*counters*/
	FILE *file;

	/*Initializing the random numbers generator */
	rlxs_init(0, 3452);

	c = create_matrix(Nsweep, N);

	/*Thermalization of the chain*/
	thermalization();

	mean = 0.0;
	mean_sq = 0.0;

	/*Correlator*/
	for (i = 0; i < Nsweep; ++i)
	{
		single_metropolis();
		for (t = 0; t < N; ++t)
		{
			c[i][t] = correlator(t);

			/*Updating the mean and the mean of the squares for t=5*/
			if (t == 5)
			{
				mean += c[i][t] / Nsweep;
				mean_sq += c[i][t] * c[i][t] / Nsweep;
			}
		}
	}

	/*Gamma function for t = 5*/
	gamma = malloc(T_M_MAX * sizeof(double));

	for (i = 0; i < Nsweep - T_M_MAX; ++i)
	{
		for (t = 0; t < T_M_MAX; ++t)
		{
			if (i == 0)
			{
				gamma[t] = 0.0;
			}
			temp = (c[i][5] * c[i + t][5] - mean * mean) / (mean_sq - mean * mean);
			gamma[t] += temp / (Nsweep - T_M_MAX);
		}
	}

	/*Writing the results on a file */
	file = fopen("../results/gamma.dat", "w");
	for (t = 0; t < T_M_MAX; t++)
	{
		fprintf(file, "%d %f\n", t, gamma[t]);
	}
	fclose(file);

	fprintf(stderr, "The file 'gamma.dat' has been generated in the directory 'results'.\n");

	return 0;
}
