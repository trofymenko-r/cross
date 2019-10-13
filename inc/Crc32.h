/*
 * Crc32.h
 *
 *  Created on: 9 жовт. 2017
 *      Author: root
 */

#pragma once

#include "types.h"

namespace cross {

class CCrc32
{
public:
   enum class EType{CRC32, CRC32_IEEE};

public:
   CCrc32(U32 u32Poly);
   CCrc32(EType Type);
   virtual ~CCrc32();

private:
   U32 au32CrcTable[256];
   EType Type;

private:
   void MakeTable(U32 u32Poly);
   U32 CalcSt(U8* pu8Data, U32 u32Bytes);
   U32 CalcIeee(U8* pu8Data, U32 u32Bytes);

public:
   U32 Calc(U8* pu8Data, U32 u32Bytes);
};

} /* namespace cross */
