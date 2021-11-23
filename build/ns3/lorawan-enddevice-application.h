/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
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

// Based on:
// ns3 - On/Off Data Source Application class
// George F. Riley, Georgia Tech, Spring 2007
// Adapted from ApplicationOnOff in GTNetS.

#ifndef LORAWAN_ENDDEVICE_APPLICATION_H
#define LORAWAN_ENDDEVICE_APPLICATION_H

#include "ns3/address.h"
#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/data-rate.h"
#include "ns3/traced-callback.h"
#include "ns3/lorawan-classB-config.h"
#include "ns3/traced-value.h"

#include "ns3/aes.h"

namespace ns3 {
  
class Address;
class RandomVariableStream;
class Socket;
namespace TracedValueCallback {
  /**
 * \ingroup lorawan
 * TracedCallback signature for tracing NS message events: DS msg transmitted, DS msg ackd and DS msg Dropped
 *
 * \param [in] deviceAddr The device address to whom the DS msg is addressed.
 * \param [in] numberofClassBTransmitted Number of Class B packets recvied
 * \param [in] microSeconds Time of which a ClassBPacket was recieved
 * \param [in] UID unique Packet ID
 */

  typedef void (* LoRaWANClassBMessageReceivedTracedCallback) (uint32_t deviceAddr, uint32_t ClassBPacketsReceived, uint32_t microSeconds , uint64_t Uid);
    /**
 * \ingroup lorawan
 * TracedCallback signature for tracing NS message events: DS msg transmitted, DS msg ackd and DS msg Dropped
 *
 * \param [in] deviceAddr The device address to whom the Beacon  was recieved
 * \param [in] m_beaconRecieved Number of Class B beacons recieved
 * \param [in] microSeconds Time of which a beacon was recieved
 */

  typedef void (* LoRaWANBeaconReceivedTracedCallback) (uint32_t deviceAddr, uint32_t m_beaconRecieved);
}
/**
 * \ingroup lorawan
 * \defgroup onoff LoRaWANEndDeviceApplication
 *
 * This application is intended to run on LoRaWAN end devices class A and was
 * based of the OnOffApplication, though it has changed drastically in that
 * US messages are generated according to a random variable (can be fixed) and
 * not according to a CBR requirement.
*/
class LoRaWANEndDeviceApplication : public Application
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  LoRaWANEndDeviceApplication ();

  virtual ~LoRaWANEndDeviceApplication();

  /**
   * \brief Set the total number of bytes to send.
   *
   * Once these bytes are sent, no packet is sent again, even in on state.
   * The value zero means that there is no limit.
   *
   * \param maxBytes the total number of bytes to send
   */
  void SetMaxBytes (uint64_t maxBytes);

  uint32_t GetDataRateIndex (void) const;
  void SetDataRateIndex (uint32_t index);
  void EnlargeWindowTimeout (void); 
  void ResetWindowTimeout (void); 
  uint8_t GetClassBDataRateIndex (void) const;
  void SetClassBDataRateIndex (uint8_t index);
  uint8_t GetClassBPingPeriodicity (void) const; 
  void SetClassBPingPeriodicity(uint8_t pow); 
/*!
 * \brief Starts Beacon Guard where no ping slots are assigned
 */
void ClassBStartGuardWindow ();

  /*! Real Implementation function from loramac-node 
 * \brief Computes the RX window timeout and the RX window offset.
 *
 * \param [IN] tSymbolInUs Symbol timeout.
 *
 * \param [IN] minRxSymbols Minimum required number of symbols to detect an Rx frame.
 *
 * \param [IN] rxErrorInMs System maximum timing error of the receiver. In milliseconds
 *                     The receiver will turn on in a [-rxErrorInMs : +rxErrorInMs] ms interval around RxOffset.
 *
 * \param [IN] wakeUpTimeInMs Wakeup time of the system.
 *
 * \param [OUT] windowTimeoutInSymbols RX window timeout.
 *
 * \param [OUT] windowOffsetInMs RX window time offset to be applied to the RX delay.
 */
void RegionCommonComputeRxWindowParameters( uint32_t tSymbolInUs, uint8_t minRxSymbols, uint32_t rxErrorInMs, uint32_t wakeUpTimeInMs, uint32_t* windowTimeoutInSymbols, int32_t* windowOffsetInMs );

/*!
 * \brief Computes the symbol time for LoRa modulation.
 *
 * \param [IN] phyDr Physical datarate to use.
 *
 * \param [IN] bandwidth Bandwidth to use.
 *
 * \retval Returns the symbol time in ns3:Time (microseconds)
 */
Time RegionCommonComputeSymbolTimeLoRa( uint8_t phyDr, uint32_t bandwidthInHz );
  /**
   * \brief Return a pointer to associated socket.
   * \return pointer to associated socket
   */
  Ptr<Socket> GetSocket (void) const;

 /**
  * \brief Assign a fixed random variable stream number to the random variables
  * used by this model.
  *
  * \param stream first stream index to use
  * \return the number of stream indices assigned by this model
  */
  int64_t AssignStreams (int64_t stream);

  void PrintFinalDetails();

  bool m_isClassB;                //!< specifies Class B, (wakes up for beacons and ping slots, sets bit in uplink packets)
  
protected:
  virtual void DoDispose (void);
private:
  bool m_offsetOn;
  // inherited from Application base class.
  virtual void StartApplication (void);    // Called at time specified by Start
  virtual void StopApplication (void);     // Called at time specified by Stop

  //helpers
  /**
   * \brief Cancel all pending events.
   */
  void CancelEvents ();

  // Event handlers
  /**
   * \brief Send a packet
   */
  void SendPacket ();

  void HandleRead (Ptr<Socket> socket);

  void HandleDSPacket (Ptr<Packet> p, Address from);

  Ptr<Socket>     m_socket;       //!< Associated socket
  bool            m_connected;    //!< True if connected
  Ptr<RandomVariableStream> m_channelRandomVariable;	//!< rng for channel selection for upstream TX
  Ptr<RandomVariableStream> m_upstreamIATRandomVariable;	//!< rng for inter arrival timing for upstream TX
  Ptr<RandomVariableStream> m_upstreamSendIATRandomVariable;
  uint32_t        m_pktSize;      //!< Size of packets
  uint32_t 	  m_dataRateIndex;	//!< Data rate index to use for US transmissions
  Time            m_lastTxTime; //!< Time last packet sent
  uint64_t        m_maxBytes;     //!< Limit total number of bytes sent
  uint64_t        m_totBytes;     //!< Total bytes sent so far
  EventId         m_txEvent;     //!< Event id for next start or stop event
  EventId         m_sendEvent;     //!< Event id for next start or stop event
  bool 		  m_confirmedData; //<! Send upstream data as Confirmed Data Up MAC packets

  uint8_t         m_framePort;	  //!< Frame port
  uint32_t        m_fCntUp;       //!< Uplink frame counter
  uint32_t        m_fCntDown;     //!< Downlink frame counter
  bool            m_setAck;      //!< Set the Ack bit in the next transmission
  uint64_t        m_totalRx;      //!< Total bytes received

  void ClassBSchedulePingSlots ();
  void ClassBReceiveBeacon ();
  void ClassBPingSlot ();
  bool SetBeaconSymbolTimeoutExpF(uint16_t beaconSymbolTimeoutEx);

  
  EventId     m_beaconTimer;      //Beacon event
  EventId     m_GuardTimer;       //Beacon Guard Timer
  uint8_t     m_ClassBPingSlots;
  uint8_t     m_ClassBPingPeriodicity;
  uint8_t     m_ClassBChannelIndex;
  uint8_t     m_ClassBDataRateIndex;  
  uint8_t     m_ClassBCodeRateIndex;
  TracedValue <uint32_t>   m_ClassBfcntDown;
  TracedValue <uint32_t> m_ClassBfcntBeacon;

  uint32_t    m_fcntRX1;
  uint32_t    m_fcntRX2;
  uint32_t    m_attemptedThroughput;

  uint32_t    m_devAddr;

  Time        m_timestamp;
  TracedValue <uint8_t> m_missedBeaconsCounter;
  Time        m_lastbeaconReceived;
  Time        m_missedBeaconsTimer; 
  Time        m_preMissedBeaconTimer; 
  uint16_t    m_BeaconWindowMovement; 
  uint16_t    m_BeaconSymbolTimeout; 
  uint16_t    m_PingSymbolTimeout;
  Time        m_tSymbol;    
  TracedCallback <uint32_t, uint32_t> m_ClassBfcntBeaconTrace; 
  TracedCallback <uint32_t ,uint32_t ,uint32_t, uint64_t> m_ClassBPacketReceivedTrace; 
  /// Traced Callback: transmitted packets.
  TracedCallback<uint32_t, uint8_t, Ptr<const Packet>> m_usMsgTransmittedTrace;

  /// Traced Callback: received packets, source address, receive window.
  TracedCallback<uint32_t, uint8_t, Ptr<const Packet>, uint8_t> m_dsMsgReceivedTrace;
private:
  /**
   * \brief Schedule the next packet transmission
   */
  void ScheduleNextTx ();
  /**
   * \brief Schedule the next On period start
   */
  void ScheduleStartEvent ();
  /**
   * \brief Schedule the next Off period start
   */
  void ScheduleStopEvent ();
  /**
   * \brief Handle a Connection Succeed event
   * \param socket the connected socket
   */
  void ConnectionSucceeded (Ptr<Socket> socket);
  /**
   * \brief Handle a Connection Failed event
   * \param socket the not connected socket
   */
  void ConnectionFailed (Ptr<Socket> socket);
};

} // namespace ns3

#endif /* LORAWAN_ENDDEVICE_APPLICATION_H */
