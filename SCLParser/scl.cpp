//#include "stdafx.h"
#include <stdlib.h>
#include "scl.h"
#include "SCDparse.h"
typedef unsigned char BYTE;
#define MAX_PATH 260
const int MAX_SIZE_OUTPUT_FILE = 4096*1024;


bool IsBitString(char* lpszStr,int len)
{
    char szTmp[MAX_PATH]="";
    if(!*lpszStr)
        return false;
	if(len != -1)
	{
		if(strlen(lpszStr) != len)
			return false;
	}
    sscanf(lpszStr," %[0-1]",szTmp);
    if(strcmp(lpszStr,szTmp))
        return false;
    return true;
}

bool IsUnsignedInteger(char* lpszStr)
{
    char szTmp[MAX_PATH]="";
    if(!*lpszStr)
        return false;
    sscanf(lpszStr," %[0-9]",szTmp);
    if(strcmp(lpszStr,szTmp))
        return false;
    return true;
}

bool IsInteger(char* lpszStr)
{
    char szTmp[MAX_PATH]="";
    if(!*lpszStr)
        return false;
    sscanf(lpszStr," %[-,0-9]",szTmp);
    if(strcmp(lpszStr,szTmp))
        return false;
    return true;
}

bool IsNumeric(char* lpszStr)
{
    char szTmp[MAX_PATH]="";
	char *p = NULL;
    if(!*lpszStr)
        return false;
    sscanf(lpszStr," %[-,.,0-9]",szTmp);
    if(strcmp(lpszStr,szTmp))
        return false;
    if(p=strstr(szTmp,"."))
        if(p=strstr(p+1 , "."))
            return false;
	if(p=strstr(szTmp,"-"))
        if(p!=szTmp)
            return false;
    return true;
}


bool GetTwoSubString(char * pString, char * pFirString,char * pSecString)
{
	char *token, *end;
	int line_no = 0;

	if(pString == NULL ||pFirString == NULL || pSecString == NULL)
	{
		printf("Invalid Char Pointer.Error..");
		return false;
	}
	
	bool bFind = false;
	for (token=pString, end=pString;(*end ) && (*end != '\0'); end++)
	{
		if( *end == '.')
		{
			bFind = true;
			*end = '\0';
			strcpy(pFirString,token);
			*end = '.';
			strcpy(pSecString,end+1);
		}
	}

	if(!bFind)
	{
		strcpy(pFirString,pString);
		strcpy(pSecString,"");
	}
	return true;
}

bool GetThirdSubString(char * pString, char * pFirString,char * pSecString,char *pThirdString)
{
	char *token, *end;
	int line_no = 0;
	int nCount;

	if(pString == NULL ||pFirString == NULL || pSecString == NULL || pThirdString == NULL)
	{
		printf("Invalid Char Pointer.Error..");
		return false;
	}

	strcpy(pFirString,"");
	strcpy(pSecString,"");
	strcpy(pThirdString,"");

	nCount = 0;
	bool bFind = false;
	for (token=pString, end=pString;(*end ) && (*end != '\0'); end++)
	{
		if( *end == '.')
		{
			bFind = true;
			nCount++;
			
			*end = '\0';
			if(nCount == 1)
			{
				strcpy(pFirString,token);
				*end = '.';
				strcpy(pSecString,end+1);
			}
			else
			{
				strcpy(pSecString,token);
				*end = '.';
				strcpy(pThirdString,end+1);
			}
			token = end + 1;
		}
	}

	if(!bFind)
	{
		strcpy(pFirString,pString);
	}

	return true;
}

/*去除一个字符串的首尾非可见字符：比如换行符之类的*/
void DeleteUnvisibleChar(char * str)
{
	if(str == NULL)
		return;
	int len =  strlen(str);
	if(len<=0)
		return;

	char * pArray = new char[len+1];
	strncpy(pArray,str,len+1);
	char c;

	//去掉尾部的非可见字符
	int i;
	for(i =len-1;i>=0;i--)
	{
		c = pArray[i];
		if((BYTE)c <= 29) //非可见字符
		{
			pArray[i]=0;
		}
		else
		{
			break;
		}
	}

	//去掉头部的非可见字符
	char * p = pArray;
	for(i =0;i<strlen(pArray);i++)
	{
		c = pArray[i];
		if((BYTE)c <= 29) //非可见字符
		{
			p++;
		}
		else
		{
			break;
		}
	}
	strcpy(str,p);
	delete[] pArray;
	pArray = NULL;
}



OnlineSettingEnum GetOnlineSetting(char * text)
{
	if(text == NULL)
		return NO;
	if(!strcmp(text, "Conf"))
		return _Conf;
	else if(!strcmp(text, "Dyn"))
		return Dyn;
	else if(!strcmp(text, "Fix"))
		return Fix;
	else
		return NO;
}

bool String2Bool(char * text)
{
	if(text == NULL)
		return false;
	if(!strcmp(text, "true"))
		return true;
	else
		return false;
}

ValKindEnum String2ValKind(char * text)
{
	if(text == NULL)
		return Set;
	if(!strcmp(text, "Spec"))
		return Spec;
	else if(!strcmp(text, "Conf"))
		return Conf;
	else if(!strcmp(text, "RO"))
		return RO;
	else
		return Set;
}

/*********************************************/

#define MEM_BLOCK_SIZE  4096000
CSclMem sclMem;

CSclMem::CSclMem()
{
	m_curMem = (char*) new int[MEM_BLOCK_SIZE/sizeof(int)];
	memset(m_curMem, 0, MEM_BLOCK_SIZE);
	//m_curMem = (char*) calloc(4, MEM_BLOCK_SIZE/4);
	m_curMemPos = m_curMem;
	m_memlist.push_back(m_curMem);
}

CSclMem::~CSclMem()
{
	Clear();
}

void CSclMem::Clear()
{
	//std::list<char*>::iterator iter;
	
	//for(iter=m_memlist.begin(); iter!=m_memlist.end(); iter++){
	//	char * p = *iter;
	//	delete p;
	//	p = NULL;
	//	//free(p);
	//}
	m_memlist.clear();
}

char* CSclMem::AllocMem(unsigned int size)
{
	char * p;

	if(m_curMemPos + size <= m_curMem + MEM_BLOCK_SIZE){
		p = m_curMemPos;
		m_curMemPos += size;
		m_curMemPos = (char*) (((long)m_curMemPos + 3) & 0xfffffffffffffffc);
		return p;
	}
	else{
		//m_curMem = (char*) calloc(4, MEM_BLOCK_SIZE/4);
		m_curMem = (char*) new int[MEM_BLOCK_SIZE/sizeof(int)];
		memset(m_curMem, 0, MEM_BLOCK_SIZE);
		m_curMemPos = m_curMem;
		m_memlist.push_back(m_curMem);
		p = m_curMemPos;
		m_curMemPos += size;
		m_curMemPos = (char*) (((long)m_curMemPos + 3) & 0xfffffffffffffffc);
		return p;
	}
}

char* CSclMem::AllocAndCopy(char* str)
{
	int len;
	char * p;

	if(str == NULL)
		return NULL;

	len = strlen(str);
	p = AllocMem(len+1);
	if(p)
		memcpy(p, str, len+1);
	return p;
}

/*********************************************/
void CHeader::Print(FILE* fp)
{
	fprintf(fp, "<Header ");
	if(id)			fprintf(fp, "id=%s ", id);
	if(version)		fprintf(fp, "version=%s ", version);
	if(revision)	fprintf(fp, "revision=%s ", revision);
	if(toolID)		fprintf(fp, "toolID=%s ", toolID);
	if(nameStructure) fprintf(fp, "nameStructure=%s ", nameStructure);

	if(listHitem.size() != 0)
	{
		fprintf(fp, "\n");
		std::list<Hitem*>::iterator iter = listHitem.begin();
		for(; iter != listHitem.end(); iter++)
		{
			Hitem *pHitem = (Hitem*) (*iter);
			fprintf(fp, "<Hitem ");
			if(pHitem->version)		fprintf(fp, "version=%s ", pHitem->version);
			if(pHitem->revision)	fprintf(fp, "revision=%s ", pHitem->revision);
			if(pHitem->when)		fprintf(fp, "when=%s ", pHitem->when);
			fprintf(fp, "/>");
		}
	}
	else
		fprintf(fp, "/>\n");

	/*if(history){
		if(history->listHitem.size() != 0)
		{
			fprintf(fp, "\n");
			std::list<Hitem*>::iterator iter = history->listHitem.begin();
			for(; iter != history->listHitem.end(); iter++)
			{
				Hitem *pHitem = (Hitem*) (*iter);
				fprintf(fp, "<Hitem ");
				if(pHitem->version)		fprintf(fp, "version=%s ", pHitem->version);
				if(pHitem->revision)	fprintf(fp, "revision=%s ", pHitem->revision);
				if(pHitem->when)		fprintf(fp, "when=%s ", pHitem->when);
				fprintf(fp, "/>");
			}
		}
		else
			fprintf(fp, "/>\n");
	}*/	
}


CScl::CScl()
	: m_pProgressNotifier(0), m_pCheckNotifier(0)
{
}

CScl::CScl(CProgressNotifier* pProgressNotifier)
	: m_pProgressNotifier(pProgressNotifier), m_pCheckNotifier(0)
{
}

CScl::CScl(CProgressNotifier* pProgressNotifier,CCheckNotifier * pCheckNotifier)
{
	m_pProgressNotifier = pProgressNotifier;
	m_pCheckNotifier = pCheckNotifier;
}


GSE* CScl::FindGSE(char* iedName, char*apName, char* ldInst, char* cbName)
{
	if(iedName==NULL || apName==NULL || ldInst==NULL || cbName==NULL)
		return NULL;

	std::list<CSubNetwork*>::iterator subnetIter = communication.subnetworks.begin();
	for(; subnetIter != communication.subnetworks.end(); subnetIter++)
	{
		CSubNetwork* subnet = *subnetIter;
		std::list<CConnectedAP*>::iterator apIter = subnet->listConnAPs.begin();
		for(; apIter != subnet->listConnAPs.end(); apIter++)
		{
			CConnectedAP *pAP = *apIter;
			if(!strcmp(iedName, pAP->iedName) && !strcmp(apName, pAP->apName))
			{
				std::list<GSE*>::iterator gseIter = pAP->listGSE.begin();
				for(; gseIter != pAP->listGSE.end(); gseIter++)
				{
					GSE* pGSE = *gseIter;
					if(!strcmp(ldInst, pGSE->ldInst) && !strcmp(cbName, pGSE->cbName))
						return pGSE;
				}
			}
		}
	}
	return NULL;
}

SMV* CScl::FindSMV(char* iedName, char*apName, char* ldInst, char* cbName)
{
	if(iedName==NULL || apName==NULL || ldInst==NULL || cbName==NULL)
		return NULL;

	std::list<CSubNetwork*>::iterator subnetIter = communication.subnetworks.begin();
	for(; subnetIter != communication.subnetworks.end(); subnetIter++)
	{
		CSubNetwork* subnet = *subnetIter;
		std::list<CConnectedAP*>::iterator apIter = subnet->listConnAPs.begin();
		for(; apIter != subnet->listConnAPs.end(); apIter++)
		{
			CConnectedAP *pAP = *apIter;
			if(!strcmp(iedName, pAP->iedName) && !strcmp(apName, pAP->apName))
			{
				std::list<SMV*>::iterator smvIter = pAP->listSMV.begin();
				for(; smvIter != pAP->listSMV.end(); smvIter++)
				{
					SMV* pSMV = *smvIter;
					if(!strcmp(ldInst, pSMV->ldInst) && !strcmp(cbName, pSMV->cbName))
						return pSMV;
				}
			}
		}
	}
	return NULL;
}

CLNodeType* CScl::FindLNodeType(char* lnClass, char* lnType)
{
	if(lnClass==NULL || lnType==NULL)
		return NULL;

	std::list<CLNodeType*>::iterator lnTypeIter = dataTypeTemplate.listLnTypes.begin();
	for(; lnTypeIter != dataTypeTemplate.listLnTypes.end(); lnTypeIter++)
	{
		CLNodeType *pLnType = *lnTypeIter;
		if(!strcmp(lnClass, pLnType->lnClass) && !strcmp(lnType, pLnType->id))
			return pLnType;
	}
	return NULL;
}

CLNodeType* CScl::FindLNodeType(char* lnType)
{
	if(lnType == NULL)
		return NULL;
	
	std::list<CLNodeType*>::iterator lnTypeIter = dataTypeTemplate.listLnTypes.begin();
	for(; lnTypeIter != dataTypeTemplate.listLnTypes.end(); lnTypeIter++)
	{
		CLNodeType *pLnType = *lnTypeIter;
		if (!strcmp(lnType, pLnType->id))
			return pLnType;
	}
	return NULL;
}

DO* CScl::findDO(CLNodeType* ln,char* ch)
{
	DO* cdo = NULL;
	if(!ln){
		return cdo;
	}
	if(strlen(ch)==0){
		return cdo;
	}
	ListOfDo::iterator iterB;
	DO * pDo = NULL;
	for(iterB = ln->listDOs.begin();iterB != ln->listDOs.end();iterB++)
	{
		pDo = *iterB;
		if(!pDo){
			continue;
		}
		if(strcmp(pDo->name,ch)==0){
			cdo = pDo;
			break;
		}
	}
	return cdo;
}

CDOType* CScl::FindDOType(char* type)
{
	if(type == NULL)
		return NULL;

	std::list<CDOType*>::iterator doTypeIter = dataTypeTemplate.listDOTypes.begin();
	for(; doTypeIter != dataTypeTemplate.listDOTypes.end(); doTypeIter++)
	{
		CDOType *pDoType = *doTypeIter;
		if(!strcmp(type, pDoType->id))
			return pDoType;
	}
	return NULL;
}

CDAType* CScl::FindDAType(char* type)
{
	if(type==NULL || !strcmp(type, ""))
		return NULL;

	std::list<CDAType*>::iterator daTypeIter = dataTypeTemplate.listDATypes.begin();
	for(; daTypeIter != dataTypeTemplate.listDATypes.end(); daTypeIter++)
	{
		CDAType * pDaType = *daTypeIter;
		if(!strcmp(type, pDaType->id))
			return pDaType;
	}
	return NULL;
}

CEnumType* CScl::FindEnumType(char* type)
{
	if(type==NULL || !strcmp(type, ""))
		return NULL;

	std::list<CEnumType*>::iterator enumTypeIter = dataTypeTemplate.listEnumTypes.begin();
	for(; enumTypeIter != dataTypeTemplate.listEnumTypes.end(); enumTypeIter++)
	{
		CEnumType* pEnumType = *enumTypeIter;
		if(!strcmp(type, pEnumType->id))
			return pEnumType;
	}
	return NULL;
}

CDataSet* CScl::FindDataSet(CAnyLN *pLn, char *name,int type)
{
	if(pLn==NULL || name==NULL)
		return NULL;

	std::list<CDataSet*>::iterator datasetIter = pLn->listDataset.begin();
	for(; datasetIter != pLn->listDataset.end(); datasetIter++)
	{
		CDataSet *pDataset = *datasetIter;
		if(type==1){
			if (!strcmp(name, pDataset->name))
				return pDataset;
		}
		else if(type==2){
			if (!strncmp(name, pDataset->name,strlen(name)))
				return pDataset;
		}
	}
	return NULL;
}

void CScl::SetStandardDoDict(CDoDict* pDict)
{
	m_pStdDoDict = pDict;
}

void CScl::BuildRelationForTpl()
{
	std::list<CLNodeType*>::iterator lnTypeIter = dataTypeTemplate.listLnTypes.begin();
	for(; lnTypeIter != dataTypeTemplate.listLnTypes.end(); lnTypeIter++)
	{
		CLNodeType *pLnType = *lnTypeIter;
		std::list<DO*>::iterator doIter = pLnType->listDOs.begin();
		for(; doIter != pLnType->listDOs.end(); doIter++)
		{
			DO *pDo = *doIter;
			if((pDo->pDOType = FindDOType(pDo->type)) != NULL)
				pDo->pDOType->bUsed = true;
		}
	}

	//建立DOType's SDO/DA与DOType、DAType及EnumType的关系
	std::list<CDOType*>::iterator doTypeIter = dataTypeTemplate.listDOTypes.begin();
	for(; doTypeIter != dataTypeTemplate.listDOTypes.end(); doTypeIter++)
	{
		CDOType *pDoType = *doTypeIter;
		//for SDO
		std::list<SDO*>::iterator sdoIter = pDoType->listSDOs.begin();
		for(; sdoIter != pDoType->listSDOs.end(); sdoIter++)
		{
			SDO *pSdo = *sdoIter;
			if((pSdo->pDOType = FindDOType(pSdo->type)) != NULL)
				pSdo->pDOType->bUsed = true;
		}
		//for DA
		std::list<CDA*>::iterator daIter = pDoType->listDAs.begin();
		for(; daIter != pDoType->listDAs.end(); daIter++)
		{
			CDA *pDa = *daIter;
			if(pDa->type==NULL || !strcmp(pDa->type, ""))  //基本数据类型
				continue;

			if(!strcmp(pDa->bType, "Struct"))
			{
				if((pDa->pDAType = FindDAType(pDa->type)) != NULL)
					pDa->pDAType->bUsed = true;
			}
			else if(!strcmp(pDa->bType, "Enum"))
			{
				if((pDa->pEnumType = FindEnumType(pDa->type)) != NULL)
					pDa->pEnumType->bUsed = true;
			}
		}
	}

	//建立DAType's BDA与DAType和EnumType的关联
	std::list<CDAType*>::iterator daTypeIter = dataTypeTemplate.listDATypes.begin();
	for(; daTypeIter != dataTypeTemplate.listDATypes.end(); daTypeIter++)
	{
		CDAType *pDaType = *daTypeIter;
		std::list<CBDA*>::iterator bdaIter = pDaType->listBDAs.begin();
		for(; bdaIter != pDaType->listBDAs.end(); bdaIter++)
		{
			CBDA* pBda = *bdaIter;
			if(pBda->type==NULL || !strcmp(pBda->type, ""))
				continue;

			if(!strcmp(pBda->bType, "Struct"))
			{
				if((pBda->pDAType = FindDAType(pBda->type)) != NULL)
					pBda->pDAType->bUsed = true;
			}
			else if(!strcmp(pBda->bType, "Enum"))
			{
				if((pBda->pEnumType = FindEnumType(pBda->type)) != NULL)
					pBda->pEnumType->bUsed = true;
			}
		}
	}
}

void CScl::BuildRelation()
{
	//建立LN与LNodeType之间关联，并置LNodeType的使用标志
	std::list<CIed*>::iterator iedIter = listIeds.begin();
	for(; iedIter != listIeds.end(); iedIter++)
	{
		CIed *pIed = *iedIter;
		std::list<CAccessPoint*>::iterator apIter = pIed->listAPs.begin();
		for(; apIter != pIed->listAPs.end(); apIter++)
		{
			CAccessPoint* pAp = *apIter;
			if(!pAp){
				continue;
			}
			if(!pAp->server){
				continue;
			}
			std::list<CLDevice*>::iterator ldIter = pAp->server->listLDs.begin();
			for(; ldIter != pAp->server->listLDs.end(); ldIter++)
			{
				CLDevice* pLd = *ldIter;
				std::list<CLN*>::iterator lnIter = pLd->listLNs.begin();
				for(; lnIter != pLd->listLNs.end(); lnIter++)
				{
					CLN *pLn = *lnIter;
					if((pLn->pLnType = FindLNodeType(pLn->lnClass, pLn->lnType)) != NULL)
						pLn->pLnType->bUsed = true;
				}
				//for LN0
				CLN0 *pLn0 = pLd->ln0;
				if((pLn0->pLnType = FindLNodeType(pLn0->lnClass, pLn0->lnType)) != NULL)
					pLn0->pLnType->bUsed = true;
			}
		}
	}

	//建立LNodeType's DO与DOType的关联，并置DOType的使用标志
	BuildRelationForTpl();

	//建立控制块与数据集之间关联；以及GSEControl、SMVControl与通讯GSE、SMV的关联
	iedIter = listIeds.begin();
	for(; iedIter != listIeds.end(); iedIter++)
	{
		CIed *pIed = *iedIter;
		std::list<CAccessPoint*>::iterator apIter = pIed->listAPs.begin();
		for(; apIter != pIed->listAPs.end(); apIter++)
		{
			CAccessPoint* pAp = *apIter;
			if(!pAp){
				continue;
			}
			if(!pAp->server){
				continue;
			}
			std::list<CLDevice*>::iterator ldIter = pAp->server->listLDs.begin();
			for(; ldIter != pAp->server->listLDs.end(); ldIter++)
			{
				CLDevice* pLd = *ldIter;
				std::list<CLN*>::iterator lnIter = pLd->listLNs.begin();
				for(; lnIter != pLd->listLNs.end(); lnIter++)
				{
					CLN *pLn = *lnIter;
					std::list<CRptControl*>::iterator rptIter = pLn->listRptControl.begin();
					for(; rptIter != pLn->listRptControl.end(); rptIter++)
					{
						CRptControl *pRpt = *rptIter;
						pRpt->pDataSet = FindDataSet(pLn, pRpt->datSet,1);
					}

					std::list<CLogControl*>::iterator logIter = pLn->listLogControl.begin();
					for(; logIter != pLn->listLogControl.end(); logIter++)
					{
						CLogControl* pLog = *logIter;
						pLog->pDataSet = FindDataSet(pLn, pLog->datSet,1);
					}
				}
				//for LN0
				CLN0 *pLn0 = pLd->ln0;
				std::list<CRptControl*>::iterator rptIter = pLn0->listRptControl.begin();
				for(; rptIter != pLn0->listRptControl.end(); rptIter++)
				{
					CRptControl *pRpt = *rptIter;
					if(!pRpt){
						continue;
					}
					CDataSet* daS = FindDataSet(pLn0, pRpt->datSet,1);
					if(daS){
						if(!daS->hasReport){
							daS->hasReport = true;
							daS->reportType = 1;
							daS->pControl = pRpt;
							pRpt->pDataSet = daS;
						}		
					}					
				}

				std::list<CLogControl*>::iterator logIter = pLn0->listLogControl.begin();
				for(; logIter != pLn0->listLogControl.end(); logIter++)
				{
					CLogControl* pLog = *logIter;
					if(!pLog){
						continue;
					}
					CDataSet* daS = FindDataSet(pLn0, pLog->datSet,1);
					if(daS){
						if(!daS->hasReport){
							daS->hasReport = true;
							daS->reportType = 2;
							daS->pControl = pLog;
							pLog->pDataSet = daS;
						}		
					}			
				}

				std::list<CGSEControl*>::iterator gseIter = pLn0->listGSEControl.begin();
				for(; gseIter != pLn0->listGSEControl.end(); gseIter++)
				{
					CGSEControl* pGseCtrl = *gseIter;
					if(!pGseCtrl){
						continue;
					}
					CDataSet* daS = FindDataSet(pLn0, pGseCtrl->datSet,1);
					if(daS){
						if(!daS->hasReport){
							daS->hasReport = true;
							daS->reportType = 3;
							daS->pControl = pGseCtrl;
							pGseCtrl->pDataSet = daS;
						}		
					}		
					if((pGseCtrl->pGSE = FindGSE(pIed->name, pAp->name, pLd->inst, pGseCtrl->name)) != NULL){
						pGseCtrl->pGSE->pGSEContrl = pGseCtrl;
					}
				}

				std::list<CSMVControl*>::iterator smvIter = pLn0->listSMVControl.begin();
				for(; smvIter != pLn0->listSMVControl.end(); smvIter++)
				{
					CSMVControl* pSmvCtrl = *smvIter;
					if(!pSmvCtrl){
						continue;
					}
					CDataSet* daS = FindDataSet(pLn0, pSmvCtrl->datSet,1);
					if(daS){
						if(!daS->hasReport){
							daS->hasReport = true;
							daS->reportType = 4;
							daS->pControl = pSmvCtrl;
							pSmvCtrl->pDataSet = daS;
						}		
					}	
					if((pSmvCtrl->pSMV = FindSMV(pIed->name, pAp->name, pLd->inst, pSmvCtrl->name)) != NULL)
						pSmvCtrl->pSMV->pSMVControl = pSmvCtrl;
				}
				if(pLn0->hasSettingControl){
					CDataSet* daS = FindDataSet(pLn0, "dsSetting",2);
					if(daS){
						if(!daS->hasReport){
							daS->hasReport = true;
							daS->reportType = 5;
							daS->setControl = &(pLn0->settingControl);
						}		
					}	
				}
			}
		}
	}	

	//建立Communication中ConnectedAP与IED中AccessPoint之间的关联
	std::list<CSubNetwork*>::iterator subnetIter = communication.subnetworks.begin();
	for(; subnetIter != communication.subnetworks.end(); subnetIter++)
	{
		CSubNetwork* subnet = *subnetIter;
		std::list<CConnectedAP*>::iterator connApIter = subnet->listConnAPs.begin();
		for(; connApIter != subnet->listConnAPs.end(); connApIter++)
		{
			CConnectedAP *pConnAp = *connApIter;
			iedIter = listIeds.begin();
			for(; iedIter != listIeds.end(); iedIter++)
			{
				CIed *pIed = *iedIter;
				if(strcmp(pConnAp->iedName, pIed->name))
					continue;

				std::list<CAccessPoint*>::iterator apIter = pIed->listAPs.begin();
				for(; apIter != pIed->listAPs.end(); apIter++)
				{
					CAccessPoint* pAp = *apIter;
					if(!strcmp(pConnAp->apName, pAp->name))
					{
						pConnAp->pAccessPoint = pAp;
						pAp->pConnectAP = pConnAp;
						break;
					}
				}

				if(apIter != pIed->listAPs.end())
					break;
			}
		}
	}

	//建立数据集FCDA与DOI、DAI之间关联


	//建立Inputs ExtRef与DOI、DAI之间关联

}

void CScl::BuildRelationTable(CScl* xmlFile,CScl* sgccTpl,CScl* iecTpl)
{
	if(!xmlFile){
		return;
	}

    //建立文件模板与sgcc、iec61850模板的关联
	//Lnodetype关联
	std::list<CLNodeType*>::iterator lnTypeIter = xmlFile->dataTypeTemplate.listLnTypes.begin();
	for(; lnTypeIter != dataTypeTemplate.listLnTypes.end(); lnTypeIter++)
	{
		CLNodeType *pLnType = *lnTypeIter;
		if(!pLnType){
			continue;
		}
		if(sgccTpl)
		{	
			std::list<CLNodeType*>::iterator lnTypeIter_sgcc = sgccTpl->dataTypeTemplate.listLnTypes.begin();
			for(;lnTypeIter_sgcc != sgccTpl->dataTypeTemplate.listLnTypes.end();lnTypeIter_sgcc++)
			{
				CLNodeType *pLN = *lnTypeIter_sgcc;
				if(!pLN){
					continue;
				}
				if(strcmp(pLN->lnClass,pLnType->lnClass) == 0)
				{
					pLnType->pSgccLN = pLN;
					break;
				}
			}
		}

		if(iecTpl)
		{
			std::list<CLNodeType*>::iterator lnTypeIter_iec = iecTpl->dataTypeTemplate.listLnTypes.begin();
			for(; lnTypeIter_iec != iecTpl->dataTypeTemplate.listLnTypes.end();lnTypeIter_iec++)
			{
				CLNodeType *pLn = *lnTypeIter_iec;
				if(!pLn){
					continue;
				}
				if(strcmp(pLn->lnClass,pLnType->lnClass) == 0)
				{
					pLnType->pIecLN = pLn;
					break;
				}
			}
		}
	}
}
//
//void CScl::BuildRelation()
//{
//	//建立LN与LNodeType之间关联，并置LNodeType的使用标志
//	std::list<CIed*>::iterator iedIter;
//	std::list<CAccessPoint*>::iterator apIter;
//	std::list<CLDevice*>::iterator ldIter;
//	std::list<CLN*>::iterator lnIter;
//	std::list<DO*>::iterator doIter;
//	std::list<CLNodeType*>::iterator lnTypeIter;
//	std::list<CDOType*>::iterator doTypeIter;
//	std::list<SDO*>::iterator sdoIter;
//	std::list<CDA*>::iterator daIter;
//	std::list<CDAType*>::iterator daTypeIter;
//	std::list<CBDA*>::iterator bdaIter;
//	std::list<CLogControl*>::iterator logIter;
//	std::list<CRptControl*>::iterator rptIter;
//	std::list<CGSEControl*>::iterator gseIter;
//	std::list<CSMVControl*>::iterator smvIter;
//	std::list<CSubNetwork*>::iterator subnetIter;
//	std::list<CConnectedAP*>::iterator connApIter;
//	std::list<CDataSet*>::iterator dataSetIter;
//	//std::list<CFcda*>::iterator fcdaIter;
//	//std::list<CDOI*>::iterator doiIter;
//	//std::list<CDAI*>::iterator daiIter;
//	//std::list<CSDI*>::iterator sdiIter;
//	//ListofDoi * pListDoi = NULL;
//	CSubNetwork* subnet = NULL;
//	CConnectedAP *pConnAp = NULL;
//	CDAType *pDaType = NULL;
//	CBDA* pBda = NULL;
//	CDOType *pDoType = NULL;
//	SDO *pSdo = NULL;
//	CDA *pDa = NULL;
//	CIed *pIed = NULL;
//	CAccessPoint* pAp = NULL;
//	CLDevice* pLd = NULL;
//	CLN *pLn = NULL;
//	CLN0 *pLn0 = NULL;
//	CLNodeType *pLnType = NULL;
//	DO *pDo = NULL;
//	CRptControl *pRpt = NULL;
//	CLogControl* pLog = NULL;
//	CGSEControl* pGseCtrl = NULL;
//	CSMVControl* pSmvCtrl = NULL;
//	CDataSet* pDataSet = NULL;
//	//FCDA* pFcda = NULL;
//	//CDOI* pDoi = NULL;
//	//CDAI* pDai = NULL;
//	//CSDI* pSdi = NULL;
//
//	//connect ln to LNodeType
//    iedIter = listIeds.begin();
//	for(; iedIter != listIeds.end(); iedIter++)
//	{
//		pIed = *iedIter;
//		apIter = pIed->listAPs.begin();
//		for(; apIter != pIed->listAPs.end(); apIter++)
//		{
//			pAp = *apIter;
//			ldIter = pAp->server->listLDs.begin();
//			for(; ldIter != pAp->server->listLDs.end(); ldIter++)
//			{
//				pLd = *ldIter;
//				lnIter = pLd->listLNs.begin();
//				for(; lnIter != pLd->listLNs.end(); lnIter++)
//				{
//					pLn = *lnIter;
//					if((pLn->pLnType = FindLNodeType(pLn->lnClass, pLn->lnType)) != NULL){
//						pLn->pLnType->bUsed = true; 
//					}
//				}
//				//for LN0
//				pLn0 = pLd->ln0;
//				if((pLn0->pLnType = FindLNodeType(pLn0->lnClass, pLn0->lnType)) != NULL)
//					pLn0->pLnType->bUsed = true;
//			}
//		}
//	}
//
//	//建立LNodeType's DO与DOType的关联，并置DOType的使用标志
//	lnTypeIter = dataTypeTemplate.listLnTypes.begin();
//	for(; lnTypeIter != dataTypeTemplate.listLnTypes.end(); lnTypeIter++)
//	{
//		pLnType = *lnTypeIter;
//		doIter = pLnType->listDOs.begin();
//		for(; doIter != pLnType->listDOs.end(); doIter++)
//		{
//			pDo = *doIter;
//			if((pDo->pDOType = FindDOType(pDo->type)) != NULL)
//				pDo->pDOType->bUsed = true;
//		}
//	}
//
//	//建立DOType's SDO/DA与DOType、DAType及EnumType的关系
//	doTypeIter = dataTypeTemplate.listDOTypes.begin();
//	for(; doTypeIter != dataTypeTemplate.listDOTypes.end(); doTypeIter++)
//	{
//		pDoType = *doTypeIter;
//		//for SDO
//		sdoIter = pDoType->listSDOs.begin();
//		for(; sdoIter != pDoType->listSDOs.end(); sdoIter++)
//		{
//			pSdo = *sdoIter;
//			if((pSdo->pDOType = FindDOType(pSdo->type)) != NULL)
//				pSdo->pDOType->bUsed = true;
//		}
//		//for DA
//		daIter = pDoType->listDAs.begin();
//		for(; daIter != pDoType->listDAs.end(); daIter++)
//		{
//			pDa = *daIter;
//			if(pDa->type==NULL || !strcmp(pDa->type, ""))  //基本数据类型
//				continue;
//			
//			if(!strcmp(pDa->bType, "Struct"))
//			{
//				if((pDa->pDAType = FindDAType(pDa->type)) != NULL)
//					pDa->pDAType->bUsed = true;
//			}
//			else if(!strcmp(pDa->bType, "Enum"))
//			{
//				if((pDa->pEnumType = FindEnumType(pDa->type)) != NULL)
//					pDa->pEnumType->bUsed = true;
//			}
//		}
//	}
//
//	//建立DAType's BDA与DAType和EnumType的关联
//	daTypeIter = dataTypeTemplate.listDATypes.begin();
//	for(; daTypeIter != dataTypeTemplate.listDATypes.end(); daTypeIter++)
//	{
//		pDaType = *daTypeIter;
//		bdaIter = pDaType->listBDAs.begin();
//		for(; bdaIter != pDaType->listBDAs.end(); bdaIter++)
//		{
//			pBda = *bdaIter;
//			if(pBda->type==NULL || !strcmp(pBda->type, ""))
//				continue;
//
//			if(!strcmp(pBda->bType, "Struct"))
//			{
//				if((pBda->pDAType = FindDAType(pBda->type)) != NULL)
//					pBda->pDAType->bUsed = true;
//			}
//			else if(!strcmp(pBda->bType, "Enum"))
//			{
//				if((pBda->pEnumType = FindEnumType(pBda->type)) != NULL)
//					pBda->pEnumType->bUsed = true;
//			}
//		}
//	}
//
//	//建立控制块与数据集之间关联；以及GSEControl、SMVControl与通讯GSE、SMV的关联
//	iedIter = listIeds.begin();
//	for(; iedIter != listIeds.end(); iedIter++)
//	{
//		pIed = *iedIter;
//		apIter = pIed->listAPs.begin();
//		for(; apIter != pIed->listAPs.end(); apIter++)
//		{
//			pAp = *apIter;
//			ldIter = pAp->server->listLDs.begin();
//			for(; ldIter != pAp->server->listLDs.end(); ldIter++)
//			{
//				pLd = *ldIter;
//				lnIter = pLd->listLNs.begin();
//				for(; lnIter != pLd->listLNs.end(); lnIter++)
//				{
//					pLn = *lnIter;
//					rptIter = pLn->listRptControl.begin();
//					for(; rptIter != pLn->listRptControl.end(); rptIter++)
//					{
//						pRpt = *rptIter;
//						pRpt->pDataSet = FindDataSet(pLn, pRpt->datSet);
//					}
//
//					logIter = pLn->listLogControl.begin();
//					for(; logIter != pLn->listLogControl.end(); logIter++)
//					{
//						pLog = *logIter;
//						pLog->pDataSet = FindDataSet(pLn, pLog->datSet);
//					}
//				}
//				//for LN0
//				pLn0 = pLd->ln0;
//				rptIter = pLn0->listRptControl.begin();
//				for(; rptIter != pLn0->listRptControl.end(); rptIter++)
//				{
//					pRpt = *rptIter;
//					pRpt->pDataSet = FindDataSet(pLn0, pRpt->datSet);
//				}
//				
//				logIter = pLn0->listLogControl.begin();
//				for(; logIter != pLn0->listLogControl.end(); logIter++)
//				{
//					pLog = *logIter;
//					pLog->pDataSet = FindDataSet(pLn0, pLog->datSet);
//				}
//
//				gseIter = pLn0->listGSEControl.begin();
//				for(; gseIter != pLn0->listGSEControl.end(); gseIter++)
//				{
//					pGseCtrl = *gseIter;
//					pGseCtrl->pDataSet = FindDataSet(pLn0, pGseCtrl->datSet);
//					if((pGseCtrl->pGSE = FindGSE(pIed->name, pAp->name, pLd->inst, pGseCtrl->name)) != NULL)
//						pGseCtrl->pGSE->pGSEContrl = pGseCtrl;
//				}
//
//				smvIter = pLn0->listSMVControl.begin();
//				for(; smvIter != pLn0->listSMVControl.end(); smvIter++)
//				{
//					pSmvCtrl = *smvIter;
//					pSmvCtrl->pDataSet = FindDataSet(pLn0, pSmvCtrl->datSet);
//					if((pSmvCtrl->pSMV = FindSMV(pIed->name, pAp->name, pLd->inst, pSmvCtrl->name)) != NULL)
//						pSmvCtrl->pSMV->pSMVControl = pSmvCtrl;
//				}
//			}
//		}
//	}	
//
//	//建立Communication中ConnectedAP与IED中AccessPoint之间的关联
//	subnetIter = communication.subnetworks.begin();
//	for(; subnetIter != communication.subnetworks.end(); subnetIter++)
//	{
//		subnet = *subnetIter;
//		connApIter = subnet->listConnAPs.begin();
//		for(; connApIter != subnet->listConnAPs.end(); connApIter++)
//		{
//			pConnAp = *connApIter;
//			iedIter = listIeds.begin();
//			for(; iedIter != listIeds.end(); iedIter++)
//			{
//				pIed = *iedIter;
//				if(strcmp(pConnAp->iedName, pIed->name))
//					continue;
//
//				apIter = pIed->listAPs.begin();
//				for(; apIter != pIed->listAPs.end(); apIter++)
//				{
//					pAp = *apIter;
//					if(!strcmp(pConnAp->apName, pAp->name))
//					{
//						pConnAp->pAccessPoint = pAp;
//						pConnAp->pAccessPoint->pConnectAP = pConnAp;
//						break;
//					}
//				}
//				
//				if(apIter != pIed->listAPs.end())
//					break;
//			}
//		}
//	}
//	
//	//建立数据集FCDA与DOI、DAI之间关联
//	//iedIter = listIeds.begin();
//	//for(; iedIter != listIeds.end(); iedIter++)
//	//{
//	//	pIed = *iedIter;
//	//	apIter = pIed->listAPs.begin();
//	//	for(; apIter != pIed->listAPs.end(); apIter++)
//	//	{
//	//		pAp = *apIter;
//	//		ldIter = pAp->server->listLDs.begin();
//	//		for(; ldIter != pAp->server->listLDs.end(); ldIter++)
//	//		{
//	//			pLd = *ldIter;
//	//			lnIter = pLd->listLNs.begin();
//	//			pLn0 = pLd->ln0;
//	//			dataSetIter = pLn0->listDataset.begin();
//	//			for(; dataSetIter != pLn0->listDataset.end(); dataSetIter++)
//	//			{
//	//				pDataSet = *dataSetIter;
//	//				if(!pDataSet){
//	//					continue;
//	//				}
//	//				fcdaIter = pDataSet->m_listFcda.begin();
//	//				for(; fcdaIter!=pDataSet->m_listFcda.end(); fcdaIter++){
//	//					pFcda = *fcdaIter;
//	//					if(!pFcda){
//	//						continue;
//	//					}
//	//					pFcda->pDOI = NULL;
//	//					pFcda->isRange = false;
//	//					if(strcmp(pFcda->ldInst,pLd->inst)!=0){
//	//						pFcda->isRange = true;
//	//						continue;
//	//					}
//	//					//针对每一个fcda，查找对应的Ln下匹配的doi并记录
//	//					if(strncmp(pFcda->lnClass,"LLN0",LN_CLASS_LEN) == 0)
//	//					{
//	//						if(pLd->m_Ln0 != NULL)
//	//						{
//	//							pListDoi = &(pLd->m_Ln0->m_ListDoi);
//	//						}
//	//					}
//	//					else
//	//					{
//	//						for(lnIter = pLd->m_listLn.begin();lnIter != pLd->m_listLn.end();lnIter++)
//	//						{
//	//							pLn = (*lnIter);
//	//							if((strncmp(pLn->prefix,pFcda->prefix,sizeof(pFcda->prefix)) == 0) 
//	//								&& (strncmp(pLn->lnClass,pFcda->lnClass,sizeof(pFcda->lnClass)) == 0)
//	//								&& (strncmp(pLn->inst,pFcda->lnInst,sizeof(pFcda->lnInst)) == 0))
//	//							{
//	//								pListDoi = &(pLn->listDOI);
//	//								break;
//	//							}
//	//						}
//	//					}
//
//	//					if(pListDoi && pListDoi->size() >0)//存在doi链表
//	//					{
//	//						for(doiIter = pListDoi->begin();doiIter != pListDoi->end(); doiIter++)
//	//						{
//	//							pDoi = (*doiIter);
//	//							//简单包含关系,因为fcda的doname可能是do.sdo的形式
//	//							if(strstr(pFcda->doName,pDoi->name) != NULL)
//	//							{
//	//								pFcda->pDOI = pDoi;
//	//								break;
//	//							}
//	//						}
//	//					}
//	//				}		
//	//			}
//	//		}
//	//	}
//	//}	
//
//	//建立Inputs ExtRef与DOI、DAI之间关联
//	subnet = NULL;
//	pConnAp = NULL;
//	pDaType = NULL;
//	pBda = NULL;
//	pDoType = NULL;
//	pSdo = NULL;
//	pDa = NULL;
//	pIed = NULL;
//	pAp = NULL;
//	pLd = NULL;
//	pLn = NULL;
//	pLn0 = NULL;
//	pLnType = NULL;
//	pDo = NULL;
//	pRpt = NULL;
//	pLog = NULL;
//	pGseCtrl = NULL;
//	pSmvCtrl = NULL;
//	pDataSet = NULL;
//
//	delete subnet;
//	delete pConnAp;
//	delete pDaType;
//	delete pBda;
//	delete pDoType;
//	delete pSdo;
//	delete pDa;
//	delete pIed;
//	delete pAp;
//	delete pLd;
//	delete pLn;
//	delete pLn0;
//	delete pLnType;
//	delete pDo;
//	delete pRpt;
//	delete pLog;
//	delete pGseCtrl;
//	delete pSmvCtrl;
//	delete pDataSet;
//}

void CScl::PrintScl(char * file)
{
	FILE *fp = fopen(file, "wt");

	if(fp == NULL)
		return;

	header.Print(fp);
	
	fclose(fp);
}


/*

1:检查lntype下是否有匹配的DO,DA,FC，其中doname不能为空,最大支持两级比如do.sdo, daname可为空,最大支持三级比如da.bda1.bda2
2:当daname为空，则检查Do下是否存在指定的fc,若daname不为空，则检查da的fc是否为指定的fc 

*/
bool CScl::CheckDoDaValid(char * do_name,char * da_name,char fc[3],char * lntype,bool CheckFcEnable)
{
	if(strlen(lntype)==0){
		return false;
	}
	ListOfLNodeType::iterator iterLnNodeType;
	CLNodeType* pLnNodeType;

	ListOfDo::iterator iterDo,iterDo2;
	std::list<SDO*>::iterator iterSDO;
	DO * pDo = NULL;
	DO * pDo2 = NULL;
	SDO * pSDO = NULL;

	bool bFindLnType(false);
	for(iterLnNodeType = dataTypeTemplate.listLnTypes.begin();iterLnNodeType != dataTypeTemplate.listLnTypes.end();iterLnNodeType++)
	{
		pLnNodeType = *iterLnNodeType;
		if(!pLnNodeType){
			continue;
		}
		if(strcmp(pLnNodeType->id,lntype) == 0)
		{
			bFindLnType = true;
			break;
		}
	}

	if(!bFindLnType)
		return false;


	char do_name_only[50];
	char sdo_name_only[50];

	GetTwoSubString(do_name,do_name_only,sdo_name_only);

	//do
	pSDO = NULL;
	bool bFindDo = false;
	for(iterDo = pLnNodeType->listDOs.begin(); iterDo != pLnNodeType->listDOs.end(); iterDo++)
	{
		pDo = *(iterDo);

		if(strcmp(do_name_only,pDo->name) ==0 )
		{  
			bFindDo = true;
			break;
		}
	}

	if(!bFindDo)
		return false;

	//sdo
	bFindDo = false;
	if(strlen(sdo_name_only) >0)
	{
		if(pDo->pDOType == NULL)
			return false;

		std::list<SDO*> tempLst = pDo->pDOType->listSDOs;
		for(iterSDO = tempLst.begin();iterSDO != tempLst.end();iterSDO++)
		{
			pSDO  = *iterSDO;
			if(!pSDO){
				continue;
			}
			if(strstr(sdo_name_only,pSDO->name) != NULL)
			{
				bFindDo = true;
				break;
			}
		}

		if(!bFindDo)
			return false;
	}


	//da check
	char da_name_only[50];
	char bda1_name_only[50];
	char bda2_name_only[50];

	//

	if(pDo->pDOType == NULL)
		return false;


	ListOfDa::iterator iterDa;
	CDA* pDa = NULL;

	ListOfBDA::iterator iterBda;
	CBDA* pBda = NULL;



	if(strlen(da_name) == 0)
	{
		//没配Da，也要检查do下是否有该FC
		if(CheckFcEnable)
		{
			bool bFindFc = false;

			//先检查do下的da
			for(iterDa = pDo->pDOType->listDAs.begin();iterDa != pDo->pDOType->listDAs.end();iterDa++)
			{
				pDa = *iterDa;
				if(!pDa){
					continue;
				}
				if(strcmp(fc,pDa->fc) == 0)
				{
					bFindFc = true;
					break;
				}
			}

			if(bFindFc)
				return bFindFc;

			//再检查sdo下的da
			for(iterSDO = pDo->pDOType->listSDOs.begin();iterSDO != pDo->pDOType->listSDOs.end();iterSDO++)
			{
				pSDO  = *iterSDO;
				if(!pSDO){
					continue;
				}
				for(iterDa = pSDO->pDOType->listDAs.begin();iterDa != pSDO->pDOType->listDAs.end();iterDa++)
				{
					pDa = *iterDa;
					if(!pDa){
						continue;
					}
					if(strcmp(fc,pDa->fc) == 0)
					{
						bFindFc = true;
						break;
					}
				}
				if(bFindFc)
					break;
			}

			return bFindFc;
		}
	}

	//准备检查da及之下的bda(目前最大支持层数为da.bda1.bda2)

	GetThirdSubString(da_name,da_name_only,bda1_name_only,bda2_name_only);

	//ad
	bool bFindDa = false;
	if(pSDO){
		for(iterDa = pSDO->pDOType->listDAs.begin();iterDa != pSDO->pDOType->listDAs.end();iterDa++)
		{
			pDa = *iterDa;
			if(!pDa){
				continue;
			}
			if(strcmp(da_name_only,pDa->name) == 0)
			{
				if(CheckFcEnable)
				{
					if(strcmp(fc,pDa->fc) == 0)
					{
						bFindDa = true;	
						break;
					}
				}
				else
				{
					bFindDa = true;
					break;
				}
			}
		}
	}
	else{
		for(iterDa = pDo->pDOType->listDAs.begin();iterDa != pDo->pDOType->listDAs.end();iterDa++)
		{
			pDa = *iterDa;
			if(!pDa){
				continue;
			}
			if(strcmp(da_name_only,pDa->name) == 0)
			{
				if(CheckFcEnable)
				{
					if(strcmp(fc,pDa->fc) == 0)
					{
						bFindDa = true;	
						break;
					}
				}
				else
				{
					bFindDa = true;
					break;
				}
			}
		}
	}
	//if((strlen(bda1_name_only)==0)&&(strlen(bda2_name_only)==0)){
	//	if(pDo){
	//		for(iterDa = pDo->pDOType->listDAs.begin();iterDa != pDo->pDOType->listDAs.end();iterDa++)
	//		{
	//			pDa = *iterDa;
	//			if(!pDa){
	//				continue;
	//			}
	//			if(strcmp(da_name_only,pDa->name) == 0)
	//			{
	//				if(CheckFcEnable)
	//				{
	//					if(strcmp(fc,pDa->fc) == 0)
	//					{
	//						bFindDa = true;	
	//						break;
	//					}
	//				}
	//				else
	//				{
	//					bFindDa = true;
	//					break;
	//				}
	//			}
	//		}
	//	}
	//}
	//else{
	//	if(pSDO){
	//		for(iterDa = pSDO->pDOType->listDAs.begin();iterDa != pSDO->pDOType->listDAs.end();iterDa++)
	//		{
	//			pDa = *iterDa;
	//			if(!pDa){
	//				continue;
	//			}
	//			if(strcmp(da_name_only,pDa->name) == 0)
	//			{
	//				if(CheckFcEnable)
	//				{
	//					if(strcmp(fc,pDa->fc) == 0)
	//					{
	//						bFindDa = true;	
	//						break;
	//					}
	//				}
	//				else
	//				{
	//					bFindDa = true;
	//					break;
	//				}
	//			}
	//		}
	//	}

	//}

	//if(!bFindDa){
	//	for(iterSDO = pDo->pDOType->listSDOs.begin();iterSDO != pDo->pDOType->listSDOs.end();iterSDO++)
	//	{
	//		pSDO = *iterDa;
	//		if(!pSDO){
	//			continue;
	//		}
	//		if(strcmp(da_name_only,pSDO->name) == 0)
	//		{
	//			if(CheckFcEnable)
	//			{
	//				bFindDa = true;	
	//				break;
	//			}
	//			else
	//			{
	//				bFindDa = true;
	//				break;
	//			}
	//		}
	//	}
	//}

	if(!bFindDa)
		return false;

	//第一层bda
	bFindDa = false;
	if(strlen(bda1_name_only) == 0)
	{
		bFindDa = true;
	}
	else
	{
		if(strcmp(pDa->bType,"Struct") == 0)
		{
			for(iterBda = pDa->pDAType->listBDAs.begin();iterBda != pDa->pDAType->listBDAs.end();iterBda++)
			{
				pBda = *iterBda;
				if(!pBda){
					continue;
				}
				if(strcmp(bda1_name_only,pBda->name) == 0)
				{
					bFindDa = true;
					break;
				}
			}
		}
	}

	if(!bFindDa)
		return false;

	bFindDa = false;
	if(strlen(bda2_name_only) == 0)
	{
		bFindDa = true;
	}
	else
	{
		if(pBda != NULL)
		{
			//第二层bda
			bFindDa = false;
			if(strcmp(pBda->bType,"Struct") == 0)
			{
				CBDA* pBdaTemp = NULL;
				for(iterBda = pBda->pDAType->listBDAs.begin();iterBda != pBda->pDAType->listBDAs.end();iterBda++)
				{
					pBdaTemp = *iterBda;
					if(!pBdaTemp){
						continue;
					}
					if(strcmp(bda2_name_only,pBdaTemp->name) == 0)
					{
						bFindDa = true;
						break;
					}
				}
			}
		}
	}

	if(!bFindDa)
		return false;

	return true;
}


/*检查stack_Ref推栈中存放的Ref在lntype下是否有效,是否正确,应用于检查doi配置的合法性*/
bool CScl::CheckDoDaRefValid(StackString* stack_ref,char * lntype,int& bda_data_type,CEnumType ** pEnumType,unsigned long lineNo)
{

	if(stack_ref == NULL)
		return false;
	if(stack_ref->IsEmpty())
		return false;
	if(lntype == NULL)
		return false;
	if(strlen(lntype) == 0)
		return false;

	bda_data_type = BDT_NULL;

	stack_ref->ResetSee();
	stack_ref->ResetTypeSee();

	ListOfLNodeType::iterator iterLnNodeType;
	CLNodeType* pLnNodeType;
	char* name;
	char* ctype;

	name = stack_ref->see();
	ctype = stack_ref->typeSee();
	if((name == NULL)||(ctype == NULL))
		return true;

	ListOfDo::iterator iterDo,iterDo2;
	std::list<SDO*>::iterator iterSDO;
	DO * pDo = NULL;
	SDO * pDo2 = NULL;

	ListOfDa::iterator iterDa;
	CDA* pDa = NULL;

	ListOfBDA::iterator iterBda;
	CBDA* pBda = NULL;


	bool bFind(false);

	for(iterLnNodeType = dataTypeTemplate.listLnTypes.begin();iterLnNodeType != dataTypeTemplate.listLnTypes.end();iterLnNodeType++)
	{
		pLnNodeType = *iterLnNodeType;
		if(!pLnNodeType){
			continue;
		}
		if(strcmp(pLnNodeType->id,lntype) == 0)
		{
			bFind = true;
			break;
		}
	}

	if(!bFind){
		return false;
	}

	//do
	bFind = false;
	for(iterDo = pLnNodeType->listDOs.begin(); iterDo != pLnNodeType->listDOs.end(); iterDo++)
	{
		pDo = *(iterDo);

		if(strcmp(name,pDo->name) ==0 )
		{  
			if(strcmp(ctype,"DOI")==0){
				bFind = true;
			}			
			break;
		}

	}

	if(!bFind)
		return false;
	name = stack_ref->see();
	ctype = stack_ref->typeSee();
	if(name == NULL)
		return true;
	if(strlen(name) == 0)
		return false;
	if(pDo->pDOType == NULL)
		return false;

	//sdo
	bFind = false;
	short nSdoOrDaType = -1; //0 -sdo type,1 - datype

	for(iterSDO = pDo->pDOType->listSDOs.begin();iterSDO != pDo->pDOType->listSDOs.end();iterSDO++)
	{
		pDo2 = *iterSDO;
		if(!pDo2){
			continue;
		}
		if(strcmp(name,pDo2->name) ==0)
		{
			if(strcmp(ctype,"SDI")==0){
				bFind = true;
			}	
			nSdoOrDaType = 0;
			break;
		}
	}


	//da
	if(!bFind)
	{
		if(pDo->pDOType == NULL)
			return false;
		for(iterDa = pDo->pDOType->listDAs.begin();iterDa != pDo->pDOType->listDAs.end();iterDa++)
		{
			pDa = *iterDa;
			if(!pDa){
				continue;
			}
			if(strcmp(name,pDa->name) == 0)
			{
				if(strcmp(pDa->bType,"Struct") != 0) //非结构型DA，获取DA类型
				{
					bda_data_type = GetBdaDataType(pDa->bType);
					*pEnumType = pDa->pEnumType;

					if(strcmp(ctype,"DAI")==0){
						bFind = true;
					}	
				}
				else{
					if(strcmp(ctype,"SDI")==0){
						bFind = true;
					}	
				}
				//bFind = true;
				nSdoOrDaType = 1;
				break;
			}
		}
	}

	if(!bFind)
		return false;

	name = stack_ref->see();
	ctype = stack_ref->typeSee();

	if(name == NULL)
		return true;
	if(strlen(name) == 0)
		return false;

	bFind = false;
	if(nSdoOrDaType == 0)// sdo.da 的情况
	{
		if(pDo2->pDOType == NULL)
			return false;
		for(iterDa = pDo2->pDOType->listDAs.begin();iterDa != pDo2->pDOType->listDAs.end();iterDa++)
		{
			pDa = *iterDa;
			if(!pDa){
				continue;
			}
			if(strcmp(name,pDa->name) == 0)
			{
				if(strcmp(pDa->bType,"Struct") != 0) //非结构型DA，获取DA类型
				{
					bda_data_type = GetBdaDataType(pDa->bType);
					*pEnumType = pDa->pEnumType;

					if(strcmp(ctype,"DAI")==0){
						bFind = true;
					}
				}
				else{
					if(strcmp(ctype,"SDI")==0){
						bFind = true;
					}
				}
			//	bFind = true;
				break;
			}
		}

		if(!bFind)
			return false;

		name = stack_ref->see();
		ctype = stack_ref->typeSee();

		if(name == NULL)
			return true;
		if(strlen(name) == 0)
			return false;
	}

	if(!pDa)
		return false;	

	//第一层bda
	bFind = false;
	if(strcmp(pDa->bType,"Struct") == 0)
	{
		if(pDa->pDAType == NULL)
			return false;

		for(iterBda = pDa->pDAType->listBDAs.begin();iterBda != pDa->pDAType->listBDAs.end();iterBda++)
		{
			pBda = *iterBda;
			if(!pBda){
				continue;
			}
			if(strcmp(name,pBda->name) == 0)
			{
				if(strcmp(pBda->bType,"Struct") != 0) //非结构型DA，获取BDA类型
				{
					bda_data_type = GetBdaDataType(pBda->bType);
					*pEnumType = pBda->pEnumType;
					if(strcmp(ctype,"DAI")==0){
						bFind = true;
					}
				}
				else{
					if(strcmp(ctype,"SDI")==0){
						bFind = true;
					}
				}
				break;
			}
		}
	}

	if(!bFind)
		return false;

	name = stack_ref->see();
	ctype = stack_ref->typeSee();

	if(name == NULL)
		return true;
	if(strlen(name) == 0)
		return false;

	if(pBda == NULL)
		return false;

	//第二层bda
	bFind = false;
	if(strcmp(pBda->bType,"Struct") == 0)
	{
		CBDA* pBdaTemp = NULL;
		for(iterBda = pBda->pDAType->listBDAs.begin();iterBda != pBda->pDAType->listBDAs.end();iterBda++)
		{
			pBdaTemp = *iterBda;
			if(!pBdaTemp){
				continue;
			}
			if(strcmp(name,pBdaTemp->name) == 0)
			{
				if(strcmp(pBdaTemp->bType,"Struct") != 0) //非结构型DA，获取BDA类型
				{
					bda_data_type = GetBdaDataType(pBdaTemp->bType);
					*pEnumType = pBdaTemp->pEnumType;
					if(strcmp(ctype,"DAI")==0){
						bFind = true;
					}
				}
				else{
					if(strcmp(ctype,"SDI")==0){
						bFind = true;
					}
				}
				break;
			}
		}
	}

	if(!bFind)
		return false;

	return true;
}

int CScl::GetBdaDataType(char *bType)
{
	int nRetDataType = BDT_NULL;

	if(bType == NULL || strcmp(bType,"") == 0)
		return nRetDataType;

	if(strcmp(bType,"BOOLEAN") == 0)
	{
		nRetDataType = BDT_BOOLEAN;
	}
	else if(strcmp(bType,"INT8") == 0)
	{
		nRetDataType = BDT_INT8;
	}
	else if(strcmp(bType,"INT16") == 0)
	{
		nRetDataType = BDT_INT16;
	}
	else if(strcmp(bType,"INT24") == 0)
	{
		nRetDataType = BDT_INT24;
	}
	else if(strcmp(bType,"INT32") == 0)
	{
		nRetDataType = BDT_INT32;
	}
	else if(strcmp(bType,"INT128") == 0)
	{
		nRetDataType = BDT_INT128;
	}
	else if(strcmp(bType,"INT8U") == 0)
	{
		nRetDataType = BDT_INT8U;
	}
	else if(strcmp(bType,"INT16U") == 0)
	{
		nRetDataType = BDT_INT16U;
	}
	else if(strcmp(bType,"INT24U") == 0)
	{
		nRetDataType = BDT_INT24U;
	}
	else if(strcmp(bType,"INT32U") == 0)
	{
		nRetDataType = BDT_INT32U;
	}
	else if(strcmp(bType,"FLOAT32") == 0)
	{
		nRetDataType = BDT_FLOAT32;
	}
	else if(strcmp(bType,"FLOAT64") == 0)
	{
		nRetDataType = BDT_FLOAT64;
	}
	else if(strcmp(bType,"Enum") == 0)
	{
		nRetDataType = BDT_ENUMERATED;
	}
	else if(strcmp(bType,"VisString32") == 0 )
	{
		nRetDataType = BDT_VISIBLESTRING32;
	}
	else if(strcmp(bType,"VisString64") == 0)
	{
		nRetDataType = BDT_VISIBLESTRING64;
	}
	else if(strcmp(bType,"VisString255") == 0)
	{
		nRetDataType = BDT_VISIBLESTRING255;
	}
	else if(strcmp(bType,"Dbpos") == 0)
	{
		nRetDataType = BDT_BITSTRING2;
	}
	else if(strcmp(bType,"Quality") == 0)
	{
		nRetDataType = BDT_BITSTRING;
	}
	else if(strcmp(bType,"Timestamp") == 0)
	{
		nRetDataType = BDT_TimeStamp;
	}
	else if(strcmp(bType,"Unicode255") == 0)
	{
		nRetDataType = BDT_UNICODESTRING;
	}
	else
	{
		;
	}
	return nRetDataType;	
}


/*检查DAI下的VAL配置的有效性*/
bool CScl::CheckValValid(char* strVal,int data_type,CEnumType * pEnumType)
{
	if(strVal == NULL)
		return false;
	if(strlen(strVal) < 1)
		return true;

	bool bValid = false;
	int i;
	float f;

	ListOfEnumVal::iterator iterEnumVal;
	EnumVal * pEnumVal = NULL;

	switch(data_type)
	{
	case BDT_BOOLEAN:
		if( strcmp(strVal,"true") == 0 || strcmp(strVal,"false") == 0 || strcmp(strVal,"true") == 0 || strcmp(strVal,"false") == 0 || strcmp(strVal,"1") == 0||strcmp(strVal,"0") == 0)
		{
			bValid = true;
		}
		break;

	case BDT_INT8:
		if(IsInteger(strVal))
		{
			i = atoi(strVal);
			if(i>=-128 && i<=127)
			{
				bValid = true;
			}
		}
		break;

	case BDT_INT16:
		if(IsInteger(strVal))
		{
			i = atoi(strVal);
			if(i>=(int)(-32768) && i<=32767)
			{
				bValid = true;
			}
		}
		break;

	case BDT_INT32:
		if(IsInteger(strVal))
		{
			i = atoi(strVal);
			if(i>=(int)(-2147483648) && i<=(int)(2147483647))
			{
				bValid = true;
			}
		}
		break;

	case BDT_INT8U:
		if(IsUnsignedInteger(strVal))
		{
			i = atoi(strVal);
			if(i>=0 && i<=255)
			{
				bValid = true;
			}
		}
		break;

	case BDT_INT16U:
		if(IsUnsignedInteger(strVal))
		{
			i = atoi(strVal);
			if(i>=0 && i<=65535)
			{
				bValid = true;
			}
		}
		break;

	case BDT_INT32U:
		if(IsUnsignedInteger(strVal))
		{
			i = atoi(strVal);
			if(i>=0 && i<=4294967295)
			{
				bValid = true;
			}
		}
		break;

	case BDT_FLOAT32:
		if(IsNumeric(strVal))
		{
			f = atof(strVal);
			bValid = true;
		}
		break;

	case BDT_FLOAT64:
		if(IsNumeric(strVal))
		{
			f = atof(strVal);
			bValid = true;
		}
		break;

	case BDT_BITSTRING2:
		if(IsBitString(strVal,2))
		{
			bValid = true;
		}
		break;

	case BDT_BITSTRING:
		if(IsBitString(strVal,-1))
		{
			bValid = true;
		}
		break;

	case BDT_VISIBLESTRING32:
		i = strlen(strVal);
		if(i<=32)
			bValid = true;
		break;
	case BDT_VISIBLESTRING64:
		i = strlen(strVal);
		if(i<=64)
			bValid = true;
		break;
	case BDT_VISIBLESTRING255:
		i = strlen(strVal);
		if(i<=255)
			bValid = true;
		break;

	case BDT_ENUMERATED:
		if(pEnumType)
		{
			for(iterEnumVal = pEnumType->listEnumVals.begin();iterEnumVal != pEnumType->listEnumVals.end();iterEnumVal++)
			{
				pEnumVal = *iterEnumVal;
				char temp1[MIDDLE_STR_LEN];
				sprintf(temp1,"%d",pEnumVal->ord);
				//itoa(pEnumVal->ord,temp1,10);
				//sprintf(temp1,"%d",pEnumVal->ord);
				if((strcmp(pEnumVal->content,strVal) == 0) || (strcmp(temp1,strVal) == 0))
				{
					bValid = true;
					break;
				}
			}
		}
		break;
	default:
		bValid = true;
		break;
	}

	return bValid;
}

void CScl::CheckLNValid(char * lntype,unsigned long lineNo)
{
	if(lntype == NULL)
		return;
	if(strlen(lntype) == 0)
		return;
	ListOfLNodeType::iterator iterLnNodeType;
	CLNodeType* pLnNodeType;
	bool bFind(false);

	for(iterLnNodeType = dataTypeTemplate.listLnTypes.begin();iterLnNodeType != dataTypeTemplate.listLnTypes.end();iterLnNodeType++)
	{
		pLnNodeType = *iterLnNodeType;
		if(strcmp(pLnNodeType->id,lntype) == 0)
		{
			bFind = true;
			break;
		}
	}

	if(!bFind){
		char Msg[500];
		char tip[700];
		strcpy(Msg,"");
		strcpy(tip,"");
		sprintf(Msg,"模板中未定义LNodeType: %s .",lntype);
		sprintf(tip,"**错误 : 第%d行, %s\n",lineNo,Msg);
		if(m_pCheckNotifier)
		{
			if(m_pCheckNotifier->m_bEnableErrorShow){
				m_pCheckNotifier->NotifyCheckInfo(tip);
			}				
			m_pCheckNotifier->m_nErrorCount++;
			m_pCheckNotifier->m_nLNErrCnt++;
		}
	}
}

char* CScl::GetIEDIP(char * strIedName,char * strSubNetwork)
{
	CSubNetwork* subNetwork = NULL;
	ListOfSubNetwork::iterator iter = communication.subnetworks.begin();
	for(; iter != communication.subnetworks.end(); iter++)
	{
		subNetwork = *iter;
		if(!strcmp(subNetwork->name,strSubNetwork))
		{
			CConnectedAP* pAp = NULL;
			ListOfConnAP::iterator pApIter = subNetwork->listConnAPs.begin();
			for(; pApIter!=subNetwork->listConnAPs.end();pApIter++)
			{
				pAp = *pApIter;
				if(!strcmp(pAp->iedName,strIedName))
				{

					if(pAp->pAddress)
					{
						return pAp->pAddress->ip;
					}
				}
			}
		}
	}
	return NULL;
}

char* CScl::GetManufacturer(char * strIedName)
{
	std::list<CIed*>::iterator iedIter = listIeds.begin();
	for(;iedIter!=listIeds.end();iedIter++)
	{
		CIed* pIed = *iedIter;
		if(!strcmp(pIed->name,strIedName))
		{
			return pIed->manufacturer;
		}
	}
	return NULL;
}

CLNInfo::CLNInfo()
: m_pProgressNotifier(0), m_pCheckNotifier(0)
{
}

CLNInfo::CLNInfo(CProgressNotifier* pProgressNotifier)
: m_pProgressNotifier(pProgressNotifier), m_pCheckNotifier(0)
{
}

CLNInfo::CLNInfo(CProgressNotifier* pProgressNotifier,CCheckNotifier * pCheckNotifier)
{
	m_pProgressNotifier = pProgressNotifier;
	m_pCheckNotifier = pCheckNotifier;
}

