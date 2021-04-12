#ifndef CONV2D_H_
#define CONV2D_H_

#include "global_para.h"
#include<stdlib.h>
#include<string.h>

template <typename T>
void im2col(
    const T *input,
        int *ishape,
        int *kshape,
        int *padding,
        int *stride,
        int *osize,
        T   *out
){
    //padding[P_TOP] < kshape[H_INDEX]/2 
    //padding[P_BOTTOM] < kshape[H_INDEX]/2
    //padding[P_LEFT] < kshape[W_INDEX]/2
    //padding[P_RIGHT] < kshape[W_INDEX]/2
    //make sure kernel center inside image

    //kernel center index
    int kmiddle_i = kshape[H_INDEX] / 2;
    int kmiddle_j = kshape[W_INDEX] / 2;
    int offset_i = kmiddle_i - padding[P_TOP];
    int offset_j = kmiddle_j - padding[P_RIGHT];
    int oline = 0;

    T* tmp = (T*)malloc(sizeof(T)*osize[W_INDEX]);


    for(int c = 0; c < ishape[C_INDEX]; c++){
        for(int i = offset_i; i<ishape[H_INDEX] - kmiddle_i + padding[P_BOTTOM]; i += stride[S_VERTICAL]){
            for(int j = offset_j; j<ishape[W_INDEX] - kmiddle_j + padding[P_RIGHT]; j+=stride[S_HORIZONTAL]){
                memset(tmp,0,sizeof(T)*osize[W_INDEX]);
                for(int ki = 0; ki<kshape[H_INDEX]; ki++){
                    // if(i + ki < kmiddle_i){
                    //     continue;
                    // }
                    // if(padding[P_LEFT] >0 && j < kmiddle_j){
                    //     memcpy(tmp+ki*kshape[W_INDEX]+padding[P_LEFT], 
                    //             input+c*ishape[H_INDEX]*ishape[W_INDEX]+(i+ki-kmiddle_i)*ishape[W_INDEX] + j - kmiddle_j + padding[P_LEFT],
                    //             sizeof(T)*(kshape[W_INDEX] - padding[P_LEFT]));
                    //     continue;
                    // }
                    // if(j+stride[S_HORIZONTAL] >= ishape[W_INDEX] - kmiddle_j + padding[P_RIGHT]){
                    //     memcpy(tmp+ki*kshape[W_INDEX],
                    //       input+c*ishape[H_INDEX]*ishape[W_INDEX]+(i+ki-kmiddle_i)*ishape[W_INDEX] + j - kmiddle_j,
                    //       sizeof(T)*(kshape[W_INDEX]-padding[P_RIGHT]));
                    //     continue;
                    // }
                    // if(padding[P_BOTTOM] >0 && i+ ki + stride[S_VERTICAL] >= ishape[H_INDEX] + padding[P_BOTTOM]){
                    //     continue;
                    // }
                    memcpy(tmp+ki*kshape[W_INDEX],
                          input+c*ishape[H_INDEX]*ishape[W_INDEX]+(i+ki-kmiddle_i)*ishape[W_INDEX] + j - kmiddle_j,
                          sizeof(T)*kshape[W_INDEX]);
                }
                memcpy(out+oline*osize[W_INDEX], tmp, sizeof(T)*osize[W_INDEX]);
                oline ++;
            }
        }
    }

    free(tmp);
}

#endif

