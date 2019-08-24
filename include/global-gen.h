
/*******************************************************************************
*
* File global.h
*
* Global parameters and arrays
*
* Let T = Na = 64 = constant, and m = w = 1 = constant be the physical 
* quantities. Then N = T/a, W = aw, and M = m/a are dimensionless parameters.
*
*******************************************************************************/

#ifndef GLOBAL_H
#define GLOBAL_H

#define N @n
#define M @m
#define W @w

/*Nsweep is set at the value 1e7*/
#define N_therm 200 /*about ten times the thermalization time of the Markov chain*/
#define dBin 1000   /*~10*TAU (TAU is the parameter of the autocorrelation function)*/
#define Nconf 10000 /*=Nsweep/dBin*/

#if defined MAIN_PROGRAM
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN double xx[N];

#undef EXTERN

#endif
