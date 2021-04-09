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
            for (int k = 0; k < 4; k++){
                C[j+i*4] += A[k+i*4] * B[j+k*4];
            }
            
        }
    }
}
#endif