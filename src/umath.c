#include "umath.h"
#include <math.h>


U32
power(
        IN  U32 u32Data,
        IN  U32 u32Pow
        )
{
    U32 u32Result = 1;

    while(u32Pow > 0){
        u32Result *= u32Data;
        u32Pow--;
    }

    return(u32Result);
}

U8
CalcHiBitsU8(
        IN  U8  u8Mask
        )
{
    U8  u8Result = 0;

    for(U8 i=0; i<8; i++){
        if((u8Mask&1) == 1)
            u8Result++;
        u8Mask >>= 1;
    }

    return(u8Result);
}

U8
CalcHiBitsU16(
        IN  U16 u16Mask
        )
{
    U8  u8Result = 0;

    for(U8 i=0; i<16; i++){
        if((u16Mask&1) == 1)
            u8Result++;
        u16Mask >>= 1;
    }

    return(u8Result);
}

U8
CalcHiBitsU32(
        IN  U32 u32Mask
        )
{
    U8  u8Result = 0;

    for(U8 i=0; i<32; i++){
        if((u32Mask&1) == 1)
            u8Result++;
        u32Mask >>= 1;
    }

    return(u8Result);
}

#define  NUMBER_IS_2_POW_K(x)   ((!((x)&((x)-1)))&&((x)>1))  // x is pow(2, k), k=1,2, ...
#define  FT_DIRECT        -1    // Direct transform.
#define  FT_INVERSE        1    // Inverse transform.
 
const double TwoPi = 6.283185307179586;
 
void FFTAnalysis128(S32 *AVal, S32 *FTvl/*, int Nvl, int Nft*/) 
{
  U32 Nvl = 128;
  U32 Nft = 128;
  S32 i, j, n, m, Mmax, Istp;
  float Tmpr, Tmpi, Wtmp, Theta;
  float Wpr, Wpi, Wr, Wi;
  S32 Tmvl[128*2];
 
  n = Nvl * 2;
 
  for (i = 0; i < n; i+=2) {
   Tmvl[i] = 0;
   Tmvl[i+1] = AVal[i/2];
  }
 
  i = 1; j = 1;
  while (i < n) {
    if (j > i) {
      Tmpr = Tmvl[i]; Tmvl[i] = Tmvl[j]; Tmvl[j] = (S32)Tmpr;
      Tmpr = Tmvl[i+1]; Tmvl[i+1] = Tmvl[j+1]; Tmvl[j+1] = (S32)Tmpr;
    }
    i = i + 2; m = Nvl;
    while ((m >= 2) && (j > m)) {
      j = j - m; m = m >> 1;
    }
    j = j + m;
  }
 
  Mmax = 2;
  while (n > Mmax) {
    Theta = -TwoPi / Mmax; 
    Wpi = sin(Theta);
    Wtmp = sin(Theta / 2); Wpr = Wtmp * Wtmp * 2;
    Istp = Mmax * 2; Wr = 1; Wi = 0; m = 1;
 
    while (m < Mmax) {
      i = m; m = m + 2; Tmpr = Wr; Tmpi = Wi;
      Wr = Wr - Tmpr * Wpr - Tmpi * Wpi;
      Wi = Wi + Tmpr * Wpi - Tmpi * Wpr;
 
      while (i < n) {
        j = i + Mmax;
        Tmpr = Wr * Tmvl[j] - Wi * Tmvl[j-1];
        Tmpi = Wi * Tmvl[j] + Wr * Tmvl[j-1];
 
        Tmvl[j] = Tmvl[i] - (S32)Tmpr; Tmvl[j-1] = Tmvl[i-1] - (S32)Tmpi;
        Tmvl[i] = Tmvl[i] + (S32)Tmpr; Tmvl[i-1] = Tmvl[i-1] + (S32)Tmpi;
        i = i + Istp;
      }
    }
 
    Mmax = Istp;
  }
 
  for (i = 0; i < Nft; i++) {
    j = i * 2; 
    FTvl[Nft - i - 1] = (S32)sqrt(pow((float)Tmvl[j],2) + pow((float)Tmvl[j+1],2));
  }

}

