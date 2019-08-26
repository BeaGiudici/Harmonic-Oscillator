/*******************************************************************************
*
* File utility.c
*
* Very common routines used in the different codes
*
* The externally accessible functions are
*
*    void single_metropolis(void)
*         Single step of the Metropolis algorithm
*
*	void thermalization()
*         Thermalization of the Markov chain
* 
*    void create_matrix(int D1, int D2)
*         Dynamical allocation of a matrix of dimensions D1xD2
*
* AUTHOR: Beatrice Giudici
* CREATED: 09/07/2019
*		
*******************************************************************************/

#define UTILITY_C

#include <limits.h>
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "global.h"
#include "phys.h"
#include "random.h"

void single_metropolis(void)
{
     float rf[2 * N]; /*vector to collect all the random numbers that need to be 
				generated during the construction of the Markov chain (the 
				used function generates float numbers)*/
     double alpha, dS, r1, r2;
     double delta = 2.;
     int j;

     /*Filling the vector with numbers generated random*/
     ranlxs(rf, 2 * N);

     for (j = 0; j < N; ++j)
     {
          r1 = (double)rf[j];
          r2 = (double)rf[j + N];
          alpha = 2. * delta * (r1 - 0.5);
          dS = delta_S(j, alpha);
          if (exp(-1 * dS) > r2)
          {
               xx[j] += alpha;
          }
     }
}

void thermalization(void)
{
     int i;
     for (i = 0; i < N; ++i)
     { /*cold start*/
          xx[i] = 0.0;
     }
     for (i = 1; i < N_therm; ++i)
     {
          single_metropolis();
     }
}

double **create_matrix(int D1, int D2)
{
     int i;
     double **c, *pc;
     pc = malloc((D1 * D2) * sizeof(double));
     c = malloc(D1 * sizeof(double *));
     for (i = 0; i < D1; i++)
     {
          c[i] = pc + D2 * i;
     }
     return c;
}