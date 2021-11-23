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
#include <vector>
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
NS_LOG_COMPONENT_DEFINE ("lorawan-PingSlot-test");
// This is an example TestCase.
class LorawanPingSlotTest : public TestCase
{
public:
  LorawanPingSlotTest ();
  virtual ~LorawanPingSlotTest ();

private:
  virtual void DoRun (void);
};

// Add some help text to this case to describe what it is intended to test
LorawanPingSlotTest::LorawanPingSlotTest ()
  : TestCase ("Lorawan Window Expanding test")
{
}

// This destructor does nothing but we include it as a reminder that
// the test case should clean up after itself
LorawanPingSlotTest::~LorawanPingSlotTest ()
{
}

//
// This method is the pure virtual method from class TestCase that every
// TestCase must implement
//
void
LorawanPingSlotTest::DoRun (void)
{
  uint32_t nNodes = 1;
  int size = 1;
  //int periodP = 0; //Period Periocity  
  uint8_t  dr = 7; //weird data rate 
  uint8_t dr1 = 0; 
  dr &= (0b111); //this is a bit of a hack, changes inputed int to same as equivalent uint for small values
  dr1 &=(0b111);
  NS_LOG_LOGIC("Start of Simulation!");
  std::vector <NodeContainer> endDeviceNodes;
  endDeviceNodes.resize(8);
  std::vector <NodeContainer> gatewayNodes;
  gatewayNodes.resize(8);
  NodeContainer allNodes;

  for (int i = 1; i <= size ; i++) 
  {
    endDeviceNodes[i-1].Create (nNodes);
    gatewayNodes[i-1].Create(1);
  }
  for (int i = 1; i <= size ; i++)
  {
    allNodes.Add (endDeviceNodes[i-1]);
    allNodes.Add (gatewayNodes[i-1]);
  }

  double m_discRadius = 6100.0;
  MobilityHelper edMobility;
  edMobility.SetPositionAllocator ("ns3::UniformDiscPositionAllocator",
                                    "X", DoubleValue (0.0),
                                    "Y", DoubleValue (0.0),
                                    "rho", DoubleValue (m_discRadius));
  edMobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  MobilityHelper gwMobility;
  Ptr<ListPositionAllocator> nodePositionList = CreateObject<ListPositionAllocator> ();
  nodePositionList->Add (Vector (0.0, 0.0, 0.0));  // gateway
  gwMobility.SetPositionAllocator (nodePositionList);
  gwMobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  for (int i = 1; i <= size ; i++)
  {
    edMobility.Install (endDeviceNodes[i-1]);
    gwMobility.Install (gatewayNodes[i-1]);
  }  


  // the gateway is placed at 0,0,0

  /*
  gwMobility.SetPositionAllocator ("ns3::UniformDiscPositionAllocator",
                                    "X", DoubleValue (0.0),
                                    "Y", DoubleValue (0.0),
                                    "rho", DoubleValue (m_discRadius));
  */                                  
 


  LoRaWANHelper lorawanHelper;
  uint32_t netID = 000013;
  int type = 0; 
  lorawanHelper.SetNbRep(1); // no retransmissions 
  for (int i = 1; i <= size ; i++)
  {
    lorawanHelper.SetDeviceType (LORAWAN_DT_END_DEVICE);
    NetDeviceContainer lorawanEDDevices = lorawanHelper.Install (endDeviceNodes[i-1],netID,type);
    lorawanHelper.SetDeviceType (LORAWAN_DT_GATEWAY);
    NetDeviceContainer lorawanGWDevices = lorawanHelper.Install (gatewayNodes[i-1],netID,type);
  }
  /*  
  Ptr<LoRaWANNetDevice> dev0 = lorawanEDDevice.Get(0);
  Ptr<LoRaWANNetDevice> devgw = lorawanGWDevices.Get(0);
  Ptr<LoRaWANNetworkServer> ntw = devgw->GetObject<LoRaWANNetworkServer>;
  uint32_t beacons = ntw->GetnumberofBeacons(); 
  */


  PacketSocketHelper packetSocket;
  for (int i = 1; i <= size ; i++)
  {
    packetSocket.Install (endDeviceNodes[i-1]);
    packetSocket.Install (gatewayNodes[i-1]);
  }
  
  
  // install end device application on nodes
  LoRaWANEndDeviceHelper enddevicehelper;
  enddevicehelper.SetAttribute ("DataRateIndex", UintegerValue (dr1));
  enddevicehelper.SetAttribute ("ClassBDataRateIndex", UintegerValue (dr));
  enddevicehelper.SetAttribute ("IsClassB", BooleanValue(true));
  std::vector <ApplicationContainer> enddeviceApps;
  enddeviceApps.resize(8);
   // install gw application on gateways
  LoRaWANGatewayHelper gatewayhelper;
  gatewayhelper.SetAttribute ("DefaultClassBDataRateIndex", UintegerValue (dr));
  std::vector <ApplicationContainer> gatewayApps;
  gatewayApps.resize(8);

  //run for 2hrs 
  for (int i = 0; i <= 0 ; i++){
    enddevicehelper.SetAttribute("ClassBPingPeriodicity",UintegerValue(7));
    enddeviceApps[i] = enddevicehelper.Install (endDeviceNodes[i]);
    gatewayApps[i] = gatewayhelper.Install(gatewayNodes[i]);
    enddeviceApps[i].Start (Seconds (0.0));
    enddeviceApps[i].Stop (Seconds (1024)); 
    gatewayApps[i].Start (Seconds (0.0));
    gatewayApps[i].Stop (Seconds (1024));
    
    
    NS_TEST_ASSERT_MSG_EQ_TOL (0.01, 0.01, 0.001, "Ping Slots are not equal within tolerance");
  }
  /*
  //run for 2hrs 
  enddeviceApps.Start (Seconds (0.0));
  enddeviceApps.Stop (Seconds (1024)); 
  gatewayApps.Start (Seconds (0.0));
  gatewayApps.Stop (Seconds (1024)); 
  NS_TEST_ASSERT_MSG_EQ_TOL (0.01, 0.01, 0.001, "Numbers are not equal within tolerance");
  Simulator::Stop (Seconds (1024)); //10800
    Simulator::Run (); 
    Simulator::Destroy ();
  enddevicehelper.SetAttribute("ClassBPingPeriodicity",UintegerValue(periodP));
  enddeviceApps = enddevicehelper.Install (endDeviceNodes[i-1]);
  */

  


  Simulator::Stop (Seconds (1024)); //10800
  Simulator::Run ();


  Simulator::Destroy ();
  // A wide variety of test macros are available in src/core/test.h
  NS_TEST_ASSERT_MSG_EQ (true, true, "true doesn't equal true for some reason");
  // Use this one for floating point comparisons
  NS_TEST_ASSERT_MSG_EQ_TOL (0.01, 0.01, 0.001, "Numbers are not equal within tolerance");
}

// The TestSuite class names the TestSuite, identifies what type of TestSuite,
// and enables the TestCases to be run.  Typically, only the constructor for
// this class must be defined
//
class LorawanPingSlotTestSuite : public TestSuite
{
public:
  LorawanPingSlotTestSuite ();
};

LorawanPingSlotTestSuite::LorawanPingSlotTestSuite ()
  : TestSuite ("lorawan-pingslot-test", UNIT)
{
  // TestDuration for TestCase can be QUICK, EXTENSIVE or TAKES_FOREVER
  LogComponentEnable("LoRaWANGatewayApplication",LOG_LEVEL_DEBUG);
  LogComponentEnable("LoRaWANEndDeviceApplication",LOG_LEVEL_DEBUG);
  AddTestCase (new LorawanPingSlotTest, TestCase::QUICK);
}

// Do not forget to allocate an instance of this TestSuite
static LorawanPingSlotTestSuite lorawanpingslotSuite;

