/*******************************************************************************
*
* File correlation.h
*
* Include correlation.c functions
*
*******************************************************************************/

#ifndef CORRELATION_H
#define CORRELATION_H

#ifndef CORRELATION_C
extern void find_correlators(double ** ptr_correlator, int N_sweep);
extern double find_autocorrelation(int t, double** ptr_correlator, int N_sweep);
extern double* find_binned_distribution(double** ptr_correlator, double** binned_correlators, int N_sweep);
extern void find_binned_correlator(double** binned_correlators, int N_sweep);
#endif
#endif