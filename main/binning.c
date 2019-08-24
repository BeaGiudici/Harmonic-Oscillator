/****************************************************************************************
*
* File binning.c
*
* This main program generates a rebinned matrix of correlators and writes it in the 
* file 'corr_rebinned_matrix.bin', in the directory 'results'
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

int main(void)
{
	/*Declaration of variables*/
	double **c, *mean;
	int i, t, k; /*counters*/
	FILE *file_matrix, *fileCmean;

	/*Initializing the random numbers generator */
	rlxs_init(0, 3452);

	thermalization();

	c = create_matrix(Nconf, N);

	mean = malloc(N * sizeof(double));

	/*Correlator and rebinning*/
	for (i = 0; i < Nconf; ++i)
	{
		/*Setting all the entries of the line to zero, in order to sum over all the correlators
		If is the first loop, also the entries of the vector of the mean values are set to zero*/
		for (t = 0; t < N; ++t)
		{
			if (i == 0)
			{
				mean[t] = 0.0;
			}
			c[i][t] = 0.0;
		}

		/*With i fixed, I compute the Markov chain for dBin times, summing the correlator 
		(averaged over dBin) at any given time interval t.*/
		for (k = 0; k < dBin; ++k)
		{
			single_metropolis();
			for (t = 0; t < N; ++t)
			{
				c[i][t] += correlator(t) / dBin;
				mean[t] += c[i][t] / Nconf;
			}
		}
	}

	/*Writing the mean value of the correlators with the corresponding indices t*/
	fileCmean = fopen("../results/corr_mean.dat", "w");
	for (t = 0; t < N; ++t)
	{
		fprintf(fileCmean, "%d %f\n", t, mean[t]);
	}
	fclose(fileCmean);

	/*Writing the matrix of the rebinned correlators on a file*/
	file_matrix = fopen("../results/corr_rebinned_matrix.bin", "wb");
	for (i = 0; i < Nconf; ++i)
	{
		for (t = 0; t < N; ++t)
		{
			fprintf(file_matrix, "%f\t", c[i][t]);
		}
		fprintf(file_matrix, "\n");
	}
	fclose(file_matrix);

	fprintf(stderr, "The files 'corr_mean.dat' and 'corr_rebinned_matrix.bin' have been generated in the directory 'results'.\n");

	return 0;
}
