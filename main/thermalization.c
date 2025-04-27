/*************************************************************************
*
*   File thermalization.c
*   
*   Makes the thermalization and prints on "thermalization_steps_N.dat"
*   the value of the action at every sweep
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

int main(){
    int i;
    double r[N];
    FILE *fptr;
    
    rlxd_init(1,270201);
    
    /*Initialization of the coordinates*/
    ranlxd(r, N);
    for (i=0;i<N;i++){
        xx[i]=r[i];
    }
    
    /*Creating data file*/
        
    fptr = fopen("thermalization_steps_64.dat", "w");
    if (fptr == NULL){
        printf("Cannot open the file.");
        exit(0);
    }

    /*Thermalization and printing*/

    for (i=0;i<100;i++){
        make_sweep();
        fprintf(fptr, "%f\n", evaluate_action());
    }

    fclose(fptr);
    return 0;
}