/*!
\file       math.h
\brief      crosslib mathematics functions
\author     Dr Michael
\date       15112011
*/
#ifndef __MATH_H
#define __MATH_H


#include "types.h"


#ifdef  __cplusplus
extern "C"  {
#endif

/*! get minimum from two variables */
#define umin(a, b)   ((a)<(b) ? (a) : (b))

/*! get maximum from two variables */
#define umax(a, b)   ((a)>(b) ? (a) : (b))

/*! absolute value */
#define absv(a)     (((signed)(a))<0 ? (-(a)) : (a))

/*! power variable
\param[in]  u32Data     variable
\param[in]  u32Pow      power
\return                 variable^power
*/
U32
power(
        IN  U32 u32Data,
        IN  U32 u32Pow
        );

U8
CalcHiBitsU8(
        IN  U8  u8Mask
        );

U8
CalcHiBitsU16(
        IN  U16 u16Mask
        );

U8
CalcHiBitsU32(
        IN  U32 u32Mask
        );

void FFTAnalysis128(/*double*/S32 *AVal, S32 *FTvl);


#ifdef  __cplusplus
}
#endif

#endif // __MATH_H

