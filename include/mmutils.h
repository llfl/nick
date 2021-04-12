#ifndef MMUTILS_H_
#define MMUTILS_H_

#include<stdlib.h>
#include<time.h>

#define H_INDEX 0
#define W_INDEX 1

template <typename T>
T* matrix(int* size){
    int total = size[H_INDEX]*size[W_INDEX];
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
    int *Asize,
    int *Bsize
){
    T* out = (T*)malloc(sizeof(T)*Asize[H_INDEX]*Bsize[W_INDEX]);
    memset(out,0,sizeof(T)*Asize[H_INDEX]*Bsize[W_INDEX]);
    if(Bsize[H_INDEX] = Asize[W_INDEX]){
        int M = Asize[H_INDEX];
        int N = Bsize[W_INDEX];
        int K = Bsize[H_INDEX];
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