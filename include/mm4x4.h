#ifndef MM4X4_H_
#define MM4X4_H_

#include <stdlib.h>

template <typename T>
void mm4x4(
    const T *A,
    const T *B,
          T *C
){
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            C[j+i*4] += A[j+i*4] * B[i+j*4];
        }
    }
}
#endif