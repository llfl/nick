#ifndef GEMM_H_
#define GEMM_H_

#include "mm4x4.h"
#include<stdlib.h>

#define W_INDEX 0
#define H_INDEX 1

template <typename T>
T* gemm(
    const T *A,
    const T *B,
    int *Ashape,
    int *Bshape
){
    T* out = (T*)malloc(sizeof(T)*Ashape[H_INDEX]*Bshape[W_INDEX]);
    memset(out,0,sizeof(T)*Ashape[H_INDEX]*Bshape[W_INDEX]);
    for(int i = 0; i < Ashape[H_INDEX]; i += 4){
        for(int j = 0; j < Bshape[W_INDEX]; j += 4){
            for(int k=0; k < Bshape[H_INDEX]; j += 4){
                mm4x4<T>(A+i*Bshape[H_INDEX]/4+j,B+i*Bshape[H_INDEX]/4+k,out+k*Bshape[H_INDEX]/4+j);
            }
        }
    }
    return out;
}

#endif