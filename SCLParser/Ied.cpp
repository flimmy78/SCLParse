#include "StdAfx.h"
#include "Communication.h"
#include "Ied.h"



CSDI::~CSDI()
{
	std::list<CDAI*>::iterator daiIter = listDAI.begin();
	for(; daiIter != listDAI.end(); daiIter++)
		delete *daiIter;

	std::list<CSDI*>::iterator sdiIter = listSDI.begin();
	for(; sdiIter != listSDI.end(); sdiIter++)
		delete *sdiIter;
}

CDOI::~CDOI()
{
	std::list<CDAI*>::iterator daiIter = listDAI.begin();
	for(; daiIter != listDAI.end(); daiIter++)
		delete *daiIter;

	std::list<CSDI*>::iterator sdiIter = listSDI.begin();
	for(; sdiIter != listSDI.end(); sdiIter++)
		delete *sdiIter;
}

CAnyLN::~CAnyLN()
{
	std::list<CDataSet*>::iterator dsIter = listDataset.begin();
	for(; dsIter != listDataset.end(); dsIter++)
		delete *dsIter;

	std::list<CRptControl*>::iterator rptIter = listRptControl.begin();
	for(; rptIter != listRptControl.end(); rptIter++)
		delete *rptIter;

	std::list<CLogControl*>::iterator logIter = listLogControl.begin();
	for(; logIter != listLogControl.end(); logIter++)
		delete *logIter;

	std::list<CDOI*>::iterator doiIter = listDOI.begin();
	for(; doiIter != listDOI.end(); doiIter++)
		delete *doiIter;
}

CLN0::~CLN0()
{
	std::list<CGSEControl*>::iterator gseIter = listGSEControl.begin();
	for(; gseIter != listGSEControl.end(); gseIter++)
		delete *gseIter;

	std::list<CSMVControl*>::iterator smvIter = listSMVControl.begin();
	for(; smvIter != listSMVControl.end(); smvIter++)
		delete *smvIter;
}

CLDevice::~CLDevice()
{
	ListOfLN::iterator iter = listLNs.begin();
	for(; iter != listLNs.end(); iter++)
		delete *iter;
}

CServer::~CServer()
{
	std::list<CLDevice*>::iterator iter = listLDs.begin();
	for(; iter != listLDs.end(); iter++)
		delete *iter;
}

CIed::~CIed()
{
	ListOfAccessPoint::iterator iter = listAPs.begin();
	for(; iter != listAPs.end(); iter++)
		delete *iter;
}

