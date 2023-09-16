#include <stdio.h>
#include <math.h>
#include <string.h>
#include "fpsqrt.h"

#define UNUSED(x) (void)(x)


fx16_16_t sqrt_i32_to_fx16_16_alt(int32_t v) {
	return (fx16_16_t)sqrt_i64((int64_t)v << 32);
}

fx16_16_t sqrt_fx16_16_to_fx16_16_alt(fx16_16_t v) {
	return (fx16_16_t)sqrt_i64((int64_t)v << 16);
}

// from https://stackoverflow.com/a/5296669/75517
unsigned short isqrt(unsigned long a) {
    unsigned long rem = 0;
    int root = 0;
    int i;

    for (i = 0; i < 16; i++) {
        root <<= 1;
        rem <<= 2;
        rem += a >> 30;
        a <<= 2;

        if (root < rem) {
            root++;
            rem -= root;
            root++;
        }
    }
    return (unsigned short) (root >> 1);
}


int main (int argc, char *argv[]) {
	UNUSED(argc);
	UNUSED(argv);
    int32_t i;
    const int32_t n = 0x7FFFFFF;
    const double k = 1<<16;

    printf( "Testing integer square roots  " );
    fflush(stdout);
    for (i = 0; i < n; ++i) {
        int32_t q32 = sqrt_i32(i);
        int32_t m32 = (int32_t)sqrt(i);
        if (q32 != m32) {
            printf( "sqrt_i32(%d) -> %d err: %d  **** ERROR\n", i, q32, m32);
            return -1; 
        }

        int64_t i64 = (uint64_t)i;
        int64_t q64 = sqrt_i64(i64);
        int64_t m64 = (int64_t)sqrt(i);
        if (q64 != m64) {
            printf( "sqrt_i64(%ld) -> %ld err: %ld  **** ERROR\n", i64, q64, m64);
            return -1;
        }
    }
    printf( "Ok !\n\n" );
 
    printf( "Testing int32 to fx16_16 sqrt  " );
    fflush(stdout);
    for (i = 0; i < n; ++i) {
        int32_t q32 = sqrt_i32_to_fx16_16(i);
        int32_t q32_alt = sqrt_i32_to_fx16_16_alt(i);
        if (q32 != q32_alt) {
            printf( "%d -> %d alt: %d  **** ERROR\n", i, q32, q32_alt);
            return -1;
        }

        int32_t d32 = (int32_t)(sqrt(i)*65536);
        int32_t err32 = q32_alt - d32;
        if (err32 < -1 || err32 > 1) {
            printf( "%08X -> %08X ref: %08X err: %08X  **** ERROR\n", i, q32, d32, err32);
            return -1;
        }
    }
    printf( "Ok !\n\n" );

    printf( "Testing fx16_16 to fx16_16 sqrt  " );
    fflush(stdout);
    for( i = 0; i < n; ++i )
    {
        int32_t q32 = sqrt_fx16_16_to_fx16_16(i);
        int32_t q32_alt = sqrt_fx16_16_to_fx16_16_alt(i);
        if (q32 != q32_alt) {
            printf( "%d -> %d alt: %d  **** ERROR\n", i, q32, q32_alt);
            return -1;
        }

        double v = ((double)i)/65536.;
        int32_t d32 = (int32_t)(sqrt(v)*65536.);
        int32_t err32 = q32 - d32;
        if (err32 < -1 || err32 > 1) {
            printf( "%08X -> %08X ref: %08X err: %08X  **** ERROR\n", i, q32, d32, err32);
            return -1;
        }
     }
    printf( "Ok !\n\n" );

    return 0;
}
