#include "mat4x4.h"

int16_t* matrix_mul_c(const int16_t *aa, 
                    const int16_t *bb, 
                    const int16_t dim)
{
    int i = 0, j = 0;
    int16_t* cc = (int16_t*) malloc(sizeof(int16_t)*dim*dim);
    for(i = 0; i < dim; i++) {
        for(j = 0; j < dim; j++) {
            cc[i*dim + j] = aa[i*dim + j] * bb[i*dim + j];
        }
    }
    return cc;
}

#ifdef __aarch64__
int16_t* matrix_mul_neon(const int16_t *aa, 
                    const int16_t *bb, 
                    const int16_t dim)
{
    int i = 0, j = 0;
    int16x4_t _aa;
    int16x4_t _bb;
    int16x4_t _cc;
    int16_t* cc = (int16_t*) malloc(sizeof(int16_t)*dim*dim);
    int16_t* c = (int16_t*) malloc(sizeof(int16_t)*dim);
    for (int i = 0; i < dim; i++)
    {
        _aa = vld1_s16((int16_t*)aa[i*dim]);
        _bb = vld1_s16((int16_t*)bb[i*dim]);
        _cc = vmul_s16(_aa, _bb);
        vst1_s16(c, _cc);
        memcpy(c, cc+i*dim, sizeof(int16_t)*dim);
    }
    return cc;
}
#endif