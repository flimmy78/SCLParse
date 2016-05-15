#ifndef _SCL_H_
#define _SCL_H_

#include <list>
#include <memory.h> 
#include <string.h>
#include <stdio.h>

#include "PrivateInfo.h"
#include "DataTypeTemplate.h"
#include "Communication.h"
#include "Ied.h"
#include "ProgressNotifier.h"
#include "CheckNotifier.h"
#include "StackString.h"
#include "LibSCLParser.h"

#define FLAG_EXIST_M 0
#define FLAG_EXIST_C 1
#define FLAG_EXIST_O 2


/*单条的Schema规则*/
typedef struct SPECIAL_SCHEMA_STRUCT{

	char RegEx_IP[100];
	char RegEx_OSI_NSAP[100];
	char RegEx_OSI_TSEL[100];
	char RegEx_OSI_SSEL[100];
	char RegEx_OSI_PSEL[100];
	char RegEx_OSI_AP_Title[100];
	char RegEx_OSI_AP_Invoke[100];
	char RegEx_MAC_Address[100];
	char RegEx_APPID[100];
	char RegEx_VLAN_PRIORITY[100];
	char RegEx_VLAN_ID[100];
	char RegEx_SGCC_DataSetName[256];
	char RegEx_SGCC_ReportCBName[256];
	char RegEx_SGCC_ACCPName[256];
	char RegEx_SGCC_LDName[256];
	char RegEx_SGCC_GSEName[256];
	char RegEx_SGCC_SMVName[256];
	char RegEx_SGCC_IEDName[256];

	int  CheckDeviceTypeEn;
	char DeviceType[512];
	char DeviceTypeEx[512];

	char strDeviceLNFile[256];
	char strDeviceDSFile[256];
	char strDeviceInputsFile[256];

	int  ManufacturerIsnaritech;
	int  SGCCVersion;

	int sgccCheck;
	int commIsCheck;
	int sub;
	int connAP;
	int phys;
	int gse;
	int smv;
	int address;

	int commCh;
	int iedName;
	int manu;
	int configVersion;
	int configVersionType;
	int appoint;
	int ld;
	int inputs;

	int serIsCheck;
	int configDataset;
	int configRP;
	int configLog;
	int rpSet;
	int logSet;
	int goose;

	int datasetIsCheck;
	int dataset;
	int fcdaLd;
	int fcdaHas;
	int fcdaNum;
	int fcdaValid;
	int fcdaDo;

	int controlIsCheck;
	int rpCtrol;
	int rpCtrolAttr;
	int rpNum;
	int logCtrol;
	int logCtrolAttr;
	int logNum;
	int gseCtrol;
	int gseCtrolAttr;
	int smvCtrol;
	int smvCtrolAttr;
	int setCtrol;

	int lnIsCheck;
	int lphd;
	int lnInst;
	int lnValid;
	int lnDesc;
	int lnSiunit;
	int descDu;
	int descRep;
	int namplt;
	int configRev;
	int swRev;
	int ctlModel;
	int sboTimeOut;

	int templateIsCheck;
	int lnode;
	int lnodeRy;
	int lnodeEmp;
	int dos;
	int doRy;
	int doEmp;
	int da;
	int daRy;
	int daEmp;
	int enums;
	int enumRy;
	int enumEmp;

} SPECIAL_SCHEMA;


typedef struct  
{
	char * version;
	char * revision;
	char * when;
	char * who;
	char * what;
	char * why;
	unsigned int lineNo;
}Hitem;

class CHistory
{
public:
	CHistory() : lineNo(-1){}
	~CHistory(){}

	std::list<Hitem*> listHitem;
	unsigned int lineNo;
};

class SCL_API CHeader
{
public:
	CHeader() : id(0),version(0),revision(0),toolID(0),nameStructure(0),lineNo(){}
	~CHeader(){}
	void Print(FILE *fp);

	char * id;
	char * version;
	char * revision;
	char * toolID;
	char * nameStructure;
	//CHistory* history;
	std::list<Hitem*> listHitem;
	unsigned int lineNo;
};


class CProgressPosInfo
{
public:
	int m_nStartPos;
	int m_nTotalLen;
};


class SCL_API CSclMem
{
public:
	CSclMem();
	~CSclMem();
	char* AllocMem(unsigned int size);
	char* AllocAndCopy(char* str);
	void Clear();

private:
	std::list<char *> m_memlist;
	char* m_curMem;
	char* m_curMemPos;
};

typedef enum {
	TYPE_NONE = -1,
	TYPE_SCD = 0,
	TYPE_ICD = 1,
	TYPE_CID = 2,
	TYPE_SSD = 3
} ENUM_SCLFILE;


class SCL_API CScl
{
public:
	CScl();
	CScl(CProgressNotifier* pProgressNotifier);
	CScl(CProgressNotifier* pProgressNotifier,CCheckNotifier * pCheckNotifier);
	virtual ~CScl(){};

	void BuildRelation();
	void BuildRelationForTpl();
	void SetStandardDoDict(CDoDict* pDict);
	void BuildRelationTable(CScl* xmlFile,CScl* sgccTpl,CScl* iecTpl);
	GSE* FindGSE(char* iedName, char*apName, char* ldInst, char* cbName);
	SMV* FindSMV(char* iedName, char*apName, char* ldInst, char* cbName);
	CLNodeType* FindLNodeType(char* lnClass, char* lnType);
	CLNodeType* FindLNodeType(char* lnType);
	DO* findDO(CLNodeType* ln,char* ch);
	CDOType* FindDOType(char* type);
	CDAType* FindDAType(char* type);
	CEnumType* FindEnumType(char* type);
	CDataSet* FindDataSet(CAnyLN *pLn, char *name,int type);
	void PrintScl(char * file);

	bool CheckDoDaValid(char * do_name,char * da_name,char fc[3],char * lntype,bool CheckFcEnable);
	int GetBdaDataType(char *bType);
	bool CheckDoDaRefValid(StackString* stack_ref,char * lntype,int& bda_data_type,CEnumType ** pEnumType,unsigned long lineNo);
    bool CheckValValid(char* strVal,int data_type,CEnumType * pEnumType);
	void CheckLNValid(char * lntype,unsigned long lineNo);
	char* GetIEDIP(char * strIedName,char * strSubNetwork);
	char* GetManufacturer(char * strIedName);
public:
	std::list<CNariPrivate*>listNariPrivates;
	CHeader header;
	CCommunication communication;
	std::list<CIed*> listIeds;
	CDataTypeTemplate dataTypeTemplate;

	CProgressNotifier * m_pProgressNotifier;
	CCheckNotifier * m_pCheckNotifier;

	CDoDict* m_pStdDoDict;//标准的Do字典
	ENUM_SCLFILE m_fileType;
};
typedef std::list<CScl*> ListOfScl;


class CLNInfo
{
public:
	CLNInfo();
	CLNInfo(CProgressNotifier* pProgressNotifier);
	CLNInfo(CProgressNotifier* pProgressNotifier,CCheckNotifier * pCheckNotifier);
	virtual ~CLNInfo(){};

public:
	std::list<CLDevice*> listDevs;

	CProgressNotifier * m_pProgressNotifier;
	CCheckNotifier * m_pCheckNotifier;
};
typedef std::list<CLNInfo*> ListOfLNInfo;

extern CSclMem sclMem;


extern void DeleteUnvisibleChar(char * str);
extern bool IsUnsignedInteger(char* lpszStr);
extern void GetFileNameExt(char * FileName, char* ExtName);

extern OnlineSettingEnum GetOnlineSetting(char * text);
extern bool String2Bool(char * text);
extern ValKindEnum String2ValKind(char * text);


#endif
