#ifndef GEMM_H_
#define GEMM_H_

#include "mm4x4.h"
#include<stdlib.h>

#define H_INDEX 0
#define W_INDEX 1

template <typename T>
T* gemm(
    const T *A,
    const T *B,
    int *Ashape,
    int *Bshape
){
    T* out = (T*)malloc(sizeof(T)*Ashape[H_INDEX]*Bshape[W_INDEX]);
    memset(out,0,sizeof(T)*Ashape[H_INDEX]*Bshape[W_INDEX]);

    int M = Ashape[H_INDEX] / 4;
    int N = Bshape[W_INDEX] / 4;
    int K = Bshape[H_INDEX] / 4;
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            for(int k=0; k < K; k++){
                mm4x4<T>(
                    (T*)(A+(i*K+k)*16),
                    (T*)(B+(k*N+j)*16),
                    (T*)(out+(i*N+j)*16));
            }
        }
    }
    return out;
}

#endif