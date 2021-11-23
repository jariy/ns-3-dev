#!/bin/bash


rm -rf MultiplePingTest0
rm -rf MultiplePingTest1
rm -rf MultiplePingTest2
rm -rf MultiplePingTest3
rm -rf MultiplePingTest4
rm -rf MultiplePingTest5
rm -rf MultiplePingTest6
rm -rf MultiplePingTest7

mkdir MultiplePingTest0
mkdir MultiplePingTest1
mkdir MultiplePingTest2
mkdir MultiplePingTest3
mkdir MultiplePingTest4
mkdir MultiplePingTest5
mkdir MultiplePingTest6
mkdir MultiplePingTest7

rm -rf Control0
rm -rf Control1
rm -rf Control2
rm -rf Control3
rm -rf Control4
rm -rf Control5
rm -rf Control6
rm -rf Control7



mkdir Control0
mkdir Control1
mkdir Control2
mkdir Control3
mkdir Control4
mkdir Control5
mkdir Control6
mkdir Control7


NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=104 --Malicioustime=3584 --DMaliciousSec=1 --totalTime=10800 --MultiplePingTest=1 --pingPeriod=0 --outputFileNamePrefix=MultiplePingTest0/LoRaWAN-MultiplePingSlot" 2>results0.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=104 --Malicioustime=3584 --DMaliciousSec=1 --totalTime=10800 --MultiplePingTest=1 --pingPeriod=1 --outputFileNamePrefix=MultiplePingTest1/LoRaWAN-MultiplePingSlot" 2>results1.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=104 --Malicioustime=3584 --DMaliciousSec=1 --totalTime=10800 --MultiplePingTest=1 --pingPeriod=2 --outputFileNamePrefix=MultiplePingTest2/LoRaWAN-MultiplePingSlot" 2>results2.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=104 --Malicioustime=3584 --DMaliciousSec=1 --totalTime=10800 --MultiplePingTest=1 --pingPeriod=3 --outputFileNamePrefix=MultiplePingTest3/LoRaWAN-MultiplePingSlot" 2>results3.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=104 --Malicioustime=3584 --DMaliciousSec=1 --totalTime=10800 --MultiplePingTest=1 --pingPeriod=4 --outputFileNamePrefix=MultiplePingTest4/LoRaWAN-MultiplePingSlot" 2>results4.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=104 --Malicioustime=3584 --DMaliciousSec=1 --totalTime=10800 --MultiplePingTest=1 --pingPeriod=5 --outputFileNamePrefix=MultiplePingTest5/LoRaWAN-MultiplePingSlot" 2>result5.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=104 --Malicioustime=3584 --DMaliciousSec=1 --totalTime=10800 --MultiplePingTest=1 --pingPeriod=6 --outputFileNamePrefix=MultiplePingTest6/LoRaWAN-MultiplePingSlot" 2>results6.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=104 --Malicioustime=3584 --DMaliciousSec=1 --totalTime=10800 --MultiplePingTest=1 --pingPeriod=7 --outputFileNamePrefix=MultiplePingTest7/LoRaWAN-MultiplePingSlot" 2>results7.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=104 --Malicioustime=3584 --DMaliciousSec=0 --totalTime=10800 --MultiplePingTest=1 --pingPeriod=0 --outputFileNamePrefix=Control0/LoRaWAN-Control" 2>resultsc0.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=104 --Malicioustime=3584 --DMaliciousSec=0 --totalTime=10800 --MultiplePingTest=1 --pingPeriod=1 --outputFileNamePrefix=Control1/LoRaWAN-Control" 2>resultsc1.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=104 --Malicioustime=3584 --DMaliciousSec=0 --totalTime=10800 --MultiplePingTest=1 --pingPeriod=2 --outputFileNamePrefix=Control2/LoRaWAN-Control" 2>resultsc2.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=104 --Malicioustime=3584 --DMaliciousSec=0 --totalTime=10800 --MultiplePingTest=1 --pingPeriod=3 --outputFileNamePrefix=Control3/LoRaWAN-Control" 2>resultsc3.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=104 --Malicioustime=3584 --DMaliciousSec=0 --totalTime=10800 --MultiplePingTest=1 --pingPeriod=4 --outputFileNamePrefix=Control4/LoRaWAN-Control" 2>resultsc4.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=104 --Malicioustime=3584 --DMaliciousSec=0 --totalTime=10800 --MultiplePingTest=1 --pingPeriod=5 --outputFileNamePrefix=Control5/LoRaWAN-Control" 2>resultc5.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=104 --Malicioustime=3584 --DMaliciousSec=0 --totalTime=10800 --MultiplePingTest=1 --pingPeriod=6 --outputFileNamePrefix=Control6/LoRaWAN-Control" 2>resultsc6.txt &
NS_LOG="" ./waf --run="src/lorawan/examples/lorawan-long-term-test.cc --nRuns=100 --nEndDevices=104 --Malicioustime=3584 --DMaliciousSec=0 --totalTime=10800 --MultiplePingTest=1 --pingPeriod=7 --outputFileNamePrefix=Control7/LoRaWAN-Control" 2>resultsc7.txt 

wait

rm -rf email.txt

cat results0.txt results1.txt results2.txt results3.txt results4.txt results5.txt results6.txt results7.txt resultsc0.txt resultsc1.txt resultsc2.txt resultsc3.txt resultsc4.txt resultsc5.txt resultsc6.txt resultsc7.txt > email.txt

rm -rf results0.txt results1.txt results2.txt results3.txt results4.txt results5.txt results6.txt results7.txt resultsc0.txt resultsc1.txt resultsc2.txt resultsc3.txt resultsc4.txt resultsc5.txt resultsc6.txt resultsc7.txt

sendmail jayanariyawansa@gmail.com < email.txt

