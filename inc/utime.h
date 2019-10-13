#pragma once


#include <ctime>

#include "types.h"

#ifdef WIN32
#include <windows.h>
#define msleep(x)    Sleep(x)
#else
#include <unistd.h>
#define msleep(x)    usleep((x)*1000)
#endif



//#ifdef  __cplusplus
//extern "C"  {
//#endif

#define LEAPYEAR(year)      (!((year) % 4) && (((year) % 100) || !((year) % 400)))
#define YEARSIZE(year)      (LEAPYEAR(year) ? 366 : 365)
#define EPOCH_YEAR          1970ul

#define MINUTE              60ul
#define HOUR                (60ul*MINUTE)
#define DAY                 (24ul*HOUR)
#define YEAR                (365ul*DAY)


#define gl_u32DateTime  std::time(nullptr)
#define gl_u32msec_cnt  GetTickCount()

typedef U32 utime_t;

typedef struct _DATETIME{
    U16 u16Sec;
    U16 u16Min;
    U16 u16Hour;
    U16 u16WeekDay;
    U16 u16MonDay;
    U16 u16Mon;
    U16 u16YearDay;
    U16 u16Year;
}DATETIME, *PDATETIME;


utime_t
DateTime2UnixTime(
        IN  PDATETIME   pDateTime
        );

VOID
GmTime(
        IN  utime_t      tTime,
        OUT PDATETIME   pDateTime
        );

extern U32 GetTickCount();

//#ifdef  __cplusplus
//}
//#endif

/******************************************************************************/
/*  CClock                                                                    */
/******************************************************************************/
//class CClock
//{
//public:
//   CClock(){}
//   CClock(PU32 pu32UnixTime_)
//   {
//      pu32UnixTime = pu32UnixTime_;
//   }
//   ~CClock(){}
//
//private:
//   PU32 pu32UnixTime;
//   bool bRun;
//
//public:
//   DATETIME DataTime;
//
//public:
//   void On()
//   {
//      bRun = true;
//   }
//
//   void Off()
//   {
//      bRun = true;
//   }
//
//   bool IsRun()
//   {
//      return(bRun);
//   }
//
//   U32 GetUnixTime(void)
//   {
//      return *pu32UnixTime;
//   }
//
//   void Service(void)
//   {
//      if(!bRun) return;
//
//      GmTime(*pu32UnixTime, &DataTime);
//   }
//
//};


