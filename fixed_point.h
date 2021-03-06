#ifndef _fixed_point_h_
#define _fixed_point_h_

// Functions for 16-bit multiplication.  This can be compiled with
// ARDUINO defined to use the hardware multiply instructions, or
// without ARDUIINO defined to allow development on "regular" systems.

#include <stdint.h>

typedef int16_t fix16_t;
typedef uint16_t ufix16_t;

#ifdef ARDUINO
  #include "mult16x16.h"
  #define times_signed(a, b) \
    ({fix16_t _r; FMultiS16X16to16(_r, (a), (b)); _r;})
  #define times_unsigned(a, b) \
    ({fix16_t _r; FMultiSU16X16to16(_r, (a), (b)); _r;})
#else
  #define times_signed(a, b) \
    ((fix16_t)(((int32_t)(a) * (int32_t)(b)) >> 15))
  #define times_unsigned(a, b) \
    ((fix16_t)(((int32_t)(a) * (uint32_t)(uint16_t)(b)) >> 15))
#endif

// fix() is a macro used at compile time to convert floating point
// constants to fixed point.

#define fix(n) ((fix16_t)(int32_t)((double)(n) * (uint16_t)(1 << 15)))

#endif /* ndef _fixed_point_h_ */
