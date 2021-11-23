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
// Include a header file from your module to test.
#include <ns3/lorawan.h>
#include <ns3/lorawan-module.h>
#include <ns3/test.h>
#include <ns3/log.h>
#include <ns3/core-module.h>
#include <ns3/callback.h>
#include <ns3/packet.h>
#include <ns3/simulator.h>
#include <ns3/net-device.h>
#include "ns3/rng-seed-manager.h"
#include <ns3/network-module.h>
#include <ns3/ipv4-address.h>
#include <ns3/propagation-loss-model.h>
#include <ns3/propagation-delay-model.h>
#include <ns3/mobility-module.h>
#include <ns3/applications-module.h>
#include <ns3/single-model-spectrum-channel.h>
#include <ns3/constant-position-mobility-model.h>
#include <ns3/node.h>


// An essential include is test.h
#include "ns3/test.h"

// Do not put your test classes in namespace ns3.  You may find it useful
// to use the using directive to access the ns3 namespace directly
using namespace ns3;
NS_LOG_COMPONENT_DEFINE ("lorawan-beaconless-test");
// This is an example TestCase.
class LorawanBeaconlessTest : public TestCase
{
public:
  LorawanBeaconlessTest();
  virtual ~LorawanBeaconlessTest ();

private:
  virtual void DoRun (void);
  void checkClassB (int i, ApplicationContainer enddeviceApps, bool *isClassB);
  void checkBeaconlessMode (int i, ApplicationContainer enddeviceApps, bool *isBL);
};

// Add some help text to this case to describe what it is intended to test
LorawanBeaconlessTest::LorawanBeaconlessTest ()
  : TestCase ("Test the Lorawan BeaconlessModel")
{
}

// This destructor does nothing but we include it as a reminder that
// the test case should clean up after itself
LorawanBeaconlessTest::~LorawanBeaconlessTest()
{
}

//
// This method is the pure virtual method from class TestCase that every
// TestCase must implement
//
void LorawanBeaconlessTest::checkClassB (int i, ApplicationContainer enddeviceApps, bool *isClassB)
{
  const Ptr<Application> app = enddeviceApps.Get(0); 
  const Ptr<Node> endDeviceNode = app->GetNode();
  const Ptr<LoRaWANEndDeviceApplication> endApp = endDeviceNode->GetApplication(0)->GetObject<LoRaWANEndDeviceApplication>();
  NS_LOG_UNCOND(this << "endApp->m_isClassB: " << (endApp->m_isClassB == true) <<" Time:" <<Simulator::Now());
  *isClassB = endApp->m_isClassB; 
}
void LorawanBeaconlessTest::checkBeaconlessMode (int i, ApplicationContainer enddeviceApps, bool *isBL)
{
  const Ptr<Application> app = enddeviceApps.Get(0); 
  const Ptr<Node> endDeviceNode = app->GetNode();
  const Ptr<LoRaWANEndDeviceApplication> endApp = endDeviceNode->GetApplication(0)->GetObject<LoRaWANEndDeviceApplication>();
  Ptr<LoRaWANNetDevice> netDevice = DynamicCast<LoRaWANNetDevice> (endApp->GetNode()->GetDevice(0));
  uint16_t temp = netDevice->GetPhy()->GetBeaconSymbolTimeout();
  NS_LOG_UNCOND(this << "m_BeaconSymbolTimeout: " << temp<< " Time:" <<Simulator::Now());
  if ( temp >= 16 )
  {
    *isBL = true;  
  }
  else 
  {
    *isBL = false; 
  }
}
void
LorawanBeaconlessTest::DoRun (void)
{
  uint32_t nNodes = 1;
  uint8_t  dr = 0; //weird data rate 
  dr &= (0b111); //this is a bit of a hack, changes inputed int to same as equivalent uint for small values
  
  NS_LOG_LOGIC("Start of Simulation!");
  NodeContainer endDeviceNodes;
  NodeContainer gatewayNodes;
  NodeContainer allNodes;


  endDeviceNodes.Create (nNodes);
  gatewayNodes.Create (1);
  allNodes.Add (endDeviceNodes);
  allNodes.Add (gatewayNodes);

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
  NetDeviceContainer lorawanEDDevices = lorawanHelper.Install (endDeviceNodes,netID,type);

  lorawanHelper.SetDeviceType (LORAWAN_DT_GATEWAY);
  NetDeviceContainer lorawanGWDevices = lorawanHelper.Install (gatewayNodes,netID,type);

  PacketSocketHelper packetSocket;
  packetSocket.Install (endDeviceNodes);
  packetSocket.Install (gatewayNodes);
  
  
  // install end device application on nodes
  LoRaWANEndDeviceHelper enddevicehelper;
  enddevicehelper.SetAttribute ("DataRateIndex", UintegerValue (dr));
  enddevicehelper.SetAttribute ("ClassBDataRateIndex", UintegerValue (7));
  enddevicehelper.SetAttribute ("IsClassB", BooleanValue(true));

  ApplicationContainer enddeviceApps = enddevicehelper.Install (endDeviceNodes);
 

  // install gw application on gateways
  /*
  Test Scenario: 
  *
  *
  * Gateway will send two beacon signals and stop at 256 seconds. The end device will enter beaconless mode after first failed signal. 
  * It will not stop being a class B  at the 2 hr rather than at the next beacon reserved (7552).
  */

  LoRaWANGatewayHelper gatewayhelper;
  gatewayhelper.SetAttribute ("DefaultClassBDataRateIndex", UintegerValue (dr));
  ApplicationContainer gatewayApps = gatewayhelper.Install (gatewayNodes);
  bool normalOpModeClass = false; 
  bool duringBeaconLModeClass = false; 
  bool beforeEndBeaconLModeClass = false; 
  bool afterEndBeaconLModeClass = true; 
  
  bool normalOpModeBL = true; 
  bool duringBeaconLModeBL = false; 
  bool beforeEndBeaconLModeBL = false; 


  //run for 2hrs 
  gatewayApps.Start (Seconds (0.0));
  gatewayApps.Stop (Seconds (256)); // only run gateway for 2 mins 

  Simulator::Schedule(Seconds(128),&LorawanBeaconlessTest::checkClassB,this,0,enddeviceApps,&normalOpModeClass);
  Simulator::Schedule(Seconds(386),&LorawanBeaconlessTest::checkClassB,this,0,enddeviceApps,&duringBeaconLModeClass);
  Simulator::Schedule(Seconds(7400),&LorawanBeaconlessTest::checkClassB,this,0,enddeviceApps,&beforeEndBeaconLModeClass); // at 7072 seconds the device should be class A 
  Simulator::Schedule(Seconds(7556),&LorawanBeaconlessTest::checkClassB,this,0,enddeviceApps,&afterEndBeaconLModeClass); 

  Simulator::Schedule(Seconds(128),&LorawanBeaconlessTest::checkBeaconlessMode,this,0,enddeviceApps,&normalOpModeBL);
  Simulator::Schedule(Seconds(386),&LorawanBeaconlessTest::checkBeaconlessMode,this,0,enddeviceApps,&duringBeaconLModeBL);
  Simulator::Schedule(Seconds(7456),&LorawanBeaconlessTest::checkBeaconlessMode,this,0,enddeviceApps,&beforeEndBeaconLModeBL); // at 7072 seconds the device should be class A 

  
  //checkClassB(0,enddeviceApps,afterBeaconLMode);
  enddeviceApps.Start (Seconds (0.0));
  enddeviceApps.Stop (Seconds (10800));

  
  //Ptr<Socket> recvSink = SetupPacketReceive (gatewayNodes.Get (0));
 
  Simulator::Stop (Seconds (10800));
  Simulator::Run ();
  NS_TEST_ASSERT_MSG_EQ (normalOpModeClass, true, "Failed to initiate into Class B");
  NS_TEST_ASSERT_MSG_EQ (duringBeaconLModeClass, true, "still in Class A");
  NS_TEST_ASSERT_MSG_EQ (beforeEndBeaconLModeClass, true, "Already in Class A");
  NS_TEST_ASSERT_MSG_EQ (afterEndBeaconLModeClass, false, "Failed changed to Class A mode after beaconless mode");

  NS_TEST_ASSERT_MSG_EQ (normalOpModeBL, false, "Shouldnt be in Beaconless Mode yet");
  NS_TEST_ASSERT_MSG_EQ (duringBeaconLModeBL, true, "Not in Beaconless Mode");
  NS_TEST_ASSERT_MSG_EQ (beforeEndBeaconLModeBL, true, "Not in Beaconless Mode");

  //std::cout << nNodes << std::endl;

  Simulator::Destroy ();

  
  // A wide variety of test macros are available in src/core/test.h

  // Use this one for floating point comparisons
  // NS_TEST_ASSERT_MSG_EQ_TOL (0.01, 0.01, 0.001, "Numbers are not equal within tolerance");
}

// The TestSuite class names the TestSuite, identifies what type of TestSuite,
// and enables the TestCases to be run.  Typically, only the constructor for
// this class must be defined
//
class LorawanBeaconlessTestSuite : public TestSuite
{
public:
  LorawanBeaconlessTestSuite ();
};

LorawanBeaconlessTestSuite::LorawanBeaconlessTestSuite ()
  : TestSuite ("lorawan-beaconless-test", UNIT)
{
  // TestDuration for TestCase can be QUICK, EXTENSIVE or TAKES_FOREVER
  LogComponentEnable("LoRaWANEndDeviceApplication",LOG_LEVEL_DEBUG);
  LogComponentEnable("LoRaWANPhy",LOG_LEVEL_WARN);
  LogComponentEnable("LoRaWANMac",LOG_LEVEL_WARN);
  LogComponentEnable("lorawan-beaconless-test",LOG_LEVEL_WARN);
  AddTestCase (new LorawanBeaconlessTest, TestCase::QUICK);
}

// Do not forget to allocate an instance of this TestSuite
static LorawanBeaconlessTestSuite lorawanBeaconlessTestSuite;

