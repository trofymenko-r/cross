
#include <sys/time.h>
#include "utime.h"


static const U32 month[12] = {
        0,
        DAY*(31),
        DAY*(31+29),
        DAY*(31+29+31),
        DAY*(31+29+31+30),
        DAY*(31+29+31+30+31),
        DAY*(31+29+31+30+31+30),
        DAY*(31+29+31+30+31+30+31),
        DAY*(31+29+31+30+31+30+31+31),
        DAY*(31+29+31+30+31+30+31+31+30),
        DAY*(31+29+31+30+31+30+31+31+30+31),
        DAY*(31+29+31+30+31+30+31+31+30+31+30)
};

static const U8 _ytab[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};


utime_t
DateTime2UnixTime(
        IN  PDATETIME   pDateTime
        )
{
    utime_t  tRes;
    U16     u16Year;


    pDateTime->u16Mon -= 1;

    u16Year = pDateTime->u16Year - EPOCH_YEAR;
/* magic offsets (y+1) needed to get leapyears right.*/
    tRes = YEAR*u16Year + DAY*((u16Year+1)/4);
    tRes += month[pDateTime->u16Mon];
/* and (y+2) here. If it wasn't a leap-year, we have to adjust */
    if(pDateTime->u16Mon>1 && ((u16Year+2)%4))
        tRes -= DAY;
    tRes += DAY*(pDateTime->u16MonDay-1);
    tRes += HOUR*pDateTime->u16Hour;
    tRes += MINUTE*pDateTime->u16Min;
    tRes += pDateTime->u16Sec;

    pDateTime->u16Mon += 1;

    return(tRes);
}

VOID
GmTime(
        IN  utime_t      tTime,
        OUT PDATETIME   pDateTime
        )
{
    U32 u32DayClock,
        u32DayNo;
    U16 u16Year = EPOCH_YEAR;
    U16 u16Mon  = 0;

    u32DayClock  = tTime % DAY;
    u32DayNo     = tTime / DAY;

    pDateTime->u16Sec   = u32DayClock % MINUTE;
    pDateTime->u16Min   = (u32DayClock % HOUR) / MINUTE;
    pDateTime->u16Hour  = u32DayClock / HOUR;

    pDateTime->u16WeekDay = (u32DayNo + 4) % 7;

    while(u32DayNo >= YEARSIZE(u16Year)){
        u32DayNo -= YEARSIZE(u16Year);
        u16Year++;
    }
    pDateTime->u16Year    = u16Year;// - 1900;
    pDateTime->u16YearDay = u32DayNo;

    while(u32DayNo >= _ytab[LEAPYEAR(u16Year)][u16Mon]){
        u32DayNo -= _ytab[LEAPYEAR(u16Year)][u16Mon];
        u16Mon++;
    }
    pDateTime->u16Mon   = u16Mon + 1;
    pDateTime->u16MonDay= u32DayNo + 1;
}

U32 GetTickCount()
{
   struct timeval tv;
   if(gettimeofday(&tv, __null) != 0)
      return 0;

   return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

