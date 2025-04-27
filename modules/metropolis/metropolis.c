/**********************************************************************
*	File metropolis.c
*   
*   Implementation of Metropolis algorithm, it generates 
*   Feynman paths according to the given action
*	
*	The externally accessible functions are
*
*	double make_sweep()
*		variation of the coordinates for the entire array (sweep).
*
*   void thermalize()
*       does the thermalization
******************************************************************************/

#define METROPOLIS_C

#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"global.h"
#include"random.h"
#include"action.h"

void make_sweep(){
    int i;
    double r[2*N];
    double dx, ds;
    ranlxd(r, 2*N);
    for (i=0; i<N; i++){
        dx = 2.0*Delta*(r[i]-0.5);
        ds=evaluate_action_variation(i, dx);
        if (r[N+i]<exp(-ds)){
            xx[i] += dx;
        }
    }
}

void thermalize(){
    int i;
    double r[N];
    
    ranlxd(r, N);
    for (i=0;i<N;i++){
        xx[i]=r[i];
    }
    for (i=0;i<Nthermal;i++){
        make_sweep();
    }
}
