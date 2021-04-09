#include <limits.h>
#include "mat4x4.h"
#include "gtest/gtest.h"

namespace{
    TEST(matrix_mul_cTest, mat4x4){
        int16_t aa[4][4] = {
            {1, 2, -3, 4},
            {5, 6, 7, 8},
            {3, 6, 8, 1},
            {2, -6, 7, 1}
        };

        int16_t bb[4][4] = {
            {1, 3, 5, -7},
            {2, 4, 6, 8},
            {2, 5, 7, 9},
            {5, 2, 7, 1}
        };
        int16_t c[4][4] = {
            {1, 6,-15,-28},
            {10,24,42,64},
            {6,30,56,9},
            {10,-12,49,1}
        };
        int16_t *cc = (int16_t *)c;
        int16_t *r;
        int16_t dim = 4;
        r = matrix_mul_c((int16_t *)aa,(int16_t *)bb,dim);
        for(int i = 0; i < dim; i++) {
            for(int j = 0; j < dim; j++) {
                EXPECT_EQ(r[i*dim+j], cc[i*dim+j]);
            }
        }
        free(r);
    }
}