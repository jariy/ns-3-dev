//Dev address class goes here 

#include "lorawan.h"
#include <ns3/object.h>
#include <stdlib.h>
#include "ns3/log.h"
#include "devAddress.h"
#include "ns3/assert.h"
#include "ns3/attribute-helper.h"
#include <iostream>
#include "ns3/ipv4-address.h"


namespace ns3 
{

NS_LOG_COMPONENT_DEFINE ("LoRaWANdevAddress");

devAddress::devAddress(uint32_t netiD, int nettype) 
{
    NS_LOG_FUNCTION (this << ":start");
    netID = netiD; 
    type = nettype; 
    unsigned char* temp = generateDevAddr(netID,type); // include generateDevAddr
    if (temp != NULL)
    {
        NS_LOG_DEBUG("Successfully created a DevAddr: " << m_addr << "NetID: " << netID << "Type: " << type); 
        m_initialized = true; 
    }
    else 
    {
    NS_LOG_ERROR ("Error: could not create a new DevAddr " << &temp );
    m_initialized = false; 
    }
     NS_LOG_FUNCTION (this << ":end");
}

devAddress::devAddress(uint32_t netiD, int nettype,uint32_t addr)
{
    NS_LOG_FUNCTION (this << ":start");
    netID = netiD; 
    type = nettype; 
    m_addr = addr; 
    m_initialized = true; 
    NS_LOG_DEBUG("Successfully created a DevAddr: " << m_addr << "NetID: " << netID << "Type: " << type);
    NS_LOG_FUNCTION (this << ":end");
}

uint32_t devAddress::Get() const {
    NS_LOG_FUNCTION (this << ":start");
    NS_LOG_FUNCTION (this << ":end");
    return m_addr; 
}
uint32_t devAddress::GetID() const {
    NS_LOG_FUNCTION (this << ":start");
    NS_LOG_FUNCTION (this << ":end");
    return netID; 
}
int devAddress::GetIDType() const {
    NS_LOG_FUNCTION (this << ":start");
    NS_LOG_FUNCTION (this << ":end");
    return type;
}


bool operator == (devAddress const &a, devAddress const &b)
{
   
    if (a.Get() == b.Get())
    {
        return true;
    }
    else 
    {
        return false;
    }

}

bool operator != (devAddress const &a, devAddress const &b)
{
    if (a.Get() != b.Get())
    {
        return true;
    }
    else 
    {
        return false;
    }
}

Ipv4Address devAddress::convertIp4(void) const {
    NS_LOG_FUNCTION (this << ":start");
    Ipv4Address addr(m_addr);
    NS_LOG_DEBUG("Successfully created a DevAddr: " << m_addr << " NetID: " << netID << " Type: " << type);
    NS_LOG_FUNCTION (this << ":end");
    return addr; 
} 
uint32_t devAddress::reshuffle(void) {
    unsigned char* temp = generateDevAddr(netID,type); // include generateDevAddr
    if (temp != NULL)
    {
        NS_LOG_DEBUG("Successfully created a DevAddr: " << m_addr << "NetID: " << netID << "Type: " << type); 
        m_initialized = true; 
    }
    else 
    {
    NS_LOG_ERROR ("Error: could not create a new DevAddr " << &temp );
    m_initialized = false; 
    }
     NS_LOG_FUNCTION (this << ":end");
    return m_addr; 
}
bool devAddress::IsInitialized() const {
    NS_LOG_FUNCTION (this << ":start");
    NS_LOG_FUNCTION (this << ":end");
    return m_initialized; 
    
}


uint devAddress::NwkAddrBits (uint32_t net, int nettype)
{
    NS_LOG_FUNCTION (this << ":start");
    switch (nettype) {
	case 0:
		return 25;
	case 1:
		return 24;
	case 2:
		return 20;
	case 3:
		return 17;
	case 4:
		return 15;
	case 5:
		return 13;
	case 6:
		return 10;
	case 7:
		return 7;
    default: 
        NS_LOG_ERROR("NwkAddrBits was provided with invalid netId type: " << nettype);
        return 0; //fail
	}
    NS_LOG_FUNCTION (this << ":end");
}

int devAddress::NwkAddrLength(uint32_t net, int nettype)
{
    NS_LOG_FUNCTION (this << ":start");
    return int((NwkAddrBits(net,nettype) + 7) / 8); 
    NS_LOG_FUNCTION (this << ":end");
}

unsigned char* devAddress::bit2char(uint32_t n,unsigned char bytes[])
{
    NS_LOG_FUNCTION (this << ":start");
    bytes[0] = (n >> 24) & 0xFF;
    bytes[1] = (n >> 16) & 0xFF;
    bytes[2] = (n >> 8) & 0xFF;
    bytes[3] = n & 0xFF;
    NS_LOG_DEBUG("Converted uint32_t to char: " << bytes[0] << " " << bytes[1] << " " << bytes[2] << " " << bytes[3]);
    NS_LOG_FUNCTION (this << ":end");
    return bytes;
}

unsigned char* devAddress::random(unsigned char nwkAddr[],int size) 
{
    NS_LOG_FUNCTION (this << ":start");
    for (int i= 0; i < size; i++)
	{
		nwkAddr[i]= rand() % 255; 
	}
    NS_LOG_DEBUG("Random function provided a nwkAddress: " << &nwkAddr); 
    NS_LOG_FUNCTION (this << ":end");
	return nwkAddr; 
}

unsigned char * devAddress::NewDevAddr(uint32_t net, int nettype, unsigned char nwkAddr[],int size)
{
    NS_LOG_FUNCTION (this << ":start");
    NS_LOG_DEBUG("NewDevAddr function's nwkAddr: " );
     for (int i = 0 ; i < size ; i++)
	 { 
		  NS_LOG_DEBUG(std::hex << nwkAddr[i]); 
	 }
	 if (size < 4)
	 {
		 // nwkAddr = append(make([]byte, 4-len(nwkAddr)), nwkAddr...) TODO: fixes the error here 
         NS_LOG_DEBUG ("STILL NEEDS TO IMPLEMENT SIZE < 4"); 
	 }
	uint debugger = (NwkAddrBits(net,nettype)-1) % 8;
	 if ((nwkAddr[0] & debugger) > 0 )
	 {
		 // error .. i think why is this an error? 
		 NS_LOG_ERROR ("nwk_addr_bits , too many bits set in NwkAddr");
		 return NULL; 
	 }
	 // nwkID
	unsigned char* nwkID = new unsigned char[4];  
	nwkID = bit2char(net,nwkID);
	unsigned char *addr = new unsigned char[size];
	 addr = nwkAddr;
	 int t = nettype; 

	switch (t) {
	case 0:
		addr[0] |= nwkID[0] << 1;
		break; 
	case 1:
		addr[0] |= nwkID[0];
		break; 
	case 2:
		addr[1] |= nwkID[1] << 4;
		addr[0] |= nwkID[1] >> 4;
		addr[0] |= nwkID[0] << 4;
		break;
	case 3:
		addr[1] |= nwkID[2] << 1;
		addr[0] |= nwkID[2] >> 7;
		addr[0] |= nwkID[1] << 1;
		break; 
	case 4:
		addr[2] |= nwkID[2] << 7;
		addr[1] |= nwkID[2] >> 1;
		addr[1] |= nwkID[1] << 7;
		addr[0] |= nwkID[1] >> 1;
		break; 
	case 5:
		addr[2] |= nwkID[2] << 5;
		addr[1] |= nwkID[2] >> 3;
		addr[1] |= nwkID[1] << 5;
		addr[0] |= nwkID[1] >> 3;
		break; 
	case 6:
		addr[2] |= nwkID[2] << 2;
		addr[1] |= nwkID[2] >> 6;
		addr[1] |= nwkID[1] << 2;
		addr[0] |= nwkID[1] >> 6;
		break; 
	case 7:
		addr[3] |= nwkID[2] << 7;
		addr[2] |= nwkID[2] >> 1;
		addr[2] |= nwkID[1] << 7;
		addr[1] |= nwkID[1] >> 1;
		addr[1] |= nwkID[0] << 7;
		break; 
	default:
        NS_LOG_ERROR ("NewDevAddr function has invalid nettype:" << nettype); 
		return NULL; 
		//crashed
	}
	addr[0] |= 0xfe << (7 - t);
	delete[] nwkID; 
    NS_LOG_FUNCTION (this << ":end");
	return addr; 

}

unsigned char * devAddress::generateDevAddr(uint32_t net, int nettype)
{
    NS_LOG_FUNCTION (this << ":start");
    int size = NwkAddrLength(net,nettype);
    unsigned char *nwkAddr = new unsigned char[size]; // might be divided by 8 
	nwkAddr = random(nwkAddr,size); 
	unsigned char temp = 0xff >> (8-NwkAddrBits(net,nettype)%8); 
    nwkAddr[0] = nwkAddr[0] & temp ; // nwkAddr[0] = nwkAddr & 0xff >> (8-NewAddrBIts((id.addr)%8))
    unsigned char * devAddr = NewDevAddr(net,nettype,nwkAddr,size); 
	delete[] nwkAddr; 
    uint32_t temp1 = (devAddr[0] << 24 | devAddr[1] << 16 | devAddr[2] << 8 | devAddr[3]);
    m_addr = temp1; // a little worry about this... 
    NS_LOG_FUNCTION (this << ":end");
	return devAddr;  
}

// ATTRIBUTE_HELPER_CPP (devAddress);
}