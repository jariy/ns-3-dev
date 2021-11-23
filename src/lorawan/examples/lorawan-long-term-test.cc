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

/*
 * Try to send data from two class A end devices to a gateway, data is
 * unconfirmed upstream data. Chain is LoRaWANMac -> LoRaWANPhy ->
 * SpectrumChannel -> LoRaWANPhy -> LoRaWANMac
 *
 * Trace Phy state changes, and Mac DataIndication and DataConfirm events
 * to stdout
 */
#include <ns3/log.h>
#include <ns3/core-module.h>
#include <ns3/network-module.h>
#include <ns3/ipv4-address.h>
#include <ns3/lorawan-module.h>
#include <ns3/propagation-loss-model.h>
#include <ns3/propagation-delay-model.h>
#include <ns3/mobility-module.h>
#include <ns3/applications-module.h>
#include <ns3/simulator.h>
#include <ns3/single-model-spectrum-channel.h>
#include <ns3/constant-position-mobility-model.h>
#include <ns3/node.h>
#include <ns3/packet.h>
#include "ns3/netanim-module.h"
#include <iomanip> 
#include "ns3/traced-value.h"
#include "ns3/trace-source-accessor.h"

#include <iostream>

using namespace ns3;


NS_LOG_COMPONENT_DEFINE ("LORAWAN_EXAMPLE");


class LoRaWANLongTermTest
{
  public: 
    LoRaWANLongTermTest(); 
    void CaseRun(uint32_t nEndDevices,
               uint32_t nGateways,
               double discRadius,
               double totalTime,
               uint32_t usPacketSize,
               uint32_t usMaxBytes,
               double usDataPeriod,
               uint32_t usUnconfirmedDataNbRep,
               bool usConfirmedData,
               uint32_t dsPacketSize,
               bool dsDataGenerate,
               double dsDataExpMean,
               bool dsConfirmedData,
               uint64_t maliciousTime, //in microsseconds
               double symbolsMalicious,//in symbols Malicious delays
               uint8_t pingPeriod,
               bool SinglePingTest, 
               bool MultiplePingTest, 
               bool SinglebeaconlessTest, 
               bool MultiplebeaconlessTest,
               bool verbose,
              std::string ClassBPacketsSentCSVFileName,
              std::string ClassBPacketsRecievedCSVFileName,
              std::string numberofBeaconsCSVFileName,
              std::string nodesCSVFileName,
              double classBDST,
              double classBInDS,
              bool   offsetOn); 
    void LogOutputLine(std::string output, std::string fileName);

    //void SinglePingTest();
    //void MultiplePingTest(); 

    //void SingleBeaconlessTest(); 
    //void MultipleBeaconlessTest(); 
    
    //Tracing Counters 
    std::ostringstream GenerateBeaconlessOutputLine (std::string traceSource, Ptr<LoRaWANNetDevice> device, Ptr<LoRaWANPhy> phy, Ptr<const Packet> packet, bool insertNewLine = true);
    static void ClassBPacketsSentTracing(LoRaWANLongTermTest* example, uint32_t deviceAddr, uint32_t ClassBPacketsSent, uint32_t MicroSeconds,uint64_t UID);
    static void ClassBPacketsRecievedTracing(LoRaWANLongTermTest* example, uint32_t deviceAddr, uint32_t ClassBPacketsRecieved, uint32_t MicroSeconds,uint64_t UID);
    static void BeaconCounterTracing(LoRaWANLongTermTest* example, uint32_t deviceAddr, uint32_t numberofBeacons);    
    private:
      uint32_t m_nEndDevices;
      uint32_t m_nGateways;
      double m_discRadius;
      double m_totalTime;
      uint32_t maliciousDelay; //from the start of the simulation when to send malicious Delay in seconds
      double symbolsMalicious;//in symbols Malicious delays
      uint8_t pingPeriod;

      uint32_t m_usPacketSize;
      uint32_t m_usMaxBytes;
      double m_usDataPeriod; // <! Period between subsequent data transmission of end devices
      uint32_t m_usUnconfirmedDataNbRep;
      bool m_usConfirmdData;

      double m_ClassBInDS = 300; // Interval between each ClassB transmission 
      double m_ClassBDST = 300; // random Time between each ClassB Transmission

      bool m_verbose;

      std::string m_ClassBPacketsSentCSVFileName;
      std::string m_ClassBPacketsRecievedCSVFileName;
      std::string m_numberofBeaconsCSVFileName;
      std::string m_nodesCSVFileName;
      std::map<std::string, std::ofstream> output_streams;

      uint32_t m_dsPacketSize;
      bool m_dsDataGenerate;
      double m_dsDataExpMean;
      bool m_dsConfirmedData;


      // Can only turn on one test at a time
      bool SinglePingTest; 
      bool MultiplePingTest;

      bool SinglebeaconlessTest;
      bool MultiplebeaconlessTest;  

      std::map<uint32_t,uint32_t> m_numberofBeacons; // number of beacons recieved by each end device (key=devAddress,m_numberofBeacons)
      std::map<uint32_t,uint32_t> m_ClassBPacketsSent; // number of packets sents to each end devices (key= devAddr,v = m_ClassBPacketsSent)
      std::map<uint32_t,uint32_t> m_ClassBPacketsRecieved; // number of packets received by each end devices  (key= devAddr,v = m_ClassBPacketsRecieved)

      uint64_t m_maliciousTime; //in seconds
      double m_symbolsMalicious;//in symbols Malicious delays
      uint8_t m_pingPeriod;
      bool m_offsetOn; //determine if you want the ping offset calculation on

      NodeContainer m_endDeviceNodes;
      NodeContainer m_gatewayNodes;
      NodeContainer m_allNodes;
      NetDeviceContainer m_EDDevices;
      NetDeviceContainer m_GWDevices;


      void CreateNodes ();
      void SetupMobility ();
      void CreateDevices ();
      void SetupTracing (bool SinglePingTest, bool MultiplePingTest, bool SinglebeaconlessTest, bool MultiplebeaconlessTest);
      void InstallApplications ();
      void OutputNodes ();
      void FinalResults(); 

};
LoRaWANLongTermTest::LoRaWANLongTermTest(){
  std::cout << "Initialiing LongTerm /n"; 
} 
void 
LoRaWANLongTermTest::CaseRun(uint32_t nEndDevices,
               uint32_t nGateways,
               double discRadius,
               double totalTime,
               uint32_t usPacketSize,
               uint32_t usMaxBytes,
               double usDataPeriod,
               uint32_t usUnconfirmedDataNbRep,
               bool usConfirmedData,
               uint32_t dsPacketSize,
               bool dsDataGenerate,
               double dsDataExpMean,
               bool dsConfirmedData,
               uint64_t maliciousTime, //in microsseconds
               double symbolsMalicious,//in symbols Malicious delays
               uint8_t pingPeriod,
               bool t_SinglePingTest, 
               bool t_MultiplePingTest, 
               bool t_SinglebeaconlessTest, 
               bool t_MultiplebeaconlessTest,
               bool verbose,
              std::string ClassBPacketsSentCSVFileName,
              std::string ClassBPacketsRecievedCSVFileName,
              std::string numberofBeaconsCSVFileName,
              std::string nodesCSVFileName,
              double classBDST,
              double classBInDS,
              bool   offsetOn)
{
  m_nEndDevices = nEndDevices;
  m_nGateways = nGateways;
  m_discRadius = discRadius;
  m_totalTime = totalTime;
  m_verbose = verbose; 
  m_maliciousTime = maliciousTime; //in microseconds
  m_symbolsMalicious = symbolsMalicious; //in symbols Malicious delays
  m_pingPeriod = pingPeriod;

  SinglebeaconlessTest = t_SinglebeaconlessTest;
  SinglePingTest = t_SinglePingTest;
  MultiplePingTest = t_MultiplePingTest;
  MultiplebeaconlessTest = t_MultiplebeaconlessTest;

  m_usPacketSize = usPacketSize;
  m_usMaxBytes = usMaxBytes;
  m_usDataPeriod = usDataPeriod;
  m_usUnconfirmedDataNbRep = usUnconfirmedDataNbRep;
  m_usConfirmdData = usConfirmedData;

  m_ClassBDST = classBDST; 
  m_ClassBInDS = classBInDS; 

  m_offsetOn = offsetOn; 

  m_ClassBPacketsSentCSVFileName = ClassBPacketsSentCSVFileName;
  m_ClassBPacketsRecievedCSVFileName = ClassBPacketsRecievedCSVFileName;
  m_numberofBeaconsCSVFileName = numberofBeaconsCSVFileName;
  m_nodesCSVFileName = nodesCSVFileName;

  CreateNodes ();
  SetupMobility (); // important: setup mobility before creating devices
  CreateDevices ();
  InstallApplications ();
  SetupTracing(SinglePingTest,MultiplePingTest,SinglebeaconlessTest,MultiplebeaconlessTest);
  OutputNodes ();

  std::cout << "Starting simulation for " << m_totalTime << " s ...\n";
  Simulator::Stop (Seconds (m_totalTime));
  Simulator::Run ();
  void FinalResults(); 
  Simulator::Destroy ();
}

void 
LoRaWANLongTermTest::CreateNodes()
{
  std::cout << "Creating " << (unsigned) m_nGateways << " LoRaWAN gateway(s).\n";
  m_gatewayNodes.Create (m_nGateways);

  std::cout << "Creating " << (unsigned) m_nEndDevices << " LoRaWAN class B end devices.\n";
  m_endDeviceNodes.Create (m_nEndDevices);

  m_allNodes.Add (m_gatewayNodes);
  m_allNodes.Add (m_endDeviceNodes);
}

void
LoRaWANLongTermTest::SetupMobility ()
{
  MobilityHelper edMobility;
  edMobility.SetPositionAllocator ("ns3::UniformDiscPositionAllocator",
                                    "X", DoubleValue (0.0),
                                    "Y", DoubleValue (0.0),
                                    "rho", DoubleValue (m_discRadius));
  edMobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  edMobility.Install (m_endDeviceNodes);

  MobilityHelper gwMobility;
  Ptr<ListPositionAllocator> nodePositionList = CreateObject<ListPositionAllocator> ();
  for (uint32_t i = 0; i < m_nGateways; i++) {
    Vector v;
    if (m_nGateways == 1) {
      v = Vector (0.0, 0.0, 0.0); // place gateway in center
    } else if (m_nGateways == 2) {
      v = Vector (-m_discRadius/2 + i*m_discRadius, 0.0, 0.0);  // place gateways on (-discRadius/2, 0) and (discRadius/2, 0)
    } else if (m_nGateways == 4) {
      // place gateways on (-discRadius/2, -discRadius/2) and (discRadius/2, -discRadius/2) and (-discRadius/2, discRadius/2) and (discRadius/2, discRadius/2)
      v = Vector (-m_discRadius/2 + (i/2)*m_discRadius, -m_discRadius/2 + (i % 2)*m_discRadius, 0.0);
    } else if (m_nGateways == 9) {
       if (i < 4) {
         // place four gateways on (-discRadius/2, -discRadius/2) and (discRadius/2, -discRadius/2) and (-discRadius/2, discRadius/2) and (discRadius/2, discRadius/2)
         v = Vector (-m_discRadius/2 + (i/2)*m_discRadius, -m_discRadius/2 + (i % 2)*m_discRadius, 0.0);
       } else if (i == 4) {
         // place one gateways in center
         v = Vector (0.0, 0.0, 0.0); // place gateway in center
       } else {
         // place four gateways on (-discRadius, 0) and (discRadius, 0) and (0, discRadius) and (0, -discRadius)
         if (i == 5) {
           v = Vector (-m_discRadius, 0.0, 0.0);
         } else if (i == 6) {
           v = Vector (m_discRadius, 0.0, 0.0);
         } else if (i == 7) {
           v = Vector (0.0, m_discRadius, 0.0);
         } else if (i == 8) {
           v = Vector (0.0, -m_discRadius, 0.0);
         }
       }
    } else {
      NS_FATAL_ERROR (this << " " << m_nGateways << " number of gateways is not supported");
      exit (-1);
    }

    nodePositionList->Add (v);
  }

  gwMobility.SetPositionAllocator (nodePositionList);
  gwMobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  gwMobility.Install (m_gatewayNodes);
}

void
LoRaWANLongTermTest::CreateDevices ()
{
  LoRaWANHelper lorawanHelper;
  uint32_t netID = 000013;
  int type = 0;
  if (m_verbose)
    lorawanHelper.EnableLogComponents (LOG_LEVEL_INFO);
  else
    lorawanHelper.EnableLogComponents (LOG_LEVEL_WARN);

  lorawanHelper.SetNbRep (m_usUnconfirmedDataNbRep);
  m_EDDevices = lorawanHelper.Install (m_endDeviceNodes);

  lorawanHelper.SetDeviceType (LORAWAN_DT_GATEWAY);
  m_GWDevices = lorawanHelper.Install (m_gatewayNodes);

}
void
LoRaWANLongTermTest::LogOutputLine (std::string output, std::string fileName)
{
  if (this->m_verbose) 
    std::cout << output;

  std::ofstream & outputstream = output_streams[fileName];   // creates the stream object and returns reference
  if (!outputstream.is_open()) {
    outputstream.open(fileName.c_str(), std::ios::app);
  }
  if (outputstream.is_open()) {
    outputstream << output;
  }
}
void
LoRaWANLongTermTest::InstallApplications(){
  PacketSocketHelper packetSocket;
  packetSocket.Install (m_endDeviceNodes); // TODO: replace two lines with m_allNodes?
  packetSocket.Install (m_gatewayNodes);

  // Gateways and Network Server:
  ApplicationContainer gatewayApps;
  ObjectFactory m_factory2; //!< Object factory.
  m_factory2.SetTypeId ("ns3::LoRaWANGatewayApplication");
  for (NodeContainer::Iterator i = m_gatewayNodes.Begin (); i != m_gatewayNodes.End (); ++i)
    {
      Ptr<Node> node = *i;
      Ptr<Application> app = m_factory2.Create<Application> ();
      node->AddApplication (app);
      gatewayApps.Add (app);
      //Ptr<LoRaWANGatewayApplication> gwApp = DynamicCast<LoRaWANGatewayApplication> (app);
    }

  gatewayApps.Start (Seconds (0.0));
  gatewayApps.Stop (Seconds (m_totalTime));

  // Set attributes on LoRaWANNetworkServer object:
  Ptr<LoRaWANNetworkServer> lorawanNSPtr = LoRaWANNetworkServer::getLoRaWANNetworkServerPointer ();
  NS_ASSERT (lorawanNSPtr);
  if (lorawanNSPtr) {
    /*
    std::stringstream downstreamiatss;
    downstreamiatss << "ns3::ExponentialRandomVariable[Mean=" << m_dsDataExpMean << "]";
    lorawanNSPtr->SetAttribute ("DownstreamIAT", StringValue (downstreamiatss.str ()));
    */
    std::stringstream ClassINdownstreamiatss;
    ClassINdownstreamiatss << "ns3::ConstantRandomVariable[Constant=" << m_ClassBInDS << "]";
    lorawanNSPtr->SetAttribute("ClassBDownstreamIAT", StringValue(ClassINdownstreamiatss.str()));

    std::stringstream ClassBTRdownstreamiatss;
    ClassBTRdownstreamiatss << "ns3::UniformRandomVariable[Min=" << m_ClassBDST -1 << "|Max=" << m_ClassBDST << "]";
    std::cout << ClassBTRdownstreamiatss.str() << std::endl;
    lorawanNSPtr->SetAttribute("ClassBDownstream", StringValue(ClassBTRdownstreamiatss.str()));
    lorawanNSPtr->SetAttribute("maliciousDelaySymbol",DoubleValue(m_symbolsMalicious));
    lorawanNSPtr->SetAttribute("startMaliciousAttack",UintegerValue(m_maliciousTime));
    lorawanNSPtr->SetAttribute ("PacketSize", UintegerValue (m_dsPacketSize));
    lorawanNSPtr->SetAttribute ("GenerateDataDown", BooleanValue (false/*m_dsDataGenerate*/));
    lorawanNSPtr->SetAttribute ("ConfirmedDataDown", BooleanValue (m_dsConfirmedData));
    lorawanNSPtr->SetAttribute  ("OffsetON",BooleanValue(m_offsetOn));


  }

  // End devices:
  ApplicationContainer endDeviceApp;
  ObjectFactory m_factory; //!< Object factory.
  m_factory.SetTypeId ("ns3::LoRaWANEndDeviceApplication");
  // Attributes shared by all end device apps:
  m_factory.Set ("PacketSize", UintegerValue (m_usPacketSize));
  m_factory.Set ("MaxBytes", UintegerValue (m_usMaxBytes));
  m_factory.Set ("ConfirmedDataUp", BooleanValue (m_usConfirmdData));
  m_factory.Set ("IsClassB", BooleanValue(true)); 
  m_factory.Set ("OffsetON",BooleanValue(m_offsetOn));
  /*
  std::stringstream upstreamiatss;
  upstreamiatss << "ns3::ConstantRandomVariable[Constant=" << m_usDataPeriod << "]";
  m_factory.Set ("UpstreamIAT", StringValue (upstreamiatss.str ()));
  */
  // Limit the number of channels
  //m_factory.Set ("ChannelRandomVariable", StringValue ("ns3::ConstantRandomVariable[Constant=0.0]"));

  int counter = 0;   
  for (NodeContainer::Iterator i = m_endDeviceNodes.Begin (); i != m_endDeviceNodes.End (); ++i)
  {
      if (MultiplePingTest && SinglePingTest)
      {
        NS_LOG_ERROR("Cannot select both MultiplePingTest and SinglePingTest");
      }
      if (MultiplePingTest)
      {
        if (counter > m_pingPeriod)
        {
          counter = 0; 
        }
        m_factory.Set("ClassBPingPeriodicity",UintegerValue(counter));
      }
      if (SinglePingTest) 
      {
        m_factory.Set("ClassBPingPeriodicity",UintegerValue(m_pingPeriod));
      }
      Ptr<Node> node = *i;
      Ptr<Application> app = m_factory.Create<Application> ();
      node->AddApplication (app);

      // Start the end device apps at the same times:
      app->SetStartTime (Seconds (0));
      app->SetStopTime(Seconds (m_totalTime));

      endDeviceApp.Add (app);
      counter++; 
  }
}

void
LoRaWANLongTermTest::OutputNodes()
{
  std::ofstream outNodes (m_nodesCSVFileName.c_str (), std::ios::app);
  // Output For Gateways: nodeid, device type, x, y
  for (NodeContainer::Iterator i = m_gatewayNodes.Begin (); i != m_gatewayNodes.End (); ++i)
  {
    Ptr<Node> node = *i;
    Ptr<LoRaWANNetDevice> netDevice = DynamicCast<LoRaWANNetDevice> (node->GetDevice (0));
    Ptr<MobilityModel> gatewayMobility = node->GetObject<MobilityModel> ();
    NS_ASSERT (gatewayMobility);
    Vector gatewayPos = gatewayMobility->GetPosition ();

    outNodes
      << node->GetId () << ","
      << netDevice->GetDeviceType () << ","
      << gatewayPos.x << ","
      << gatewayPos.y << std::endl;
  }

  // Output For End Devices: nodeid, device type, x, y, distancetoclosestgateway, datarateindex
  for (NodeContainer::Iterator i = m_endDeviceNodes.Begin (); i != m_endDeviceNodes.End (); ++i)
  {
    Ptr<Node> node = *i;
    Ptr<LoRaWANNetDevice> netDevice = DynamicCast<LoRaWANNetDevice> (node->GetDevice (0));

    Ptr<MobilityModel> endDeviceMobility = node->GetObject<MobilityModel> ();
    NS_ASSERT (endDeviceMobility);
    Vector endDevicePos = endDeviceMobility->GetPosition ();

    // find distance to the closest gateway:
    Vector closestGwPos; // to be determined
    double dmin = std::numeric_limits<double>::max ();
    {
    for (NodeContainer::Iterator it_gw = m_gatewayNodes.Begin (); it_gw != m_gatewayNodes.End (); ++it_gw)
    {
      Ptr<MobilityModel> gatewayMobility = (*it_gw)->GetObject<MobilityModel> ();
      NS_ASSERT (gatewayMobility);
      Vector gwPos = gatewayMobility->GetPosition ();

      double distance = CalculateDistance (endDevicePos, gwPos);
      if (distance < dmin) {
        dmin = distance;
        closestGwPos = gwPos;
      }
    }
    }
    Ipv4Address myAddress = Ipv4Address::ConvertFrom (node->GetDevice (0)->GetAddress ());
    uint32_t deviceAddress = myAddress.Get ();
    Ptr<LoRaWANEndDeviceApplication> edApp = node->GetApplication (0)->GetObject<LoRaWANEndDeviceApplication> ();
    uint8_t pingPeriodicity = edApp->GetClassBPingPeriodicity();

    outNodes
      << deviceAddress<< ","
      << netDevice->GetDeviceType () << ","
      << endDevicePos.x << ","
      << endDevicePos.y << ","
      << dmin << ","
      << (uint32_t)pingPeriodicity << std::endl;
  }

}
void
LoRaWANLongTermTest::SetupTracing(bool SinglePingTest, bool MultiplePingTest, bool SinglebeaconlessTest, bool MultiplebeaconlessTest)
{
  Ptr<LoRaWANNetworkServer> lorawanNSPtr = LoRaWANNetworkServer::getLoRaWANNetworkServerPointer ();
  NS_ASSERT (lorawanNSPtr);
  if (lorawanNSPtr) {
    lorawanNSPtr->TraceConnectWithoutContext ("ClassBPacketsSentTrace", MakeBoundCallback (&LoRaWANLongTermTest::ClassBPacketsSentTracing, this));
  }
  for (NodeContainer::Iterator i = m_endDeviceNodes.Begin (); i != m_endDeviceNodes.End (); ++i)
  {
      Ptr<Node> node = *i;
      NS_ASSERT (node != 0);
      Ptr<LoRaWANEndDeviceApplication> edApp = node->GetApplication (0)->GetObject<LoRaWANEndDeviceApplication> ();
      edApp->TraceConnectWithoutContext ("ClassBPacketReceivedTrace", MakeBoundCallback (&LoRaWANLongTermTest::ClassBPacketsRecievedTracing, this));
      edApp->TraceConnectWithoutContext ("ClassBBeaconReceivedTrace", MakeBoundCallback (&LoRaWANLongTermTest::BeaconCounterTracing, this));
  }
}

void
LoRaWANLongTermTest::ClassBPacketsSentTracing(LoRaWANLongTermTest* example, uint32_t deviceAddr, uint32_t ClassBPacketsSent, uint32_t MicroSeconds, uint64_t UID){
  example->m_ClassBPacketsSent[deviceAddr] = ClassBPacketsSent;
  std::ostringstream output;
  output << std::setiosflags (std::ios::fixed) << std::setprecision (9) << MicroSeconds << ","
    << deviceAddr << ","
    << ClassBPacketsSent << "," << UID << std::endl;
  /*
  if (example->m_verbose)
  {
    std::cout << "Time (ms): " << MicroSeconds << " NS sent Class B Packets to devAddress: " << deviceAddr << " Total ClassBPacketsSent: " << ClassBPacketsSent << " /n";
  }
  */
  example->LogOutputLine(output.str(),example->m_ClassBPacketsSentCSVFileName);
}

void 
LoRaWANLongTermTest::ClassBPacketsRecievedTracing(LoRaWANLongTermTest* example, uint32_t deviceAddr, uint32_t ClassBPacketsRecieved, uint32_t MicroSeconds, uint64_t UID){
  example->m_ClassBPacketsRecieved[deviceAddr] = ClassBPacketsRecieved;
  std::ostringstream output;
  output << std::setiosflags (std::ios::fixed) << std::setprecision (9) << MicroSeconds << ","
    << deviceAddr << ","
    << ClassBPacketsRecieved << "," << UID << std::endl;
  /*
  if (example->m_verbose)
  {
    std::cout << "Time (ms): " << MicroSeconds << " Received Class B Packets to devAddress: " << deviceAddr << " Total ClassBPacketsSent: " << ClassBPacketsRecieved << " /n";
  }
  */
  example->LogOutputLine(output.str(),example->m_ClassBPacketsRecievedCSVFileName);
}

void 
LoRaWANLongTermTest::BeaconCounterTracing(LoRaWANLongTermTest* example, uint32_t deviceAddr, uint32_t numberofBeacons){
  example->m_numberofBeacons[deviceAddr] = numberofBeacons;
  /* 
  if (example->m_verbose)
  {
    std::cout 
  }
  */
  std::ostringstream output;
  output << std::setiosflags (std::ios::fixed) << std::setprecision (9) << Simulator::Now ().GetMicroSeconds () << ","
    << deviceAddr << ","
    << numberofBeacons << std::endl;
  example->LogOutputLine(output.str(),example->m_numberofBeaconsCSVFileName);
}



void
ReceivePacket (Ptr<Socket> socket)
{
  Ptr<Packet> packet;
  uint64_t bytes = 0;
  while ((packet = socket->Recv ()))
    {
      bytes += packet->GetSize ();
    }

  NS_LOG_LOGIC("SOCKET received " << bytes << " bytes");

}


int main (int argc, char *argv[])
{
  ns3::Packet::EnablePrinting();
  uint32_t randomSeed = 12345;
  uint32_t nEndDevices = 1;
  uint32_t nGateways = 9;
  double discRadius = 5000.0;
  double totalTime = 6000.0; 
  uint32_t nRuns = 1;
  double ClassBInDS = 100; 
  double ClassBDST = 100; 
  //uint32_t drCalcMethodIndex = 0;
  //double drCalcPerLimit = 0.01;
  //double drCalcFixedDRIndex = 0;
  uint32_t usPacketSize = 21;
  uint32_t usMaxBytes = 0;
  double usDataPeriod = 600.0;
  uint32_t usUnconfirmedDataNbRep = 1;
  bool usConfirmedData = false;
  uint32_t dsPacketSize = 21;
  bool dsDataGenerate = false;
  double dsDataExpMean = -1;
  bool dsConfirmedData = false;
  bool verbose = false;
  uint64_t maliciousTime = 0; //in microsseconds
  double symbolsMalicious = 0;//in symbols Malicious delays
  uint8_t pingPeriod = 7;
  bool SinglePingTest = 0; 
  bool MultiplePingTest = 0; 
  bool SinglebeaconlessTest = 0; 
  bool MultiplebeaconlessTest = 0;
  bool offsetOn = 1; 
  std::string outputFileNamePrefix = "output/LoRaWAn-long-term-test";
  

  CommandLine cmd;
  cmd.AddValue ("randomSeed", "Random seed used in experiments[Default:12345]", randomSeed);
  cmd.AddValue ("nEndDevices", "Number of LoRaWAN class A end devices nodes[Default:30]", nEndDevices);
  cmd.AddValue ("nGateways", "Number of LoRaWAN gateways [Default:1]", nGateways);
  cmd.AddValue ("discRadius", "The radius of the disc (in meters) in which end devices and gateways are placed[Default:5000.0]", discRadius);
  cmd.AddValue ("totalTime", "Simulation time for one run in Seconds[Default:100]", totalTime);
  cmd.AddValue ("nRuns", "Number of simulation runs[Default:100]", nRuns);
  cmd.AddValue ("usPacketSize", "Packet size used for generating US packets[Default:21]", usPacketSize);
  cmd.AddValue ("usMaxBytes", "Maximum number of bytes to be queued for transmission in the upstream direction, note this does not take into account retransmissions. 0 means no limit. [Default:0]", usMaxBytes);
  cmd.AddValue ("usDataPeriod", "Period between subsequent Upstream data transmissions from an end device[Default:600]", usDataPeriod);
  cmd.AddValue ("usUnconfirmedDataNbRep", "Number of repetitions for unconfirmed US data messages[Default:1]", usUnconfirmedDataNbRep);
  cmd.AddValue ("usConfirmedData", "0 for Unconfirmed Upstream Data MAC packets, 1 for Confirmed Upstream Data MAC Packets[Default:0]", usConfirmedData);
  cmd.AddValue ("dsPacketSize", "Packet size used for generating DS packets[Default:21]", dsPacketSize);
  cmd.AddValue ("dsDataGenerate", "Should NS generate DS traffic for end devices, note that Acks are always sent.[Default:0]", dsDataGenerate);
  cmd.AddValue ("classBInDS", "Interval between each ClassB transmission [Default:300]", ClassBInDS); 
  cmd.AddValue ("classBDST", "random Time between each ClassB Transmission [Default:300]", ClassBDST);
  //cmd.AddValue ("dsDataExpMean", "Mean for the Exponential random variable for inter packet time for DS transmission for an end device[Default:10*usDataPeriod]", dsDataExpMean);
  //cmd.AddValue ("dsConfirmedData", "0 for Unconfirmed Downstream Data MAC packets, 1 for Confirmed Downstream Data MAC Packets[Default:0]", dsConfirmedData);
  cmd.AddValue ("verbose", "turn on all log components[Default:0]", verbose);
  cmd.AddValue ("SinglePingTest", "Turn on Single Ping Test, with a pingPeriod [Default:0]", SinglePingTest);
  cmd.AddValue ("SingleBeaconLessTest", "Turn on Multiple BeaconlessTest[Default:0]", SinglebeaconlessTest);
  cmd.AddValue ("MultiplePingTest", "Turn on Multiple Ping Test [Default:0]", MultiplePingTest);
  cmd.AddValue ("MultipleBeaconlessTest", "Trace messages on end devices[Default:0]", MultiplebeaconlessTest);
  cmd.AddValue ("Malicioustime", "MicroSeconds time from start of simulation to send a malicious beacon 0 means no attack [Default:0]", maliciousTime);
  cmd.AddValue ("DMaliciousSec", "malicious delay in symbols[Default:0]", symbolsMalicious);
  cmd.AddValue ("pingPeriod", "Number of PingSlots for all end devices[Default:0]", pingPeriod);
  cmd.AddValue ("outputFileNamePrefix", "The prefix for the names of the output files[Default:output/LoRaWAn-long-term-test]", outputFileNamePrefix);
  cmd.AddValue ("offsetOn","Determine whether to turn off ping offset calculation [Default:1]",offsetOn);
  //cmd.AddValue ("phyMode", "Wifi Phy mode[Default:DsssRate11Mbps]", phyMode);
  //cmd.AddValue ("rate", "CBR traffic rate[Default:8kbps]", rate);
  //cmd.AddValue ("nodeSpeed", "Node speed in RandomWayPoint model[Default:10]", nodeSpeed);
  //cmd.AddValue ("periodicUpdateInterval", "Periodic Interval Time[Default=15]", periodicUpdateInterval);
  //cmd.AddValue ("settlingTime", "Settling Time before sending out an update for changed metric[Default=6]", settlingTime);
  //cmd.AddValue ("dataStart", "Time at which nodes start to transmit data[Default=50.0]", dataStart);
  //cmd.AddValue ("printRoutingTable", "print routing table for nodes[Default:1]", printRoutingTable);
  cmd.Parse (argc, argv);

  if (dsDataExpMean == -1)
    dsDataExpMean = 10 * usDataPeriod; // set default value for dsDataExpMean



  std::time_t unix_epoch = std::time(nullptr);
  for (uint32_t i = 0; i < nRuns; i++) {
    uint32_t seed = randomSeed + i;
    SeedManager::SetSeed (seed);

    std::ostringstream simRunFilesPrefix;
    simRunFilesPrefix << outputFileNamePrefix << "-" << unix_epoch << "-" << std::to_string(i);
    // prep csv files:
    std::ostringstream ClassBPacketsSentCSVFileName;
    ClassBPacketsSentCSVFileName << simRunFilesPrefix.str() << "-trace-ClassB-Packets-tx.csv";
      std::ofstream out (ClassBPacketsSentCSVFileName.str ().c_str ());
      out << "Time(MicroSeconds)," <<
          "DeviceAddr," <<
          "ClassBPacketsSent," << "Uid" << std::endl;
      out.close ();
    

    std::ostringstream ClassBPacketsRecievedCSVFileName;
    ClassBPacketsRecievedCSVFileName << simRunFilesPrefix.str() << "-trace-ClassB-Packets-rx.csv";
      std::ofstream out2 (ClassBPacketsRecievedCSVFileName.str ().c_str ());
       out2 << "Time(MicroSeconds)," <<
              "DeviceAddr," <<
              "ClassBPacketsRecieved," << "Uid" << std::endl;
      out2.close ();
    

    std::ostringstream numberofBeaconsCSVFileName;
    numberofBeaconsCSVFileName << simRunFilesPrefix.str() << "-trace-numberofBeacons-rx.csv";
      std::ofstream out3 (numberofBeaconsCSVFileName.str ().c_str ());
      // TODO
      out3 << "Time(MicroSeconds)," <<
          "DeviceAddr," <<
          "numberofBeaconsRecieved:," << std::endl;
      out3.close ();
/*
    std::ostringstream macStateTraceCSVFileName;
    macStateTraceCSVFileName << simRunFilesPrefix.str() << "-trace-mac-state.csv";
    if (traceMacStates) {
      std::ofstream out3 (macStateTraceCSVFileName.str ().c_str ());
      out3 << "Time," <<
        "DeviceType," <<
        "NodeId," <<
        "IfIndex," <<
        "MacIndex," <<
        "TraceSource," <<
        "OldState," <<
        "NewState" <<
        std::endl;
      out3.close ();
    }

    std::ostringstream edMsgTraceCSVFileName;
    edMsgTraceCSVFileName << simRunFilesPrefix.str() << "-trace-ed-msgs.csv";
    if (traceEdMsgs) {
      std::ofstream outed (edMsgTraceCSVFileName.str ().c_str ());
      outed << "Time," <<
        "TraceSource," <<
        "NodeId," <<
        "MsgType," <<
        "PacketHex," <<
        "PacketLength" <<
        std::endl;
      outed.close ();
    }

    std::ostringstream nsDSMsgTraceCSVFileName;
    nsDSMsgTraceCSVFileName << simRunFilesPrefix.str() << "-trace-ns-dsmsgs.csv";
    if (traceNsDsMsgs) {
      std::ofstream outns (nsDSMsgTraceCSVFileName.str ().c_str ());
      outns << "Time," <<
        "TraceSource," <<
        "NodeId," <<
        "MsgType," <<
        "TxRemaining," <<
        "PacketHex," <<
        "PacketLength" <<
        std::endl;
      outns.close ();
    }

    std::ostringstream miscTraceCSVFileName;
    miscTraceCSVFileName << simRunFilesPrefix.str() << "-trace-misc.csv";
    if (traceMisc) {
      std::ofstream out4 (miscTraceCSVFileName.str ().c_str ());
      out4 << "nrRW1Sent," <<
        "nrRW2Sent," <<
        "nrRW1Missed," <<
        "nrRW2Missed" <<
        std::endl;
      out4.close ();
    }
*/
    std::ostringstream nodesCSVFileName;
    nodesCSVFileName << simRunFilesPrefix.str() << "-nodes.csv";
    std::ofstream out5 (nodesCSVFileName.str ().c_str ());
    out5 << "DeviceType," <<
      "NodeId," <<
      "Position x," <<
      "Position y," <<
      "DistanceToClosestGW," <<
      "ClassBPingPeriodicity" <<
      std::endl;
    out5.close ();

    std::cout << std::endl;

    std::ostringstream simSettings;
    simSettings << "{" << std::endl; 
    //simSettings << "Simulation settings:" << std::endl;
    if(SinglePingTest == 1) {
      simSettings << "\t\"pingPeriod\" : " << "\"" << (int)pingPeriod << "\"" << "," << std::endl;
    }
    simSettings << "\t\"randomSeed\" : " << "\"" << randomSeed << "\"" << "," << std::endl;
    simSettings << "\t\"nEndDevices\" : "<< "\"" << nEndDevices << "\"" << "," << std::endl;
    simSettings << "\t\"nGateways\" : " << "\""<< nGateways<< "\"" << "," << std::endl;
    simSettings << "\t\"discRadius\" : " << "\"" << discRadius << "\"" << "," << std::endl;
    simSettings << "\t\"totalTime\" : "<< "\"" << totalTime << "\"" << "," << std::endl;
    simSettings << "\t\"nRuns\" : " << "\"" << nRuns<< "\""  << ","  << std::endl;
    simSettings << "\t\"usPacketSize\" : " << "\"" << usPacketSize << "\"" << "," << std::endl;
    simSettings << "\t\"usMaxBytes\" : " << "\"" << usMaxBytes << "\"" << "," << std::endl;
    simSettings << "\t\"usDataPeriod\" : " << "\"" << usDataPeriod << "\"" << "," << std::endl;
    simSettings << "\t\"usUnconfirmedDataNbRep\" : " << "\"" << usUnconfirmedDataNbRep << "\"" << "," << std::endl;
    simSettings << "\t\"usConfirmedData\" : " << "\"" << usConfirmedData << "\""<< "," << std::endl;
    simSettings << "\t\"dsPacketSize\" : " << "\"" << dsPacketSize << "\""<< "," << std::endl;
    simSettings << "\t\"dsDataGenerate\" : " << "\"" << dsDataGenerate<< "\"" << "," << std::endl;
    simSettings << "\t\"dsDataExpMean\" : " << "\"" << dsDataExpMean << "\""<< "," << std::endl;
    simSettings << "\t\"dsConfirmedData\" : " << "\"" << dsConfirmedData<< "\"" << "," << std::endl;
    simSettings << "\t\"verbose\" : " << "\"" << verbose << "\"" << "," << std::endl;
    simSettings << "\t\"classBDST\" : " << "\"" << ClassBDST << "\"" << "," << std::endl; 
    simSettings << "\t\"classBInDS\" : " << "\"" << ClassBInDS<< "\"" << "," << std::endl;
    simSettings << "\t\"offsetOn\" : " << "\"" << offsetOn << "\"" << "," << std::endl;
    simSettings << "\t\"MaliciousTime\" : " << "\"" << maliciousTime << "\"" << "," << std::endl;
    simSettings << "\t\"DMaliciousSec\" : " << "\"" << symbolsMalicious  << "\"" << "," << std::endl;
    /*
    simSettings << "\ttracePhyTransmissions = " << tracePhyTransmissions << std::endl;
    simSettings << "\ttracePhyStates = " << tracePhyStates << std::endl;
    simSettings << "\ttraceMacPackets = " << traceMacPackets << std::endl;
    simSettings << "\ttraceMacStates = " << traceMacStates << std::endl;
    simSettings << "\ttraceEdMsgs = " << traceEdMsgs << std::endl;
    simSettings << "\ttraceNsDsMsgs = " << traceNsDsMsgs << std::endl;
    simSettings << "\ttraceMisc = " << traceMisc << std::endl;
    */
    simSettings << "\t\"outputFileNamePrefix\" : " << "\""  << outputFileNamePrefix << "\"" <<"," << std::endl;
    simSettings << "\t\"run\"  : " << "\"" << i << "\"" << "," << std::endl;
    simSettings << "\t\"seed\" : " << "\"" << seed << "\"" << "," << std::endl;
    simSettings << "\t\"classBPacketsSentCSVFileName\" :  " << "\"" << ClassBPacketsSentCSVFileName.str() << "\"" << "," << std::endl;
    simSettings << "\t\"ClassBPacketsRecievedCSVFileName\" : " << "\"" << ClassBPacketsRecievedCSVFileName.str() << "\"" << "," << std::endl;
    simSettings << "\t\"numberofBeaconsCSVFileName\" : " << "\"" << numberofBeaconsCSVFileName.str() << "\"" << "," << std::endl;
    /*
    simSettings << "\tmacStateTraceCSVFileName = " << macStateTraceCSVFileName.str() << std::endl;
    simSettings << "\tedMsgTraceCSVFileName = " << edMsgTraceCSVFileName.str() << std::endl;
    simSettings << "\tnsDSMsgTraceCSVFileName = " << nsDSMsgTraceCSVFileName.str() << std::endl;
    simSettings << "\tmiscTraceCSVFileName = " << miscTraceCSVFileName.str() << std::endl;
    */
    simSettings << "\t\"nodesCSVFileName\" : " << "\"" << nodesCSVFileName.str() << "\"" << std::endl;
     simSettings << "}" << std::endl;


    // print settings to std cout
    std::cout << simSettings.str();
    // write settings to file:
    std::ostringstream simSettingsFileName;
    simSettingsFileName << simRunFilesPrefix.str() << "-sim-settings.json";
    std::ofstream out6 (simSettingsFileName.str ().c_str ());
    out6 << simSettings.str();
    out6.close ();

    // Start sim run:
    LoRaWANLongTermTest example = LoRaWANLongTermTest ();
    example.CaseRun (nEndDevices, nGateways, discRadius, totalTime,
        usPacketSize, usMaxBytes, usDataPeriod, usUnconfirmedDataNbRep, usConfirmedData,
        dsPacketSize, dsDataGenerate, dsDataExpMean, dsConfirmedData,maliciousTime,symbolsMalicious,pingPeriod,
        SinglePingTest, MultiplePingTest, SinglebeaconlessTest, MultiplebeaconlessTest,verbose,
        ClassBPacketsSentCSVFileName.str (), ClassBPacketsRecievedCSVFileName.str (), numberofBeaconsCSVFileName.str (),nodesCSVFileName.str(),ClassBDST,ClassBInDS,offsetOn);
  }

  return 0;
}
/*
Ptr<Socket>
SetupPacketReceive (Ptr<Node> node)
{
  TypeId tid = TypeId::LookupByName ("ns3::PacketSocketFactory");
  Ptr<Socket> sink = Socket::CreateSocket (node, tid);
  sink->Bind ();
  sink->SetRecvCallback (MakeCallback (&ReceivePacket));
  return sink;
}


int main (int argc, char *argv[])
{

  AnimationInterface anim ("animation.xml");
  anim.EnableQueueCounters(Seconds(0.0),Seconds (86400),Seconds (100));
  anim.SetStartTime(Seconds(0.0)); 
  anim.SetStopTime(Seconds(0.0)); 
  anim.SetMobilityPollInterval(Seconds(100)); 

  LogComponentEnable("LoRaWANEndDeviceApplication",LOG_LEVEL_DEBUG);
  LogComponentEnable("LoRaWANGatewayApplication",LOG_LEVEL_DEBUG);
  LogComponentEnable("LoRaWANdevAddress",LOG_LEVEL_DEBUG);
  LogComponentEnable("LoRaWANPhy",LOG_LEVEL_WARN);
  LogComponentEnable("LoRaWANMac",LOG_LEVEL_WARN);


  uint32_t nNodes = 1;
  uint8_t  dr = 0; //weird data rate 


  CommandLine cmd;
  cmd.AddValue("nNodes", "Number of nodes to add to simulation", nNodes);
  cmd.AddValue("dr", "Data rate to be used (up and down, a and b)", dr);
  cmd.Parse (argc, argv);
  dr &= (0b111); //this is a bit of a hack, changes inputed int to same as equivalent uint for small values

  NS_LOG_LOGIC("Start of Simulation!");
  NodeContainer endDeviceNodes;
  NodeContainer gatewayNodes;
  NodeContainer allNodes;

  endDeviceNodes.Create (nNodes);
  gatewayNodes.Create (1);
  allNodes.Add (endDeviceNodes);
  allNodes.Add (gatewayNodes);

  

  // position allocator, where nodes are randomly placed in a disk of discradius size.
  double m_discRadius = 6100.0;
  MobilityHelper edMobility;
  edMobility.SetPositionAllocator ("ns3::UniformDiscPositionAllocator",
                                    "X", DoubleValue (0.0),
                                    "Y", DoubleValue (0.0),
                                    "rho", DoubleValue (m_discRadius));
  edMobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  edMobility.Install (endDeviceNodes);


  // the gateway is placed at 0,0,0
  MobilityHelper gwMobility;
  Ptr<ListPositionAllocator> nodePositionList = CreateObject<ListPositionAllocator> ();
  nodePositionList->Add (Vector (0.0, 0.0, 0.0));  // gateway
  gwMobility.SetPositionAllocator (nodePositionList);
  gwMobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  gwMobility.Install (gatewayNodes);


  LoRaWANHelper lorawanHelper;
  uint32_t netID = 000013;
  int type = 0; 
  lorawanHelper.SetNbRep(1); // no retransmissions
  lorawanHelper.SetDeviceType (LORAWAN_DT_GATEWAY);
  NetDeviceContainer lorawanGWDevices = lorawanHelper.Install (gatewayNodes,netID,type);
  lorawanHelper.SetDeviceType (LORAWAN_DT_END_DEVICE);
  NetDeviceContainer lorawanEDDevices = lorawanHelper.Install (endDeviceNodes,netID,type);


  PacketSocketHelper packetSocket;
  packetSocket.Install (endDeviceNodes);
  packetSocket.Install (gatewayNodes);

    // install gw application on gateways
  LoRaWANGatewayHelper gatewayhelper;
  gatewayhelper.SetAttribute ("DefaultClassBDataRateIndex", UintegerValue (dr));
  ApplicationContainer gatewayApps = gatewayhelper.Install (gatewayNodes); 
  
  // install end device application on nodes
  LoRaWANEndDeviceHelper enddevicehelper;
  enddevicehelper.SetAttribute ("DataRateIndex", UintegerValue (dr));
  enddevicehelper.SetAttribute ("ClassBDataRateIndex", UintegerValue (dr));
  enddevicehelper.SetAttribute ("IsClassB", BooleanValue(true));

  ApplicationContainer enddeviceApps = enddevicehelper.Install (endDeviceNodes);

  
 
  //run for a day
  gatewayApps.Start (Seconds (0.0));
  gatewayApps.Stop (Seconds (256)); //86400

  enddeviceApps.Start (Seconds (0.0));
  enddeviceApps.Stop (Seconds (86400));

  Ptr<Socket> recvSink = SetupPacketReceive (gatewayNodes.Get (0));

  Simulator::Stop (Seconds (86400));
  Simulator::Run ();
  
  std::cout << "RESULTS START HERE" << std::endl;
  //std::cout << nNodes << std::endl;

  Simulator::Destroy ();

  return 0;
}
*/