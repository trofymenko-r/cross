/*!
\file       crc.h
\brief      crosslib crc functions
\author     Dr Michael
\date       11112011
*/
#ifndef __CRC_H
#define __CRC_H


#include "types.h"


#ifdef  __cplusplus
extern "C"  {
#endif
/******************************************************************************/
//!@{ \name crc 16
/******************************************************************************/
//#define Crc16Hdlc_Table             /*!< use table function for crc 16 hdlc   */
#define Crc16HdlcCorrect    0x0f47  /*!< correct constant for crc16 hdlc      */
/*! calculate crc 16 hdlc
iso 3309, x^16 + x^12 + x^5 + x^0, 0x8408, inverted
\param[in]  pu16Data    pointer to data, allign to 2
\param[in]  u32Bytes    count bytes(u8)
\return                 calced crc
*/
U16
Crc16HdlcCalc(
        IN  PU16    pu16Data,
        IN  U32     u32Bytes
        );

//#define Crc16Ccitt_Table            /*!< use table function for crc 16 ccitt  */
#define Crc16CcittCorrect   0x0000  /*!< correct constant for crc16 ccitt     */
/*! calculate crc 16 ccitt
crc-ccitt, x^16 + x^12 + x^5 + x^0, 0x1021
\param[in]  pu16Data    pointer to data, allign to 2
\param[in]  u32Bytes    count bytes(u8)
\return                 calced crc
*/
U16
Crc16CcittCalc(
        IN  PU16    pu16Data,
        IN  U32     u32Bytes
        );
//@}

/******************************************************************************/
//!@{ \name crc 32
/******************************************************************************/
#define Crc32_Table                 /*!< use table function for crc 32        */
/*! calculate crc 32
\param[in]  pvData      pointer to data
\param[in]  u32Bytes    count bytes(u8)
\return                 calced crc
*/
U32
Crc32Calc(
        IN  PVOID   pvData,
        IN  U32     u32Bytes
        );
//@}




#ifdef  __cplusplus
}
#endif

#endif  // __CRC_H

