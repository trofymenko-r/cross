 /*
 *  Created on: 12 лип. 2016
 *      Author: root
 */
/*
 * func.cpp
 *
 *  Created on: 12 лип. 2016
 *      Author: root
 */


#include "func.h"


void xor8(U8* pu8Src, U8* pu8Dst)
{
   *((U64*)pu8Dst) = (*((U64*)pu8Dst))^(*((U64*)pu8Src));
}

VOID xorbuf(PVOID pvSrc, PVOID pvDst, U32 u32Bytes)
{
   U32 u32CurrByte = 0;
   U8* pu8Src = (U8*)pvSrc;
   U8* pu8Dst = (U8*)pvDst;
   while(u32CurrByte < u32Bytes){
      *pu8Dst = (*pu8Src)^(*pu8Dst);
      pu8Src++;
      pu8Dst++;
      u32CurrByte++;
   }
}

/******************************************************************************/
/*  checksum16                                                                */
/******************************************************************************/
//U16 checksum16(U8* pu8Data, int len)
//{
//   long sum = 0;  /* assume 32 bit long, 16 bit short */
//
//   while(len > 1){
//      U16* pu16Temp = (U16*)pu8Data;
//      sum += *(pu16Temp++);
//      if(sum & 0x80000000)   /* if high order bit set, fold */
//         sum = (sum & 0xFFFF) + (sum >> 16);
//      len -= 2;
//   }
//
//   if(len)       /* take care of left over byte */
//      sum += (U16)*(U8*)pu8Data;
//
//   while(sum>>16)
//      sum = (sum & 0xFFFF) + (sum >> 16);
//
//   return ~sum;
//}

U16 checksum16(U16* ptr, int length)
{
   register int sum = 0;
   U16 answer = 0;
   register U16 *w = ptr;
   register int nleft = length;

   while(nleft > 1){
      sum += *w++;
      nleft -= 2;
   }

   sum = (sum >> 16) + (sum & 0xFFFF);
   sum += (sum >> 16);
   answer = ~sum;
   return(answer);
}



