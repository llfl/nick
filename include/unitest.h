#include <limits.h>
#include "gtest/gtest.h"

template <typename T>
void TestMatrix(
    const T *a,
    const T *b,
        int *size
){
    for(int i = 0; i < size[0]; i++) {
        for(int j = 0; j < size[1]; j++) {
            EXPECT_EQ(a[i*size[1]+j], b[i*size[1]+j]) << "Position:(" << i << "," << j << ")";
        }
    }
}