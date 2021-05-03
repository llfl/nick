#ifndef CONV2D_H_
#define CONV2D_H_

#include "global_para.h"
#include "gemm.h"
#include<stdlib.h>
#include<string.h>

template <typename T>
void im2col(
    const T *input,
        int *ishape,
        int *ksize,
        int *padding,
        int *stride,
        int *osize,
        T   *out
){
    //padding[P_TOP] < ksize[H_INDEX]/2 
    //padding[P_BOTTOM] < ksize[H_INDEX]/2
    //padding[P_LEFT] < ksize[W_INDEX]/2
    //padding[P_RIGHT] < ksize[W_INDEX]/2
    //make sure kernel center inside image

    //kernel center index
    int kmiddle_i = ksize[H_INDEX] / 2;
    int kmiddle_j = ksize[W_INDEX] / 2;
    int offset_i = kmiddle_i - padding[P_TOP];
    int offset_j = kmiddle_j - padding[P_RIGHT];
    int oline = 0;

    T* tmp = (T*)malloc(sizeof(T)*osize[W_INDEX]);

    for(int c = 1; c < ishape[C_INDEX]+1; c++){
        for(int i = offset_i; i < ishape[H_INDEX] - kmiddle_i + padding[P_BOTTOM]; i+=stride[S_VERTICAL]){
            for(int j = offset_j; j < ishape[W_INDEX] - kmiddle_j + padding[P_RIGHT]; j+=stride[S_HORIZONTAL]){
                memset(tmp,0,sizeof(T)*osize[W_INDEX]);
                for(int ki = 0; ki<ksize[H_INDEX]; ki++){
                    if(i + ki < kmiddle_i){
                        continue;
                    }
                    if(padding[P_BOTTOM] > 0 && i + ki - kmiddle_i + stride[S_VERTICAL] >= ishape[H_INDEX] + padding[P_BOTTOM]){
                        continue;
                    }
                    if(padding[P_LEFT] >0 && j < kmiddle_j){
                        memcpy(tmp+ki*ksize[W_INDEX]+padding[P_LEFT], 
                                input+(c-1)*ishape[H_INDEX]*ishape[W_INDEX]+(i+ki-kmiddle_i)*ishape[W_INDEX] + j - kmiddle_j + padding[P_LEFT],
                                sizeof(T)*(ksize[W_INDEX] - padding[P_LEFT]));
                        continue;
                    }
                    if(j+stride[S_HORIZONTAL] >= ishape[W_INDEX] - kmiddle_j + padding[P_RIGHT]){
                        memcpy(tmp+ki*ksize[W_INDEX],
                          input+(c-1)*ishape[H_INDEX]*ishape[W_INDEX]+(i+ki-kmiddle_i)*ishape[W_INDEX] + j - kmiddle_j,
                          sizeof(T)*(ksize[W_INDEX]-padding[P_RIGHT]));
                        continue;
                    }
                    memcpy(tmp+ki*ksize[W_INDEX],
                          input + (c-1)*ishape[H_INDEX]*ishape[W_INDEX] +
                          (i+ki-kmiddle_i)*ishape[W_INDEX] + j - kmiddle_j,
                          sizeof(T)*ksize[W_INDEX]);
                }
                memcpy(out+oline*osize[W_INDEX], tmp, sizeof(T)*osize[W_INDEX]);
                oline ++;
            }
        }
    }
    free(tmp);
}


template <typename T>
void k2col(
    const T *kernel,
        int *kshape,
        int *ksize,
          T *out
){
    T* tmp = (T*)malloc(sizeof(T)*ksize[W_INDEX]);
    for(int i = 0; i < kshape[W_INDEX]*kshape[H_INDEX]; i++){
        memset(tmp,0,sizeof(T)*ksize[W_INDEX]);
        for(int c = 1; c < kshape[C_INDEX]+1; c++){
            tmp[c-1] = kernel[i + (c-1)*kshape[W_INDEX]*kshape[H_INDEX]];
        }
        memcpy(out+i*ksize[W_INDEX], tmp, sizeof(T)*ksize[W_INDEX]);
    }
    free(tmp);
}


template <typename T>
void conv2d(
    const T *input,
    const T *kernel,
        int *ishape,
        int *kshape,
        int *padding,
        int *stride,
        int *oshape,
          T *out
){
    //kernel and output channel must padding to multiple of 4

    int isize[2];
    int ksize[2];

    ksize[W_INDEX] = kshape[C_INDEX] + (4 - (kshape[C_INDEX] & 3)) % 4;
    ksize[H_INDEX] = kshape[H_INDEX] * kshape[W_INDEX] + 
        (4 - ((kshape[H_INDEX] * kshape[W_INDEX]) & 3)) % 4;

    isize[W_INDEX] = ksize[H_INDEX];
    isize[H_INDEX] = oshape[H_INDEX]*oshape[W_INDEX] +\
        (4 - (oshape[H_INDEX]*oshape[W_INDEX] & 3)) % 4;

    T* col = (T*) malloc(sizeof(T)*
        isize[W_INDEX]*isize[H_INDEX]*oshape[C_INDEX]);

    T* kcol = (T*) malloc(sizeof(T)*ksize[W_INDEX]*ksize[H_INDEX]);

    T* outcol = (T*) malloc(sizeof(T)*isize[H_INDEX]*ksize[W_INDEX]);

    memset(col, 0, isize[W_INDEX]*isize[H_INDEX]*oshape[C_INDEX]);
    im2col(input, ishape, kshape, padding, stride, isize, col);
    memset(outcol, 0, isize[W_INDEX]*isize[H_INDEX]*oshape[C_INDEX]);
    for(int c = 1; c < ishape[C_INDEX]+1; c++){
        memset(kcol, 0, sizeof(T)*isize[H_INDEX]*ksize[W_INDEX]);
        k2col(kernel + 
            (c-1) * kshape[H_INDEX] * kshape[W_INDEX] * kshape[C_INDEX],
            kshape, ksize, kcol);
        vgemm(col+(c-1)*isize[W_INDEX]*isize[H_INDEX], kcol, isize, ksize, outcol);
    }

    // col2im
    for(int c = 1; c < oshape[C_INDEX]+1; c++){
        for(int i = 0; i < oshape[H_INDEX]*oshape[W_INDEX]; i++){
            out[(c-1)*oshape[H_INDEX]*oshape[W_INDEX] + i] =
                outcol[i*ksize[W_INDEX]+(c-1)];
        }
    }
    free(outcol);
    free(kcol);
    free(col);
}

#endif

