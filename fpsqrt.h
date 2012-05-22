#ifndef _H_FPSQRT_
#define _H_FPSQRT_

/*
  Computing the square root of an integer or a fixed point into a 
  fixed point integer. A fixed point is a 32 bit value with the comma between
  the bits 15 and 16, where bit 0 is the less significant bit of the value. 
  
  The algorithms can be easily extended to 64bit integers, or different 
  fixed point comma positions. 
 
  Algorithm and code Author: Christophe Meessen 1993. 
  Initially published in: usenet comp.lang.c, Thu, 28 Jan 1993 08:35:23 GMT, 
  Subject: Fixed point sqrt ; by Meessen Christophe
*/


#include <stdint.h>

/* Fixed point representation with the comma between bit 15 and bit 16 */
typedef int32_t fixed;

/*
 * int32_t sqrtI2I( int32_t v );
 *
 * Compute int32_t to int32_t square root
 * RETURNS the integer square root of v
 * REQUIRES v is positive
 */
int32_t sqrtI2I( int32_t X );

/*
 * fixed sqrtI2F( long v );
 *
 * Compute int32_t to fixed square root
 * RETURNS the fixed point square root of v
 * REQUIRES v is positive
 *          The less significant bit may be inaccurate for some values bigger
 *          than 57 millions because of computation overflow and rounding error
 */
fixed sqrtI2F( int32_t v );

/*
 * fixed sqrtF2F( fixed v );
 *
 * Compute fixed to fixed square root
 * RETURNS the fixed point square root of v (fixed)
 * REQUIRES v is positive
 */

fixed sqrtF2F ( fixed X );


#endif
