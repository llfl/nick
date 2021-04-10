#ifndef MMUTILS_H_
#define MMUTILS_H_

#include<stdlib.h>
#include<time.h>

#define H_INDEX 0
#define W_INDEX 1

template <typename T>
T* matrix(int* shape){
    int total = shape[H_INDEX]*shape[W_INDEX];
    T* out = (T*)malloc(sizeof(T)*total);
    srand((unsigned)time(NULL) + (unsigned)rand());
    for(int i = 0; i< total; i++){
        out[i] = (T)(rand()%200-100);
    }
    return out;
}

template <typename T>
T* mm(
    const T *A,
    const T *B,
    int *Ashape,
    int *Bshape
){
    T* out = (T*)malloc(sizeof(T)*Ashape[H_INDEX]*Bshape[W_INDEX]);
    memset(out,0,sizeof(T)*Ashape[H_INDEX]*Bshape[W_INDEX]);
    if(Bshape[H_INDEX] = Ashape[W_INDEX]){
        int M = Ashape[H_INDEX];
        int N = Bshape[W_INDEX];
        int K = Bshape[H_INDEX];
        for(int i = 0; i < M; i++){
            for(int j = 0; j < N; j++){
                for(int k = 0; k<K; k++){
                    out[i*N+j] += A[i*K+k] * B[k*N+j];
                }
            }
        }
    }
    return out;
}

#endif