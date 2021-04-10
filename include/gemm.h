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

    for(int i = 0; i < Ashape[H_INDEX]; i += 4){
        for(int j = 0; j < Bshape[W_INDEX]; j += 4){
            for(int k=0; k < Bshape[H_INDEX]; k += 4){
                mm4x4s<T>(
                    (T*)(A+ i   *Bshape[H_INDEX]+k),
                    (T*)(A+(i+1)*Bshape[H_INDEX]+k),
                    (T*)(A+(i+2)*Bshape[H_INDEX]+k),
                    (T*)(A+(i+3)*Bshape[H_INDEX]+k),
                    (T*)(B+ k   *Bshape[W_INDEX]+j),
                    (T*)(B+(k+1)*Bshape[W_INDEX]+j),
                    (T*)(B+(k+2)*Bshape[W_INDEX]+j),
                    (T*)(B+(k+3)*Bshape[W_INDEX]+j),
                    (T*)(out+ i   *Bshape[W_INDEX]+j),
                    (T*)(out+(i+1)*Bshape[W_INDEX]+j),
                    (T*)(out+(i+2)*Bshape[W_INDEX]+j),
                    (T*)(out+(i+3)*Bshape[W_INDEX]+j));
            }
        }
    }
    return out;
}

#endif