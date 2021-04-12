#ifndef GEMM_H_
#define GEMM_H_

#include "global_para.h"
#include "mm4x4.h"
#include<stdlib.h>

template <typename T>
T* gemm(
    const T *A,
    const T *B,
    int *Asize,
    int *Bsize
){
    T* out = (T*)malloc(sizeof(T)*Asize[H_INDEX]*Bsize[W_INDEX]);
    memset(out,0,sizeof(T)*Asize[H_INDEX]*Bsize[W_INDEX]);

    for(int i = 0; i < Asize[H_INDEX]; i += 4){
        for(int j = 0; j < Bsize[W_INDEX]; j += 4){
            for(int k=0; k < Bsize[H_INDEX]; k += 4){
                mm4x4s<T>(
                    (T*)(A+ i   *Bsize[H_INDEX]+k),
                    (T*)(A+(i+1)*Bsize[H_INDEX]+k),
                    (T*)(A+(i+2)*Bsize[H_INDEX]+k),
                    (T*)(A+(i+3)*Bsize[H_INDEX]+k),
                    (T*)(B+ k   *Bsize[W_INDEX]+j),
                    (T*)(B+(k+1)*Bsize[W_INDEX]+j),
                    (T*)(B+(k+2)*Bsize[W_INDEX]+j),
                    (T*)(B+(k+3)*Bsize[W_INDEX]+j),
                    (T*)(out+ i   *Bsize[W_INDEX]+j),
                    (T*)(out+(i+1)*Bsize[W_INDEX]+j),
                    (T*)(out+(i+2)*Bsize[W_INDEX]+j),
                    (T*)(out+(i+3)*Bsize[W_INDEX]+j));
            }
        }
    }
    return out;
}

#endif
