/*******************************************************************************
*
* File corr.c
*
* Collection of useful functions for the calculation of the correlators
* of an harmonic oscillator
*
* The externally accessible functions are
*
*	double correlator(int t)
*		Given a time interval t, this function calculate the correlator
*		<x_l x_k>, where |l-k| = t
*
*	double deltaE(double c1, double c2, double c3)
*		This function compute the value of the energy step as function
*		of the correlators at different times
*
*	double matrix_el(double c, double E, int t)
*		This function returns the value of the matrix element, computed
*		from the correlator c at a time t and deltaE
*
*
* AUTHOR: Beatrice Giudici
* CREATED: 21/03/2019
*		
*******************************************************************************/

#define CORR_C

#include <limits.h>
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "global.h"
#include "extras.h"

double correlator(int t)
{
	int j;
	double sum = 0;
	for (j = 0; j < N; j++)
	{
		sum += (xx[j] * xx[(j + t) % N]);
	}
	return sum / N;
}

double deltaE(double c1, double c2, double c3)
{
	double arg; /*argument of the arccosh*/
	arg = (c1 + c2) / (2. * c3);
	return acosh(arg);
}

double matrix_el(double c, double E, int t)
{
	double num, den;
	num = c * exp(E * N / 2.);
	den = 2. * cosh(((N / 2.) - t) * E);
	return sqrt(num / den);
}
