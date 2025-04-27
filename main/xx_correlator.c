/*************************************************************************
*
*   File xx_correlator.c
*
*   Evaluation of the correlator of the operator xx and its autocorrelation
*   the results are printed on "correlator_data_N.dat" and
*   "autocorrelator_data_N.dat" respectevly.
*   The correlators are then binned and the autocorrelation is evaluated again
*   the results are printed on "binned_data_N.dat" and
*   "binned_autocorrelator_data_N.dat"
*   
*
**************************************************************************/

#define MAIN_PROGRAM

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"action.h"
#include"global.h"
#include"random.h"
#include"metropolis.h"
#include"correlation.h"


int main(){
    int i, j, t;
    int N_sweep = 500000;
    int n_bin = (int)floor(N_sweep/10/Tau0);
    double **ptr_correlator=(double**)malloc((N_sweep+1)*sizeof(double*));
    double** binned_correlators = (double**)malloc((n_bin+1)*sizeof(double*));
    double* variance_of_binned = (double*)malloc(N*sizeof(double));
    FILE *fptr;
    rlxd_init(1,270201);
    
    thermalize();  
    
    /*Initialization of variables*/
    for (i=0; i<(N_sweep+1); i++){
        ptr_correlator[i] = (double*)malloc(N*sizeof(double));
    }
    for (i=0; i<(n_bin+1); i++){
        binned_correlators[i] = (double*)malloc(N*sizeof(double));
    }
    for (j=0; j<N; j++){
        ptr_correlator[N_sweep][j] = 0.0;
    }
    for (j=0;j<n_bin+1;j++){
        for(i=0;i<N;i++){
        binned_correlators[j][i]=0;
        }
    }
 
 
 
    /*Evaluation of correlators and printing*/


    find_correlators(ptr_correlator, N_sweep);


    fptr = fopen("correlator_data_64.dat", "w");
    if (fptr == NULL)
        {
            printf("Cannot open the file.");
            exit(0);
        }
    for (j=0; j<N; j++){
        fprintf(fptr, "%14.10f\n", ptr_correlator[N_sweep][j]);
    } 
    fclose(fptr);



    /*Evaluation of autocorrelations and printing*/
   
    fptr = fopen("autocorrelator_data_64.dat", "w");
    if (fptr == NULL)
        {
            printf("Cannot open the file.");
            exit(0);
        }
    for (t=0; t<60; t++){
        fprintf(fptr, "%d\t %14.10f\n", t, find_autocorrelation(t, ptr_correlator, N_sweep)/find_autocorrelation(0, ptr_correlator, N_sweep));
    } 
    fclose(fptr);



    /*Binning the correlators and printing*/

    fptr = fopen("binned_data_64.dat", "w");
    if (fptr == NULL)
        {
            printf("Cannot open the file.");
            exit(0);
        }

    variance_of_binned = find_binned_distribution(ptr_correlator, binned_correlators, N_sweep);
    
    
    for (j=0; j<N; j++){
        fprintf(fptr, "%14.10f\t %14.10f\n", binned_correlators[n_bin][j], sqrt(variance_of_binned[j]));        
    } 
    fclose(fptr);
    

    
    /*Evaluation of the autocorrelation of the binned correlators and printing*/
    fptr = fopen("binned_autocorrelator_data_64.dat", "w");
    if (fptr == NULL)
        {
            printf("Cannot open the file.");
            exit(0);
        }
    for (t=0; t<60; t++){
        fprintf(fptr, "%d\t %14.10f\n", t, find_autocorrelation(t, binned_correlators, n_bin)/find_autocorrelation(0, binned_correlators, n_bin));
    } 
    fclose(fptr);
    return 0;
}