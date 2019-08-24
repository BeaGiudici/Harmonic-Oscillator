/*******************************************************************************
*
* File action.c
*
* Collection of useful functions for the calculation of the action
* of a harmonic oscillator
*
* The externally accessible functions are
*
*	double lagrangian(double x, double y)
*		Returns the disctretized (Eucledian) Lagrangian, computed 
*		between the points x and y
*
*	double action(void)
*		Returns the action of the system as the sum of the discretized 
*		Lagrangian (it is implemented with the global variable xx[N])
*
*	double delta_S(int i, double alpha)
*		Returns the difference between the action in (xx[0],...,xx[i],...x[N-1])
*		and the one in (xx[0],...,y,...,xx[N-1]), where y = xx[i] + alpha.
*
* AUTHOR: Beatrice Giudici <b.giudici1@campus.unimib.it>
* CREATED: 14/03/2019
* MODIFIED: 16/04/2019
*		
*******************************************************************************/

#define ACTION_C

#include <limits.h>
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "global.h"

double lagrangian(double x, double y)
{
	double K = 0.5 * M * (x - y) * (x - y);
	double V = 0.25 * M * (W * W) * (x * x + y * y);
	return K + V;
}

double action(void)
{
	double S = 0;
	int i;
	for (i = 0; i < N; i++)
	{
		S += lagrangian(xx[(i + 1) % N], xx[i]);
	}
	return S;
}

double delta_S(int i, double alpha)
{
	return M * alpha * (alpha - xx[(i + 1) % N] + 2 * xx[i] - xx[(i - 1 + N) % N]) + 0.5 * M * W * W * alpha * (alpha + 2 * xx[i]);
}
