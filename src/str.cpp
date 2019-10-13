#include "str.h"
#include "strcat.h"
#include "func.h"
#include <string.h>
#include "stdio.h"
#include "strl.h"
#include "utime.h"


VOID
trunc(
        IN  PCHAR   pcStr
        )
{
    U32     u32StrLen   = strlen(pcStr);
    PCHAR   pcTmp       = pcStr;

    U32 i = u32StrLen - 1;
    while((*(pcStr+i) == ' ')&&(i>0)){
        *(pcStr+i) = 0x00;
        u32StrLen--;
        i--;
    }

    i = 0;
    while((*(pcStr+i) == ' ')&&(i<u32StrLen)){
        pcTmp++;
        i++;
    }

    strcpy(pcTmp, pcStr);
}

VOID
lowercase(
        IN  PCHAR   pcStr
        )
{
    U32 u32Len = strlen(pcStr);

    for(U32 i=0; i<u32Len; i++){
        if((*(pcStr + i) <= 'Z')&&(*(pcStr + i) >= 'A'))
            *(pcStr + i) += 0x20;
    }
}

VOID
uppercase(
        IN  PCHAR   pcStr
        )
{
    U32 u32Len = strlen(pcStr);

    for(U32 i=0; i<u32Len; i++){
        if((*(pcStr + i) <= 'z')&&(*(pcStr + i) >= 'a'))
            *(pcStr + i) -= 0x20;
    }
}

PCHAR
i2a(
        IN  U32     u32Number,
        OUT PCHAR   pcStr
        )
{
    if(u32Number/10 > 0){
        pcStr = i2a(u32Number/10, pcStr);
        *pcStr++= u32Number%10 + '0';
        *pcStr  = 0x00;
    }else{
        *pcStr++= u32Number + '0';
        *pcStr  = 0x00;
    }

    return(pcStr);
}

BOOL
a2i(
        IN  PCHAR   pcStr,
        OUT PU32    pu32Number
        )
{
    U32 u32Len = strlen(pcStr);

    if(u32Len == 0)
        return(FALSE);

    *pu32Number = 0;
    for(U32 i=0; i<u32Len; i++){
        if((*pcStr >= '0')&&(*pcStr <= '9')){
            if((*pu32Number*10 + *pcStr - '0') < *pu32Number)
                return(FALSE);
            *pu32Number = *pu32Number*10 + *pcStr - '0';
            pcStr++;
        }else
            return(FALSE);
    }

    return(TRUE);
}

BOOL
a2i(
        IN  PCHAR   pcStr,
        OUT PU8     pu8Number
        )
{
    U32 u32Len = strlen(pcStr);

    if(u32Len == 0)
        return(FALSE);

    *pu8Number = 0;
    for(U32 i=0; i<u32Len; i++){
        if((*pcStr >= '0')&&(*pcStr <= '9')){
            if((*pu8Number*10 + *pcStr - '0') < *pu8Number)
                return(FALSE);
            *pu8Number = *pu8Number*10 + *pcStr - '0';
            pcStr++;
        }else
            return(FALSE);
    }

    return(TRUE);
}

VOID
h2a(
        IN  PU8     pu8Data,
        IN  U32     u32Bytes,
        OUT PCHAR   pcStr
        )
{
    CHAR    acTrans[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                            '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    while(u32Bytes-- > 0){
        *pcStr++ = acTrans[(*(pu8Data)&0xf0)>>4];
        *pcStr++ = acTrans[(*(pu8Data++)&0x0f)];
    }
    *pcStr++ = 0x00;
}

VOID
h2a_(
        IN  PU8     pu8Data,
        IN  U32     u32Bytes,
        OUT PCHAR   pcStrIn
        )
{
    CHAR    acTrans[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                            '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    PCHAR   pcStr = pcStrIn;
    pu8Data += (u32Bytes-1);
    while(u32Bytes > 0){
        *pcStr = acTrans[(*(pu8Data)&0xf0)>>4];
        pcStr++;
        *pcStr = acTrans[(*(pu8Data)&0x0f)];
        pcStr++;
        pu8Data--;
        u32Bytes--;
    }
    *pcStr = 0x00;
}

BOOL
a2h(
        IN  PCHAR   pcStr,
        IN  U32     u32StrBytes,
        OUT PU8     pu8Data
        )
{
    while(u32StrBytes-- > 0){
        if((*pcStr >= '0')&&(*pcStr <= '9')){
            *pu8Data = (*pcStr-'0')<<4;
        }else if((*pcStr >= 'a')&&(*pcStr <= 'f')){
            *pu8Data = (*pcStr-'a'+10)<<4;
        }else if((*pcStr >= 'A')&&(*pcStr <= 'F')){
            *pu8Data = (*pcStr-'A'+10)<<4;
        }else{
            return(FALSE);
        }
        pcStr++;

        if((*pcStr >= '0')&&(*pcStr <= '9')){
            *pu8Data += (*pcStr-'0');
        }else if((*pcStr >= 'a')&&(*pcStr <= 'f')){
            *pu8Data += (*pcStr-'a'+10);
        }else if((*pcStr >= 'A')&&(*pcStr <= 'F')){
            *pu8Data += (*pcStr-'A'+10);
        }else{
            return(FALSE);
        }
        pcStr++;

        pu8Data++;
    }

    return(TRUE);
}

VOID
mac2str(
        IN  PU8     pu8Mac,
        OUT PCHAR   pcStr
        )
{
    h2a(pu8Mac, 1, pcStr);
    pu8Mac++; pcStr += 2; *pcStr++ = ':';
    h2a(pu8Mac, 1, pcStr);
    pu8Mac++; pcStr += 2; *pcStr++ = ':';
    h2a(pu8Mac, 1, pcStr);
    pu8Mac++; pcStr += 2; *pcStr++ = ':';
    h2a(pu8Mac, 1, pcStr);
    pu8Mac++; pcStr += 2; *pcStr++ = ':';
    h2a(pu8Mac, 1, pcStr);
    pu8Mac++; pcStr += 2; *pcStr++ = ':';
    h2a(pu8Mac, 1, pcStr);
    pu8Mac++; pcStr += 2; *pcStr++ = 0x00;
}

BOOL
str2mac(
        IN  PCHAR   pcStr,
        OUT PU8     pu8Mac
        )
{
    if(strlen(pcStr) != 17)
        return(FALSE);

    lowercase(pcStr);
    for(U8 i=0; i<5; i++)
        if(*(pcStr+2+3*i) != ':')
            return(FALSE);
    for(U8 i=0; i<6; i++){
        if(!a2h(pcStr, 1, (pu8Mac+i)))
            return(FALSE);
        pcStr += 3;
    }

    return(TRUE);
}

VOID
ip2str(
        IN  PU8     pu8Ip,
        OUT PCHAR   pcStr
        )
{
    CHAR    acTmpStr_11[11];

    i2a(*pu8Ip++, pcStr);
    strcat(pcStr, (char*)".", pcStr);
    i2a(*pu8Ip++, acTmpStr_11);
    strcat(pcStr, acTmpStr_11, pcStr);
    strcat(pcStr, (char*)".", pcStr);
    i2a(*pu8Ip++, acTmpStr_11);
    strcat(pcStr, acTmpStr_11, pcStr);
    strcat(pcStr, (char*)".", pcStr);
    i2a(*pu8Ip++, acTmpStr_11);
    strcat(pcStr, acTmpStr_11, pcStr);
}

BOOL
str2ip(
        IN  PCHAR   pcStr,
        OUT PU8     pu8Ip
        )
{
    CHAR    acTmp_4[4];
    PCHAR   pcTmpPtr;
    U8      u8IpLen = strlen(pcStr);

    if((u8IpLen < 7)||(u8IpLen > 15))
        return(FALSE);

    pcTmpPtr = &acTmp_4[0];
    for(U8 i=0; i<=u8IpLen; i++){
        if(pcTmpPtr > &acTmp_4[3])
            return(FALSE);
        if((*pcStr != 0)&&(*pcStr != '.')){
            *pcTmpPtr++ = *pcStr++;
        }else{
            U32 u32IpOctet;
            *pcTmpPtr = 0;
            if(!a2i(acTmp_4, &u32IpOctet))
                return(FALSE);
            if(u32IpOctet > 255)
                return(FALSE);
            *pu8Ip++ =u32IpOctet;
            pcTmpPtr = &acTmp_4[0];
            pcStr++;
        }
    }

    return(TRUE);
}

VOID
time2str(
        IN  PDATETIME   pdtTime,
        OUT PCHAR       pcStr // size not checked, can lead to buffer overflow
        )
{
    CHAR    acTmpStr_11[11];

    if(pdtTime->u16Hour < 10)
        strcat(pcStr, (char*)"0", pcStr);
    i2a(pdtTime->u16Hour, acTmpStr_11);
    strcat(pcStr, acTmpStr_11, pcStr);
    strcat(pcStr, (char*)":", pcStr);
    if(pdtTime->u16Min < 10)
        strcat(pcStr, (char*)"0", pcStr);
    i2a(pdtTime->u16Min, acTmpStr_11);
    strcat(pcStr, acTmpStr_11, pcStr);
    strcat(pcStr, (char*)":", pcStr);
    if(pdtTime->u16Sec < 10)
        strcat(pcStr, (char*)"0", pcStr);
    i2a(pdtTime->u16Sec, acTmpStr_11);
    strcat(pcStr, acTmpStr_11, pcStr);
}

BOOL
str2time(
        IN  PCHAR       pcStr,
        OUT PDATETIME   pdtDateTime
        )
{
    CHAR    acTmp_3[3];
    U32     u32TmpTime;
    // houres
    memcpy(acTmp_3, pcStr, 3);
    if(acTmp_3[1] == ':'){
        acTmp_3[1] = 0x00;
        pcStr += 2;
    }else if(acTmp_3[2] == ':'){
        acTmp_3[2] = 0x00;
        pcStr += 3;
    }else
        return(FALSE);
    if(!a2i(acTmp_3, &u32TmpTime))
        return(FALSE);
    if(u32TmpTime > 23)
        return(FALSE);
    pdtDateTime->u16Hour = u32TmpTime;
    // minutes
    memcpy(acTmp_3, pcStr, 3);
    if(acTmp_3[1] == ':'){
        acTmp_3[1] = 0x00;
        pcStr += 2;
    }else if(acTmp_3[2] == ':'){
        acTmp_3[2] = 0x00;
        pcStr += 3;
    }else
        return(FALSE);
    if(!a2i(acTmp_3, &u32TmpTime))
        return(FALSE);
    if(u32TmpTime > 59)
        return(FALSE);
    pdtDateTime->u16Min = u32TmpTime;
    // seconds
    memcpy(acTmp_3, pcStr, 3);
    if(!a2i(acTmp_3, &u32TmpTime))
        return(FALSE);
    if(u32TmpTime > 59)
        return(FALSE);
    pdtDateTime->u16Sec = u32TmpTime;

    return(TRUE);
}

VOID
date2str(
        IN  PDATETIME   pdtDate,
        OUT PCHAR       pcStr // size not checked, can lead to buffer overflow
        )
{
    CHAR    acTmpStr_11[11];

    if(pdtDate->u16MonDay < 10)
        strcat(pcStr, (char*)"0", pcStr);
    i2a(pdtDate->u16MonDay, acTmpStr_11);
    strcat(pcStr, acTmpStr_11, pcStr);
    strcat(pcStr, (char*)".", pcStr);
    if(pdtDate->u16Mon < 10)
        strcat(pcStr, (char*)"0", pcStr);
    i2a(pdtDate->u16Mon, acTmpStr_11);
    strcat(pcStr, acTmpStr_11, pcStr);
    strcat(pcStr, (char*)".", pcStr);
    i2a(pdtDate->u16Year, acTmpStr_11);
    strcat(pcStr, acTmpStr_11, pcStr);
}

BOOL
str2date(
        IN  PCHAR       pcStr,
        OUT PDATETIME   pdtDateTime
        )
{
    CHAR    acTmp_5[5];
    U32     u32TmpDate;
    // day
    memcpy(acTmp_5, pcStr, 3);
    if(acTmp_5[1] == '.'){
        acTmp_5[1] = 0x00;
        pcStr += 2;
    }else if(acTmp_5[2] == '.'){
        acTmp_5[2] = 0x00;
        pcStr += 3;
    }else
        return(FALSE);
    if(!a2i(acTmp_5, &u32TmpDate))
        return(FALSE);
    if((u32TmpDate < 1)||(u32TmpDate > 31))
        return(FALSE);
    pdtDateTime->u16MonDay = u32TmpDate;
    // month
    memcpy(acTmp_5, pcStr, 3);
    if(acTmp_5[1] == '.'){
        acTmp_5[1] = 0x00;
        pcStr += 2;
    }else if(acTmp_5[2] == '.'){
        acTmp_5[2] = 0x00;
        pcStr += 3;
    }else
        return(FALSE);
    if(!a2i(acTmp_5, &u32TmpDate))
        return(FALSE);
    if((u32TmpDate < 1)||(u32TmpDate > 12))
        return(FALSE);
    pdtDateTime->u16Mon = u32TmpDate;

    // year
    memcpy(acTmp_5, pcStr, 4);
    acTmp_5[4] = 0x00;
    if(!a2i(acTmp_5, &u32TmpDate))
        return(FALSE);
    if((u32TmpDate < 1970)||(u32TmpDate > 2100))
        return(FALSE);
    pdtDateTime->u16Year = u32TmpDate;

    return(TRUE);
}

VOID
daytime2str(
        IN  U32       u32Time,
        OUT PCHAR     pcStr,
        U16           u16StrLen
        )
{
    CHAR    acTmpStr_16[16];
    U16 u16Days = u32Time/86400;
    U8  u8Hours = (u32Time%86400)/3600;
    U8  u8Min   = ((u32Time%86400)%3600)/60;
    U8  u8Sec   = ((u32Time%86400)%3600)%60;
    
    strlcpy(pcStr, "", u16StrLen);
    if(u16Days!=0){
       if(u16Days>1) sprintf(acTmpStr_16, "%d days ", u16Days);
       else sprintf(acTmpStr_16, "%d day ", u16Days);    
       strlcpy(pcStr, acTmpStr_16, u16StrLen);
    }
    sprintf(acTmpStr_16, "%02d:%02d:%02d", u8Hours, u8Min, u8Sec);
    strlcat(pcStr, acTmpStr_16, u16StrLen);
}

void strleft(
             IN PCHAR      pcStrIn,
             OUT PCHAR     pcStrOut,
             U8            u8Number
            )
{
   strlcpy(pcStrOut, pcStrIn, u8Number+1);
}

void strleft(
             IN PCHAR      pcStrIn,
             U8            u8Number
            )
{
   CHAR acTemp[128];
   strleft(pcStrIn, acTemp, u8Number);
   strlcpy(pcStrIn, acTemp, strlen(acTemp)+1);
}

void strright(
             IN PCHAR      pcStrIn,
             OUT PCHAR     pcStrOut,
             U8            u8Number
            )
{
   U8 u8StrLen = strlen(pcStrIn);
   strlcpy(pcStrOut, pcStrIn+(u8StrLen-u8Number), u8Number+1);
}

void strright(
             IN PCHAR      pcStrIn,
             U8            u8Number
            )
{
   CHAR acTemp[128];
   strright(pcStrIn, acTemp, u8Number);
   strlcpy(pcStrIn, acTemp, strlen(acTemp)+1);
}

int snprintfDateTime(char *pcStr, int iStrBytes, utime_t Time)
{
   DATETIME   DateTime;
   CHAR acTime[9] = {0};
   CHAR acDate[11] = {0};

   GmTime(Time, &DateTime);
   date2str(&DateTime, acDate);
   time2str(&DateTime, acTime);
   return snprintf(pcStr, iStrBytes-1, "%s %s", acDate, acTime);
}

