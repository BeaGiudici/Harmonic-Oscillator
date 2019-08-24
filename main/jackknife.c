/****************************************************************************************
*
* File jackknife.c
*
* This code reads the matrix of the rebinned correlators and uses it to find the
* differences of energy between the first excitated state and the ground state, with
* errors, using jackknife method
*
* AUTHOR: Beatrice Giudici <b.giudici1@campus.unimib.it>
* CREATED: 04/04/2019
* MODIFIED: 20/07/2019
*
****************************************************************************************/

#define MAIN_PROGRAM

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "global.h"
#include "phys.h"

int main(void)
{
	double *pc, **c, *c_mean, *pE, **delta_E, *E_mean, *E_var, **mel, *pm, *mel_mean, *mel_var;
	int i, t; /*counters*/
	int ct;   /*Needed because fscanf returns an integer 
			(the compiler gives an error otherwise)*/
	FILE *file_in, *file_energy, *file_mel;

	/*Dynamical allocation of the matrices (the function is not used, because this way 
	there is only one for-loop)*/
	pc = malloc((Nconf * N) * sizeof(double));
	pE = malloc((Nconf * N) * sizeof(double));
	pm = malloc((Nconf * N) * sizeof(double));
	c = malloc(Nconf * sizeof(double *));
	delta_E = malloc(Nconf * sizeof(double *));
	mel = malloc(Nconf * sizeof(double *));
	for (i = 0; i < Nconf; i++)
	{
		c[i] = pc + N * i;
		delta_E[i] = pE + N * i;
		mel[i] = pm + N * i;
	}

	/*Dynamical allocation of the vectors*/
	c_mean = malloc(N * sizeof(double));
	E_mean = malloc(N * sizeof(double));
	E_var = malloc(N * sizeof(double));
	mel_mean = malloc(N * sizeof(double));
	mel_var = malloc(N * sizeof(double));

	/*Read the file*/
	file_in = fopen("../results/corr_rebinned_matrix.bin", "rb");
	for (i = 0; i < Nconf; ++i)
	{
		for (t = 0; t < N; ++t)
		{
			if (i == 0)
			{
				c_mean[t] = 0.0;
			}
			ct = fscanf(file_in, "%lf", &c[i][t]);
			if (feof(file_in))
				break;
			/*Check if the data are stored as expected*/
			if (ct != 1)
			{
				fprintf(stderr, "Unexpected error in input data.\n");
				return 1;
			}
			c_mean[t] += c[i][t] / Nconf;
		}
	}
	fclose(file_in);

	/*Clustering*/
	for (i = 0; i < Nconf; ++i)
	{
		for (t = 0; t < N; ++t)
		{
			c[i][t] = c_mean[t] - (c[i][t] - c_mean[t]) / (Nconf - 1);
		}
	}

	for (i = 0; i < Nconf; ++i)
	{
		for (t = 0; t < N; ++t)
		{
			/*Inizializing to zero the entries of the vectors in the first loop*/
			if (i == 0)
			{
				E_var[t] = 0.0;
				mel_var[t] = 0.0;
			}
			delta_E[i][t] = deltaE(c[i][(t + 1) % N], c[i][(t - 1 + N) % N], c[i][t]);
			mel[i][t] = matrix_el(c[i][t], delta_E[i][t], t);
			E_mean[t] = deltaE(c_mean[(t + 1) % N], c_mean[(t - 1 + N) % N], c_mean[t]);
			mel_mean[t] = matrix_el(c_mean[t], E_mean[t], t);
			E_var[t] += (delta_E[i][t] - E_mean[t]) * (delta_E[i][t] - E_mean[t]) * (Nconf - 1) / Nconf;
			mel_var[t] += (mel[i][t] - mel_mean[t]) * (mel[i][t] - mel_mean[t]) * (Nconf - 1) / Nconf;
		}
	}

	/*Writing on a file all the results*/
	file_energy = fopen("../results/deltaE.dat", "w");
	file_mel = fopen("../results/matrix_el.dat", "w");
	fprintf(file_energy, "%d\n", N);
	fprintf(file_mel, "%d\n", N);
	for (t = 0; t < N; ++t)
	{
		fprintf(file_energy, "%d %f %f\n", t, E_mean[t], sqrt(E_var[t]));
		fprintf(file_mel, "%d %f %f\n", t, mel_mean[t], sqrt(mel_var[t]));
	}
	fclose(file_energy);
	fclose(file_mel);

	fprintf(stderr, "The files 'deltaE.dat' and 'matrix_el.dat' have been generated in the directory 'results'.\n");

	return 0;
}
