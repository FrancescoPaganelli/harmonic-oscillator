/*************************************************************************************************************
*	File jackknife.c
*
*	Computing clusters, energies, matrix element and finding variance through Jackknife.
*	
*	The externally accessible function are:
*
*	double find_energy(int t, double* C)
*		given the correlators it computes the energy difference at time t 
*       
*
*	double find_matrix_element(int t, double* C, double* DE)
*		given the correlators and the energy difference it computes the matrix element at time t 
*
*   
*   double** find_JK_clusters(double** C, int n_k, int time_lenght)
*       it returns the classical clusterizzation of a double pointer of dimentions n_k and time_lenght
*
*   double find_JK_variance(double** cluster, int t, int n_k)
*       given a cluster it returns the variance of the element in position t according to Jackknife
*
*
*****************************************************************************************************************/

#define JACKKNIFE_C

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"global.h"
#include"metropolis.h"


double find_energy(int t, double* C){
    return acosh((C[t+1]+ C[t-1])/(2*C[t]));
}

double find_matrix_element(int t, double* C, double* DE){
    return C[t]/(2.0*exp(-DE[t]*(double)N*0.5)*cosh(-DE[t]*(0.5*(double)N-(double)t)));
}

double** find_JK_clusters(double** C, int n_k, int time_lenght){
    int k, t;
    double** clusters = (double**)malloc((n_k+1)*sizeof(double*));
    for (k=0;k<n_k+1;k++){
        clusters[k] = (double*)malloc(time_lenght*sizeof(double));
    }
    
    /*Clusterization*/
    for(k=0;k<n_k;k++){
        for (t=0;t<time_lenght;t++){
            clusters[k][t] = C[n_k][t]- (C[k][t]-C[n_k][t])/((double) (n_k-1));
        }
    }
    
    for (t=0;t<time_lenght;t++){
        clusters[n_k][t] = C[n_k][t];
    }

    return clusters;
}

double find_JK_variance(double** cluster, int t, int n_k){
    double variance = 0;
    int i;
    for(i=0;i<n_k; i++){
        variance += (cluster[i][t]-cluster[n_k][t])*(cluster[i][t]-cluster[n_k][t]);
    }
    
    return ((double)(n_k-1))/((double) n_k)* variance;
}