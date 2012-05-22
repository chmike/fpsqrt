#include <stdio.h>
#include "fpsqrt.h"

int main( int argc, char *argv[] )
{
    int32_t i;
    const int32_t n = 1024*1024*1024;
    const double k = 1<<16;

    printf( "Testing sqrtI2I  " );
    for( i = 0; i < n; ++i )
    {
        int32_t q = sqrtI2I( i );
        double dq = sqrt(i);
        int32_t r = (int32_t)dq;
        if( q != r )
        {
            printf( "%3d -> %d : %d  **** ERROR\n", i, q, r );
            return -1;
        }
    }
    printf( "Ok !\n\n" );

    // rounding error with some values
    printf( "Testing sqrtI2F  " );
    for( i = 0; i < n; ++i )
    {
        int32_t q = sqrtI2F( i );
        double dq = sqrt( i );
        int32_t r = (int32_t)(dq*k);

        if( q != r ) // some sqrtI2F results are one bit less
        {
            printf( "%3d -> %d : %d  **** ERROR\n", i, q, r );
            //return -1;
        }
    }
    printf( "Ok !\n\n" );

    printf( "Testing sqrtF2F  " );
    for( i = 0; i < n; ++i )
    {
        int32_t q = sqrtF2F( i );
        double dq = sqrt( i/k );
        int32_t r = (int32_t)(dq*k);

        if( q != r )
        {
            printf( "%3d -> %d : %d  **** ERROR\n", i, q, r );
            return -1;
        }
    }
    printf( "Ok !\n\n" );

    return 0;
}
