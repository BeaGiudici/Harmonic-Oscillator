/****************************************************************************************
*
* File correlator.c
*
* This main program computes the matrix of the correlators and the mean value of the
* correlators at any given time interval t (note, here the rebinning does not occur)
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
	double **c, *c_mean;
	int i, t; /*counters*/
	FILE *fileCmean, *file_matrix;

	/*Initializing the random numbers generator */
	rlxs_init(0, 3452);

	c_mean = malloc(N * sizeof(double));

	c = create_matrix(Nsweep, N);

	thermalization();

	/*Correlator*/
	for (i = 0; i < Nsweep; ++i)
	{
		single_metropolis();
		for (t = 0; t < N; ++t)
		{
			if (i == 0)
			{
				c_mean[t] = 0.0;
			}
			c[i][t] = correlator(t);
			c_mean[t] += c[i][t] / Nsweep;
		}
	}

	/*Writing the mean value of the correlator with the corresponding indices t*/
	fileCmean = fopen("../../results/corr_mean.dat", "w");
	for (t = 0; t < N; ++t)
	{
		fprintf(fileCmean, "%d %f\n", t, c_mean[t]);
	}
	fclose(fileCmean);

	/*Writing the matrix of the correlators on a file*/
	file_matrix = fopen("../../results/corr_matrix.bin", "wb"); /*Write the file in binary*/
	for (i = 0; i < Nsweep; ++i)
	{
		for (t = 0; t < N; ++t)
		{
			fprintf(file_matrix, "%f\t", c[i][t]);
		}
		fprintf(file_matrix, "\n");
	}
	fclose(file_matrix);

	fprintf(stderr, "The files 'corr_mean.dat' and 'corr_matrix.bin' have been generated in the directory 'results'.\n");

	return 0;
}
