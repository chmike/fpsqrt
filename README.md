Fixed point square root function
--------------------------------

**check the note at the end of this README**


Computing the square root of an integer or a fixed point integer into a 
fixed point integer. A fixed point is a 32 bit value with the decimal point
between the bits 15 and 16, where bit 0 is the less significant bit of the value.

The functions `sqrt_i32` and `sqrt_i64` compute a simple integer square root.

The functions `sqrt_i32_to_fx16_16` and `sqrt_fx16_16_to_fx16_16` compute the 
square root by using only 32 bit registers, addition, subtraction and
shifts. 

When 64bit registers and operations are available, one can produce the same
result by simply using the 64bit integer square root as shown below:

```c
fx16_16_t sqrt_i32_to_fx16_16(int32_t v) {
    return (fx16_16)sqrt_i64((int64_t)v << 32);
}

fx16_16_t sqrt_fx16_16_to_fx16_16(fx16_16_t v) {
    return (fx16_16_t)sqrt_i64((int64_t)v << 16);
}
```

We can thus compute the square root of a fixed point with any number of
fractional bits. Below are examples for fixed point with 6 bit fractional
part.

```c
fx26_6 sqrt_i32_to_fx26_6(int32_t v) {
    return (fx26_6)sqrt_i64((int64_t)v << 12);
}

fx26_6 sqrt_fx26_6_to_fx26_6(fx26_6 v) {
    return (fx26_6)sqrt_i64((int64_t)v << 6);
}
```

The main.c test the functions over a big range of values. To compile and 
run it, use the command `gcc *.c -lm -o fpsqrt && ./fpsqrt`. 

*Algorithm and code Author*: Christophe Meessen 1993.\
*Initially published in*: usenet comp.lang.c, Thu, 28 Jan 1993 08:35:23 GMT, \
*Subject*: Fixed point sqrt \
*by*: Meessen Christophe\
*Ref*: [usenet post](https://groups.google.com/forum/?hl=fr%05aacf5997b615c37&fromgroups#!topic/comp.lang.c/IpwKbw0MAxw/discussion)

Last update : May 21, 2021

## Note Sep 16, 2023

The github user *apodtele* found a bug with the `sqrt_fx16_16_to_fx16_16()` function. 
An overflow occurs when the input value is bigger or equal to 0x40000200.
The bug is now fixed with a slight performance penalty. 

