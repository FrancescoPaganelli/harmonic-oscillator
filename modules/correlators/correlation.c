/*************************************************************************************************************
*	File correlation.c
*
*	Evaluation of correlators and autocorrelators.
*	
*	The externally accessible function are:
*
*	void find_correlators(double ** ptr_correlator, int N_sweep)
*		given a double pointer and the number of sweeps, it fills the pointer 
*       with the correlator for each sweep and, in the last position, the mean 
*       value of the correlators.
*
*	double find_autocorrelation(int t, double** ptr_correlator, int N_sweep)
*		evaluate the autocorrelation of the given correlators at time t for j=3.
*
*   
*   double find_binned_distribuition(double** ptr_correlator, double** binned_correlators, int N_sweep)
*       given the correlators and the number of sweep, it fills a pointer with the binned
*       correlators acoording to the global parameter tau_0. It also returns the variance for each
*       binned correlator.
*
*   void find_binned_correlator(double** binned_correlators, int N_sweep)
*       it computes the correlators binning them at each step. This function is used instead of the previous
*       one when N_sweep is too large to save every unbinned correlator.
*
*
*****************************************************************************************************************/

#define CORRELATION_C

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"global.h"
#include"metropolis.h"

static double find_estimator(int j){
    int i;
    double estimator=0.0;

    for (i=0; i<N; i++){
        estimator += xx[i]*xx[(i+j)%N];
    }
    estimator /= (double) N;

    return estimator;
}






void find_correlators(double ** ptr_correlator, int N_sweep){
    int i, j;
    double temp_estimator;
    for (i=0; i<N_sweep; i++){
        make_sweep();
        for (j=0; j<N; j++){   
            temp_estimator = find_estimator(j);
            ptr_correlator[N_sweep][j] += (temp_estimator/N_sweep);
            ptr_correlator[i][j] = temp_estimator;
        }
    }
}





double find_autocorrelation(int t, double** ptr_correlator, int N_sweep){
    double total_expectation = ptr_correlator[N_sweep][3];
    double sweep_expectation=0;
    double autocorrelation;
    int i;
    
    for (i=0; i<(N_sweep-t); i++){
        sweep_expectation += (ptr_correlator[i][3]*ptr_correlator[i+t][3]);
    }
    sweep_expectation /= (double) (N_sweep-t);

    autocorrelation = sweep_expectation - total_expectation*total_expectation;
    return fabs(autocorrelation);
}



double* find_binned_distribution(double** ptr_correlator, double** binned_correlators, int N_sweep){
    int k, j, i;
    int lenght_bin = 10* Tau0; 
    int n_bin = (int) floor(N_sweep/lenght_bin);
    double* squared_mean = (double*)malloc(N*sizeof(double));
    double* variance = (double*)malloc(N*sizeof(double));

    /*Initialization of the pointer*/
    for (i=0;i<N;i++){
        squared_mean[i]=0;
    }
    
    /*Binning*/
    for (k=0; k<n_bin; k++){
        for (j=0;j<N; j++){
            for (i=lenght_bin*k;i<(k+1)*lenght_bin;i++){
                binned_correlators[k][j] += (ptr_correlator[i][j]/(double) lenght_bin);
            }
        }
    }
    
    /*Finds variance and mean value*/
    for (j=0;j<N;j++){
        for(k=0;k<n_bin;k++){
            binned_correlators[n_bin][j] += binned_correlators[k][j];
            squared_mean[j] += binned_correlators[k][j]*binned_correlators[k][j];
        }
    }
    for (j=0; j<N;j++){
        binned_correlators[n_bin][j] /= (double) n_bin;
        squared_mean[j] /= (double) n_bin;
        variance[j] = (squared_mean[j] - binned_correlators[n_bin][j]*binned_correlators[n_bin][j])/((double) n_bin);
    }

    return variance;
} 



void find_binned_correlator(double** binned_correlators, int N_sweep){
    int k, j, i;
    int lenght_bin = 10* Tau0; 
    int n_bin = (int) floor(N_sweep/lenght_bin);
    
    /*Finding correlators and binning them*/
    for (k=0; k<n_bin; k++){
        for (i=lenght_bin*k;i<(k+1)*lenght_bin;i++){
             make_sweep();
            for (j=0;j<N; j++){
                binned_correlators[k][j] += (find_estimator(j)/(double) lenght_bin);
            }
        }
    }
    
    /*Finding mean value*/
    for (j=0;j<N;j++){
        for(k=0;k<n_bin;k++){
            binned_correlators[n_bin][j] += binned_correlators[k][j];
        }
        binned_correlators[n_bin][j] /= (double) n_bin;
    }
} 

