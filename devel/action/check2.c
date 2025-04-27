/*************************************************************************
*
*   File check1.c
*
*   Tests if the action is evaluated correctly for coordinates
*   
*
**************************************************************************/

#define MAIN_PROGRAM
#define CHECK2_C

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"action.h"
#include"global.h"

int main(){
    double action_old, action_new;
    int i, k;
    double dx = 0.5;
    for(i=0; i<N;i++){
        xx[i]= i;
    }
    
    action_old = evaluate_action();

    for (k = 0; k<N; k++){
        xx[k] = xx[k]+ dx;
        
        action_new = evaluate_action();
        xx[k] = xx[k]-dx;
        printf("The unefficient variation is: %f.\n", action_new-action_old);
        printf("The efficient variation is: %f.\n \n", evaluate_action_variation(k, dx));
        
    }
    return 0;
}