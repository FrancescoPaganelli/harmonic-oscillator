/*************************************************************************
*
*   File check1.c
*
*   Tests if the action is evaluated correctly for coordinates
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

int main(){
    double action;
    int i;

    for(i=0; i<N;i++){
        xx[i]= sin(i*2*M_PI/N);
    }
    
    action = evaluate_action();

    printf("The action is %f.\n", action);
    return 0;
}