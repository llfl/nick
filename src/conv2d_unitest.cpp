#include <limits.h>
#include "conv2d.h"
#include "mmutils.h"
#include "gtest/gtest.h"

namespace{
    TEST(conv2d_im2col, nopadding){
        int16_t aa[4][4] = {
            {1, 2, -3, 4},
            {5, 6, 7, 8},
            {3, 6, 8, 1},
            {2, -6, 7, 1}
        };
        int16_t c[4][12] = {
            {1,2,-3,5,6,7,3,6,8,0,0,0},
            {2,-3,4,6,7,8,6,8,1,0,0,0},
            {5,6,7,3,6,8,2,-6,7,0,0,0},
            {6,7,8,6,8,1,-6,7,1,0,0,0}
        };
        int16_t *cc = (int16_t *)c;
        int ishape[3] = {4,4,1};
        int kshape[3] = {3,3,1};
        int padding[4] = {0,0,0,0};
        int stride[2] = {1,1};
        int osize[2] = {4,12};
        int16_t *r = (int16_t*)malloc(sizeof(int16_t)*osize[H_INDEX]*osize[W_INDEX]);
        im2col<int16_t>((int16_t *)aa,ishape,kshape,padding,stride,osize,r);
        for(int i = 0; i < osize[0]; i++) {
            for(int j = 0; j < osize[1]; j++) {
                EXPECT_EQ(r[i*osize[1]+j], cc[i*osize[1]+j]);
            }
        }
        free(r);
    }

    TEST(conv2d_im2col, nopadding_1_1_1_1){
        int16_t aa[4][4] = {
            {1, 2, -3, 4},
            {5, 6, 7, 8},
            {3, 6, 8, 1},
            {2, -6, 7, 1}
        };
        int16_t c[16][12] = {
            {0,0,0,0,1,2,0,5,6,0,0,0},
            {0,0,0,1,2,-3,5,6,7,0,0,0},
            {0,0,0,2,-3,4,6,7,8,0,0,0},
            {0,0,0,-3,4,0,7,8,0,0,0,0},
            {0,1,2,0,5,6,0,3,6,0,0,0},
            {1,2,-3,5,6,7,3,6,8,0,0,0},
            {2,-3,4,6,7,8,6,8,1,0,0,0},
            {-3,4,0,7,8,0,8,1,0,0,0,0},
            {0,5,6,0,3,6,0,2,-6,0,0,0},
            {5,6,7,3,6,8,2,-6,7,0,0,0},
            {6,7,8,6,8,1,-6,7,1,0,0,0},
            {7,8,0,8,1,0,7,1,0,0,0,0},
            {0,3,6,0,2,-6,0,0,0,0,0,0},
            {3,6,8,2,-6,7,0,0,0,0,0,0},
            {6,8,1,-6,7,1,0,0,0,0,0,0},
            {8,1,0,7,1,0,0,0,0,0,0,0}
        };
        int16_t *cc = (int16_t *)c;
        int ishape[3] = {4,4,1};
        int kshape[3] = {3,3,1};
        int padding[4] = {1,1,1,1};
        int stride[2] = {1,1};
        int osize[2] = {4,12};
        int16_t *r = (int16_t*)malloc(sizeof(int16_t)*osize[H_INDEX]*osize[W_INDEX]);
        im2col<int16_t>((int16_t *)aa,ishape,kshape,padding,stride,osize,r);
        for(int i = 0; i < osize[0]; i++) {
            for(int j = 0; j < osize[1]; j++) {
                EXPECT_EQ(r[i*osize[1]+j], cc[i*osize[1]+j]);
            }
        }
        free(r);
    }
}