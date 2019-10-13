/*!
\file       types.h
\brief      crosslib base types definitions
\author     Dr Michael
\date       10112011
*/

#pragma once

#include <stdint.h>

//!@{ \name unsigned types 
#define U8      unsigned char           /*!< unsigned 8 bit type    */
#define U16     unsigned short          /*!< unsigned 16 bit type   */
#define U32     uint32_t/*unsigned long*/           /*!< unsigned 32 bit type   */
#define U64     uint64_t
#define PU8     U8*         /*!< pointer to unsigned 8 bit type     */
#define PU16    U16*        /*!< pointer to unsigned 16 bit type    */
#define PU32    U32*        /*!< pointer to unsigned 32 bit type    */
//@}
//!@{ \name signed types
#define S8      signed char             /*!< signed 8 bit type      */
#define S16     signed short            /*!< signed 16 bit type     */
#define S32     signed long             /*!< signed 32 bit type     */
#define PS8     S8*         /*! pointer to signed 8 bit type       */
#define PS16    S16*        /*! pointer to signed 16 bit type      */
#define PS32    S32*        /*! pointer to signed 32 bit type      */
//@}
//!@{ \name volatile unsigned types
#define VU8     volatile unsigned char  /*!< volatile unsigned 8 bit type   */
#define VU16    volatile unsigned short /*!< volatile unsigned 16 bit type  */
#define VU32    volatile unsigned long  /*!< volatile unsigned 32 bit type  */
#define VPU8    VU8*        /*!< volatile pointer to unsigned 8 bit type    */
#define VPU16   VU16*       /*!< volatile pointer to unsigned 16 bit type   */
#define VPU32   VU32*       /*!< volatile pointer to unsigned 32 bit type   */
//@}
//!@{ \name volatile signed types
#define VS8     volatile signed char    /*!< volatile signed 8 bit type     */
#define VS16    volatile signed short   /*!< volatile signed 16 bit type    */
#define VS32    volatile signed long    /*!< volatile signed 32 bit type    */
#define VPS8    VS8*        /*!< volatile pointer to signed 8 bit type      */
#define VPS16   VS16*       /*!< volatile pointer to signed 16 bit type     */
#define VPS32   VS32*       /*!< volatile pointer to signed 32 bit type     */
//@}
//!@{ \name bool type
#define BOOL    U8
#define TRUE    1u
#define FALSE   0u
//@}
//!@{ \name void type
#define VOID    void
#define PVOID   VOID*
//@}
//!@{ \name char type
#define CHAR    char
#define PCHAR   CHAR*
//@}
//!@{ \name direction descriptors
#define IN                  /*!< used to descript input to func parametr    */
#define OUT                 /*!< used to descript output to func parametr   */
//@}
#ifndef NULL
   #define NULL    ((PVOID)0)  /*!< null defenition    */
#endif /* NULL */

#define __arm
#define __thumb
#define RAMFUNC

#define ITEM_NOT_FOUND     ((U32)-1)

