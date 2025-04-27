/**********************************************************************
*	File action.c
*
*	Evaluation of an action with periodic boundary conditions
*	on the coordinates.
*	
*	The externally accessible functions are
*
*	double evaluate_action()
*		evaluate the action with periodic boundary condition.
*
*	double evaluate_action_variation(int l, int dx)
*		evaluate the difference between an old action and an action with the l-th
*		coordinate shifted by dx
******************************************************************************/

#define ACTION_C

#include<stdlib.h>
#include"global.h"

static double step(double x1, double x2){
	double S;
	S = 0.5*M*((x1-x2)*(x1-x2)+ W*W*x1*x1); 
	return S;
}


double evaluate_action(){
	int i;
	double S;
	S = 0.0;
	for(i=0; i<N; i++){
		S += step(xx[i%N], xx[(i+1)%N]);
	} 
	return S;
}


double evaluate_action_variation(int l, double dx){
	double dS_l, dS_ll;
	l = l%N;
	dS_l = 0.5*M*(dx*dx-2.0*xx[(l+1)%N]*dx+2.0*xx[l]*dx) + 0.5*M*W*W*(dx*dx+2.0*xx[l]*dx);
	dS_ll = 0.5*M*(dx*dx+2.0*xx[l]*dx-2.0*xx[(l-1+N)%N]*dx);
	return dS_l+dS_ll;
}