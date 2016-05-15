#ifndef _TYPE_COMMUNICATION_H_
#define _TYPE_COMMUNICATION_H_

#include <list>
#include <memory.h> 
#include <string.h>
#include <stdio.h>


class CAccessPoint;
class CGSEControl;
class CSMVControl;

typedef struct  
{
	char * conn_type;
	char * p_type;
	char * p_plug;
	char * p_cable;
	char * p_port;
	unsigned int lineNo;    //在原始SCl文件中的行号
}PhysConn;
typedef std::list<PhysConn*> ListOfPhysConn;

typedef struct  
{
	char *  ip;
	char *  ip_subnet;
	char *  ip_gateway;
	char *  osi_nsap;
	char *  osi_tsel;
	char *  osi_psel;
	char *  osi_ssel;
	char *  osi_ap_title;
	char *  osi_ap_invoke;
	char *  osi_ae_qualifier;
	char *  osi_ae_invoke;
	char *  mac_address;
	char *  vlan_id;
	char *  vlan_priority;
	char *  appid;
	char *  sntp_port;
	char *  mms_port;
	unsigned int lineNo;
}Address;
typedef std::list<Address*> ListOfAddress; 

typedef struct  
{
	Address * address;
	char * ldInst;
	char * cbName;
	int minTime;    //unit must be ms, schema promises
	int maxTime;
	char * desc;
	unsigned int lineNo;
	CGSEControl * pGSEContrl;
}GSE;
typedef std::list<GSE*> ListOfGSE; 

typedef struct  
{
	Address * address;
	char * ldInst;
	char * cbName;
	char * desc;
	unsigned int lineNo;
	CSMVControl * pSMVControl;
}SMV;
typedef std::list<SMV*> ListOfSMV; 

class CConnectedAP
{
public:
	CConnectedAP() : pAddress(0),iedName(0),apName(0),desc(0),pAccessPoint(0),lineNo(-1){}
	virtual ~CConnectedAP(){}

	Address * pAddress;
	ListOfGSE listGSE;
	ListOfSMV listSMV;
    ListOfPhysConn listPhysConn;
	char *  iedName;
	char *  apName;
	char *  desc;
	unsigned int lineNo;
	CAccessPoint *pAccessPoint;
};
typedef std::list<CConnectedAP*> ListOfConnAP; 

class CSubNetwork
{
public:
	CSubNetwork():name(0),type(0),desc(0),bitRate(0),lineNo(-1){}
	virtual ~CSubNetwork(){
		ListOfConnAP::iterator iter = listConnAPs.begin();
		for(; iter != listConnAPs.end(); iter++)
			delete *iter;
	}

	char *  name;
	char *  type;
	char *  desc;
	int  bitRate;   //unit must be Mb, schema promises
	unsigned int lineNo;
	ListOfConnAP listConnAPs;
};
typedef std::list<CSubNetwork*> ListOfSubNetwork;

class CCommunication
{
public:
	CCommunication(){desc=NULL;lineNo=-1;}
	virtual ~CCommunication(){
		ListOfSubNetwork::iterator iter = subnetworks.begin();
		for(; iter != subnetworks.end(); iter++)
			delete *iter;
	}

	char * desc;
	ListOfSubNetwork subnetworks;
	int lineNo;
};


#endif