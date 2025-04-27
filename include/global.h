
/*******************************************************************************
*
* File global.h
*
* Global parameters and arrays
*
*******************************************************************************/

#ifndef GLOBAL_H
#define GLOBAL_H

#ifndef  M_PI
#define  M_PI  3.1415926535897932384626433
#endif

#define N 64/* N = 64-> M=1 W=1 N=128 -> M=2 W=0.5 N=256 -> M=4 W=0.25 N=512 -> M=8 W = 0.125*/
#define M 1.0
#define W 1.0

#define Delta 1.0
#define Nthermal 300
#define Tau0 10

#if defined MAIN_PROGRAM
  #define EXTERN
#else
  #define EXTERN extern
#endif

EXTERN double xx[N];

#undef EXTERN

#endif


