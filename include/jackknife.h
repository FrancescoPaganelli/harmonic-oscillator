/*******************************************************************************
*
* File jackknife.h
*
* Include jackknife.c functions
*
*******************************************************************************/

#ifndef JACKKNIFE_H
#define JACKKNIFE_H

#ifndef JACKKNIFE_C
extern double** find_JK_clusters(double** C, int n_bin, int time_lenght);
extern double find_energy(int t, double* C);
extern double find_matrix_element(int t, double* C, double* DE);
extern double find_JK_variance(double** cluster, int t, int n_k);
#endif
#endif