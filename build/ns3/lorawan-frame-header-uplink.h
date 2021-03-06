/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2017 IDLab-imec
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Floris Van den Abeele <floris.vandenabeele@ugent.be>
 */
#ifndef LORAWAN_FRAME_HEADER_UPLINK_H
#define LORAWAN_FRAME_HEADER_UPLINK_H

#include <ns3/header.h>
#include "ns3/ipv4-address.h"

//common to both
#define LORAWAN_FHDR_ADR_MASK 0x80
#define LORAWAN_FHDR_ACK_MASK 0x20
#define LORAWAN_FHDR_FOPTSLEN_MASK 0x0F

//only uplink
#define LORAWAN_FHDR_ADRACKREQ_MASK 0x40
#define LORAWAN_FHDR_CLASSB_MASK 0x10

#define LORAWAN_FHDR_FOPTSLEN_MAX_SIZE 15

namespace ns3 {

/**
 * \ingroup lorawan
 * Represent the Frame Header (FHDR) in LoRaWAN
 */
class LoRaWANFrameHeaderUplink : public Header
{
public:
  LoRaWANFrameHeaderUplink (void);

  LoRaWANFrameHeaderUplink (Ipv4Address devAddr, bool adr, bool adrAckReq, bool ack, bool framePending, uint8_t FOptsLen, uint16_t frameCounter, uint16_t framePort,uint8_t periodP);
  ~LoRaWANFrameHeaderUplink (void);

  Ipv4Address getDevAddr(void) const;
  void setDevAddr(Ipv4Address);

  bool getAck() const;
  void setAck(bool);

  bool getAdr() const;
  void setAdr(bool);

  bool getAdrAckReq() const;
  void setAdrAckReq(bool);

  bool getClassB() const; //note: not currently used.
  void setClassB(bool); 

  uint8_t getClassBPingPeriodicity() const; 
  void  setClassBPingPeriodicity(uint8_t); 
  

  uint16_t getFrameCounter() const;
  void setFrameCounter(uint16_t);

  uint8_t getFramePort() const;
  void setFramePort(uint8_t);

  bool getSerializeFramePort() const;
  void setSerializeFramePort(bool);

  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;

  void Print (std::ostream &os) const;
  uint32_t GetSerializedSize (void) const;
  void Serialize (Buffer::Iterator start) const;
  uint32_t Deserialize (Buffer::Iterator start);

  bool IsAck() const;
  bool IsFramePending() const;

private:
  Ipv4Address m_devAddr; //!< Short device address of end-device
  uint8_t m_frameControl;
  uint16_t m_frameCounter;
  uint8_t m_framePort; // Not actually part of the frame header, but we include it here for ease of use TODO: isn't it?
  bool m_serializeFramePort;
  uint8_t m_ClassBPingPeriodicity; 
  
}; //LoRaWANFrameHeader

}; // namespace ns-3

#endif /* LORAWAN_FRAME_HEADER_UPLINK_H */
