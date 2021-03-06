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
    int16x4_t _aa;
    int16x4_t _bb;
    int16_t* cc = (int16_t*) malloc(sizeof(int16_t)*dim*dim);
    int16_t* a = (int16_t*) malloc(sizeof(int16_t)*dim);
    int16_t* b = (int16_t*) malloc(sizeof(int16_t)*dim);
    int16_t* c = (int16_t*) malloc(sizeof(int16_t)*dim);

    for (int16_t i = 0; i < dim; i++)
    {   
        a = (int16_t*)(aa+i*dim);
        b = (int16_t*)(bb+i*dim);
        _aa = vld1_s16(a);
        _bb = vld1_s16(b);
        vst1_s16(c, vmul_s16(_aa, _bb));
        memcpy(cc+i*dim, c, sizeof(int16_t)*dim);
    }
    return cc;
}
#endif
