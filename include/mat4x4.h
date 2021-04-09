#ifndef MAT4X4_H_
#define MAT4X4_H_

#include <stdlib.h>
#include <string.h>

#ifdef __aarch64__
#include <arm_neon.h>
int16_t* matrix_mul_neon(const int16_t *aa, 
                    const int16_t *bb, 
                    const int16_t dim);
#endif

int16_t* matrix_mul_c(const int16_t *aa, 
                    const int16_t *bb, 
                    const int16_t dim);

#endif

