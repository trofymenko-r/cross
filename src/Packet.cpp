/*
 * Packet.cpp
 *
 *  Created on: 13 бер. 2017
 *      Author: root
 */

#include <utility>
#include <stdexcept>

#include "Packet.h"


namespace cross {

U32 CPacket::u32Packets = 0;

CPacket::CPacket():u32Bytes(0), u32ReservBeforeBytes(0)
{
   ptrData = std::unique_ptr<U8[]>(new U8[32]);
   MakeIndex();
}

CPacket::CPacket(U32 u32Bytes):u32Bytes(u32Bytes), u32ReservBeforeBytes(0)
{
   if(u32Bytes > u32MaxPacketBytes) throw std::runtime_error("CPacket overflow u32MaxPacketBytes");
   ptrData = std::unique_ptr<U8[]>(new U8[u32Bytes]);
   bExtData = false;
   MakeIndex();
}

CPacket::CPacket(U32 u32Bytes, U32 u32ReservBeforeBytes):CPacket(u32Bytes + u32ReservBeforeBytes)
{
   this->u32Bytes = u32Bytes;
   this->u32ReservBeforeBytes = u32ReservBeforeBytes;
}

CPacket::CPacket(U8* pu8Buffer, U32 u32Bytes):CPacket(u32Bytes)
{
   memcpy(ptrData.get(), pu8Buffer, u32Bytes);
}

CPacket::CPacket(U8* pu8Buffer, U32 u32Bytes, U32 u32ReservBeforeBytes):CPacket(u32Bytes+u32ReservBeforeBytes)
{
   memcpy(ptrData.get()+u32ReservBeforeBytes, pu8Buffer, u32Bytes);
   this->u32Bytes = u32Bytes;
   this->u32ReservBeforeBytes = u32ReservBeforeBytes;
}

CPacket::CPacket(U8* pu8Buffer, U32 u32Bytes, bool bUseExtBuffer)
  :ptrData(pu8Buffer),
   u32Bytes(u32Bytes),
   u32ReservBeforeBytes(0),
   bExtData(true)
{
   MakeIndex();
}

CPacket::CPacket(std::unique_ptr<U8[]>& ptrData, U32 u32Bytes)
  :u32Bytes(u32Bytes),
   u32ReservBeforeBytes(0),
   bExtData(false)
{
   this->ptrData = std::move(ptrData);
   MakeIndex();
}

CPacket::CPacket(std::unique_ptr<U8[]>& ptrData, U32 u32Bytes, U32 u32ReservBeforeBytes)
  :u32Bytes(u32Bytes),
   u32ReservBeforeBytes(u32ReservBeforeBytes),
   bExtData(false)
{
   this->ptrData = std::move(ptrData);
   MakeIndex();
}

CPacket::CPacket(const CPacket& Packet):CPacket(Packet.getBytes())
{
   u32ReservBeforeBytes = Packet.u32ReservBeforeBytes;
   u32Index = Packet.getIndex();
   memcpy(ptrData.get(), Packet.getData(), u32Bytes);
}

CPacket::CPacket(CPacket&& Packet)
  :u32Bytes(Packet.getBytes()),
   u32ReservBeforeBytes(Packet.u32ReservBeforeBytes),
   bExtData(true),
   u32Index(Packet.getIndex())
{
   ptrData = std::move(Packet.ptrData);
}

/******************************************************************************/
/*  operators                                                                 */
/******************************************************************************/
CPacket& CPacket::operator=(CPacket const& op)
{
   if(this!=&op){
      this->ptrData = std::move(((CPacket&)op).ptrData);
      this->u32Bytes = op.u32Bytes;
      this->u32Index = op.u32Index;
      this->u32ReservBeforeBytes = op.u32ReservBeforeBytes;
   }
   return *this;
}

bool CPacket::operator==(CPacket const& op)
{
   if(u32Bytes!=op.getBytes()) return false;
   return(memcmp(getData(), op.getData(), u32Bytes)==0);
}

bool CPacket::operator!=(CPacket const & op)
{
   return !(*this==op);
}

/******************************************************************************/
/*  geters                                                                    */
/******************************************************************************/
U8* CPacket::getData() const {return(ptrData.get() + u32ReservBeforeBytes);}

U32 CPacket::getBytes() const {return u32Bytes;}

U32 CPacket::getMaxBytes() const {return u32MaxPacketBytes;}

U32 CPacket::getIndex() const {return u32Index;}

bool CPacket::IsValid() const {return(getData()!=nullptr);}

std::unique_ptr<U8[]>& CPacket::getPtr() {return ptrData;}

U32 CPacket::getResBefBytes() const {return u32ReservBeforeBytes;}

/******************************************************************************/
/*  MakeIndex                                                                 */
/******************************************************************************/
void CPacket::MakeIndex()
{
   u32Index = u32Packets;
   u32Packets++;
}

/******************************************************************************/
/*  SetPacket                                                                 */
/******************************************************************************/
void CPacket::SetPacket(std::unique_ptr<U8[]>& ptrData, U32 u32Bytes)
{
   this->ptrData = std::move(ptrData);
   this->u32Bytes = u32Bytes;
}

/******************************************************************************/
/*  AddBefore                                                                 */
/******************************************************************************/
bool CPacket::AddBefore(U32 u32AddBytes)
{
   if(u32AddBytes > u32ReservBeforeBytes) return false;
   u32ReservBeforeBytes -= u32AddBytes;
   u32Bytes += u32AddBytes;
   return true;
}

}
