#!/bin/bash


rm -rf SinglePingTest0
rm -rf SinglePingTest1
rm -rf SinglePingTest2
rm -rf SinglePingTest3
rm -rf SinglePingTest4
rm -rf SinglePingTest5
rm -rf SinglePingTest6
rm -rf SinglePingTest7

mkdir SinglePingTest0
mkdir SinglePingTest1
mkdir SinglePingTest2
mkdir SinglePingTest3
mkdir SinglePingTest4
mkdir SinglePingTest5
mkdir SinglePingTest6
mkdir SinglePingTest7


NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=1 --Malicioustime=3584 --DMaliciousSec=1 --totalTime=10800 --SinglePingTest=1 --pingPeriod=0 --outputFileNamePrefix=SinglePingTest0/LoRaWAN-SinglePingSlot --classBInDS=1" 2>results0.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=1 --Malicioustime=3584 --DMaliciousSec=1 --totalTime=10800 --SinglePingTest=1 --pingPeriod=1 --outputFileNamePrefix=SinglePingTest1/LoRaWAN-SinglePingSlot --classBInDS=1" 2>results1.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=1 --Malicioustime=3584 --DMaliciousSec=1 --totalTime=10800 --SinglePingTest=1 --pingPeriod=2 --outputFileNamePrefix=SinglePingTest2/LoRaWAN-SinglePingSlot --classBInDS=1" 2>results2.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=1 --Malicioustime=3584 --DMaliciousSec=1 --totalTime=10800 --SinglePingTest=1 --pingPeriod=3 --outputFileNamePrefix=SinglePingTest3/LoRaWAN-SinglePingSlot --classBInDS=1 " 2>results3.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=1 --Malicioustime=3584 --DMaliciousSec=1 --totalTime=10800 --SinglePingTest=1 --pingPeriod=4 --outputFileNamePrefix=SinglePingTest4/LoRaWAN-SinglePingSlot --classBInDS=1 " 2>results4.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=1 --Malicioustime=3584 --DMaliciousSec=1 --totalTime=10800 --SinglePingTest=1 --pingPeriod=5 --outputFileNamePrefix=SinglePingTest5/LoRaWAN-SinglePingSlot --classBInDS=1 " 2>results5.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=1 --Malicioustime=3584 --DMaliciousSec=1 --totalTime=10800 --SinglePingTest=1 --pingPeriod=6 --outputFileNamePrefix=SinglePingTest6/LoRaWAN-SinglePingSlot --classBInDS=1 " 2>results6.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=1 --Malicioustime=3584 --DMaliciousSec=1 --totalTime=10800 --SinglePingTest=1 --pingPeriod=7 --outputFileNamePrefix=SinglePingTest7/LoRaWAN-SinglePingSlot --classBInDS=1 " 2>results7.txt &6

wait

rm -rf email.txt

cat results0.txt results1.txt results2.txt results3.txt results4.txt results5.txt results6.txt results7.txt > email.txt

rm -rf results0.txt results1.txt results2.txt results3.txt results4.txt results5.txt results6.txt results7.txt

sendmail jayanariyawansa@gmail.com < email.txt
