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
#include "ns3/log.h"
#include "ns3/address.h"
#include "ns3/inet-socket-address.h"
#include "ns3/inet6-socket-address.h"
#include "ns3/packet-socket-address.h"
#include "ns3/node.h"
#include "ns3/nstime.h"
#include "ns3/data-rate.h"
#include "ns3/random-variable-stream.h"
#include "ns3/socket.h"
#include "ns3/simulator.h"
#include "ns3/socket-factory.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include "ns3/double.h"
#include "ns3/boolean.h"
#include "ns3/trace-source-accessor.h"
#include "lorawan.h"
#include "lorawan-net-device.h"
#include "lorawan-enddevice-application.h"
#include "lorawan-frame-header-uplink.h"
#include "lorawan-frame-header-downlink.h"
#include "ns3/udp-socket-factory.h"
#include "ns3/string.h"
#include "ns3/pointer.h"
#include "lorawan-classB-config.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("LoRaWANEndDeviceApplication");

NS_OBJECT_ENSURE_REGISTERED (LoRaWANEndDeviceApplication);

TypeId
LoRaWANEndDeviceApplication::GetTypeId (void)
{
  // Construct default value for the channel random variable:
  std::stringstream channelRandomVariableSS;
  const uint32_t channelRandomVariableDefaultMin = 0;
  const uint32_t channelRandomVariableDefaultMax = (LoRaWAN::m_supportedChannels.size () - 1) - 9; // additional -9 as not to use the downlink only channel as an upstream channel
  channelRandomVariableSS << "ns3::UniformRandomVariable[Min=" << channelRandomVariableDefaultMin << "|Max=" << channelRandomVariableDefaultMax << "]";
  
  NS_LOG_LOGIC("LoRaWANEndDeviceApplication::m_supportedChannels: " << LoRaWAN::m_supportedChannels.size ());
  NS_LOG_LOGIC("LoRaWANEndDeviceApplication::GetTypeId: " << channelRandomVariableSS.str());

  static TypeId tid = TypeId ("ns3::LoRaWANEndDeviceApplication")
    .SetParent<Application> ()
    .SetGroupName("Applications")
    .AddConstructor<LoRaWANEndDeviceApplication> ()
    .AddAttribute ("OffsetON",
                   "Turn on PingOffset Operations",
                   BooleanValue(true), 
                   MakeBooleanAccessor (&LoRaWANEndDeviceApplication::m_offsetOn),
                   MakeBooleanChecker())
    .AddAttribute ("DataRateIndex",
                   "DataRate index used for US transmissions of this end device.",
                   UintegerValue (0), // default data rate is SF12 BW125
                   MakeUintegerAccessor (&LoRaWANEndDeviceApplication::GetDataRateIndex, &LoRaWANEndDeviceApplication::SetDataRateIndex),
                   MakeUintegerChecker<uint16_t> (0, LoRaWAN::m_supportedDataRates.size ()))
     .AddAttribute ("ClassBPingPeriodicity",
                   "Number of ping slots per beacon period. In a power of 2 integer",
                   UintegerValue (0),
                   MakeUintegerAccessor (&LoRaWANEndDeviceApplication::GetClassBPingPeriodicity, &LoRaWANEndDeviceApplication::SetClassBPingPeriodicity),
                   MakeUintegerChecker<uint8_t> (0, 7))
    .AddAttribute ("ClassBDataRateIndex",
                   "DataRate index used for Class B receives of this end device.",
                   UintegerValue (7), // default data rate is SF12 BW500
                   MakeUintegerAccessor (&LoRaWANEndDeviceApplication::GetClassBDataRateIndex, &LoRaWANEndDeviceApplication::SetClassBDataRateIndex),
                   MakeUintegerChecker<uint8_t> (7, LoRaWAN::m_supportedDataRates.size ()-1))               
    .AddAttribute ("IsClassB",
                  "False means device is in Class A mode",
                  BooleanValue(false),
                  MakeBooleanAccessor (&LoRaWANEndDeviceApplication::m_isClassB),
                  MakeBooleanChecker ())
    .AddAttribute ("PacketSize", "The size of packets sent in on state",
                   UintegerValue (21),
                   MakeUintegerAccessor (&LoRaWANEndDeviceApplication::m_pktSize),
                   MakeUintegerChecker<uint32_t> (1))
    .AddAttribute ("ConfirmedDataUp",
                   "Send Upstream data as Confirmed Data UP MAC packets."
                   "False means Unconfirmed data up packets are sent.",
                   BooleanValue (false),
                   MakeBooleanAccessor (&LoRaWANEndDeviceApplication::m_confirmedData),
                   MakeBooleanChecker ())
    .AddAttribute ("ChannelRandomVariable", "A RandomVariableStream used to pick the channel for upstream transmissions.",
                   StringValue (channelRandomVariableSS.str ()),
                   MakePointerAccessor (&LoRaWANEndDeviceApplication::m_channelRandomVariable),
                   MakePointerChecker <RandomVariableStream>())
    .AddAttribute ("UpstreamIAT", "A RandomVariableStream used to pick the interval between sends from this device.",
                   StringValue ("ns3::ConstantRandomVariable[Constant=900.0]"),
                   MakePointerAccessor (&LoRaWANEndDeviceApplication::m_upstreamIATRandomVariable),
                   MakePointerChecker <RandomVariableStream>())
    .AddAttribute ("UpstreamSend", "A RandomVariableStream used to pick the time between subsequent US transmissions from this end device.",
                   StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=900.0]"),
                   MakePointerAccessor (&LoRaWANEndDeviceApplication::m_upstreamSendIATRandomVariable),
                   MakePointerChecker <RandomVariableStream>())
    .AddAttribute ("MaxBytes",
                   "The total number of bytes to send. Once these bytes are sent, "
                   "no packet is sent again, even in on state. The value zero means "
                   "that there is no limit.",
                   UintegerValue (0),
                   MakeUintegerAccessor (&LoRaWANEndDeviceApplication::m_maxBytes),
                   MakeUintegerChecker<uint64_t> ())
    .AddTraceSource ("USMsgTransmitted", "An US message is sent",
                     MakeTraceSourceAccessor (&LoRaWANEndDeviceApplication::m_usMsgTransmittedTrace),
                     "ns3::Packet::TracedCallback")
    .AddTraceSource ("DSMsgReceived", "An acknowledgement for an US message has been received.",
                     MakeTraceSourceAccessor (&LoRaWANEndDeviceApplication::m_dsMsgReceivedTrace),
                     "ns3::Packet::TracedCallback")
    .AddTraceSource ("ClassBfcntDown","The number of times that a Class B DS packet was received",
                    MakeTraceSourceAccessor (&LoRaWANEndDeviceApplication::m_ClassBfcntDown),
                    "ns3::TracedValueCallback::Uint32")
    .AddTraceSource ("ClassBfcntBeacon","The number of times that a Beacon was received",
                    MakeTraceSourceAccessor (&LoRaWANEndDeviceApplication::m_ClassBfcntBeacon),
                    "ns3::TracedValueCallback::Uint32")
    .AddTraceSource ("missedBeaconsCounter","The number of times that a Beacon was missed",
                    MakeTraceSourceAccessor (&LoRaWANEndDeviceApplication::m_missedBeaconsCounter),
                    "ns3::TracedValueCallback::Uint8")       
    .AddTraceSource ("ClassBPacketReceivedTrace","The number of times that a Class B DS packet was received with Timestamp",
                    MakeTraceSourceAccessor (&LoRaWANEndDeviceApplication::m_ClassBPacketReceivedTrace),
                    "ns3::TracedValueCallback::LoRaWANClassBMessageReceivedTracedCallback")
    .AddTraceSource ("ClassBBeaconReceivedTrace","The number of times that a Beacon was received with Timestamp",
                    MakeTraceSourceAccessor (&LoRaWANEndDeviceApplication::m_ClassBfcntBeaconTrace),
                    "ns3::TracedValueCallback::LoRaWANBeaconReceivedTracedCallback")                                            
  ;
  return tid;
}


LoRaWANEndDeviceApplication::LoRaWANEndDeviceApplication ()
  : m_socket (0),
    m_connected (false),
    m_lastTxTime (Seconds (0)),
    m_totBytes (0),
    m_framePort (0),
    m_fCntUp (0),
    m_fCntDown (0),
    m_setAck (false),
    m_totalRx (0), 
    m_ClassBChannelIndex(15), 
    m_ClassBCodeRateIndex(1),
    m_ClassBfcntDown(0),
    m_ClassBfcntBeacon(0),
    m_fcntRX1(0),
    m_fcntRX2(0),
    m_attemptedThroughput(0),
    m_timestamp(0),
    m_missedBeaconsCounter(0),
    m_BeaconWindowMovement(CLASSB_WINDOW_MOVE_DEFAULT),
    m_BeaconSymbolTimeout(CLASSB_BEACON_SYMBOL_TO_DEFAULT),
    m_PingSymbolTimeout(CLASSB_BEACON_SYMBOL_TO_DEFAULT),
    m_tSymbol(0) //Need better default

{
  NS_LOG_FUNCTION (this);
}

LoRaWANEndDeviceApplication::~LoRaWANEndDeviceApplication ()
{
  NS_LOG_FUNCTION (this);
}

void
LoRaWANEndDeviceApplication::SetMaxBytes (uint64_t maxBytes)
{
  NS_LOG_FUNCTION (this << maxBytes);
  m_maxBytes = maxBytes;
}

uint32_t
LoRaWANEndDeviceApplication::GetDataRateIndex (void) const
{
  return m_dataRateIndex;
}

void
LoRaWANEndDeviceApplication::SetDataRateIndex (uint32_t index)
{
  NS_LOG_FUNCTION (this << index);

  if (index <= LoRaWAN::m_supportedDataRates.size () - 1)
    m_dataRateIndex = index;
  else
    NS_LOG_ERROR (this << " " << index << " is an invalid data rate index");
}

uint8_t
LoRaWANEndDeviceApplication::GetClassBDataRateIndex (void) const
{
  return m_ClassBDataRateIndex;
}
uint8_t
LoRaWANEndDeviceApplication::GetClassBPingPeriodicity (void) const
{
  return m_ClassBPingPeriodicity;
}

void
LoRaWANEndDeviceApplication::SetClassBPingPeriodicity (uint8_t pow)
{
  NS_LOG_DEBUG (this << "Set Class B Ping Periodicity: " << (int)pow);
  if (pow <= 7 && pow >= 0 )
  {
    m_ClassBPingPeriodicity = (int)pow;
    m_ClassBPingSlots = std::pow(2.0, m_ClassBPingPeriodicity);
  }
  else
    NS_LOG_ERROR (this << " " << pow << " is an invalid Class B Ping Periodicity");
}

void
LoRaWANEndDeviceApplication::SetClassBDataRateIndex (uint8_t index)
{
  NS_LOG_DEBUG (this << "Set ClassB DataRate Index: " << (int)index);

  if (index <= LoRaWAN::m_supportedDataRates.size () - 1 && index >= 7 )
    m_ClassBDataRateIndex = index;
  else
    NS_LOG_ERROR (this << " " << index << " is an Class B invalid data rate index");
}

Ptr<Socket>
LoRaWANEndDeviceApplication::GetSocket (void) const
{
  NS_LOG_FUNCTION (this);
  return m_socket;
}
void LoRaWANEndDeviceApplication::RegionCommonComputeRxWindowParameters( uint32_t tSymbolInUs, uint8_t minRxSymbols, uint32_t rxErrorInMs, uint32_t wakeUpTimeInMs, uint32_t* windowTimeoutInSymbols, int32_t* windowOffsetInMs )
{

    *windowTimeoutInSymbols = MAX( DIV_CEIL( ( ( 2 * minRxSymbols - 8 ) * tSymbolInUs + 2 * ( rxErrorInMs * 1000 ) ),  tSymbolInUs ), minRxSymbols ); // Computed number of symbols
    *windowOffsetInMs = ( int32_t )DIV_CEIL( ( int32_t )( 4 * tSymbolInUs ) -
                                               ( int32_t )DIV_CEIL( ( *windowTimeoutInSymbols * tSymbolInUs ), 2 ) -
                                               ( int32_t )( wakeUpTimeInMs * 1000 ), 1000 );
    
   
    NS_LOG_FUNCTION(this << "tSymbolInUs: " << tSymbolInUs);
    NS_LOG_FUNCTION(this << "minRxSymbols: " << minRxSymbols);
    NS_LOG_FUNCTION(this << "rxErrorInMs: " << rxErrorInMs);
    NS_LOG_FUNCTION(this << "wakeUpTimeInMs: " << wakeUpTimeInMs);
    NS_LOG_FUNCTION(this << "windowTimeoutInSymbols: " << *windowTimeoutInSymbols);
    NS_LOG_FUNCTION(this <<"windowOffsetInMs: " << *windowOffsetInMs);

  
}

Time LoRaWANEndDeviceApplication::RegionCommonComputeSymbolTimeLoRa( uint8_t phyDr, uint32_t bandwidthInHz )
{
    //Check CalculateTxTime for other calculation
    uint32_t temp = ( 1 << phyDr ) * 1000000 / bandwidthInHz;
    Time retv; 
    if (temp > 0)
    {
      retv = MicroSeconds(temp); 
      NS_LOG_DEBUG(this << " tSymbolInUs: " << retv.GetMilliSeconds());
      NS_LOG_DEBUG(this << " DataRate: " << phyDr);
      NS_LOG_DEBUG(this << " Bandwidth(Hz): " << bandwidthInHz);
    }
    else
    {
      retv = MicroSeconds(0);  
      NS_LOG_ERROR(this << "tSymbolInUs is invalid number" << temp); 
    }
    //microseconds
    return retv;
}
int64_t
LoRaWANEndDeviceApplication::AssignStreams (int64_t stream)
{
  NS_LOG_FUNCTION (this << stream);
  m_channelRandomVariable->SetStream (stream);
  m_upstreamIATRandomVariable->SetStream (stream + 1);
  m_upstreamSendIATRandomVariable->SetStream (stream + 2);
  return 2;
}

void
LoRaWANEndDeviceApplication::DoDispose (void)
{
  NS_LOG_FUNCTION (this);
  PrintFinalDetails();

  m_socket = 0;

  // chain up
  Application::DoDispose ();
}

// Application Methods
void LoRaWANEndDeviceApplication::StartApplication () // Called at time specified by Start
{
  m_missedBeaconsTimer = MilliSeconds (0); // intializer
  
  NS_LOG_FUNCTION (this);

  // Create the socket if not already
  if (!m_socket)
    {
      m_socket = Socket::CreateSocket (GetNode (), TypeId::LookupByName ("ns3::PacketSocketFactory"));
      m_socket->Bind ();

      PacketSocketAddress socketAddress;
      socketAddress.SetSingleDevice (GetNode ()->GetDevice (0)->GetIfIndex ()); // Set the address to match only a specified NetDevice...
      m_socket->Connect (Address (socketAddress)); // packet-socket documentation mentions: "Send: send the input packet to the underlying NetDevices with the default destination address. The socket must be bound and connected."

      m_socket->Listen ();
      //m_socket->SetAllowBroadcast (true); // TODO: does not work on packet socket?
      m_socket->SetRecvCallback (MakeCallback (&LoRaWANEndDeviceApplication::HandleRead, this));

      // TODO: remove?
      m_socket->SetConnectCallback (
        MakeCallback (&LoRaWANEndDeviceApplication::ConnectionSucceeded, this),
        MakeCallback (&LoRaWANEndDeviceApplication::ConnectionFailed, this));

      m_devAddr = Ipv4Address::ConvertFrom (GetNode ()->GetDevice (0)->GetAddress ()).Get();
    }

  // Insure no pending event
  CancelEvents ();


  if(m_isClassB)
  {

      m_ClassBPingSlots = std::pow(2.0, m_ClassBPingPeriodicity);
      NS_LOG_DEBUG(" Number of ClassBPingSlots: " << (int)m_ClassBPingSlots);
      // There should be a beacon hopping equation to figure out the Channel Index, however this is not in our scope, therefore it will be 927.5 as our beaocn frequency 
      const uint32_t bandwidth = LoRaWAN::m_supportedChannels [15].m_bw;
      // SF12 DR8
      const LoRaSpreadingFactor sf = LoRaWAN::m_supportedDataRates [7].spreadingFactor; //Default is SF_12 and beacon is 12
      m_tSymbol = RegionCommonComputeSymbolTimeLoRa( sf /*GetClassBDataRateIndex()*/,bandwidth);
      
      NS_LOG_LOGIC("Scheduling ClassBReceiveBeacon! addr is " << GetNode ()->GetDevice (0)->GetAddress ());
      //schedule event to wake up at exact time of next expected beacon
      Time BeaconDelay = MicroSeconds(1500); 
      Time t = Seconds (128); //+ BeaconDelay;
      m_beaconTimer = Simulator::Schedule (t, &LoRaWANEndDeviceApplication::ClassBReceiveBeacon, this);
      NS_LOG_DEBUG (this << " ED: Class B beacon " << "scheduled to be received at " << t);  
      SendPacket(); //To get the pingPeriodicity correct
  }
  else {
    NS_LOG_LOGIC("Not Scheduling ClassBReceiveBeacon! addr is " << GetNode ()->GetDevice (0)->GetAddress ());
  }

  // If we are not yet connected, there is nothing to do here
  // The ConnectionComplete upcall will start timers at that time
  //if (!m_connected) return;
  
  // this is the original from the Van den Abeele simulator - send a packet straight away, and schedule another packet to be sent every x seconds after that
  // results in continuous collisions (and all start at time 0)
  //m_txEvent = Simulator::ScheduleNow (&LoRaWANEndDeviceApplication::SendPacket, this);

  //this is probably more what they intended - choose a starting time between 0 and X, and then send a packet every X seconds
  /*Time nextSendTime (Seconds (this->m_upstreamSendIATRandomVariable->GetValue ()));
  NS_LOG_LOGIC (this << " upstream nextTime = " << nextSendTime);
  m_txEvent = Simulator::Schedule (nextSendTime,
                                       &LoRaWANEndDeviceApplication::SendPacket, this);*/

  
  // another approach / traffic type
  //Once every x seconds it chooses a time in the next x seconds interval to send a packet, and schedules the initial event again
  Time nextTime (Seconds(this->m_upstreamIATRandomVariable->GetValue ())); //this->m_upstreamIATRandomVariable->GetValue ()
  NS_LOG_LOGIC (this << " scheduleNextTx nextTime = " << nextTime);
  m_sendEvent = Simulator::Schedule (nextTime,
                                       &LoRaWANEndDeviceApplication::ScheduleNextTx, this);

  Time nextSendTime (Seconds (this->m_upstreamSendIATRandomVariable->GetValue ())); //Seconds (this->m_upstreamSendIATRandomVariable->GetValue ())
  NS_LOG_LOGIC (this << " upstream nextTime = " << nextSendTime);
  m_txEvent = Simulator::Schedule (nextSendTime,
                                       &LoRaWANEndDeviceApplication::SendPacket, this);
}

void LoRaWANEndDeviceApplication::StopApplication () // Called at time specified by Stop
{
  NS_LOG_FUNCTION (this);

  CancelEvents ();
  if(m_socket != 0)
    {
      m_socket->Close ();
    }
  else
    {
      NS_LOG_WARN ("LoRaWANEndDeviceApplication found null socket to close in StopApplication");
    }
}

void LoRaWANEndDeviceApplication::CancelEvents ()
{
  NS_LOG_FUNCTION (this);

  Simulator::Cancel (m_txEvent);
  Simulator::Cancel (m_sendEvent);
}


// Private helpers
void LoRaWANEndDeviceApplication::ScheduleNextTx ()
{
  NS_LOG_FUNCTION (this);

  if (m_maxBytes == 0 || m_totBytes < m_maxBytes)
    {
      /*Time nextTime (Seconds (this->m_upstreamIATRandomVariable->GetValue ()));
      NS_LOG_LOGIC (this << " nextTime = " << nextTime);
      m_txEvent = Simulator::Schedule (nextTime,
                                       &LoRaWANEndDeviceApplication::SendPacket, this);*/

      Time nextTime (Seconds (this->m_upstreamIATRandomVariable->GetValue ()));
      NS_LOG_DEBUG (this << " scheduleNextTx nextTime = " << nextTime);
      m_sendEvent = Simulator::Schedule (nextTime,
                                       &LoRaWANEndDeviceApplication::ScheduleNextTx, this);

      Time nextSendTime (Seconds (this->m_upstreamSendIATRandomVariable->GetValue ()));
      NS_LOG_DEBUG (this << " upstream nextTime = " << nextSendTime);
      m_txEvent = Simulator::Schedule (nextSendTime,
                                       &LoRaWANEndDeviceApplication::SendPacket, this);
    }
  else
    { // All done, cancel any pending events
      StopApplication ();
    }
}

void LoRaWANEndDeviceApplication::SendPacket ()
{
  NS_LOG_FUNCTION (this);
  NS_ASSERT (m_txEvent.IsExpired ());

  Ipv4Address myAddress = Ipv4Address::ConvertFrom (GetNode ()->GetDevice (0)->GetAddress ());
  
  LoRaWANFrameHeaderUplink fhdr;
  //LoRaWANFrameHeader fhdr;

  fhdr.setDevAddr (myAddress);
  fhdr.setAdr (false); //ADR is not currently implemented.
  fhdr.setAck (m_setAck);
  fhdr.setClassB (m_isClassB);
  fhdr.setClassBPingPeriodicity(m_ClassBPingPeriodicity);

  fhdr.setFrameCounter (++m_fCntUp); // increment frame counter
  // FPort: we will send FRMPayload so set the frame port
  fhdr.setFramePort (m_framePort);

  // Construct MACPayload
  // PHYPayload: MHDR | MACPayload | MIC
  // MACPayload: FHDR | FPort | FRMPayload
  Ptr<Packet> packet;
  uint8_t frmPayloadSize = m_pktSize  - fhdr.GetSerializedSize() - 1 - 4;  // subtract 8 bytes for frame header, 1B for MAC header and 4B for MAC MIC
  if (frmPayloadSize >= sizeof(uint64_t)) { // check whether payload size is large enough to hold 64 bit integer
    // send decrementing counter as payload (note: globally shared counter)
    uint8_t* payload = new uint8_t[frmPayloadSize](); // the parenthesis initialize the allocated memory to zero
    if (payload) {
      const uint64_t counter = LoRaWANCounterSingleton::GetCounter ();
      ((uint64_t*)payload)[0] = counter; // copy counter to beginning payload
      packet = Create<Packet> (payload, frmPayloadSize);
      delete[] payload;
    } else {
      packet = Create<Packet> (frmPayloadSize);
    }
  } else {
    packet = Create<Packet> (frmPayloadSize);
  }

  packet->AddHeader (fhdr); // Packet now represents MACPayload

  // Select channel to use:
  uint32_t channelIndex = m_channelRandomVariable->GetInteger ();
  NS_ASSERT (channelIndex <= LoRaWAN::m_supportedChannels.size () - (1+9)); // -9 because end devices should not use the special high power channel for US traffic

  LoRaWANPhyParamsTag phyParamsTag;
  phyParamsTag.SetChannelIndex (channelIndex);
  phyParamsTag.SetDataRateIndex (m_dataRateIndex);
  phyParamsTag.SetCodeRate (1);

  if (m_isClassB == true)
  {
    phyParamsTag.SetClassBPingPeriodicity (m_ClassBPingPeriodicity);
  }

  phyParamsTag.SetPreambleLength (8);

  packet->AddPacketTag (phyParamsTag);

  // Set Msg type
  LoRaWANMsgTypeTag msgTypeTag;
  if (m_confirmedData)
    msgTypeTag.SetMsgType (LORAWAN_CONFIRMED_DATA_UP);
  else
    msgTypeTag.SetMsgType (LORAWAN_UNCONFIRMED_DATA_UP);
  packet->AddPacketTag (msgTypeTag);

  uint32_t deviceAddress = myAddress.Get ();
  m_usMsgTransmittedTrace (deviceAddress, msgTypeTag.GetMsgType (), packet);

  // Set NetDevice MTU Data rate before calling socket::Send
  Ptr<LoRaWANNetDevice> netDevice = DynamicCast<LoRaWANNetDevice> (GetNode ()->GetDevice (0));
  netDevice->SetMTUSpreadingFactor(LoRaWAN::m_supportedDataRates [m_dataRateIndex].spreadingFactor);

  m_attemptedThroughput++;

  int16_t r = m_socket->Send (packet);
  if (r < 0) {
    NS_LOG_ERROR(this << "PacketSocket::Send failed and returned " << static_cast<int16_t>(r) << ". Errno is set to " << m_socket->GetErrno ());
  } else {
    m_setAck = false; // reset m_setAck
    m_totBytes += packet->GetSize ();

    NS_LOG_INFO ("At time " << Simulator::Now ().GetSeconds ()
        << "s LoRaWANEndDevice application on node #"
        << GetNode()->GetId()
        << " sent "
        <<  packet->GetSize () << " bytes,"
        << " total Tx " << m_totBytes << " bytes");
  }




  m_lastTxTime = Simulator::Now ();
  //ScheduleNextTx ();

  NS_LOG_DEBUG("Finished sending!");
}

void LoRaWANEndDeviceApplication::HandleRead (Ptr<Socket> socket)
{
  NS_LOG_FUNCTION (this << socket);
  Ptr<Packet> packet;
  Address from;

  while ((packet = socket->RecvFrom (from))) //the sender address is placed into from
    {
      if (packet->GetSize () == 0)
        { //EOF
          break;
        }
     

      if (PacketSocketAddress::IsMatchingType (from)) //TODO: note this sentence from the doc for this method: This method checks that the types are exactly equal. This method is really used only by the PacketSocketAddress and there is little point in using it otherwise so, you have been warned: DO NOT USE THIS METHOD
        {
          NS_LOG_INFO ("At time " << Simulator::Now ().GetSeconds ()
                       << "s end device on node #"
                       << GetNode()->GetId()
                       <<  " received " << packet->GetSize () << " bytes from "
                       << PacketSocketAddress::ConvertFrom(from).GetPhysicalAddress ()
                       << ", total Rx " << m_totalRx << " bytes");

          this->HandleDSPacket (packet, from);
        }
      else
        {
          NS_LOG_WARN (this << " Unexpected address type");
        }
    }
}

void
LoRaWANEndDeviceApplication::HandleDSPacket (Ptr<Packet> p, Address from)
{
  NS_LOG_FUNCTION(this << p);

  Ptr<LoRaWANNetDevice> netDevice = DynamicCast<LoRaWANNetDevice> (GetNode ()->GetDevice (0));
  Ptr<LoRaWANMac> mac = netDevice->GetMac ();
  LoRaWANMacState state = mac->GetLoRaWANMacState ();

  if(state == MAC_RW1 || state == MAC_RW2) { //beacon frame has no FrameHeader
    LoRaWANFrameHeaderDownlink frmHdr;
    frmHdr.setSerializeFramePort (true); // Assume that frame Header contains Frame Port so set this to true so that RemoveHeader will deserialize the FPort
    p->RemoveHeader (frmHdr);
      //TODO: use contents of the FrameHeaderDownlink i.e. isAck, isFramePending, isAdr - not needed for Class B so not implemented here

    m_totalRx += p->GetSize (); // only counting payload size as RX, not counting contents of beacon frames or FrameHeaders
  }



  // set m_setAck to true in case a CONFIRMED_DATA_DOWN message was received:
  // Try to parse Packet tag:
  LoRaWANMsgTypeTag msgTypeTag;
  if (p->RemovePacketTag (msgTypeTag)) {
    LoRaWANMsgType msgType = msgTypeTag.GetMsgType (); 
    if (msgType == LORAWAN_CONFIRMED_DATA_DOWN) {
      m_setAck = true; // next packet should set Ack bit
      NS_LOG_DEBUG (this << " Set Ack bit to 1");
    }
  } else {
    NS_LOG_WARN (this << " LoRaWANMsgTypeTag packet tag is missing from packet");
  }



  // Was packet received in first or second receive window?
  // -> Look at Mac state
  NS_ASSERT (state == MAC_RW1 || state == MAC_RW2 || state == MAC_BEACON || state == MAC_CLASS_B_PACKET);

  // Log packet reception
  Ipv4Address myAddress = Ipv4Address::ConvertFrom (GetNode ()->GetDevice (0)->GetAddress ());
  uint32_t deviceAddress = myAddress.Get ();
  if (state == MAC_RW1) {
      m_dsMsgReceivedTrace (deviceAddress, msgTypeTag.GetMsgType(), p, 1);
      m_fcntRX1++;
  }
  else if (state == MAC_RW2) {
      m_dsMsgReceivedTrace (deviceAddress, msgTypeTag.GetMsgType(), p, 2);
      m_fcntRX2++;
  }
  else if (state == MAC_BEACON && msgTypeTag.GetMsgType () == LORAWAN_BEACON) {
    // extract timestamp from packet
     uint8_t beacon[17];
     p->CopyData(beacon, 17);

     m_ClassBfcntBeacon++;
     m_ClassBfcntBeaconTrace(deviceAddress,m_ClassBfcntBeacon);

     uint32_t time = (uint32_t)((beacon[4] << 24) | (beacon[3] << 16) | (beacon[2] << 8) | (beacon[1] << 0));
     
     m_timestamp = Seconds(time); //Set the timestamp, this will be used in the later call to ClassBSchedulePingSlots.
     NS_LOG_DEBUG("Received beacon frame, extracting timestamp: " << m_timestamp << " and time is " << time << " time received:" << Simulator::Now());

     m_dsMsgReceivedTrace (deviceAddress, msgTypeTag.GetMsgType(), p, 3);
  }
  else if (state == MAC_CLASS_B_PACKET) {
    NS_LOG_DEBUG("Received class b downlink!" << Simulator::Now());
    m_ClassBfcntDown++;
    m_ClassBPacketReceivedTrace(deviceAddress,m_ClassBfcntDown,Simulator::Now().GetMilliSeconds(),p->GetUid()); 
  }
  else {
    NS_LOG_WARN (this << " Unexpected type of packet received during this state" << state  << " " << msgTypeTag.GetMsgType ());
  }

}

void LoRaWANEndDeviceApplication::ConnectionSucceeded (Ptr<Socket> socket)
{
  NS_LOG_FUNCTION (this << socket);
  m_connected = true;
}

void LoRaWANEndDeviceApplication::ConnectionFailed (Ptr<Socket> socket)
{
  NS_LOG_FUNCTION (this << socket);
  NS_FATAL_ERROR (this << " Connection failed");
}
void
LoRaWANEndDeviceApplication::EnlargeWindowTimeout ()
{
  // Update beacon movement
    m_BeaconWindowMovement *= CLASSB_WINDOW_MOVE_EXPANSION_FACTOR;
    if( m_BeaconWindowMovement > CLASSB_WINDOW_MOVE_EXPANSION_MAX )
    {
        m_BeaconWindowMovement = CLASSB_WINDOW_MOVE_EXPANSION_MAX;
    }
    // Update symbol timeout
    m_BeaconSymbolTimeout *= CLASSB_BEACON_SYMBOL_TO_EXPANSION_FACTOR;
    if(  m_BeaconSymbolTimeout > CLASSB_BEACON_SYMBOL_TO_EXPANSION_MAX )
    {
         m_BeaconSymbolTimeout = CLASSB_BEACON_SYMBOL_TO_EXPANSION_MAX;
    }
    m_PingSymbolTimeout *= CLASSB_BEACON_SYMBOL_TO_EXPANSION_FACTOR;
    if( m_PingSymbolTimeout > CLASSB_PING_SLOT_SYMBOL_TO_EXPANSION_MAX )
    {
        m_PingSymbolTimeout = CLASSB_PING_SLOT_SYMBOL_TO_EXPANSION_MAX;
    }
}

void
LoRaWANEndDeviceApplication::ResetWindowTimeout ()
{
    m_BeaconSymbolTimeout = CLASSB_BEACON_SYMBOL_TO_DEFAULT;
    m_PingSymbolTimeout = CLASSB_BEACON_SYMBOL_TO_DEFAULT;
    m_BeaconWindowMovement  = CLASSB_WINDOW_MOVE_DEFAULT;
}

void
LoRaWANEndDeviceApplication::ClassBReceiveBeacon ()
{
  NS_LOG_FUNCTION (this << " ED: attempt to receive beacon at" << Simulator::Now ().GetSeconds () );
  NS_LOG_DEBUG (this << " ED: attempt to receive beacon at" << Simulator::Now ().GetSeconds () );

  Ptr<LoRaWANNetDevice> netDevice = DynamicCast<LoRaWANNetDevice> (GetNode ()->GetDevice (0));
  netDevice->StartReceivingBeacon();
  m_timestamp = Seconds (0);
  Time t_pingSlots;
  t_pingSlots = MilliSeconds((uint64_t)2120);
 /*
  if (m_missedBeaconsCounter == 0) {
      
		//if the preamble is detected then we add the required amount to get the rest of the beacon frame 
    Time RXerror = 1.5 * m_tSymbol; //relocate this somewhere else where maybe as initialized
    Time RXwindow = 2 * m_tSymbol + 2 * RXerror; 
    Time RXoffset = 4 * m_tSymbol + (RXwindow * -.5);
    t_pingSlots = RXwindow + RXoffset;  //Since ns3 cannot simulate timed functions we implemented WindowOffset and WindowTimeout together. Ns3 is a discrete simulator. 
      // no BeaconWindowMovement
    }
  else 
  {
    NS_LOG_DEBUG(this << "Beaconless Mode Activated. Expanding Beacon Window to: " << m_BeaconSymbolTimeout);
    t_pingSlots = MilliSeconds(m_BeaconSymbolTimeout);
  }
  if (m_ClassBfcntBeacon == 0) // if its first time to synchronized with the beacon then we give the whole 2120 (beacon_reserved)
  {
    t_pingSlots = MilliSeconds(2120);//MilliSeconds((uint64_t)173.056);
  }
  */
  /*
    // For this simulator, a constant Rxerror because the system wouldn't work without this. Becaause the minimum RXwindow must be at least 5 symbols long, the system always tolerates at least an RXerror of at least 1.5 x Tsymbol
      MAKE SURE THAT ITS UNDER 2120 ms (before the reserve endsss)
  */
  NS_LOG_DEBUG(this << "ED : Beacon Recieving Window: " << t_pingSlots.GetMilliSeconds() << " ms");
  //Time t_pingSlots =  MilliSeconds((uint64_t)173.056); // Time to receive a LoRaWAN beacon frame (17 bytes, SF9, no LoRaWAN header - calculated via LoRaWAN Calculator) TODO: magic number Have to create this for ping slots
  //Time t_pingSlots = MilliSeconds((uint64_t)2120); //2120// BEACON RESERVED RATED IS 2120 Linked Layer LoRaWAN
  Simulator::Schedule(t_pingSlots, &LoRaWANEndDeviceApplication::ClassBSchedulePingSlots, this); //schedule next ping slots 
  NS_LOG_DEBUG(this << "ED: CLASS B PING SLOTS STARTS: " << t_pingSlots); 
  //schedule next beacon receive.
  /*
  Time t = Seconds(125); 
  // Need to to implement the Window Expansions and Movement here;
  m_GuardTimer = Simulator::Schedule (t, &LoRaWANEndDeviceApplication::ClassBStartGuardWindow, this); 
  NS_LOG_DEBUG (this << " ED: Class B beacon Guard" << "scheduled in " << t );
  */
}

void LoRaWANEndDeviceApplication::ClassBStartGuardWindow ()
{
  
  //No Guard
  Time t = Seconds (3); //+ MicroSeconds(1500); //BeaconDelay 
  NS_LOG_DEBUG (this << " ED: Class B beacon " << "scheduled at " << t);
  m_beaconTimer = Simulator::Schedule (t, &LoRaWANEndDeviceApplication::ClassBReceiveBeacon, this);
  } 


void
LoRaWANEndDeviceApplication::ClassBSchedulePingSlots ()
{
    NS_LOG_DEBUG(" ED timestamp is " << m_timestamp);
    if (m_timestamp.IsZero()) {
      //no beacon was received this time
       m_missedBeaconsCounter++; 
      Time currentTime = m_lastbeaconReceived + Seconds(128*m_missedBeaconsCounter);
     
      if (m_missedBeaconsCounter == 1 )
      {
        m_missedBeaconsTimer = m_lastbeaconReceived;//Simulator::Now(); 
      }
      //TODO: increase reception window of all rx slots progressively to account for clock drift without beacon frames
      // ms
      // "A device shall be capable of maintaining Class B operation for 2 hours (120 minutes) after it received the last beacon" = 7200seconds = 56.25 beacon periods  
      if(currentTime - m_missedBeaconsTimer < MilliSeconds((uint64_t)7200000)){//Simulator::Now() - m_missedBeaconsTimer < MilliSeconds((uint64_t)7200000)){ //m_missedBeaconsCounter < 57
        //Simulator::Now() - m_missedBeaconsTimer < MilliSeconds((uint64_t)7200000
        //if we haven't missed so many beacons (so the internal clock is still reliable), generate the expected offset (should be calculatable if time sync isn't too far off) and generate the ping slots anyway
        //m_timestamp = Simulator::Now() - MilliSeconds((uint64_t)173.056);  // Time to receive a LoRaWAN beacon frame (17 bytes, SF9, no LoRaWAN header - calculated via LoRaWAN Calculator) 
        //
        EnlargeWindowTimeout();
        m_timestamp = currentTime;//Simulator::Now(); // - MilliSeconds((uint64_t)2120); // BEACON_RESERVED IS USED TO ALLOW FOR FUTURE IMPLEMENTATIONS
        NS_LOG_DEBUG("end device missed beacon frame, generated timestamp is: " << m_timestamp.GetSeconds() );

      } else {
        NS_LOG_DEBUG(" ED: missed too many beacons, device turning to Class A mode: " << Simulator::Now());
        // If no beacon has been received for a given period (2 hours), synchronisation with the network is lost - the device has to change back to Class A
        // i.e. stop setting the Class B bit in uplink frames.
        // the end device can try to swap back to Class B periodically (i.e. via a beacon search - not currently implemented)
        m_isClassB = false; // this setting gets passed as a bit in the next uplink frame, telling the NS to stop scheduling pings for this device.
        //m_txEvent = Simulator::Schedule (MilliSeconds(1),
                                       //&LoRaWANEndDeviceApplication::SendPacket, this);//To inform gateway its a class A device now
        Simulator::Cancel(m_beaconTimer);
        Simulator::Cancel(m_GuardTimer);                     // Needs to stop calculating a Beacon Signals 
        //and don't attempt to calculate ping slots
        return;
      }
    } 
    else {
      m_lastbeaconReceived = m_timestamp;
      ResetWindowTimeout(); // beaconWindow was created 
      //beacon was successfully received, use the timestamp contained within
      m_missedBeaconsCounter = 0;
      m_missedBeaconsTimer = MilliSeconds(0); 
      NS_LOG_DEBUG(" ED:beacon was received successfully");

      //TODO: and reset the reception window length (as the timestamp can be used to reset the clock)
      //issue with this though: the timestamp in the packet isn't THAT precise (it's in seconds).
    }

    NS_LOG_WARN(" ED: timestamp is: " << m_timestamp.GetSeconds() );

    uint64_t period = std::pow(2.0, 12) / m_ClassBPingSlots;;   
    uint8_t key[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // the key. Encryption of packets isn't fully supported right now so assuming a key of all 0s.
    uint8_t buf[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    // add time from beacon frame to buffer
    double secs = m_timestamp.GetSeconds(); // convert to a 4 byte buffer 
    uint32_t secsTruncated = (uint32_t) secs;

    uint8_t *sp = (uint8_t *)&secsTruncated;
    buf[0] = sp[0];
    buf[1] = sp[1];
    buf[2] = sp[2];
    buf[3] = sp[3];
    
    // add own node address to buffer
    Ipv4Address devAddr = Ipv4Address::ConvertFrom (GetNode ()->GetDevice (0)->GetAddress ());
    NS_LOG_DEBUG(this << "ed: device address is: " << devAddr );    
    uint8_t addr[4];
    devAddr.Serialize(addr);
    buf[4] = addr[0];
    buf[5] = addr[1];
    buf[6] = addr[2];
    buf[7] = addr[3];
    
    //pad16 is to ensure the buffer is 16 bytes long
    //the rest of the buffer (the other 8 bytes) is just 0s.
    for(uint i=8; i<16;i++){
      buf[i] = 0;
    }

    AES aes;
    aes.SetKey(key, 16);
    aes.Encrypt(buf, 16);
    uint64_t O; 
    if (m_offsetOn == 1){
       O = (buf[0] + buf[1]*256) % period;
        //NS_LOG_WARN (" ENO: " << O << " Buf[0]: " << (char)buf[0] << " buf[1]: "<< (char)buf[1]);
    }
    else {
      O = 0; 
    }
    NS_LOG_DEBUG(this << "PingOffset:" << O  );    
    uint32_t beacon_reserved = 2120; 
    uint32_t slotLength = 30; // ms
    uint32_t dAddr = (uint32_t) devAddr.Get ();

    //calculate and schedule ping slots for this device

    //on the end device pingTime factors in the time in between the given timestamp and now
    NS_LOG_DEBUG(" m_timestamp: "<< m_timestamp << " Simulator::Now(): " << Simulator::Now());
    //offset helps simulate the end device internal clocks
    Time offset = Simulator::Now() - m_timestamp;

    Time t = Seconds(125);
    t-=offset;
    // Need to to implement the Window Expansions and Movement here;
    m_GuardTimer = Simulator::Schedule (t, &LoRaWANEndDeviceApplication::ClassBStartGuardWindow, this); 

    // Ping slot must be less the guard window
    NS_LOG_DEBUG("ED: Scheduling ping slots for device" << devAddr.Get ());
    for(uint i=0;i< m_ClassBPingSlots; i++){
      uint64_t pingTime = beacon_reserved + (O + period*i) * slotLength; // Ping slot time is (beacon_reserved- + (pingOffset + N*pingPeriod) * slotLength
      Time ping = MilliSeconds(pingTime);
      ping -= offset;
      //NS_LOG_WARN(" ED PingSlot Offset Slot: " << O + period*i); 
      NS_LOG_DEBUG(this << " ED : ping slot for device " << dAddr << " is at " << Simulator::Now() + ping);
      Simulator::Schedule (ping, &LoRaWANEndDeviceApplication::ClassBPingSlot, this);
    }
}

void
LoRaWANEndDeviceApplication::ClassBPingSlot ()
{
  NS_LOG_FUNCTION(this << "ED: Start a ping slot");
  //attempt to receive a packet from the NS
  NS_LOG_DEBUG(" ED: Start of a ping slot");

  Ptr<LoRaWANNetDevice> netDevice = DynamicCast<LoRaWANNetDevice> (GetNode ()->GetDevice (0));
  netDevice->StartReceivingClassBPacket(m_ClassBChannelIndex, m_ClassBDataRateIndex, m_ClassBCodeRateIndex);
}
bool LoRaWANEndDeviceApplication::SetBeaconSymbolTimeoutExpF(uint16_t beaconSymbolTimeoutEx)
{
  Ptr<LoRaWANNetDevice> netDevice = DynamicCast<LoRaWANNetDevice> (GetNode ()->GetDevice (0));
  return netDevice->GetPhy()->SetBeaconSymbolTimeoutExpF(beaconSymbolTimeoutEx);
}

void
LoRaWANEndDeviceApplication::PrintFinalDetails ()
{
  std::cout << "m_devAddr: " << m_devAddr << "\t" <<  "m_attemptedThroughput: " << m_attemptedThroughput <<  "\t" << "m_fcntRX1: " << m_fcntRX1 << "\t" << "m_fcntRX2: "<< m_fcntRX2 << "\t" << "m_ClassBfcntDown: " << m_ClassBfcntDown << "\t" << "m_ClassBfcntBeacon: " << m_ClassBfcntBeacon << "\t" << "m_ClassBPingPeriodicity: " << (int)m_ClassBPingPeriodicity << std::endl;
}

} // Namespace ns3
