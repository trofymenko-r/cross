#ifndef __STR_H
#define __STR_H


#include "types.h"
#include "utime.h"


//#ifdef  __cplusplus
//extern "C"  {
//#endif


VOID
trunc(
        IN  PCHAR   pcStr
        );

VOID
lowercase(
        IN  PCHAR   pcStr
        );

VOID
uppercase(
        IN  PCHAR   pcStr
        );

PCHAR
i2a(
        IN  U32     u32Number,
        OUT PCHAR   pcStr
        );

BOOL
a2i(
        IN  PCHAR   pcStr,
        OUT PU32    pu32Number
        );

VOID
h2a(
        IN  PU8     pu8Data,
        IN  U32     u32Bytes,
        OUT PCHAR   pcStr
        );

VOID
h2a_(
        IN  PU8     pu8Data,
        IN  U32     u32Bytes,
        OUT PCHAR   pcStr
        );

BOOL
a2h(
        IN  PCHAR   pcStr,
        IN  U32     u32StrBytes,
        OUT PU8     pu8Data
        );

VOID
mac2str(
        IN  PU8     pu8Mac,
        OUT PCHAR   pcStr
        );

BOOL
str2mac(
        IN  PCHAR   pcStr,
        OUT PU8     pu8Mac
        );

VOID
ip2str(
        IN  PU8     pu8Ip,
        OUT PCHAR   pcStr
        );

BOOL
str2ip(
        IN  PCHAR   pcStr,
        OUT PU8     pbIp
        );

VOID
time2str(
        IN  PDATETIME   pdtTime,
        OUT PCHAR       pcStr
        );

BOOL
str2time(
        IN  PCHAR       pcStr,
        OUT PDATETIME   pdtDateTime
        );
VOID
date2str(
        IN  PDATETIME   pdtDate,
        OUT PCHAR       pcStr
        );

BOOL
str2date(
        IN  PCHAR       pcStr,
        OUT PDATETIME   pdtDateTime
        );

VOID
daytime2str(
        IN  U32       u32Time,
        OUT PCHAR     pcStr,
        U16           u16StrLen
        );

void strleft(
             IN PCHAR      pcStrIn,
             OUT PCHAR     pcStrOut,
             U8            u8Number
            );



void strright(
             IN PCHAR      pcStrIn,
             OUT PCHAR     pcStrOut,
             U8            u8Number
            );

int snprintfDateTime(char *pcStr, int iStrBytes, utime_t Time);

//#ifdef  __cplusplus
//}
//#endif

BOOL
a2i(
        IN  PCHAR   pcStr,
        OUT PU8     pu8Number
        );

void strleft(
             IN PCHAR      pcStrIn,
             U8            u8Number
            );

void strright(
             IN PCHAR      pcStrIn,
             U8            u8Number
            );


#endif  //  __STR_H

