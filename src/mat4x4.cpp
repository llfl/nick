#include "mat4x4.h"

int16_t* matrix_mul_c(const int16_t *aa, 
                    const int16_t *bb, 
                    const uint16_t dim)
{
    int i = 0, j = 0;
    int16_t* cc = (int16_t*) malloc(sizeof(int16_t)*dim*dim);
    for(i = 0; i < dim; i++) {
        for(j = 0; j < dim; j++) {
            cc[i*dim + j] = aa[i*dim + j] * bb[i*dim + j];
        }
    }

}