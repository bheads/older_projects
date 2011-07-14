/***
 * STDTYPE.H
 *  Used to define standard data types to be used accross
 *  all code.
 *
 *  Byron Heads bheads@emich.edu
 */

#ifndef OZ_STDTYPE_H
#define OZ__STDTYPE_H

#include <stdint.h>
#include <stdlib.h>

typedef uint8_t U8;
typedef int8_t I8;

typedef uint16_t U16;
typedef int16_t I16;

typedef uint32_t U32;
typedef int32_t I32;

typedef uint64_t U64;
typedef int64_t I64;

typedef float F32;
typedef double F64;

typedef size_t ERRCODE;
typedef size_t IDX;

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else //__cplusplus
#define NULL ((void *)0)
#endif //__cplusplus
#endif //NULL

#endif //OZ_STDTYPE_H

