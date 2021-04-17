#include "unitest.h"
#include "conv2d.h"
#include "mmutils.h"

namespace {
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

        int ishape[3] = {4,4,1};
        int kshape[3] = {3,3,1};
        int padding[4] = {0,0,0,0};
        int stride[2] = {1,1};
        int osize[2] = {4,12};
        int16_t *r = (int16_t*)malloc(sizeof(int16_t)*osize[H_INDEX]*osize[W_INDEX]);
        im2col<int16_t>((int16_t *)aa,ishape,kshape,padding,stride,osize,r);
        TestMatrix<int16_t>(r,(int16_t *)c,osize);
        free(r);
    }

    TEST(conv2d_im2col, nopadding_ichannel2){
        int16_t aa[2][4][4] = {{
            {1, 2, -3, 4},
            {5, 6, 7, 8},
            {3, 6, 8, 1},
            {2, -6, 7, 1}
        },{
            {1, 2, -3, 4},
            {5, 6, 7, 8},
            {3, 6, 8, 1},
            {2, -6, 7, 1}
        }};
        int16_t c[8][12] = {
            {1,2,-3,5,6,7,3,6,8,0,0,0},
            {2,-3,4,6,7,8,6,8,1,0,0,0},
            {5,6,7,3,6,8,2,-6,7,0,0,0},
            {6,7,8,6,8,1,-6,7,1,0,0,0},
            {1,2,-3,5,6,7,3,6,8,0,0,0},
            {2,-3,4,6,7,8,6,8,1,0,0,0},
            {5,6,7,3,6,8,2,-6,7,0,0,0},
            {6,7,8,6,8,1,-6,7,1,0,0,0}
        };
        int ishape[3] = {4,4,2};
        int kshape[3] = {3,3,1};
        int padding[4] = {0,0,0,0};
        int stride[2] = {1,1};
        int osize[2] = {8,12};
        int16_t *r = (int16_t*)malloc(sizeof(int16_t)*osize[H_INDEX]*osize[W_INDEX]);
        im2col<int16_t>((int16_t *)aa,ishape,kshape,padding,stride,osize,r);
        TestMatrix<int16_t>(r,(int16_t *)c,osize);
        free(r);
    }

    TEST(conv2d_im2col, padding_1_1_1_1){
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
        int ishape[3] = {4,4,1};
        int kshape[3] = {3,3,1};
        int padding[4] = {1,1,1,1};
        int stride[2] = {1,1};
        int osize[2] = {16,12};
        int16_t *r = (int16_t*)malloc(sizeof(int16_t)*osize[H_INDEX]*osize[W_INDEX]);
        im2col<int16_t>((int16_t *)aa,ishape,kshape,padding,stride,osize,r);
        TestMatrix<int16_t>(r,(int16_t *)c,osize);
        free(r);
    }

    TEST(conv2d_im2col, padding_ichannel2_1_1_1_1){
        int16_t aa[2][4][4] = {{
            {1, 2, -3, 4},
            {5, 6, 7, 8},
            {3, 6, 8, 1},
            {2, -6, 7, 1}
        },{
            {1, 2, -3, 4},
            {5, 6, 7, 8},
            {3, 6, 8, 1},
            {2, -6, 7, 1}
        }};
        int16_t c[32][12] = {
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
            {8,1,0,7,1,0,0,0,0,0,0,0},
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
        int ishape[3] = {4,4,3};
        int kshape[3] = {3,3,1};
        int padding[4] = {1,1,1,1};
        int stride[2] = {1,1};
        int osize[2] = {32,12};
        int16_t *r = (int16_t*)malloc(sizeof(int16_t)*osize[H_INDEX]*osize[W_INDEX]);
        im2col<int16_t>((int16_t *)aa,ishape,kshape,padding,stride,osize,r);
        TestMatrix<int16_t>(r,(int16_t *)c,osize);
        free(r);
    }

    TEST(conv2d_k2img, 3x3){

        int16_t kernel[3][3] = {
            {1, 2, -3},
            {5, 6, 7},
            {3, 6, 8},
        };
        int16_t out[12][4] = {
            {1,0,0,0},
            {2,0,0,0},
            {-3,0,0,0},
            {5,0,0,0},
            {6,0,0,0},
            {7,0,0,0},
            {3,0,0,0},
            {6,0,0,0},
            {8,0,0,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0},
        };
        int kshape[4] = {3,3,1,1};
        int osize[2] = {12,4};
        int16_t *r = (int16_t*)malloc(sizeof(int16_t)*osize[H_INDEX]*osize[W_INDEX]);
        memset(r,0,sizeof(int16_t)*osize[H_INDEX]*osize[W_INDEX]);
        k2col<int16_t>((int16_t *)kernel, kshape, osize, r);
        TestMatrix<int16_t>(r,(int16_t *)out,osize);
        free(r);
    }

    TEST(conv2d_k2img, 3x3x2x1){
        
        int16_t kernel[2][3][3] = {{
            {1, 2, -3},
            {5, 6, 7},
            {3, 6, 8},
        },{
            {1, 2, -3},
            {5, 6, 7},
            {3, 6, 8},
        }};
        int16_t out[12][4] = {
            {1 ,1 ,0,0},
            {2 ,2 ,0,0},
            {-3,-3,0,0},
            {5 ,5 ,0,0},
            {6 ,6 ,0,0},
            {7 ,7 ,0,0},
            {3 ,3 ,0,0},
            {6 ,6 ,0,0},
            {8 ,8 ,0,0},
            {0 ,0 ,0,0},
            {0 ,0 ,0,0},
            {0 ,0 ,0,0},
        };
        int kshape[4] = {3,3,2,1};
        int osize[2] = {12,4};
        int16_t *r = (int16_t*)malloc(sizeof(int16_t)*osize[H_INDEX]*osize[W_INDEX]);
        memset(r,0,sizeof(int16_t)*osize[H_INDEX]*osize[W_INDEX]);
        k2col<int16_t>((int16_t *)kernel, kshape, osize, r);
        TestMatrix<int16_t>(r,(int16_t *)out,osize);
        free(r);
    }

    TEST(conv2d_conv2d, nopadding){
        int16_t input[4][4] = {
            {1, 2, -3, 4},
            {5, 6, 7, 8},
            {3, 6, 8, 1},
            {2, -6, 7, 1}
        };
        int16_t kernel[3][3] = {
            {1, 1, 1},
            {1, 1, 1},
            {1, 1, 1}
        };
        int16_t out[2][2] = {
            {35, 39},
            {38, 38}
        };
        int ishape[3] = {4,4,1};
        int kshape[4] = {3,3,1,1};
        int padding[4] = {0,0,0,0};
        int stride[2] = {1,1};
        int oshape[3] = {2,2,1};
        int16_t *r = (int16_t*)malloc(sizeof(int16_t)*oshape[H_INDEX]*oshape[W_INDEX]);
        conv2d<int16_t>((int16_t *)input, (int16_t *)kernel, ishape, kshape, padding, stride, oshape, r);
        TestMatrix<int16_t>(r,(int16_t *)out,oshape);
        free(r);
    }
}