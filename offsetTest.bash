#!/bin/bash


rm -rf SingleOffsetTest7On 
rm -rf SingleOffsetTest7Off

mkdir SingleOffsetTest7On 
mkdir SingleOffsetTest7Off

NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=1 --Malicioustime=3584 --DMaliciousSec=1 --totalTime=10800 --SinglePingTest=1 --pingPeriod=7 --outputFileNamePrefix=SingleOffsetTest7On/LoRaWAN-SinglePingSlot --classBInDS=1 " 2>results7off.txt &

NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=1 --Malicioustime=3584 --DMaliciousSec=1 --totalTime=10800 --SinglePingTest=1 --pingPeriod=7 --outputFileNamePrefix=SingleOffsetTest7Off/LoRaWAN-SinglePingSlot --classBInDS=1 --offsetOn=0" 2>results7on.txt 