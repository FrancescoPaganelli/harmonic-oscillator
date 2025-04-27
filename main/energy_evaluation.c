/*************************************************************************
*
*   File energy_evaluation.c
*
*   Evaluate harmonic oscillator's matrix element and its error
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
#include"jackknife.h"

int main(){
    int i, j, t;
    int N_sweep = 10000000;
    int n_bin = (int)floor(N_sweep/10/Tau0);
    double** binned_correlators = (double**)malloc((n_bin+1)*sizeof(double*));
    double** JK_clusters = (double**)malloc((n_bin+1)*sizeof(double*));
    double** JK_energies = (double**)malloc((n_bin+1)*sizeof(double*));
    double* energy_variance = (double*)malloc(N*sizeof(double));
    double final_result = 0;
    double variance_sum = 0;
    double expected_value;
    FILE* fptr;
    rlxd_init(1,270201);
    
    thermalize();    
    
    /*Array inizialization*/
    for (i=0; i<(n_bin+1); i++){
        binned_correlators[i] = (double*)malloc(N*sizeof(double));
        JK_clusters[i] = (double*)malloc(N*sizeof(double));
        JK_energies[i] = (double*)malloc(N*sizeof(double));
    }
    for (j=0;j<n_bin+1;j++){
        for(i=0;i<N;i++){
        binned_correlators[j][i]=0;
        }
    }

    /*Finding binned correlator*/
    find_binned_correlator(binned_correlators, N_sweep);
    

    /*Clusteriztion of the binned correlators and computing the energy difference*/
    JK_clusters = find_JK_clusters(binned_correlators, n_bin, N);
    for (i=0;i<n_bin+1;i++){
        for (t=0;t<N; t++){
            JK_energies[i][t] = find_energy(t, JK_clusters[i]);
        }
    }

    /*Clusteriztion of the energt difference and computing the matrix element*/
    JK_energies = find_JK_clusters(JK_energies, n_bin, N);
    
    for (i=0;i<n_bin+1;i++){
        for (t=0;t<N; t++){
            JK_energies[i][t] = find_matrix_element(t, JK_clusters[i], JK_energies[i]);
        }
    }
    
    /*Computinge the matrix element's variance using Jackknife algorithm*/
    for (t=0;t<N;t++){
        energy_variance[t] = find_JK_variance(JK_energies, t, n_bin);
    }
    
    fptr = fopen("matrix_elements_64.dat", "w");
    if (fptr == NULL)
        {
            printf("Cannot open the file.");
            exit(0);
        }
    for (j=0; j<N; j++){
        fprintf(fptr, "%14.10f\t %14.10f\n", JK_energies[n_bin][j], energy_variance[j]);
    } 
    fclose(fptr);

    /*Weighted mean of the matrix elements and printing*/
    for (t=2; t<7;t++){
        final_result += JK_energies[n_bin][t]/(energy_variance[t]);
        variance_sum += 1/(energy_variance[t]);
    }
    
    printf("Final matrix element: %f pm %f\n", final_result/variance_sum, 1/sqrt(variance_sum));
    expected_value = 1/(2*M*W*sqrt(1+W*W/4));
    printf("Sigma from expected value: %f\n", (final_result/variance_sum-expected_value)/(1/sqrt(variance_sum)));
    return 0;
}