#include "fpsqrt.h"

#include <stdio.h>

/*
  Computing the square root of an integer or a fixed point integer into a 
  fixed point integer. A fixed point is a 32 bit value with the comma between
  the bits 15 and 16, where bit 0 is the less significant bit of the value. 
  
  The algorithms can be easily extended to 64bit integers, or different 
  fixed point comma positions. 

  The algorithm uses the property that computing x² is trivial compared to the
  sqrt. It will thus search the biggest x so that x² <= v, assuming we compute
  sqrt(v).  
    
  The algorithm tests each bit of x starting with the most significant toward
  the less significant. It tests if the bit must be set or not. 
  
  The algorithm uses the relation (x + a)² = x² + 2ax + a² to add the bit
  efficiently. Instead of computing x² it keeps track of (x + a)² - x².
  
  When computing sqrt(v), r = v - x², q = 2ax, b = a² and t = 2ax + a2. 

  Note that the input integers are signed and that the sign bit is used in 
  the computation. To accept unsigned integer as input, unfolding the initial
  loop is required to handle this particular case. See the usenet discussion
  for the proposed solution. 
  
 
  Algorithm and code Author Christophe Meessen 1993. 
  Initially published in usenet comp.lang.c, Thu, 28 Jan 1993 08:35:23 GMT, 
  Subject: Fixed point sqrt ; by Meessen Christophe
  
  https://groups.google.com/forum/?hl=fr%05aacf5997b615c37&fromgroups#!topic/comp.lang.c/IpwKbw0MAxw/discussion
  Note: there was a bug in the published sqrtL2L routine. It is corrected in
        this implementation.
  
*/


/*
 * int32_t sqrtI2I( int32_t v );
 *
 * Compute int32_t to int32_t square root
 * RETURNS the integer square root of v
 * REQUIRES v is positive
 */
int32_t sqrtI2I( int32_t v )
{
    uint32_t t, q, b, r;
    r = v;           // r = v - x²
    b = 0x40000000;  // a²
    q = 0;           // 2ax
    while( b > 0 )
    {
        t = q + b;   // t = 2ax + a²
        q >>= 1;     // if a' = a/2, then q' = q/2
        if( r >= t ) // if (v - x²) >= 2ax + a²
        {
            r -= t;  // r' = (v - x²) - (2ax + a²)
            q += b;  // if x' = (x + a) then ax' = ax + a², thus q' = q' + b
        }
        b >>= 2;     // if a' = a/2, then b' = b / 4
    }
    return q;
}


/*
 * fixed sqrtI2F( long v );
 *
 * Compute int32_t to fixed square root
 * RETURNS the fixed point square root of v
 * REQUIRES v is positive
 *          The less significant bit may be inaccurate for some values bigger
 *          than 57 millions because of computation overflow and rounding error
 *
 * Shifts comma one bit left at each iteration. Last instruction adjusts
 * rounding approximation in last bit. 
 */
fixed sqrtI2F( int32_t v )
{
    uint32_t t, q, b, r;
    if( !v ) return 0;
    r = v;
    b = 0x40000000;
    q = 0;
    while( b > 0 )
    {
        t = q + b;
        if( r >= t )
        {
            r -= t;
            q = t + b; // equivalent to q += 2*b
        }
        r <<= 1;
        b >>= 1;
    }
    if( r >= q ) ++q;
    return q;
}


/*
 * fixed sqrtF2F( fixed v );
 *
 * Compute fixed to fixed square root
 * RETURNS the fixed point square root of v (fixed)
 * REQUIRES v is positive
 */
fixed sqrtF2F ( fixed x )
{
    uint32_t t, q, b, r;
    r = x;
    b = 0x40000000;
    q = 0;
    while( b > 0x40 )
    {
        t = q + b;
        if( r >= t )
        {
            r -= t;
            q = t + b; // equivalent to q += 2*b
        }
        r <<= 1;
        b >>= 1;
    }
    q >>= 8;
    return q;
}


