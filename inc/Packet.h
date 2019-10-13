/*
 * Packet.h
 *
 *  Created on: 11 квіт. 2017
 *      Author: root
 */

#pragma once

#include <iostream>
#include <string.h>
#include <memory>
#include <stdexcept>


#include "types.h"

namespace cross {

class CPacket
{
public:
   static const U32 u32MaxPacketBytes = 65535;
   static U32 u32Packets;

public:
   CPacket();
   CPacket(U32 u32Bytes);
   CPacket(U32 u32Bytes, U32 u32ReservBeforeBytes);
   CPacket(U8* pu8Buffer, U32 u32Bytes);
   CPacket(U8* pu8Buffer, U32 u32Bytes, U32 u32ReservBeforeBytes);
   CPacket(U8* pu8Buffer, U32 u32Bytes, bool bUseExtBuffer);
   CPacket(std::unique_ptr<U8[]>& ptrData, U32 u32Bytes);
   CPacket(std::unique_ptr<U8[]>& ptrData, U32 u32Bytes, U32 u32ReservBeforeBytes);
   CPacket(const CPacket& Packet);
   CPacket(CPacket&& Packet);

   virtual ~CPacket(){}

private:
   std::unique_ptr<U8[]> ptrData;
   U32 u32Bytes;
   U32 u32ReservBeforeBytes;
   bool bExtData;
   U32 u32Index;

public:
   CPacket& operator=(CPacket const& op);
   bool operator==(CPacket const& op);
   bool operator!=(CPacket const & op);

private:
   void MakeIndex();

//protected:
public:
   std::unique_ptr<U8[]>& getPtr();
   U32 getResBefBytes() const;

public:
   U8* getData() const;
   U32 getBytes() const;
   U32 getMaxBytes() const;
   U32 getIndex() const;
   bool IsValid() const;

   void SetPacket(std::unique_ptr<U8[]>& ptrData, U32 u32Bytes);
   bool AddBefore(U32 u32Bytes);
};

} /* namespace cross */
