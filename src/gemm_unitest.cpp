#include <limits.h>
#include "gemm.h"
#include "mmutils.h"
#include "gtest/gtest.h"

namespace 
{
    TEST(mmutilTest, mm_4x4_4x4){
        int16_t aa[8][4] = {
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
        int16_t c[8][4] = {
            {19, 4,24,-14},
            {71,90,166,84},
            {36,75,114,100},
            {9,19,30,2}
        };

        int16_t *cc = (int16_t *)c;
        int asize[2] = {4,4};
        int bsize[2] = {4,4};

        int16_t *r = mm<int16_t>((int16_t *)aa,(int16_t *)bb, asize,bsize);
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                EXPECT_EQ(r[i*4+j], cc[i*4+j]);
            }
        }
        free(r);
    }

    TEST(mmutilTest, mm_8x4_4x4){
        int16_t aa[8][4] = {
            {1, 2, -3, 4},
            {5, 6, 7, 8},
            {3, 6, 8, 1},
            {2, -6, 7, 1},
            {19, 4,24,-14},
            {7,9,16,8},
            {6,5,4,1},
            {9,1,3,2}
        };
        int16_t bb[4][4] = {
            {1, 3, 5, -7},
            {2, 4, 6, 8},
            {2, 5, 7, 9},
            {5, 2, 7, 1}
        };
        int16_t c[8][4] = {
            {19, 4,24,-14},
            {71,90,166,84},
            {36,75,114,100},
            {9,19,30,2},
            {5,165,189,101},
            {97,153,257,175},
            {29,60,95,35},
            {27,50,86,-26},
        };

        int16_t *cc = (int16_t *)c;
        int asize[2] = {8,4};
        int bsize[2] = {4,4};

        int16_t *r = mm<int16_t>((int16_t *)aa,(int16_t *)bb, asize,bsize);
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 4; j++) {
                EXPECT_EQ(r[i*4+j], cc[i*4+j]);
            }
        }
        free(r);
    }

    TEST(gemmTest, mm_8x4_4x4){
        int16_t aa[8][4] = {
            {1, 2, -3, 4},
            {5, 6, 7, 8},
            {3, 6, 8, 1},
            {2, -6, 7, 1},
            {19, 4,24,-14},
            {7,9,16,8},
            {6,5,4,1},
            {9,1,3,2}
        };
        int16_t bb[4][4] = {
            {1, 3, 5, -7},
            {2, 4, 6, 8},
            {2, 5, 7, 9},
            {5, 2, 7, 1}
        };
        int16_t c[8][4] = {
            {19, 4,24,-14},
            {71,90,166,84},
            {36,75,114,100},
            {9,19,30,2},
            {5,165,189,101},
            {97,153,257,175},
            {29,60,95,35},
            {27,50,86,-26},
        };

        int16_t *cc = (int16_t *)c;
        int asize[2] = {8,4};
        int bsize[2] = {4,4};

        int16_t *r = gemm<int16_t>((int16_t *)aa,(int16_t *)bb, asize,bsize);
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 4; j++) {
                EXPECT_EQ(r[i*4+j], cc[i*4+j]);
            }
        }
        free(r);
    }

    TEST(gemmTest, rand_4x4_4x4){
        int size[2] = {4,4};
        int16_t *a = matrix<int16_t>(size);
        int16_t *b = matrix<int16_t>(size);
        int16_t *res = gemm<int16_t>(a,b,size,size);
        int16_t *ref = mm<int16_t>(a,b,size,size);
        for(int i = 0; i < size[0]; i++) {
            for(int j = 0; j < size[1]; j++) {
                EXPECT_EQ(res[i*size[1]+j], ref[i*size[1]+j]);
            }
        }
    }

    TEST(gemmTest, rand_8x4_4x4){
        int asize[2] = {8,4};
        int bsize[2] = {4,4};
        int16_t *a = matrix<int16_t>(asize);
        int16_t *b = matrix<int16_t>(bsize);
        int16_t *res = gemm<int16_t>(a,b,asize,bsize);
        int16_t *ref = mm<int16_t>(a,b,asize,bsize);
        for(int i = 0; i < asize[0]; i++) {
            for(int j = 0; j < bsize[1]; j++) {
                EXPECT_EQ(res[i*bsize[1]+j], ref[i*bsize[1]+j]);
            }
        }
    }

    TEST(gemmTest, rand_4x8_8x4){
        int asize[2] = {4,8};
        int bsize[2] = {8,4};
        int16_t *a = matrix<int16_t>(asize);
        int16_t *b = matrix<int16_t>(bsize);
        int16_t *res = gemm<int16_t>(a,b,asize,bsize);
        int16_t *ref = mm<int16_t>(a,b,asize,bsize);
        for(int i = 0; i < asize[0]; i++) {
            for(int j = 0; j < bsize[1]; j++) {
                EXPECT_EQ(res[i*bsize[1]+j], ref[i*bsize[1]+j]);
            }
        }
    }

    // TEST(gemmTest, rand_8x8_8x8){
    //     int size[2] = {8,8};
    //     int16_t *a = matrix<int16_t>(size);
    //     int16_t *b = matrix<int16_t>(size);
    //     int16_t *res = gemm<int16_t>(a,b,size,size);
    //     int16_t *ref = mm<int16_t>(a,b,size,size);
    //     for(int i = 0; i < size[0]; i++) {
    //         for(int j = 0; j < size[1]; j++) {
    //             EXPECT_EQ(res[i*size[1]+j], ref[i*size[1]+j]);
    //         }
    //     }
    // }

} 
