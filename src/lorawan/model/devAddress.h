//dev address header goes here 
#ifndef DEVADDRESS_H
#define DEVADDRESS_H

#include "lorawan.h"
#include <ns3/object.h>
#include <stdlib.h>
#include "ns3/attribute-helper.h"

//Creating Dev Address properly 
namespace ns3 {



class devAddress
{
public:

/*

netID must match with type otherwise it would crash TODO: CHECK TYPE WITH NETID

*/
explicit devAddress(uint32_t netID, int type); 

explicit devAddress(uint32_t netID, int type,uint32_t addr); 

uint32_t Get (void) const;
uint32_t GetID (void) const; 
int GetIDType (void) const; 

friend bool operator == (devAddress const &a, devAddress const &b);

friend bool operator != (devAddress const &a, devAddress const &b);

Ipv4Address convertIp4(void) const; 

uint32_t reshuffle(void);

bool IsInitialized (void) const;

private: 


uint32_t    m_addr; //addr 
int         type; //netID type 
uint32_t    netID; //netID
bool m_initialized; // explicitily initialized

private: 

uint NwkAddrBits (uint32_t net, int nettype); 



int NwkAddrLength(uint32_t net, int nettype);

unsigned char* bit2char(uint32_t n,unsigned char bytes[]);

unsigned char* random(unsigned char nwkAddr[],int size);

unsigned char * NewDevAddr(uint32_t net, int nettype, unsigned char nwkAddr[],int size);

unsigned char *  generateDevAddr(uint32_t net, int nettype);
};
// ATTRIBUTE_HELPER_HEADER (devAddress);
} //namespace ns3
#endif