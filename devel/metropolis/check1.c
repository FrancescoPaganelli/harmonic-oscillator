/*************************************************************************
*
*   File check1.c
*
*   Tests if the sweep is done correctly
*   
*
**************************************************************************/

#define MAIN_PROGRAM
#define CHECK1_C

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
    double S;
    
    rlxd_init(1,270201);
    ranlxd(r, N);

    for (i=0;i<N;i++)
        xx[i]=r[i];
    make_sweep();
    S = evaluate_action();
    printf("The action is: %f\n", S);
    
    return 0;
}