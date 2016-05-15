#ifndef _TYPE_IED_H_
#define _TYPE_IED_H_

#include <list>
#include <memory.h> 
#include <string.h>
#include <stdio.h>

#include "Communication.h"
#include "DataTypeTemplate.h"

class CInput;
class CGSEControl;
class CSMVControl;
class CDOI;
class CIed;
class CLDevice;
class CDataSet;

typedef struct FCDA 
{
	char * ldInst;
	char * lnClass;
	char * lnInst;
	char * prefix;
	char * doName;
	char * daName;
	char * fc;
	char * desc;
	CDOI * pDOI;
	bool flag;
	bool isRange;
	unsigned int  lineNo;
	int m_nStdNo;
	void initFCDA(){
		ldInst = "";
		lnClass = "";
		lnInst = "";
		prefix = "";
		doName = "";
		daName = "";
		desc = "";
		fc = "";
		flag = false;
		pDOI = NULL;
		isRange = false;
		lineNo = -1;
		m_nStdNo = -1;
	}
};
typedef std::list<FCDA*> ListOfFCDA; 

//typedef struct CDataSet 
//{
//	char * name;
//	char * desc;
//	ListOfFCDA FCDAs;
//	unsigned int  lineNo;
//	bool hasReport;
//	int reportType;//1：reportcontrol  2:logcontrol 3:gsecontrol 4:smvcontrol 5:settingcontrol 6:no report
//	CControl* pControl;
//	SettingControl* setControl;
//	void initCDataSet(){
//		name = "";
//		desc = "";
//		lineNo = -1;
//		hasReport = false;
//		reportType = -1;
//		pControl = NULL;
//		setControl = NULL;
//	}
//};

class CControl 
{
public:
	CControl() : name(""),desc(""),datSet(""),pDataSet(NULL){}
	virtual	~CControl(){}

	char * name;
	char * desc;
	char * datSet;
	CDataSet * pDataSet;
};

typedef struct SettingControl
{
	char * desc;
	unsigned int numOfSGs;
	unsigned int actSG;    //default = 1
	unsigned int lineNo;
	void initSettingControl(){
		desc = "";
		numOfSGs = -1;
		actSG = -1;
		lineNo = -1;
	}
};

class CDataSet 
{
public:
	CDataSet() : name(""),desc(""),lineNo(-1),hasReport(false),reportType(-1),pControl(NULL),setControl(NULL),flag(false){}
	~CDataSet(){};

	char * name;
	char * desc;
	ListOfFCDA FCDAs;
	unsigned int  lineNo;
	bool hasReport;
	int reportType;//1：reportcontrol  2:logcontrol 3:gsecontrol 4:smvcontrol 5:settingcontrol 6:no report
	CControl* pControl;
	SettingControl* setControl;
	bool flag;
};
typedef std::list<CDataSet*> ListOfDataSet;

class CGSEControl : public CControl
{
public:
	CGSEControl() : confRev(0),type(""),appID(""),pGSE(NULL),lineNo(-1),bChecked(false){}
	virtual ~CGSEControl(){}

	unsigned int confRev;
	std::list<char*> listIedNames;
	char * type;
	char * appID;     // actual goID
	GSE * pGSE;
	unsigned int  lineNo;
	bool bChecked;
};
typedef std::list<CGSEControl*> ListOfGSEControl;

typedef struct SMVOpts  
{
	bool refreshTime;
	bool smpSynced;
	bool smpRate;
	bool dataset;
	bool security;
	unsigned int  lineNo;
	void initSMVOpts(){
		refreshTime = false;
		smpSynced = false;
		smpRate = false;
		dataset = false;
		security = false;
		lineNo = -1;
	}
};

class CSMVControl : public CControl
{
public:
	CSMVControl() : confRev(0),smvID(""),multicast(true),smpRate(0),nofASDU(0),lineNo(-1){
		pSMV = NULL;
		memset(&smvOpts, 0, sizeof(smvOpts));
		smvOpts.initSMVOpts();
	}
	virtual ~CSMVControl(){}

	unsigned int confRev;
	std::list<char*> listIedNames;
	char * smvID;
	bool multicast;
	unsigned int  smpRate;
	unsigned int  nofASDU;
	SMVOpts smvOpts;
	SMV * pSMV;
	unsigned int  lineNo;
	bool bChecked;
};
typedef std::list<CSMVControl*> ListOfSMVControl;

typedef struct TrgOps
{
	bool dchg;
	bool qchg;
	bool dupd;
	bool period;
	unsigned int lineNo;
	void initTrgOps(){
		lineNo = -1;
	}
};

class CLogControl : public CControl
{
public:
	CLogControl() : intgPd(0),logName(""),logEna(true),reasonCode(true),lineNo(-1){
		memset(&trgOps, 0, sizeof(trgOps));
		trgOps.initTrgOps();
	}
	virtual ~CLogControl(){}

	unsigned int intgPd;
	TrgOps  trgOps;
	char * logName;
	bool logEna;
	bool reasonCode;
	unsigned int lineNo;
};

typedef struct OptFields
{
	bool seqNum;
	bool timeStamp;
	bool dataSet;
	bool reasonCode;
	bool dataRef;
	bool bufOvfl;
	bool entryID;
	bool configRef;
	bool segmentation;
	unsigned int lineNo;
	void initOptFields()
	{
		lineNo = -1;
	}
};

typedef struct ClientLN 
{
	char * iedName;
	char * ldInst;
	char * prefix;
	char * lnClass;
	char * lnInst;
	unsigned int lineNo;
	void initClientLN(){
		iedName = "";
		ldInst = "";
		prefix = "";
		lnClass = "";
		lnInst = "";
		lineNo = -1;
	}
};

class CRptEnabled
{
public:
	CRptEnabled() : desc(""){
		max = 1;
	}
	virtual ~CRptEnabled(){}

	char * desc;
	unsigned int max;     //default = 1
	std::list<ClientLN*> listClientLNs;
};

class CRptControl : public CControl 
{
public:
	CRptControl() : intgPd(0),rptID(""),confRev(0),buffered(false),bufTime(0),lineNo(-1){
		memset(&trgOps, 0, sizeof(trgOps));
		memset(&optFields, 0, sizeof(optFields));
		trgOps.initTrgOps();
		optFields.initOptFields();
	}
	virtual ~CRptControl(){}

	unsigned int intgPd;
	TrgOps  trgOps;
	char * rptID;
	unsigned int confRev;
	bool buffered;
	unsigned int bufTime;
	OptFields optFields;
	CRptEnabled rptEnabled;
	unsigned int lineNo;
};

typedef struct ExtRef  
{
	char * iedName;
	char * ldInst;
	char * lnInst;
	char * prefix;
	char * lnClass;
	char * doName;
	char * daName;
	char * intAddr;
	char * desc;
	bool flag;
	unsigned int  lineNo;
	int m_nStdNo;
	void initExtRef(){
		iedName = "";
		ldInst = "";
		lnInst = "";
		prefix = "";
		lnClass = "";
		doName = "";
		daName = "";
		intAddr = "";
		desc = "";
		lineNo = -1;
		m_nStdNo = -1;
		flag = false;
	}
};
typedef std::list<ExtRef*> ListOfExtRef; 

class CInputs
{
public:
	CInputs() :desc(""),lineNo(-1),flag(false){}
	virtual ~CInputs(){}

	char * desc;
	ListOfExtRef listExtRef;
	unsigned int  lineNo;
	bool flag;
};
typedef std::list<CInputs*> ListOfInput;



class CDAI 
{
public:
	CDAI() : desc(""),name(""),sAddr(""),valKind(Set),ix(0),lineNo(-1){}
	virtual ~CDAI(){}

	std::list<ValType*> listVals;
	char * desc;
	char * name;
	char * sAddr;
	ValKindEnum valKind;   //default = Set
	unsigned int ix;
	unsigned int lineNo;
};

class CSDI
{
public:
	CSDI() : desc(""),name(""),ix(0),lineNo(-1){}
	virtual ~CSDI();

	char * desc;
	char * name;
	unsigned int ix;
	std::list<CDAI*>  listDAI;
	std::list<CSDI*>  listSDI;
	unsigned int lineNo;
};

class CDOI
{
public:
	CDOI() : name(""),desc(""),ix(0),accessControl(0),lineNo(-1){}
	virtual ~CDOI();

	char * name;
	char * desc;
	unsigned int ix;
	std::list<CDAI*>  listDAI;
	std::list<CSDI*>  listSDI;
	char * accessControl;
	unsigned int lineNo;
};
typedef std::list<CDOI*> ListOfDOI;

class  CAnyLN
{
public:
	CAnyLN() : desc(""),lnType(""),inputs(0),lnClass(""),mop(""){}
	virtual ~CAnyLN();

public:
	char * desc;
	char * lnType;
	char * lnClass;
	char * mop;
	std::list<CDataSet*> listDataset;
	std::list<CRptControl*> listRptControl;
	std::list<CLogControl*> listLogControl;
	std::list<CDOI*> listDOI;
	CInputs * inputs;
};

class CLN0 : public CAnyLN
{
public:
	CLN0() : pLnType(0),lineNo(-1),hasSettingControl(false){
		inst[0] = 0;
		memset(&settingControl, 0, sizeof(settingControl));
		settingControl.initSettingControl();
		settingControl.actSG = 1;
	}
	virtual ~CLN0();

public:
	char inst[2];
	std::list<CGSEControl*> listGSEControl;
	std::list<CSMVControl*> listSMVControl;
	SettingControl settingControl;
	unsigned int lineNo;
	CLNodeType * pLnType;
	bool hasSettingControl;
};

class CLN : public CAnyLN
{
public:
	CLN() : prefix(""),inst(""),lnType(""),pLnType(NULL),lineNo(-1),info(""){}
	virtual ~CLN(){}

public:	
	char * prefix;
	char * inst;
	char * lnType;
	char * info;
	CLNodeType * pLnType;
	unsigned int lineNo;
};
typedef std::list<CLN*> ListOfLN; 


class CLNElement
{
public:
	char* Key;
	std::list<CAnyLN*> list_anyln;
};
typedef std::list<CLNElement*> ListofLNElement; 

class  CLDevice
{
public:
	CLDevice() : inst(""),desc(""),ln0(NULL),lineNo(-1),flag(false){}
	virtual ~CLDevice();

public:
	char * inst;
	char * desc;
	CLN0 * ln0;
	ListOfLN listLNs;
	ListofLNElement listLnEle;
	unsigned int lineNo;
	bool flag;
};
typedef std::list<CLDevice*> ListOfLDevice; 

typedef struct Authentication
{
	bool none;
	bool password;
	bool weak;
	bool strong;
	bool certificate;
	unsigned int lineNo;
	void initAuthentication(){
		lineNo = -1;
	}
};

typedef struct Association 
{
	char * kind;
	char * associationID;
	char * iedName;
	char * ldInst;
	char * prefix;
	char * lnClass;
	char * lnInst;
	unsigned int lineNo;
	void initAssociation(){
		kind = "";
		associationID = "";
		iedName = "";
		ldInst = "";
		prefix = "";
		lnClass = "";
		lnInst = "";
		lineNo = -1;
	}
};

class CServer
{
public:
	CServer() : desc(""),lineNo(-1){
		timeout = 30;
		auth.none = true;
	};
	virtual ~CServer();

public:
	char * desc;
	unsigned int timeout;   //default 30 secs
	Authentication auth;
	std::list<Association*> listAssociations;
	std::list<CLDevice*> listLDs;
	unsigned int lineNo;
};

class  CAccessPoint 
{
public:
	CAccessPoint() : name(""),desc(""),server(NULL),lineNo(-1),pConnectAP(NULL){
		router=clock=false;
	}
	virtual ~CAccessPoint(){
		if(server)
			delete server;
	}

public:
	char * name;
	char * desc;
	bool router;
	bool clock;
	CServer * server;
	unsigned int lineNo;
    CConnectedAP *pConnectAP;
};
typedef std::list<CAccessPoint*> ListOfAccessPoint; 

class CLDDict
{
public:
	char* devName;
	ListofLNElement list_ln;
};
typedef std::list<CLDDict*> ListofLDDict; 

class CAPDict
{
public:
	char* apName;
	ListofLDDict list_ld;
};
typedef std::list<CAPDict*> ListofAPDict; 

class CIEDDict
{
public:
	char* iedName;
	ListofAPDict list_ap;
};
typedef std::list<CIEDDict*> ListofIEDDict; 

class CSCLDict
{
public:
	ListofIEDDict list_ied;
};

typedef enum{
	_Conf, Dyn, Fix, NO
}OnlineSettingEnum;

typedef struct  
{
	bool dynAssociation;
	bool settingGroups;   //selectActiveSG
	bool sgEdit;
	bool confSG;
	bool getDirectory;
	bool getDataDefinition;
	bool getDataDirectory;
	bool getDataSetValue;
	bool setDataSetValue;
	bool dataSetDirectory;
	unsigned int maxConfDataset;
	unsigned int maxConfDatasetAttributes;
	bool confDatasetModify;
	unsigned int maxDynDataset;
	unsigned int maxDynDatasetAttributes;
	bool readWrite;
	bool timeActivatedControl;
	unsigned int maxRptControl;
	bool getCBValues;
	unsigned int maxLogControl;
	OnlineSettingEnum rptCbName;
	OnlineSettingEnum rptDataset;
	OnlineSettingEnum rptID;
	OnlineSettingEnum rptOptFields;
	OnlineSettingEnum rptBufTime;
	OnlineSettingEnum rptTrgOps;
	OnlineSettingEnum rptIntgPd;
	OnlineSettingEnum logCbName;
	OnlineSettingEnum logDataset;
	OnlineSettingEnum logEna;
	OnlineSettingEnum logTrgOps;
	OnlineSettingEnum logIntgPd;
	OnlineSettingEnum gseCbName;
	OnlineSettingEnum gseDataset;
	OnlineSettingEnum gseAppid;   //goId
	OnlineSettingEnum smvCbName;
	OnlineSettingEnum smvDataset;
	OnlineSettingEnum svID;
	OnlineSettingEnum smvOptFields;
	OnlineSettingEnum smvSmpRate;
	bool fixLNprefix;
	bool fixLNinst;
	bool GSEDir;
	bool GOOSE;              //goose server or client
	unsigned int maxGoose;   //0 for client
	bool GSSE;
	unsigned int maxGsse;
	bool fileHandling;
	unsigned int lineNo;
	bool hasConfDataSet;
	bool hasConfReport;
	bool hasConfLogCtl;
	bool hasReportSet;
	bool hasLogSet;
	bool hasGoose;
	void intService(){
		hasConfDataSet = false;
		hasConfReport = false;
		hasConfLogCtl = false;
		hasReportSet = false;
		hasLogSet = false;
		hasGoose = false;
		rptCbName = NO;
		rptDataset = NO;
		rptID = NO;
		rptOptFields = NO;
		rptBufTime = NO;
		rptTrgOps = NO;
		rptIntgPd = NO;
		logCbName = NO;
		logDataset = NO;
		logEna = NO;
		logTrgOps = NO;
		logIntgPd = NO;
		gseCbName = NO;
		gseDataset = NO;
		gseAppid = NO;   //goId
		smvCbName = NO;
		smvDataset = NO;
		svID = NO;
		smvOptFields = NO;
		smvSmpRate = NO;
	}
}Service;

class  CIed
{
public:
	CIed() : name(""),desc(""),manufacturer(""),type(""),configVersion(""),lineNo(-1),hasServers(false){
		memset(&services, 0, sizeof(services));
		services.intService();
	};
	virtual ~CIed();

public:
	char * name;
	char * desc;
	char * manufacturer;
	char * type;
	char * configVersion;
	Service services;
	bool hasServers;
	ListOfAccessPoint listAPs;
	unsigned int lineNo;   //在原始SCl文件中的行号
};
typedef std::list<CIed*> ListOfIed; 



#endif