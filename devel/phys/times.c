/****************************************************************************************
*
* File times.c
* 
* Performing metropolis and keeping track of the times (in seconds) of some operations
*
* AUTHOR: Beatrice Giudici <b.giudici1@campus.unimib.it>
* CREATED: 16/08/2019
*
****************************************************************************************/

#define MAIN_PROGRAM

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "global.h"
#include "phys.h"
#include "random.h"
#include "extras.h"

int main(void)
{
     double **c;      /*Double pointer for the matrix of the correlators*/
     float rf[2 * N]; /*vector to collect all the random numbers that need to be 
				generated during the construction of the Markov chain (the 
				used function generates float numbers)*/
     double alpha, dS, r1, r2;
     double delta = 2.;
     double t0 = 0.0, t1 = 0.0, t2 = 0.0; /*Tracking the time */
     int j, i, k, t;                      /*Counters*/

     /*Initializing the random numbers generator */
     rlxs_init(0, 3452);

     thermalization();

     c = create_matrix(Nconf, N);

     /*Correlator and rebinning*/
     for (i = 0; i < Nconf; ++i)
     {

          /*Setting all the entries of the line to zero, in order to sum 
          over all the correlators in the rebinning process*/
          for (t = 0; t < N; ++t)
          {
               c[i][t] = 0.0;
          }

          /*With i fixed, I compute the Markov chain for dBin times, summing the correlator 
		(averaged over dBin) at any given time interval t.*/
          for (k = 0; k < dBin; ++k)
          {
               ranlxs(rf, 2 * N);
               t0 += (double)clock();
               /*Metropolis step*/
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
               t1 += (double)clock();

               /*Computing the correlators*/
               for (t = 0; t < N; ++t)
               {
                    c[i][t] += correlator(t) / dBin;
               }
               t2 += (double)clock();
          }
     }

     /*Printing the results, in a shape useful for writing .json files during the
     execution of the bash*/
     fprintf(stdout, "\t\"N\" : %d,\n", N);
     fprintf(stdout, "\t\"Metropolis\" : %f,\n", (t1 - t0) / (double)(CLOCKS_PER_SEC));
     fprintf(stdout, "\t\"Correlators\" : %f\n", (t2 - t1) / (double)(CLOCKS_PER_SEC));

     return 0;
}