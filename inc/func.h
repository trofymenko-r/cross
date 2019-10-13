/*
 * func.hpp
 *
 *  Created on: 12 лип. 2016
 *      Author: root
 */

#pragma once

#include "types.h"



#define memcpy4(src, dst) memcpy(dst, src, 4)
#define memcpy8(src, dst) memcpy(dst, src, 8)
#define memcpy16(src, dst) memcpy(dst, src, 16)
#define memclr(pvSrc, u32Bytes)     memset(pvSrc, 0x00u, u32Bytes)

#ifdef  __cplusplus
extern "C"  {
#endif

void xor8(U8* pu8Src, U8* pu8Dst);
VOID xorbuf(PVOID pvSrc, PVOID pvDst, U32 u32Bytes);
U16 checksum16(U16* pu8Data, int len);

#ifdef  __cplusplus
}
#endif

