//#include "stdafx.h"
#include "SclSAX2Handler.hpp"
#include "StrX.hpp"
#include <iostream>

#include <memory.h> 
#include <string.h>
#include <list>

#include <memory.h> 
#include <string.h>
#include <stdio.h>
#include "scl.h"

using namespace std;

const SCL_TAG SCL_[] = {TAG_SCL};
const SCL_TAG SCL_Private[] = {TAG_SCL,TAG_PRIVATE};
const SCL_TAG VOLTAGE[] = {TAG_SCL,TAG_PRIVATE,TAG_NARI_VOL};
const SCL_TAG NARI_BAY[]={TAG_SCL,TAG_PRIVATE,TAG_NARI_VOL,TAG_NARI_BAY};
const SCL_TAG NARI_IED[]={TAG_SCL,TAG_PRIVATE,TAG_NARI_VOL,TAG_NARI_BAY,TAG_NARI_IED};
const SCL_TAG SCL_Header[] = {TAG_SCL, TAG_Header};
const SCL_TAG _History[] = {TAG_History};
const SCL_TAG _History_Hitem[] = {TAG_History, TAG_Hitem};
const SCL_TAG SCL_Communication[] = {TAG_SCL, TAG_Communication};
const SCL_TAG _SubNetwork[] = {TAG_SubNetwork};
const SCL_TAG _SubNetwork_BitRate[] = {TAG_SubNetwork, TAG_BitRate};
const SCL_TAG _SubNetwork_ConnectedAP[] = {TAG_SubNetwork, TAG_ConnectedAP};
const SCL_TAG _SubNetwork_ConnectedAP_Address[] = {TAG_SubNetwork, TAG_ConnectedAP, TAG_Address};
const SCL_TAG _SubNetwork_ConnectedAP_Address_P[] = {TAG_SubNetwork, TAG_ConnectedAP, TAG_Address, TAG_P};
const SCL_TAG _SubNetwork_ConnectedAP_GSE[] = {TAG_SubNetwork, TAG_ConnectedAP, TAG_GSE};
const SCL_TAG _SubNetwork_ConnectedAP_GSE_Address[] = {TAG_SubNetwork, TAG_ConnectedAP, TAG_GSE, TAG_Address};
const SCL_TAG _SubNetwork_ConnectedAP_GSE_Address_P[] = {TAG_SubNetwork, TAG_ConnectedAP, TAG_GSE, TAG_Address, TAG_P};
const SCL_TAG _SubNetwork_ConnectedAP_GSE_MinTime[] = {TAG_SubNetwork, TAG_ConnectedAP, TAG_GSE, TAG_MinTime};
const SCL_TAG _SubNetwork_ConnectedAP_GSE_MaxTime[] = {TAG_SubNetwork, TAG_ConnectedAP, TAG_GSE, TAG_MaxTime};
const SCL_TAG _SubNetwork_ConnectedAP_SMV[] = {TAG_SubNetwork, TAG_ConnectedAP, TAG_SMV};
const SCL_TAG _SubNetwork_ConnectedAP_SMV_Address[] = {TAG_SubNetwork, TAG_ConnectedAP, TAG_SMV, TAG_Address};
const SCL_TAG _SubNetwork_ConnectedAP_SMV_Address_P[] = {TAG_SubNetwork, TAG_ConnectedAP, TAG_SMV, TAG_Address, TAG_P};
const SCL_TAG _SubNetwork_ConnectedAP_PhysConn[] = {TAG_SubNetwork, TAG_ConnectedAP, TAG_PhysConn};
const SCL_TAG _SubNetwork_ConnectedAP_PhysConn_P[] = {TAG_SubNetwork, TAG_ConnectedAP, TAG_PhysConn, TAG_P};
const SCL_TAG SCL_IED[] = {TAG_SCL, TAG_IED};
const SCL_TAG _Service[] = {TAG_Service};
const SCL_TAG _Service_DynAssociation[] = {TAG_Service, TAG_DynAssociation};
const SCL_TAG _Service_SettingGroups[] = {TAG_Service, TAG_SettingGroups};
const SCL_TAG _Service_SettingGroups_SGEdit[] = {TAG_Service, TAG_SettingGroups, TAG_SGEdit};
const SCL_TAG _Service_SettingGroups_ConfSG[] = {TAG_Service, TAG_SettingGroups, TAG_ConfSG};
const SCL_TAG _Service_GetDirectory[] = {TAG_Service, TAG_GetDirectory};
const SCL_TAG _Service_GetDataObjectDefinition[] = {TAG_Service, TAG_GetDataObjectDefinition};
const SCL_TAG _Service_DataObjectDirectory[] = {TAG_Service, TAG_DataObjectDirectory};
const SCL_TAG _Service_GetDataSetValue[] = {TAG_Service, TAG_GetDataSetValue};
const SCL_TAG _Service_SetDataSetValue[] = {TAG_Service, TAG_SetDataSetValue};
const SCL_TAG _Service_DataSetDirectory[] = {TAG_Service, TAG_DataSetDirectory};
const SCL_TAG _Service_ConfDataSet[] = {TAG_Service, TAG_ConfDataSet};
const SCL_TAG _Service_DynDataSet[] = {TAG_Service, TAG_DynDataSet};
const SCL_TAG _Service_ReadWrite[] = {TAG_Service, TAG_ReadWrite};
const SCL_TAG _Service_TimerActivatedControl[] = {TAG_Service, TAG_TimerActivatedControl};
const SCL_TAG _Service_ConfReportControl[] = {TAG_Service, TAG_ConfReportControl};
const SCL_TAG _Service_GetCBValues[] = {TAG_Service, TAG_GetCBValues};
const SCL_TAG _Service_ConfLogControl[] = {TAG_Service, TAG_ConfLogControl};
const SCL_TAG _Service_ReportSettings[] = {TAG_Service, TAG_ReportSettings};
const SCL_TAG _Service_LogSettings[] = {TAG_Service, TAG_LogSettings};
const SCL_TAG _Service_GSESettings[] = {TAG_Service, TAG_GSESettings};
const SCL_TAG _Service_SMVSettings[] = {TAG_Service, TAG_SMVSettings};
const SCL_TAG _Service_SMVSettings_SmpRate[] = {TAG_Service, TAG_SMVSettings, TAG_SmpRate};
const SCL_TAG _Service_GSEDir[] = {TAG_Service, TAG_GSEDir};
const SCL_TAG _Service_GOOSE[] = {TAG_Service, TAG_GOOSE};
const SCL_TAG _Service_GSSE[] = {TAG_Service, TAG_GSSE};
const SCL_TAG _Service_FileHandling[] = {TAG_Service, TAG_FileHandling};
const SCL_TAG _Service_ConfLNs[] = {TAG_Service, TAG_ConfLNs};
const SCL_TAG _AccessPoint[] = {TAG_AccessPoint};
const SCL_TAG _Server[] = {TAG_Server};
const SCL_TAG _Server_Authentication[] = {TAG_Server, TAG_Authentication};
const SCL_TAG _Server_LDevice[] = {TAG_Server, TAG_LDevice};
const SCL_TAG _Server_LDevice_LN0[] = {TAG_Server, TAG_LDevice, TAG_LN0};
const SCL_TAG _DataSet[] = {TAG_DataSet};
const SCL_TAG _DataSet_FCDA[] = {TAG_DataSet, TAG_FCDA};
const SCL_TAG _ReportControl[] = {TAG_ReportControl};
const SCL_TAG _ReportControl_TrgOps[] = {TAG_ReportControl, TAG_TrgOps};
const SCL_TAG _ReportControl_OptFields[] = {TAG_ReportControl, TAG_OptFields};
const SCL_TAG _ReportControl_RptEnabled[] = {TAG_ReportControl, TAG_RptEnabled};
const SCL_TAG _ReportControl_RptEnabled_ClientLN[] = {TAG_ReportControl, TAG_RptEnabled, TAG_ClientLN};
const SCL_TAG _LogControl[] = {TAG_LogControl};
const SCL_TAG _LogControl_TrgOps[] = {TAG_LogControl, TAG_TrgOps};
const SCL_TAG _DOI[] = {TAG_DOI};
const SCL_TAG _DOI_SDI[] = {TAG_DOI, TAG_SDI};
const SCL_TAG _SDI[] = {TAG_SDI};
const SCL_TAG _SDI_DAI[] = {TAG_SDI, TAG_DAI};
const SCL_TAG _DOI_DAI[] = {TAG_DOI, TAG_DAI};
const SCL_TAG _DAI[] = {TAG_DAI};
const SCL_TAG _DAI_Val[] = {TAG_DAI, TAG_Val};
const SCL_TAG _Val[] = {TAG_Val};
const SCL_TAG _Inputs[] = {TAG_Inputs};
const SCL_TAG _Inputs_ExtRef[] = {TAG_Inputs, TAG_ExtRef};
const SCL_TAG _GSEControl[] = {TAG_GSEControl};
const SCL_TAG _GSEControl_IEDName[] = {TAG_GSEControl, TAG_IEDName};
const SCL_TAG _SampledValueControl[] = {TAG_SampledValueControl};
const SCL_TAG _SampledValueControl_IEDName[] = {TAG_SampledValueControl, TAG_IEDName};
const SCL_TAG _SampledValueControl_SmvOpts[] = {TAG_SampledValueControl, TAG_SmvOpts};
const SCL_TAG _SettingControl[] = {TAG_SettingControl};
const SCL_TAG _Server_LDevice_LN[] = {TAG_Server, TAG_LDevice, TAG_LN};
const SCL_TAG _Server_LDevice_AccessControl[] = {TAG_Server, TAG_LDevice, TAG_AccessControl};
const SCL_TAG _Server_Association[] = {TAG_Server, TAG_Association};
const SCL_TAG SCL_DataTypeTemplates[] = {TAG_SCL, TAG_DataTypeTemplates};
const SCL_TAG _LNodeType[] = {TAG_LNodeType};
const SCL_TAG _LNodeType_DO[] = {TAG_LNodeType, TAG_DO};
const SCL_TAG _DOType[] = {TAG_DOType};
const SCL_TAG _DOType_SDO[] = {TAG_DOType, TAG_SDO};
const SCL_TAG _SDO_SDO[] = {TAG_SDO, TAG_SDO};
const SCL_TAG _SDO_DA[] = {TAG_SDO, TAG_DA};
const SCL_TAG _DA[] = {TAG_DA};
const SCL_TAG _DA_Val[] = {TAG_DA, TAG_Val};
const SCL_TAG _DAType[] = {TAG_DAType};
const SCL_TAG _DAType_BDA[] = {TAG_DAType, TAG_BDA};
const SCL_TAG _DAType_BDA_Val[] = {TAG_DAType, TAG_BDA, TAG_Val};
const SCL_TAG _EnumType[] = {TAG_EnumType};
const SCL_TAG _EnumType_EnumVal[] = {TAG_EnumType, TAG_EnumVal};
const SCL_TAG _EnumVal[] = {TAG_EnumVal};



void CParserInd::Push(void* pEle, SCL_TAG tag)
{
	if(ind<sizeof(elemType)/sizeof(SCL_TAG)-1 || ind==0xffffffff)
	{
		ind++;
	 	pElement[ind] = pEle;
	 	elemType[ind] = tag;
	}
}

void * CParserInd::Pop()
{
//	printf("ind=%d \n",ind);
	if(ind >= 0){
		elemType[ind] = TAG_NULL;
		return pElement[ind--];
	}
	else
		return NULL;
}

int CParserInd::CmpPath(const SCL_TAG* path, unsigned int level)
{
	int i, sub;

//	if(ind+1 != level)
//		return level - ind - 1;
	for(i=0; i<level; i++){
		sub = path[i] - elemType[i];
		if(sub != 0)
			return sub;
	}
	return 0;
}

int CParserInd::CmpPathR(const SCL_TAG* path, unsigned int level)
{
	int i, sub, begin;
	
	begin = ind + 1 - level;
	if(begin < 0)
		return begin;
	for(i=0; i<level; i++){
		sub = path[i] - elemType[begin+i];
		if(sub != 0)
			return sub;
	}
	return 0;
}

int CParserInd::CmpPartPath(int begin, const SCL_TAG* path, unsigned int level)
{
	int i, sub;
	
// 	if(ind+1 != level+begin)
// 		return -1;
	for(i=0; i<level; i++){
		sub = path[i] - elemType[i+begin];
		if(sub != 0)
			return sub;
	}
	return 0;

}


SclSAX2Handler::SclSAX2Handler(CScl * pScl,int parseType)
{
	m_pParInd = (CParserInd*) sclMem.AllocMem(sizeof(CParserInd));
	m_pParInd->ind = 0xffffffff;
	m_pScl = pScl;
	this->m_parseType = parseType;
	m_preTag = "";
	m_strList.clear();
};

SclSAX2Handler::~SclSAX2Handler()
{
}

char* SclSAX2Handler::GetAttribVal(const Attributes& attrs, char* attr_name)
{
	int i;
	
	if(attr_name == NULL)
		return "";

	for(i=0; i<attrs.getLength(); i++)
	{
		char AttrVal[MAX_STR_LEN];
		strncpy(AttrVal,StrX(attrs.getLocalName(i)).localForm(),MAX_STR_LEN);
		/*if (!strcmp(attr_name, StrX(attrs.getLocalName(i)).localForm()))*/
		if (!strcmp(attr_name, AttrVal))
			return XMLString::transcode(attrs.getValue(i));
	}
	return NULL;
}

void SclSAX2Handler::GetAttribVals(const Attributes& attrs, char** names, char** vals, int num)
{
	int i, j;
	
	if(names==NULL || vals==NULL)
		return;
	for(i=0; i<num; i++)
		vals[i] = NULL;

	for(i=0; i<attrs.getLength(); i++)
	{
		StrX s(attrs.getLocalName(i));
		const char * p = s.localForm();
		for(j=0; j<num; j++)
		{
			if (!strcmp(p, names[j])){
				vals[j] = XMLString::transcode(attrs.getValue(i));
				break;
			}
		}
	}
}

void SclSAX2Handler::GetAttribValsWithMemAlloc(const Attributes& attrs, char** names, char*** ppVars, int num)
{
	int i, j;
	
	if(names==NULL || ppVars==NULL)
		return;
	for(i=0; i<num; i++){
		if(ppVars[i] == NULL)
			return;
		else
			*(ppVars[i]) = "";
	}
	
	for(i=0; i<attrs.getLength(); i++)
	{
		StrX s(attrs.getLocalName(i));
		const char * attribName = s.localForm();
		for(j=0; j<num; j++)
		{
			if (!strcmp(attribName, names[j])){
				char * p = XMLString::transcode(attrs.getValue(i));
				*(ppVars[j]) = sclMem.AllocAndCopy(p);
				XMLString::release(&p);
				break;
			}
		}
	}
}

void SclSAX2Handler::ReleaseXmlString(char** p, int num)
{
	if(p)
	{
		for(int i=0; i<num; i++){
			if(p[i] != NULL)
				XMLString::release(&(p[i]));
		}
	}
}

#define GetAttribToApp(attrs, pApp, v1) { \
	char * names[] = {#v1}; \
	char ** ppVars[10]; \
	ppVars[0] = &(pApp->v1); \
	GetAttribValsWithMemAlloc(attrs, names, ppVars, sizeof(names)/sizeof(char*)); \
}

#define GetAttribToApp_2(attrs, pApp, v1, v2) { \
	char * names[] = {#v1, #v2}; \
	char ** ppVars[10]; \
	ppVars[0] = &(pApp->v1); \
	ppVars[1] = &(pApp->v2); \
	GetAttribValsWithMemAlloc(attrs, names, ppVars, sizeof(names)/sizeof(char*)); \
}

#define GetAttribToApp_3(attrs, pApp, v1, v2, v3) { \
	char * names[] = {#v1, #v2, #v3}; \
	char ** ppVars[10]; \
	ppVars[0] = &(pApp->v1); \
	ppVars[1] = &(pApp->v2); \
	ppVars[2] = &(pApp->v3); \
	GetAttribValsWithMemAlloc(attrs, names, ppVars, sizeof(names)/sizeof(char*)); \
}

#define GetAttribToApp_4(attrs, pApp, v1, v2, v3, v4) { \
	char * names[] = {#v1, #v2, #v3, #v4}; \
	char ** ppVars[10]; \
	ppVars[0] = &(pApp->v1); \
	ppVars[1] = &(pApp->v2); \
	ppVars[2] = &(pApp->v3); \
	ppVars[3] = &(pApp->v4); \
	GetAttribValsWithMemAlloc(attrs, names, ppVars, sizeof(names)/sizeof(char*)); \
}

#define GetAttribToApp_5(attrs, pApp, v1, v2, v3, v4, v5) { \
	char * names[] = {#v1, #v2, #v3, #v4, #v5}; \
	char ** ppVars[10]; \
	ppVars[0] = &(pApp->v1); \
	ppVars[1] = &(pApp->v2); \
	ppVars[2] = &(pApp->v3); \
	ppVars[3] = &(pApp->v4); \
	ppVars[4] = &(pApp->v5); \
	GetAttribValsWithMemAlloc(attrs, names, ppVars, sizeof(names)/sizeof(char*)); \
}

#define GetAttribToApp_6(attrs, pApp, v1, v2, v3, v4, v5, v6) { \
	char * names[] = {#v1, #v2, #v3, #v4, #v5, #v6}; \
	char ** ppVars[10]; \
	ppVars[0] = &(pApp->v1); \
	ppVars[1] = &(pApp->v2); \
	ppVars[2] = &(pApp->v3); \
	ppVars[3] = &(pApp->v4); \
	ppVars[4] = &(pApp->v5); \
	ppVars[5] = &(pApp->v6); \
	GetAttribValsWithMemAlloc(attrs, names, ppVars, sizeof(names)/sizeof(char*)); \
}

#define GetAttribToApp_7(attrs, pApp, v1, v2, v3, v4, v5, v6, v7) { \
	char * names[] = {#v1, #v2, #v3, #v4, #v5, #v6, #v7}; \
	char ** ppVars[10]; \
	ppVars[0] = &(pApp->v1); \
	ppVars[1] = &(pApp->v2); \
	ppVars[2] = &(pApp->v3); \
	ppVars[3] = &(pApp->v4); \
	ppVars[4] = &(pApp->v5); \
	ppVars[5] = &(pApp->v6); \
	ppVars[6] = &(pApp->v7); \
	GetAttribValsWithMemAlloc(attrs, names, ppVars, sizeof(names)/sizeof(char*)); \
}

#define GetAttribToApp_8(attrs, pApp, v1, v2, v3, v4, v5, v6, v7, v8) { \
	char * names[] = {#v1, #v2, #v3, #v4, #v5, #v6, #v7, #v8}; \
	char ** ppVars[10]; \
	ppVars[0] = &(pApp->v1); \
	ppVars[1] = &(pApp->v2); \
	ppVars[2] = &(pApp->v3); \
	ppVars[3] = &(pApp->v4); \
	ppVars[4] = &(pApp->v5); \
	ppVars[5] = &(pApp->v6); \
	ppVars[6] = &(pApp->v7); \
	ppVars[7] = &(pApp->v8); \
	GetAttribValsWithMemAlloc(attrs, names, ppVars, sizeof(names)/sizeof(char*)); \
}


void SclSAX2Handler::GetSclAttribs(const Attributes& attrs)
{
	SCL_TAG tag = m_pParInd->elemType[m_pParInd->ind];
	char * vals[16];

	switch(tag)
	{
	case TAG_PRIVATE:	{
		CNariPrivate *pPrivate = (CNariPrivate*) m_pParInd->GetCurElement();
		GetAttribToApp(attrs,pPrivate,type);
		break;
						
		}

		case TAG_NARI_VOL:{
		Nari_Voltage *pVol = (Nari_Voltage*) m_pParInd->GetCurElement();
		GetAttribToApp(attrs,pVol,name);
		break;
		}
		case TAG_NARI_BAY:{
		Nari_Bay * pBay = (Nari_Bay*)m_pParInd->GetCurElement();
		GetAttribToApp(attrs,pBay,name);
		break;
	    }
		case TAG_NARI_IED:{
		Nari_IED * pIed = (Nari_IED*)m_pParInd->GetCurElement();
		GetAttribToApp_2(attrs,pIed,name,desc);
		break;
		}

	case TAG_Header: 	{
		CHeader *pHeader = (CHeader*) m_pParInd->pElement[m_pParInd->ind];
		GetAttribToApp_5(attrs, pHeader, id, version, revision, toolID, nameStructure)
// 		char * names[] = {"id", "version", "revision", "toolID", "nameStructure"};
// 
// 		GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
// 		pHeader->id = sclMem.AllocAndCopy(vals[0]);
// 		pHeader->version = sclMem.AllocAndCopy(vals[1]);
// 		pHeader->revision = sclMem.AllocAndCopy(vals[2]);
// 		pHeader->toolID = sclMem.AllocAndCopy(vals[3]);
// 		pHeader->nameStructure = sclMem.AllocAndCopy(vals[4]);
// 		ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		break;
		}
	
	case TAG_Hitem:	{
		Hitem *pHitem = (Hitem*) m_pParInd->GetCurElement();
		GetAttribToApp_6(attrs, pHitem, version, revision, when, who, what, why)
		}
		break;
	
	case TAG_Communication:
		break;

	case TAG_SubNetwork:	{
		CSubNetwork *pSubNet = (CSubNetwork*) m_pParInd->GetCurElement();
		GetAttribToApp_3(attrs, pSubNet, desc, name, type)
		}
		break;

	case TAG_ConnectedAP:	{
		CConnectedAP *pConnectAP = (CConnectedAP*) m_pParInd->GetCurElement();
		GetAttribToApp_3(attrs, pConnectAP, desc, iedName, apName)
		}
		break;

	case TAG_GSE:	{
		GSE *pGSE = (GSE*) m_pParInd->GetCurElement();
		GetAttribToApp_3(attrs, pGSE, desc, ldInst, cbName)
		}
		break;

	case TAG_SMV:	{
		SMV *pSMV = (SMV*) m_pParInd->GetCurElement();
		GetAttribToApp_3(attrs, pSMV, desc, ldInst, cbName)
		}
		break;

	case TAG_PhysConn:	{
			PhysConn *pPhysConn = (PhysConn*) m_pParInd->GetCurElement();
			char *p = GetAttribVal(attrs, "type");
			if(p != NULL){
				pPhysConn->conn_type = sclMem.AllocAndCopy(p);
				XMLString::release(&p);
			}
		}
		break;
		
	case TAG_IED:	{
		CIed *pIed = (CIed*) m_pParInd->GetCurElement();
		GetAttribToApp_5(attrs, pIed, name, desc, type, manufacturer, configVersion)
		}
		break;

	case TAG_ConfDataSet:	{
			Service *pService = (Service*) m_pParInd->GetElementByOffset(-1);
			pService->hasConfDataSet = true;
			char * names[] = {"max", "maxAttributes", "modify"};

	 		GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			if(vals[0])		pService->maxConfDataset = atoi(vals[0]);
			else			pService->maxConfDataset = 0xffff;

			if(vals[1])		pService->maxConfDatasetAttributes = atoi(vals[1]);
			else			pService->maxConfDatasetAttributes = 0xffff;
			pService->confDatasetModify = String2Bool(vals[2]);
	 		ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		}
		break;

	case TAG_DynDataSet:	{
			Service *pService = (Service*) m_pParInd->GetElementByOffset(-1);
			char * names[] = {"max", "maxAttributes"};
			
			GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			if(vals[0])		pService->maxDynDataset = atoi(vals[0]);
			else			pService->maxDynDataset = 0xffff;
			if(vals[1])		pService->maxDynDatasetAttributes = atoi(vals[1]);
			else			pService->maxDynDatasetAttributes = 0xffff;
	 		ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		}
		break;

	case TAG_ReportSettings:	{
			Service *pService = (Service*) m_pParInd->GetElementByOffset(-1);
			pService->hasReportSet = true;
			char * names[] = {"cbName", "datSet", "rptID", "optFields", "bufTime", "trgOps", "intgPd"};
	
			GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			pService->rptCbName = GetOnlineSetting(vals[0]);
			pService->rptDataset = GetOnlineSetting(vals[1]);
			pService->rptID = GetOnlineSetting(vals[2]);
			pService->rptOptFields = GetOnlineSetting(vals[3]);
			pService->rptBufTime = GetOnlineSetting(vals[4]);
			pService->rptTrgOps = GetOnlineSetting(vals[5]);
			pService->rptIntgPd = GetOnlineSetting(vals[6]);
			ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		}
		break;

	case TAG_LogSettings:	{
			Service *pService = (Service*) m_pParInd->GetElementByOffset(-1);
			pService->hasLogSet = true;
			char * names[] = {"cbName", "datSet", "logEna", "trgOps", "intgPd"};
			
			GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			pService->logCbName = GetOnlineSetting(vals[0]);
			pService->logDataset = GetOnlineSetting(vals[1]);
			pService->logEna = GetOnlineSetting(vals[2]);
			pService->logTrgOps = GetOnlineSetting(vals[3]);
			pService->logIntgPd = GetOnlineSetting(vals[4]);
			ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		}
		break;

	case TAG_GSESettings:	{
			Service *pService = (Service*) m_pParInd->GetElementByOffset(-1);
			char * names[] = {"cbName", "datSet", "appID"};
			
			GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			pService->gseCbName = GetOnlineSetting(vals[0]);
			pService->gseDataset = GetOnlineSetting(vals[1]);
			pService->gseAppid = GetOnlineSetting(vals[2]);
			ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		}
		break;

	case TAG_SMVSettings:	{
			Service *pService = (Service*) m_pParInd->GetElementByOffset(-1);
			char * names[] = {"cbName", "datSet", "svID", "optFields", "smpRate"};
			
			GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			pService->smvCbName = GetOnlineSetting(vals[0]);
			pService->smvDataset = GetOnlineSetting(vals[1]);
			pService->svID = GetOnlineSetting(vals[2]);
			pService->smvOptFields = GetOnlineSetting(vals[3]);
			pService->smvSmpRate = GetOnlineSetting(vals[4]);
			ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		}
		break;

	case TAG_ConfLNs:	{
			Service *pService = (Service*) m_pParInd->GetElementByOffset(-1);
			char * names[] = {"fixPrefix", "fixLnInst"};
			
			GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			pService->fixLNprefix = String2Bool(vals[0]);
			pService->fixLNinst = String2Bool(vals[1]);
			ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		}
		break;

	case TAG_AccessPoint:	{
			CAccessPoint *pAp = (CAccessPoint*) m_pParInd->GetCurElement();
			char * names[] = {"name", "desc", "router", "clock"};

			GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			pAp->name = sclMem.AllocAndCopy(vals[0]);
			pAp->desc = sclMem.AllocAndCopy(vals[1]);
			pAp->router = String2Bool(vals[2]);
			pAp->clock = String2Bool(vals[3]);
			ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		}
		break;

	case TAG_Server:	{
			CServer* pSvr = (CServer*) m_pParInd->GetCurElement();
			char * names[] = {"desc", "timeout"};

			GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			pSvr->desc = sclMem.AllocAndCopy(vals[0]);
			if(vals[1])			pSvr->timeout = atoi(vals[1]);
			else				pSvr->timeout = 30;
			ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		}
		break;

	case TAG_Authentication:	{
			Authentication *pAuth = (Authentication*) m_pParInd->GetCurElement();
			char * names[] = {"none", "password", "weak", "strong", "certificate"};

			GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			if(vals[0])		pAuth->none = String2Bool(vals[0]);
			else			pAuth->none = true;
			pAuth->password = String2Bool(vals[1]);
			pAuth->weak = String2Bool(vals[2]);
			pAuth->strong = String2Bool(vals[3]);
			pAuth->certificate = String2Bool(vals[4]);
			ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		}
		break;

	case TAG_LDevice:	{
			CLDevice *pLd = (CLDevice*) m_pParInd->GetCurElement();
			GetAttribToApp_2(attrs, pLd, desc, inst)
		}
		break;

	case TAG_LN0:	{
			CLN0* pLn0 = (CLN0*) m_pParInd->GetCurElement();
			GetAttribToApp_3(attrs, pLn0, desc, lnType, lnClass)
		}
		break;

	case TAG_LN:	{
			CLN* pLn = (CLN*) m_pParInd->GetCurElement();
			GetAttribToApp_5(attrs, pLn, desc, lnType, lnClass, inst, prefix)
			char* infoc = (char*)malloc(MIDDLE_STR_LEN);
			strcpy(infoc,pLn->prefix);//= (*pLn->prefix)+(*pLn->lnClass)+(*pLn->inst);
			strcat(infoc,pLn->lnClass);
			strcat(infoc,pLn->inst);
			pLn->info = infoc;
		}
		break;

	case TAG_GSEControl:	{
			CGSEControl* pGSEControl = (CGSEControl*) m_pParInd->GetCurElement();
			GetAttribToApp_5(attrs, pGSEControl, name, desc, datSet, type, appID)
			char *p = GetAttribVal(attrs, "confRev");
			if(p){
				pGSEControl->confRev = atoi(p);
				XMLString::release(&p);
			}
		}
		break;

	case TAG_SampledValueControl:	{
			CSMVControl *pSMVControl = (CSMVControl*) m_pParInd->GetCurElement();
			GetAttribToApp_4(attrs, pSMVControl, name, desc, datSet, smvID)
			char * names[] = {"confRev", "multicast", "smpRate", "nofASDU"};
			GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			if(vals[0])
				pSMVControl->confRev = atoi(vals[0]);
			pSMVControl->multicast = String2Bool(vals[1]);
			if(vals[2])
				pSMVControl->smpRate = atoi(vals[2]);
			if(vals[3])
				pSMVControl->nofASDU = atoi(vals[3]);
			ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		}
		break;

	case TAG_SmvOpts:	{
			SMVOpts *pOpts = (SMVOpts*) m_pParInd->GetCurElement();
			char * names[] = {"refreshTime", "sampleSynchronized", "sampleRate", "security", "dataRef"};

			GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			pOpts->refreshTime = String2Bool(vals[0]);
			pOpts->smpSynced = String2Bool(vals[1]);
			pOpts->smpRate = String2Bool(vals[2]);
			pOpts->security = String2Bool(vals[3]);
			pOpts->dataset = String2Bool(vals[4]);
			ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		}
		break;

	case TAG_SettingControl:	{
			SettingControl *pSet = (SettingControl*) m_pParInd->GetCurElement();
			char * names[] = {"desc", "numOfSGs", "actSG"};

			GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			pSet->desc = sclMem.AllocAndCopy(vals[0]);
			if(vals[1])
				pSet->numOfSGs = atoi(vals[1]);
			if(vals[2])			pSet->actSG = atoi(vals[2]);
			else				pSet->actSG = 1;
			ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		}
		break;

	case TAG_DataSet:	{
			CDataSet *pDataSet = (CDataSet*) m_pParInd->GetCurElement();
			GetAttribToApp_2(attrs, pDataSet, name, desc)
		}
		break;

	case TAG_FCDA:	{
			FCDA *pFCDA = (FCDA*) m_pParInd->GetCurElement();
			GetAttribToApp_7(attrs, pFCDA, ldInst, prefix, lnClass, lnInst, doName, daName, fc)
		}
		break;

	case TAG_ReportControl:	{
			CRptControl *pRpt = (CRptControl*) m_pParInd->GetCurElement();
			GetAttribToApp_4(attrs, pRpt, name, desc, datSet, rptID)
			char *names[] = {"intgPd", "confRev", "buffered", "bufTime"};
			GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			if(vals[0])
				pRpt->intgPd = atoi(vals[0]);
			if(vals[1])
				pRpt->confRev = atoi(vals[1]);
			pRpt->buffered = String2Bool(vals[2]);
			if(vals[3])	
				pRpt->bufTime = atoi(vals[3]);
			ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		}
		break;

	case TAG_TrgOps:	{
			TrgOps *pTrgOps = (TrgOps*) m_pParInd->GetCurElement();
			char *names[] = {"dchg", "qchg", "dupd", "period"};
			GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			pTrgOps->dchg = String2Bool(vals[0]);
			pTrgOps->qchg = String2Bool(vals[1]);
			pTrgOps->dupd = String2Bool(vals[2]);
			pTrgOps->period = String2Bool(vals[3]);
			ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		}
		break;

	case TAG_OptFields:	{
			OptFields *pOptFields = (OptFields*) m_pParInd->GetCurElement();
			char *names[] = {"seqNum", "timeStamp", "dataSet", "reasonCode", "dataRef", "entryID", "configRef"};
			GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			pOptFields->seqNum = String2Bool(vals[0]);
			pOptFields->timeStamp = String2Bool(vals[1]);
			pOptFields->dataSet = String2Bool(vals[2]);
			pOptFields->reasonCode = String2Bool(vals[3]);
			pOptFields->dataRef = String2Bool(vals[4]);
			pOptFields->entryID = String2Bool(vals[5]);
			pOptFields->configRef = String2Bool(vals[6]);
			ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		}
		break;

	case TAG_RptEnabled:	{
			CRptEnabled *pRptEnabled = (CRptEnabled*) m_pParInd->GetCurElement();
			char *names[] = {"desc", "max"};
			GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			pRptEnabled->desc = sclMem.AllocAndCopy(vals[0]);
			if(vals[1])	
				pRptEnabled->max = atoi(vals[1]);
			ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		}
		break;

	case TAG_ClientLN:	{
			ClientLN *pClient = (ClientLN*) m_pParInd->GetCurElement();
			GetAttribToApp_5(attrs, pClient, iedName, ldInst, prefix, lnClass, lnInst)
		}
		break;

	case TAG_LogControl:	{
			CLogControl* pLogControl = (CLogControl*) m_pParInd->GetCurElement();
			GetAttribToApp_4(attrs, pLogControl, name, desc, datSet, logName)
			char *names[] = {"intgPd", "logEna", "reasonCode"};
			GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			if(vals[0])	
				pLogControl->intgPd = atoi(vals[0]);
			pLogControl->logEna = String2Bool(vals[1]);
			pLogControl->reasonCode = String2Bool(vals[2]);
			ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		}
		break;

	case TAG_DOI:	{
			CDOI *pDoi = (CDOI*) m_pParInd->GetCurElement();
			GetAttribToApp_3(attrs, pDoi, name, desc, accessControl)
			char * p = GetAttribVal(attrs, "ix");
			if(p)
				pDoi->ix = atoi(p);
			XMLString::release(&p);
		}
		break;

	case TAG_SDI:	{
			CSDI *pSdi = (CSDI*) m_pParInd->GetCurElement();
			GetAttribToApp_2(attrs, pSdi, desc, name)
			char * p = GetAttribVal(attrs, "ix");
			if(p)
				pSdi->ix = atoi(p);
			XMLString::release(&p);
		}
		break;

	case TAG_DAI:	{
			CDAI *pDai = (CDAI*) m_pParInd->GetCurElement();
			GetAttribToApp_3(attrs, pDai, desc, name, sAddr)
			char *names[] = {"ix", "valKind"};
			GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			if(vals[0])
				pDai->ix = atoi(vals[0]);
			pDai->valKind = String2ValKind(vals[1]);
			ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		}
		break;

	case TAG_Inputs:	{
			CInputs *pInputs = (CInputs*) m_pParInd->GetCurElement();
			char *p = GetAttribVal(attrs, "desc");
			pInputs->desc = sclMem.AllocAndCopy(p);
			XMLString::release(&p);
		}
		break;

	case TAG_ExtRef:	{
			ExtRef *pExtRef = (ExtRef*) m_pParInd->GetCurElement();
			GetAttribToApp_8(attrs, pExtRef, iedName, ldInst, prefix, lnClass, lnInst, doName, daName, intAddr)
		}
		break;

	case TAG_Association:	{
			Association *pAssoc = (Association*) m_pParInd->GetCurElement();
			GetAttribToApp_7(attrs, pAssoc, kind, associationID, iedName, ldInst, prefix, lnClass, lnInst)
		}
		break;
	
	case TAG_DataTypeTemplates:
		break;

	case TAG_LNodeType:	{
			//if(this->m_parseType==1){//sgcc
			//	CLNodeType * pLnType =  (CLNodeType*) m_pParInd->GetCurElement();
			//	char *p = GetAttribVal(attrs, "lnClass");
			//	if(!p){
			//		pLnType->lnClass = sclMem.AllocAndCopy(p);
			//		pLnType->id = sclMem.AllocAndCopy(p);
			//	}
			//    //GetAttribToApp_2(attrs, pLnType, id, lnClass)
			//}
			if((this->m_parseType==2)||(this->m_parseType==1)){//61850
				CLNodeType * pLnType =  (CLNodeType*) m_pParInd->GetCurElement();
                char *p = GetAttribVal(attrs, "lnClass");
				if(p){
					pLnType->lnClass = sclMem.AllocAndCopy(p);
					pLnType->id = sclMem.AllocAndCopy(p);
				}				
				XMLString::release(&p);
			}
			else{//icd
				CLNodeType * pLnType =  (CLNodeType*) m_pParInd->GetCurElement();
				GetAttribToApp_4(attrs, pLnType, id, desc, iedType, lnClass)
			}			
		}
		break;

	case TAG_DO:	{
			if((this->m_parseType==2)||(this->m_parseType==1)){
				DO *pDo = (DO*) m_pParInd->GetCurElement();
				char * names[] = {"name", "cdc", "mop"};
				GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
				pDo->name = sclMem.AllocAndCopy(vals[0]);
				pDo->type = sclMem.AllocAndCopy(vals[1]);
				if(vals[2]){
					if(strcmp(vals[2],"M")==0){
						pDo->m_nExistType = FLAG_EXIST_M;
					}
					else if(strcmp(vals[2],"C")==0){
						pDo->m_nExistType = FLAG_EXIST_C;
					}
					else
					{
						pDo->m_nExistType = FLAG_EXIST_O;
					}
				}
				ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
			}
/*			else if(m_parseType==1){
				DO *pDo = (DO*) m_pParInd->GetCurElement();
				GetAttribToApp_4(attrs, pDo, desc, name, type, accessControl)
				char *p = GetAttribVal(attrs, "transient");
				pDo->transient = String2Bool(p);
				char *p1 = GetAttribVal(attrs, "mop");
				if(p1){
					if(strcmp(p1,"M")==0){
						pDo->m_nExistType = FLAG_EXIST_M;
					}
					else if(strcmp(p1,"C")==0){
						pDo->m_nExistType = FLAG_EXIST_C;
					}
					else
					{
						pDo->m_nExistType = FLAG_EXIST_O;
					}
				}				
				XMLString::release(&p);
				XMLString::release(&p1);
			}	*/	
			else{
				DO *pDo = (DO*) m_pParInd->GetCurElement();
				GetAttribToApp_4(attrs, pDo, desc, name, type, accessControl)
				char *p = GetAttribVal(attrs, "transient");
				pDo->transient = String2Bool(p);
				XMLString::release(&p);
			}
		}
		break;

	case TAG_DOType:	{
			if(m_parseType==1){
				CDOType *pDOType = (CDOType*) m_pParInd->GetCurElement();
				GetAttribToApp_2(attrs, pDOType, id, cdc)				
			}
			else if(m_parseType==2){
				CDOType *pDOType = (CDOType*) m_pParInd->GetCurElement();
				char *p = GetAttribVal(attrs, "cdc");
				pDOType->cdc = sclMem.AllocAndCopy(p);
				char *p1 = GetAttribVal(attrs, "id");
				if(p1){
					if(strlen(p1)==0){
						pDOType->id = sclMem.AllocAndCopy(p);
					}
					else{
						pDOType->id = sclMem.AllocAndCopy(p1);
					}
				}	
				else{
					pDOType->id = sclMem.AllocAndCopy(p);
				}
				XMLString::release(&p);
				XMLString::release(&p1);
			}
			else{
				CDOType *pDOType = (CDOType*) m_pParInd->GetCurElement();
				GetAttribToApp_4(attrs, pDOType, id, desc, iedType, cdc)
			}
		}
		break;

	case TAG_SDO:	{
			if((this->m_parseType==2)||(this->m_parseType==1)){
				SDO *pSdo = (SDO*) m_pParInd->GetCurElement();
				char * names[] = {"name", "cdc", "mop"};
				GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
				pSdo->name = sclMem.AllocAndCopy(vals[0]);
				pSdo->type = sclMem.AllocAndCopy(vals[1]);
				if(vals[2]){
					if(strcmp(vals[2],"M")==0){
						pSdo->m_nExistType = FLAG_EXIST_M;
					}
					else if(strcmp(vals[2],"C")==0){
						pSdo->m_nExistType = FLAG_EXIST_C;
					}
					else
					{
						pSdo->m_nExistType = FLAG_EXIST_O;
					}
				}				
				ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
			}
			/*else if(m_parseType==1){
				SDO *pSdo = (SDO*) m_pParInd->GetCurElement();
				GetAttribToApp_3(attrs, pSdo, name, desc, type)
				char *p = GetAttribVal(attrs, "mop");
				if(p){
					if(strcmp(p,"M")==0){
						pSdo->m_nExistType = FLAG_EXIST_M;
					}
					else if(strcmp(p,"C")==0){
						pSdo->m_nExistType = FLAG_EXIST_C;
					}
					else
					{
						pSdo->m_nExistType = FLAG_EXIST_O;
					}
				}				
				XMLString::release(&p);
			}*/
			else{
				SDO *pSdo = (SDO*) m_pParInd->GetCurElement();
				GetAttribToApp_3(attrs, pSdo, name, desc, type)
			}
		}
		break;

	case TAG_DA:	{
			CDA *pDa = (CDA*) m_pParInd->GetCurElement();
			GetAttribToApp_5(attrs, pDa, desc, name, sAddr, bType, type)
			char * names[] = {"valKind", "count", "dchg", "qchg", "dupd", "fc",};
			GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			pDa->valKind = String2ValKind(vals[0]);
			if(vals[1])
				pDa->count = atoi(vals[1]);
			pDa->dchg = String2Bool(vals[2]);
			pDa->qchg = String2Bool(vals[3]);
			pDa->dupd = String2Bool(vals[4]);
			if(vals[5]){
				memcpy(pDa->fc, vals[5], 3);
			}
			ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
			if((m_parseType==1)||(m_parseType==2)){
				char *p = GetAttribVal(attrs, "mop");
				if(p){
					if(strcmp(p,"M")==0){
						pDa->m_nExistType = FLAG_EXIST_M;
					}
					else if(strcmp(p,"C")==0){
						pDa->m_nExistType = FLAG_EXIST_C;
					}
					else
					{
						pDa->m_nExistType = FLAG_EXIST_O;
					}
				}				
				XMLString::release(&p);
			}
		}
		break;

	case TAG_DAType:
		{
			CDAType *pDAType = (CDAType*) m_pParInd->GetCurElement();
			GetAttribToApp_3(attrs, pDAType, id, desc, iedType)
		}
		break;

	case TAG_BDA:	{
			CBDA *pBda = (CBDA*) m_pParInd->GetCurElement();
			GetAttribToApp_5(attrs, pBda, desc, name, sAddr, bType, type)
				char * names[] = {"valKind", "count","mop"};
			GetAttribVals(attrs, names, vals, sizeof(names)/sizeof(char*));
			pBda->valKind = String2ValKind(vals[0]);
			if(vals[1])
				pBda->count = atoi(vals[1]);
			if(vals[2]){
				if(strcmp(vals[2],"M")==0){
					pBda->m_nExistType = FLAG_EXIST_M;
				}
				else if(strcmp(vals[2],"C")==0){
					pBda->m_nExistType = FLAG_EXIST_C;
				}
				else
				{
					pBda->m_nExistType = FLAG_EXIST_O;
				}
			}			
			ReleaseXmlString(vals, sizeof(names)/sizeof(char*));
		}
		break;

	case TAG_EnumType:
		{
			CEnumType *pEnumType = (CEnumType*) m_pParInd->GetCurElement();
			GetAttribToApp_2(attrs, pEnumType, id, desc)
		}
		break;

	case TAG_EnumVal:
		{
			EnumVal *pEnumVal = (EnumVal*) m_pParInd->GetCurElement();
			char *p = GetAttribVal(attrs, "ord");
			pEnumVal->ord = atoi(p);
			XMLString::release(&p);
		}
		break;

	default:
		break;
	}
}

void SclSAX2Handler::startElement(const   XMLCh* const    uri,
                            const   XMLCh* const    localname,
                            const   XMLCh* const    qname,
                            const   Attributes&     attrs)
{
   // char* element = XMLString::transcode(localname);
	char* element = XMLString::transcode(qname);
    //cout << "I saw element: "<< element << endl;
	m_preTag = (string)element;
	m_strList.clear();

	//printf("%s\n",element);
	if (!strcmp(element, "SCL"))
	{
		if(m_pScl)
		{
			m_pParInd->Push(m_pScl, TAG_SCL);
			if(m_pScl->m_pProgressNotifier)
				m_pScl->m_pProgressNotifier->UpdateProgress("开始扫描模型文件...", 1);
		}
		XMLString::release(&element);
		return;
	}
	else if(m_pParInd->GetLevel()==1&&!m_pParInd->CmpPath(SCL_Private, 1) &&!strcmp(element,"Private"))
	{
		//printf("in it?");
		CNariPrivate* pPrivte = new CNariPrivate;
		m_pScl->listNariPrivates.push_back(pPrivte);
		m_pParInd->Push(pPrivte,TAG_PRIVATE);
		GetSclAttribs(attrs);
		pPrivte->lineNo = m_locator->getLineNumber();
	}
// 	else if(!m_pParInd->CmpPath(SCL_Private,2))
// 	{
	else if(!m_pParInd->CmpPath(VOLTAGE, 2) &&!strcmp(element,"naritech:Voltage"))
		{
			CNariPrivate * pPrivate = (CNariPrivate*) m_pParInd->GetCurElement();
			Nari_Voltage * pVol = new Nari_Voltage;//(Nari_Voltage*) sclMem.AllocMem(sizeof(Nari_Voltage));
			pPrivate->listVol.push_back(pVol);
			m_pParInd->Push(pVol, TAG_NARI_VOL);
			GetSclAttribs(attrs);
			pVol->lineNo = m_locator->getLineNumber();
		}
		else if(!m_pParInd->CmpPath(NARI_BAY, 3)&&!strcmp(element,"naritech:Bay"))
		{
			Nari_Voltage * pVol = (Nari_Voltage*)m_pParInd->GetCurElement();
			Nari_Bay * pBay = new Nari_Bay;//(Nari_Bay*) sclMem.AllocMem(sizeof(Nari_Bay));
			pVol->listOfNari_Bay.push_back(pBay);
			m_pParInd->Push(pBay,TAG_NARI_BAY);
			GetSclAttribs(attrs);
			pBay->lineNo = m_locator->getLineNumber();

		}
		else if(!m_pParInd->CmpPath(NARI_IED, 4)&&!strcmp(element,"naritech:IED"))
		{
			Nari_Bay * pBay = (Nari_Bay*)m_pParInd->GetCurElement();
			Nari_IED * pIED = new Nari_IED;//(Nari_IED*)sclMem.AllocMem(sizeof(Nari_IED));
			pBay->listOfNari_IED.push_back(pIED);
			m_pParInd->Push(pIED,TAG_NARI_IED);
			GetSclAttribs(attrs);
			pIED->lineNo = m_locator->getLineNumber();
		}
// 		else 
// 		{
// 			m_pParInd->Push(NULL, TAG_NULL);
// 		}
		
	//}

	else if(!m_pParInd->CmpPath(SCL_, 1) && !strcmp(element, "IED"))
	{
		CIed *pIed = new CIed;
		m_pScl->listIeds.push_back(pIed);
		m_pParInd->Push(pIed, TAG_IED);
		GetSclAttribs(attrs);
		pIed->lineNo = m_locator->getLineNumber();
		if(strcmp(pIed->name,"MPT220001")==0){
			int f=3;
		}
	}

	else if( !strcmp(element, "DataTypeTemplates") )
	{
		if(m_pScl)
		{
			if(m_pScl->m_pProgressNotifier)
				m_pScl->m_pProgressNotifier->UpdateProgress("正在扫描模型文件...",18);
		}
	}
	else if (!m_pParInd->CmpPath(SCL_,1) && !strcmp(element, "Header"))
	{
		m_pParInd->Push(&m_pScl->header, TAG_Header);
		GetSclAttribs(attrs);
		m_pScl->header.lineNo = m_locator->getLineNumber();
	}
	else if(!m_pParInd->CmpPath(SCL_Header, 2))
	{
		if(!strcmp(element, "History"))
		{
			/*CHeader * pHead = (CHeader*) m_pParInd->GetCurElement();
			pHead->history = (CHistory*) sclMem.AllocMem(sizeof(CHistory));
			m_pParInd->Push(pHead->history, TAG_History);
			pHead->history->lineNo = m_locator->getLineNumber();*/
			m_pParInd->Push(NULL, TAG_History);
		}
		else if(!m_pParInd->CmpPartPath(2, _History, 1) && !strcmp(element, "Hitem"))
		{
			//CHeader * pHead = (CHeader*) m_pParInd->GetCurElement();
			/*CHistory * pHis = (CHistory*) m_pParInd->GetCurElement();
			Hitem * pHitem = (Hitem*) sclMem.AllocMem(sizeof(Hitem));
			pHis->listHitem.push_back(pHitem);
			m_pParInd->Push(pHitem, TAG_Hitem);
			GetSclAttribs(attrs);
			pHitem->lineNo = m_locator->getLineNumber();*/

			CHeader * pHead = (CHeader*) m_pParInd->GetElementByOffset(-1);
			Hitem * pHitem = (Hitem*) sclMem.AllocMem(sizeof(Hitem));
			pHead->listHitem.push_back(pHitem);
			m_pParInd->Push(pHitem, TAG_Hitem);
			GetSclAttribs(attrs);
			pHitem->lineNo = m_locator->getLineNumber();
		}
		else
			m_pParInd->Push(NULL, TAG_NULL);
	}
	else if(!m_pParInd->CmpPath(SCL_, 1) && !strcmp(element, "Substation"))
	{
		m_pParInd->Push(NULL, TAG_Substation);
	}
	else if(!m_pParInd->CmpPath(SCL_, 1) && !strcmp(element, "Communication"))
	{
		m_pParInd->Push(&m_pScl->communication, TAG_Communication);
		GetSclAttribs(attrs);
		m_pScl->communication.lineNo = m_locator->getLineNumber();
	}
	else if(!m_pParInd->CmpPath(SCL_Communication, 2))
	{
		if(!strcmp(element, "SubNetwork"))
		{
			CCommunication *pComm = (CCommunication*) m_pParInd->GetCurElement();
			CSubNetwork * pSubNet = new CSubNetwork;
			pComm->subnetworks.push_back(pSubNet);
			m_pParInd->Push(pSubNet, TAG_SubNetwork);
			GetSclAttribs(attrs);
			pSubNet->lineNo = m_locator->getLineNumber();
		}
		else if(!m_pParInd->CmpPartPath(2, _SubNetwork, 1) && !strcmp(element, "BitRate"))
		{
			m_pParInd->Push(NULL, TAG_BitRate);
		}
		else if(!m_pParInd->CmpPartPath(2, _SubNetwork, 1) && !strcmp(element, "ConnectedAP"))
		{
			CSubNetwork * pSubNet = (CSubNetwork*) m_pParInd->GetCurElement();
			CConnectedAP * pConnectedAP = new CConnectedAP;
			pSubNet->listConnAPs.push_back(pConnectedAP);
			m_pParInd->Push(pConnectedAP, TAG_ConnectedAP);
			GetSclAttribs(attrs);
			pConnectedAP->lineNo = m_locator->getLineNumber();
		}
		else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP_Address, 3) && !strcmp(element, "P"))
		{
			m_pParInd->Push(NULL, TAG_P);
			curPType = GetAttribVal(attrs, "type");
		}
		else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP, 2) && !strcmp(element, "GSE"))
		{
			CConnectedAP * pConnectedAP = (CConnectedAP*) m_pParInd->GetCurElement();
			GSE *pGSE = (GSE*) sclMem.AllocMem(sizeof(GSE));
			m_pParInd->Push(pGSE, TAG_GSE);
			GetSclAttribs(attrs);
			pGSE->lineNo = m_locator->getLineNumber();
			pConnectedAP->listGSE.push_back(pGSE);
		}
		else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP_GSE, 3) && !strcmp(element, "Address"))
		{
			GSE *pGSE = (GSE*) m_pParInd->GetCurElement();
			pGSE->address = (Address*) sclMem.AllocMem(sizeof(Address));
			m_pParInd->Push(pGSE->address, TAG_Address);
			pGSE->address->lineNo = m_locator->getLineNumber();
		}
		else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP_GSE_Address, 4) && !strcmp(element, "P"))
		{
			m_pParInd->Push(NULL, TAG_P);
			curPType = GetAttribVal(attrs, "type");
		}
		else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP_GSE, 3) && !strcmp(element, "MinTime"))
		{
			m_pParInd->Push(NULL, TAG_MinTime);
		}
		else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP_GSE, 3) && !strcmp(element, "MaxTime"))
		{
			m_pParInd->Push(NULL, TAG_MaxTime);
		}
		else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP, 2) && !strcmp(element, "SMV"))
		{
			CConnectedAP * pConnectedAP = (CConnectedAP*) m_pParInd->GetCurElement();
			SMV *pSMV = (SMV*) sclMem.AllocMem(sizeof(SMV));
			pConnectedAP->listSMV.push_back(pSMV);
			m_pParInd->Push(pSMV, TAG_SMV);
			GetSclAttribs(attrs);
			pSMV->lineNo = m_locator->getLineNumber();
		}
		else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP_SMV, 3) && !strcmp(element, "Address"))
		{
			SMV *pSMV = (SMV*) m_pParInd->GetCurElement();
			pSMV->address = (Address*) sclMem.AllocMem(sizeof(Address));
			m_pParInd->Push(pSMV->address, TAG_Address);
			pSMV->address->lineNo = m_locator->getLineNumber();
		}
		else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP_SMV_Address, 4) && !strcmp(element, "P"))
		{
			m_pParInd->Push(NULL, TAG_P);
			curPType = GetAttribVal(attrs, "type");
		}
		else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP, 2) && !strcmp(element, "PhysConn"))
		{
			CConnectedAP * pConnectedAP = (CConnectedAP*) m_pParInd->GetCurElement();
			PhysConn * pPhysConn = (PhysConn*) sclMem.AllocMem(sizeof(PhysConn));
			pConnectedAP->listPhysConn.push_back(pPhysConn);
			m_pParInd->Push(pPhysConn, TAG_PhysConn);
			GetSclAttribs(attrs);
			pPhysConn->lineNo = m_locator->getLineNumber();
		}
		else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP_PhysConn, 3) && !strcmp(element, "P"))
		{
			m_pParInd->Push(NULL, TAG_P);
			curPType = GetAttribVal(attrs, "type");
		}
		else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP, 2) && !strcmp(element, "Address"))
		{
			CConnectedAP * pConnectedAP = (CConnectedAP*) m_pParInd->GetCurElement();
			pConnectedAP->pAddress = (Address*) sclMem.AllocMem(sizeof(Address));
			m_pParInd->Push(pConnectedAP->pAddress, TAG_Address);
			pConnectedAP->pAddress->lineNo = m_locator->getLineNumber();
		}
		else
			m_pParInd->Push(NULL, TAG_NULL);
	}
	else if(!m_pParInd->CmpPath(SCL_, 1) && !strcmp(element, "IED"))
	{
		CIed *pIed = new CIed;
		m_pScl->listIeds.push_back(pIed);
		m_pParInd->Push(pIed, TAG_IED);
		GetSclAttribs(attrs);
		pIed->lineNo = m_locator->getLineNumber();
		if(strcmp(pIed->name,"MPT220001")==0){
			int f=3;
		}
	}
	else if(!m_pParInd->CmpPath(SCL_IED, 2))
	{
		if(!strcmp(element, "Services"))
		{
			CIed *pIed = (CIed*) m_pParInd->GetCurElement();
			m_pParInd->Push(&pIed->services, TAG_Service);
			pIed->services.lineNo = m_locator->getLineNumber();
			pIed->hasServers = true;
		}
		else if(!m_pParInd->CmpPartPath(2, _Service, 1))
		{
			Service *pService = (Service*) m_pParInd->GetCurElement();
			int flag = 0;

			if(!strcmp(element, "DynAssociation"))
				pService->dynAssociation = true;
			else if(!strcmp(element, "SettingGroups")){
				pService->settingGroups = true;
				m_pParInd->Push(NULL, TAG_SettingGroups);
				flag = 1;
			}
			else if(!m_pParInd->CmpPartPath(2, _Service_SettingGroups, 2) && !strcmp(element, "SGEdit")){
				pService = (Service*) m_pParInd->GetElementByOffset(-1);
				pService->sgEdit = true;
			}				
			else if(!m_pParInd->CmpPartPath(2, _Service_SettingGroups, 2) && !strcmp(element, "ConfSG")){
				pService = (Service*) m_pParInd->GetElementByOffset(-1);
				pService->confSG = true;
			}				
			else if(!strcmp(element, "GetDirectory"))
				pService->getDirectory = true;
			else if(!strcmp(element, "GetDataObjectDefinition"))
				pService->getDataDefinition = true;
			else if(!strcmp(element, "DataObjectDirectory"))
				pService->getDataDirectory = true;
			else if(!strcmp(element, "GetDataSetValue"))
				pService->getDataSetValue = true;
			else if(!strcmp(element, "SetDataSetValue"))
				pService->setDataSetValue = true;
			else if(!strcmp(element, "DataSetDirectory"))
				pService->dataSetDirectory = true;
			else if(!strcmp(element, "ConfDataSet")){
				m_pParInd->Push(NULL, TAG_ConfDataSet);
				GetSclAttribs(attrs);
				flag = 1;
			}
			else if(!strcmp(element, "DynDataSet")){
				m_pParInd->Push(NULL, TAG_DynDataSet);
				GetSclAttribs(attrs);
				flag = 1;
			}
			else if(!strcmp(element, "ReadWrite"))
				pService->readWrite = true;
			else if(!strcmp(element, "TimerActivatedControl"))
				pService->timeActivatedControl = true;
			else if(!strcmp(element, "ConfReportControl")){
				char * p = GetAttribVal(attrs, "max");
				if(p != NULL){
					pService->hasConfReport = true;
					pService->maxRptControl = atoi(p);
					XMLString::release(&p);
				}
			}
			else if(!strcmp(element, "GetCBValues"))
				pService->getCBValues = true;
			else if(!strcmp(element, "ConfLogControl")){
				char * p = GetAttribVal(attrs, "max");
				if(p != NULL){
					pService->hasConfLogCtl = true;
					pService->maxLogControl = atoi(p);
					XMLString::release(&p);
				}
			}
			else if(!strcmp(element, "ReportSettings")){
				m_pParInd->Push(NULL, TAG_ReportSettings);
				GetSclAttribs(attrs);
				flag = 1;
			}
			else if(!strcmp(element, "LogSettings")){
				m_pParInd->Push(NULL, TAG_LogSettings);
				GetSclAttribs(attrs);
				flag = 1;
			}
			else if(!strcmp(element, "GSESettings")){
				m_pParInd->Push(NULL, TAG_GSESettings);
				GetSclAttribs(attrs);
				flag = 1;
			}
			else if(!strcmp(element, "SMVSettings")){
				m_pParInd->Push(NULL, TAG_SMVSettings);
				GetSclAttribs(attrs);
				flag = 1;
			}
			else if(!strcmp(element, "GSEDir"))
				pService->GSEDir = true;
			else if(!strcmp(element, "GOOSE")){
				char *p = GetAttribVal(attrs, "max");
				if(p != NULL){
					pService->hasGoose = true;
					pService->maxGoose = atoi(p);
					XMLString::release(&p);
				}
			}
			else if(!strcmp(element, "GSSE")){
				char *p = GetAttribVal(attrs, "max");
				if(p != NULL){
					pService->maxGsse = atoi(p);
					XMLString::release(&p);
				}
			}
			else if(!strcmp(element, "FileHandling"))
				pService->fileHandling = true;
			else if(!strcmp(element, "ConfLNs")){
				m_pParInd->Push(NULL, TAG_ConfLNs);
				GetSclAttribs(attrs);
				flag = 1;
			}
			/*else if(!strcmp(element, "ClientServices")){
				m_pParInd->Push(NULL, TAG_ClientServices);
				flag = 1;
			}*/

			if(flag == 0)
				m_pParInd->Push(NULL, TAG_NULL);
		}
		else if(!strcmp(element, "AccessPoint"))
		{
			CIed *pIed = (CIed*) m_pParInd->GetCurElement();
			CAccessPoint *pAp = new CAccessPoint;
			pIed->listAPs.push_back(pAp);
			m_pParInd->Push(pAp, TAG_AccessPoint);
			GetSclAttribs(attrs);
			pAp->lineNo = m_locator->getLineNumber();
		}
		else if(!m_pParInd->CmpPartPath(2, _AccessPoint, 1))
		{
			if (!strcmp(element, "Server"))
			{
				CAccessPoint *pAp = (CAccessPoint*) m_pParInd->GetCurElement();
				if(pAp->server == NULL)
					pAp->server = new CServer;
				m_pParInd->Push(pAp->server, TAG_Server);
				GetSclAttribs(attrs);
				pAp->server->lineNo = m_locator->getLineNumber();
			}
			else if(!m_pParInd->CmpPartPath(3, _Server, 1 ) && !strcmp(element, "Authentication"))
			{
				CServer *pSvr = (CServer*) m_pParInd->GetCurElement();
				m_pParInd->Push(&pSvr->auth, TAG_Authentication);
				GetSclAttribs(attrs);
				pSvr->auth.lineNo = m_locator->getLineNumber();
			}
			else if(!m_pParInd->CmpPartPath(3, _Server, 1 ) && !strcmp(element, "LDevice"))
			{
				CServer *pSvr = (CServer*) m_pParInd->GetCurElement();
				CLDevice *pLd = new CLDevice;
				pSvr->listLDs.push_back(pLd);
				m_pParInd->Push(pLd, TAG_LDevice);
				GetSclAttribs(attrs);
				pLd->lineNo = m_locator->getLineNumber();
			}
			else if(!m_pParInd->CmpPartPath(3, _Server_LDevice, 2) && !strcmp(element, "LN0"))
			{
				CLDevice *pLd = (CLDevice*) m_pParInd->GetCurElement();
				if(pLd->ln0 == NULL)
					pLd->ln0 = new CLN0;
				m_pParInd->Push(pLd->ln0, TAG_LN0);
				GetSclAttribs(attrs);
				pLd->ln0->lineNo = m_locator->getLineNumber();
			}
			else if(!m_pParInd->CmpPartPath(3, _Server_LDevice_LN0, 3) && !strcmp(element, "GSEControl"))
			{
				CLN0 *pLn0 = (CLN0*) m_pParInd->GetCurElement();
				CGSEControl *pGSEControl = new CGSEControl;
				pLn0->listGSEControl.push_back(pGSEControl);
				m_pParInd->Push(pGSEControl, TAG_GSEControl);
				GetSclAttribs(attrs);
				pGSEControl->lineNo = m_locator->getLineNumber();
			}
			else if(!m_pParInd->CmpPartPath(6, _GSEControl, 1) && !strcmp(element, "IEDName"))
			{
				m_pParInd->Push(NULL, TAG_IEDName);
			}
			else if(!m_pParInd->CmpPartPath(3, _Server_LDevice_LN0, 3) && !strcmp(element, "SampledValueControl"))
			{
				CLN0 *pLn0 = (CLN0*) m_pParInd->GetCurElement();
				CSMVControl *pSmvControl = new CSMVControl;
				pLn0->listSMVControl.push_back(pSmvControl);
				m_pParInd->Push(pSmvControl, TAG_SampledValueControl);
				GetSclAttribs(attrs);
				pSmvControl->lineNo = m_locator->getLineNumber();
			}
			else if(!m_pParInd->CmpPartPath(6, _SampledValueControl, 1) && !strcmp(element, "IEDName"))
			{
				m_pParInd->Push(NULL, TAG_IEDName);
			}
			else if(!m_pParInd->CmpPartPath(6, _SampledValueControl, 1) && !strcmp(element, "SmvOpts"))
			{
				CSMVControl *pSmvControl = (CSMVControl*) m_pParInd->GetCurElement();
				m_pParInd->Push(&pSmvControl->smvOpts, TAG_SmvOpts);
				pSmvControl->smvOpts.lineNo = m_locator->getLineNumber();
			}
			else if(!m_pParInd->CmpPartPath(3, _Server_LDevice_LN0, 3) && !strcmp(element, "SettingControl"))
			{
				CLN0 *pLn0 = (CLN0*) m_pParInd->GetCurElement();
				m_pParInd->Push(&pLn0->settingControl, TAG_SettingControl);
				GetSclAttribs(attrs);
				pLn0->settingControl.lineNo = m_locator->getLineNumber();
				pLn0->hasSettingControl = true;
			}
			else if(!m_pParInd->CmpPartPath(3, _Server_LDevice, 2) && !strcmp(element, "LN"))
			{
				CLDevice *pLd = (CLDevice*) m_pParInd->GetCurElement();
				CLN *pLn = new CLN;
				pLn->lineNo = m_locator->getLineNumber();
				pLd->listLNs.push_back(pLn);
				m_pParInd->Push(pLn, TAG_LN);
				GetSclAttribs(attrs);
			}
			else if(!m_pParInd->CmpPartPath(3, _Server_LDevice_LN0, 3) || !m_pParInd->CmpPartPath(3, _Server_LDevice_LN, 3))
			{
				if(!strcmp(element, "DataSet"))
				{
					CAnyLN * pLn = (CAnyLN*) m_pParInd->GetCurElement();
					CDataSet * pDataSet = new CDataSet;
					pLn->listDataset.push_back(pDataSet);
					m_pParInd->Push(pDataSet, TAG_DataSet);
					GetSclAttribs(attrs);
					pDataSet->lineNo = m_locator->getLineNumber();
				}
				else if(!m_pParInd->CmpPartPath(6, _DataSet, 1) && !strcmp(element, "FCDA"))
				{
					CDataSet *pDataSet = (CDataSet*) m_pParInd->GetCurElement();
					FCDA *pFCDA = (FCDA*) sclMem.AllocMem(sizeof(FCDA));
					pFCDA->initFCDA();
					pDataSet->FCDAs.push_back(pFCDA);
					m_pParInd->Push(pFCDA, TAG_FCDA);
					GetSclAttribs(attrs);
					pFCDA->lineNo = m_locator->getLineNumber();
				}
				else if(!strcmp(element, "ReportControl"))
				{
					CAnyLN * pLn = (CAnyLN*) m_pParInd->GetCurElement();
					CRptControl *pRptControl = new CRptControl;
					pLn->listRptControl.push_back(pRptControl);
					m_pParInd->Push(pRptControl, TAG_ReportControl);
					GetSclAttribs(attrs);
					pRptControl->lineNo = m_locator->getLineNumber();
				}
				else if(!m_pParInd->CmpPartPath(6, _ReportControl, 1) && !strcmp(element, "TrgOps"))
				{
					CRptControl *pRptControl = (CRptControl*) m_pParInd->GetCurElement();
					m_pParInd->Push(&pRptControl->trgOps, TAG_TrgOps);
					GetSclAttribs(attrs);
					pRptControl->trgOps.lineNo = m_locator->getLineNumber();
				}
				else if(!m_pParInd->CmpPartPath(6, _ReportControl, 1) && !strcmp(element, "OptFields"))
				{
					CRptControl *pRptControl = (CRptControl*) m_pParInd->GetCurElement();
					m_pParInd->Push(&pRptControl->optFields, TAG_OptFields);
					GetSclAttribs(attrs);
					pRptControl->optFields.lineNo = m_locator->getLineNumber();
				}
				else if(!m_pParInd->CmpPartPath(6, _ReportControl, 1) && !strcmp(element, "RptEnabled"))
				{
					CRptControl *pRptControl = (CRptControl*) m_pParInd->GetCurElement();
					m_pParInd->Push(&pRptControl->rptEnabled, TAG_RptEnabled);
					GetSclAttribs(attrs);
				}
				else if(!m_pParInd->CmpPartPath(6, _ReportControl_RptEnabled, 2) && !strcmp(element, "ClientLN"))
				{
					CRptEnabled * pRptEnabled = (CRptEnabled*) m_pParInd->GetCurElement();
					ClientLN *pClientLN = (ClientLN*) sclMem.AllocMem(sizeof(ClientLN));
					pClientLN->initClientLN();
					pRptEnabled->listClientLNs.push_back(pClientLN);
					m_pParInd->Push(pClientLN, TAG_ClientLN);
					GetSclAttribs(attrs);
					pClientLN->lineNo = m_locator->getLineNumber();
				}
				else if(!strcmp(element, "LogControl"))
				{
					CAnyLN * pLn = (CAnyLN*) m_pParInd->GetCurElement();
					CLogControl *pLogControl = new CLogControl;
					pLn->listLogControl.push_back(pLogControl);
					m_pParInd->Push(pLogControl, TAG_LogControl);
					GetSclAttribs(attrs);
					pLogControl->lineNo = m_locator->getLineNumber();
				}
				else if(!m_pParInd->CmpPartPath(6, _LogControl, 1) && !strcmp(element, "TrgOps"))
				{
					CLogControl *pLogControl = (CLogControl*) m_pParInd->GetCurElement();
					m_pParInd->Push(&pLogControl->trgOps, TAG_TrgOps);
					GetSclAttribs(attrs);
					pLogControl->trgOps.lineNo = m_locator->getLineNumber();
				}
				else if(!strcmp(element, "DOI"))
				{
					CAnyLN * pLn = (CAnyLN*) m_pParInd->GetCurElement();
					CDOI *pDoi = new CDOI;
					pLn->listDOI.push_back(pDoi);
					m_pParInd->Push(pDoi, TAG_DOI);
					GetSclAttribs(attrs);
					pDoi->lineNo = m_locator->getLineNumber();
				}
				else if(!m_pParInd->CmpPartPath(6, _DOI, 1) && !strcmp(element, "SDI"))
				{
					CDOI *pDoi = (CDOI*) m_pParInd->GetCurElement();
					CSDI *pSdi = new CSDI;
					pDoi->listSDI.push_back(pSdi);
					m_pParInd->Push(pSdi, TAG_SDI);
					GetSclAttribs(attrs);
					pSdi->lineNo = m_locator->getLineNumber();
				}
				else if(!m_pParInd->CmpPartPath(6, _DOI, 1) && !strcmp(element, "DAI"))
				{
					CDOI *pDoi = (CDOI*) m_pParInd->GetCurElement();
					CDAI *pDai = new CDAI;
					pDoi->listDAI.push_back(pDai);
					m_pParInd->Push(pDai, TAG_DAI);
					GetSclAttribs(attrs);
					pDai->lineNo = m_locator->getLineNumber();
				}
				else if(!m_pParInd->CmpPathR(_DAI, 1) && !strcmp(element, "Val"))
				{
					CDAI *pDai = (CDAI*) m_pParInd->GetCurElement();
					ValType *pVal = (ValType*) sclMem.AllocMem(sizeof(ValType));
					pVal->initValType();
					pDai->listVals.push_back(pVal);
					m_pParInd->Push(pVal, TAG_Val);
					pVal->lineNo = m_locator->getLineNumber();
				}
				else if(!m_pParInd->CmpPathR(_SDI, 1) && !strcmp(element, "SDI"))
				{
					CSDI *pSdi = (CSDI*) m_pParInd->GetCurElement();
					CSDI *pChild = new CSDI;
					pSdi->listSDI.push_back(pChild);
					m_pParInd->Push(pChild, TAG_SDI);
					GetSclAttribs(attrs);
					pChild->lineNo = m_locator->getLineNumber();
				}
				else if(!m_pParInd->CmpPathR(_SDI, 1) && !strcmp(element, "DAI"))
				{
					CSDI *pSdi = (CSDI*) m_pParInd->GetCurElement();
					CDAI *pDai = new CDAI;
					pSdi->listDAI.push_back(pDai);
					m_pParInd->Push(pDai, TAG_DAI);
					GetSclAttribs(attrs);
					pDai->lineNo = m_locator->getLineNumber();
				}
				else if(!strcmp(element, "Inputs"))
				{
					CAnyLN *pLn = (CAnyLN*) m_pParInd->GetCurElement();
					if(pLn->inputs == NULL)
						pLn->inputs = new CInputs;
					m_pParInd->Push(pLn->inputs, TAG_Inputs);
					GetSclAttribs(attrs);
					pLn->inputs->lineNo = m_locator->getLineNumber();
				}
				else if(!m_pParInd->CmpPartPath(6, _Inputs, 1) && !strcmp(element, "ExtRef"))
				{
					CInputs *pInputs= (CInputs*) m_pParInd->GetCurElement();
					ExtRef *pExtRef = (ExtRef*) sclMem.AllocMem(sizeof(ExtRef));
					pExtRef->initExtRef();
					pInputs->listExtRef.push_back(pExtRef);
					m_pParInd->Push(pExtRef, TAG_ExtRef);
					GetSclAttribs(attrs);
					pExtRef->lineNo = m_locator->getLineNumber();
				}
				else
					m_pParInd->Push(NULL, TAG_NULL);
			}
			else if(!m_pParInd->CmpPartPath(3, _Server, 1 ) && !strcmp(element, "Association"))
			{
				CServer *pSvr = (CServer*) m_pParInd->GetCurElement();
				Association *pAssoc = (Association*) sclMem.AllocMem(sizeof(Association));
				pAssoc->initAssociation();
				pSvr->listAssociations.push_back(pAssoc);
				m_pParInd->Push(pAssoc, TAG_Association);
				GetSclAttribs(attrs);
				pAssoc->lineNo = m_locator->getLineNumber();
			}
			else
				m_pParInd->Push(NULL, TAG_NULL);
		}
		else
			m_pParInd->Push(NULL, TAG_NULL);
	}
	else if(!m_pParInd->CmpPath(SCL_, 1) && !strcmp(element, "DataTypeTemplates"))
	{
		m_pParInd->Push(&m_pScl->dataTypeTemplate, TAG_DataTypeTemplates);
	}
	else if(!m_pParInd->CmpPath(SCL_DataTypeTemplates, 2))
	{
		if (!strcmp(element, "LNodeType"))
		{
			CDataTypeTemplate * pTemplate = (CDataTypeTemplate*) m_pParInd->GetCurElement();
			CLNodeType * pLnType = new CLNodeType;
			pTemplate->listLnTypes.push_back(pLnType);
			m_pParInd->Push(pLnType, TAG_LNodeType);
			GetSclAttribs(attrs);
			pLnType->lineNo = m_locator->getLineNumber();
		}
		else if(!m_pParInd->CmpPartPath(2, _LNodeType, 1) && !strcmp(element, "DO"))
		{
			CLNodeType * pLnType = (CLNodeType*) m_pParInd->GetCurElement();
			DO *pDo = (DO*) sclMem.AllocMem(sizeof(DO));
			pDo->initDO();
			pLnType->listDOs.push_back(pDo);
			m_pParInd->Push(pDo, TAG_DO);
			GetSclAttribs(attrs);
			pDo->lineNo = m_locator->getLineNumber();
			if(pDo->m_nExistType == FLAG_EXIST_M){
				if(!pLnType->hasC){
					pLnType->hasC = true;
				}
			}
		}
		else if(!strcmp(element, "DOType"))
		{
			CDataTypeTemplate * pTemplate = (CDataTypeTemplate*) m_pParInd->GetCurElement();
			CDOType *pDoType = new CDOType;
			pTemplate->listDOTypes.push_back(pDoType);
			m_pParInd->Push(pDoType, TAG_DOType);
			GetSclAttribs(attrs);
			pDoType->lineNo = m_locator->getLineNumber();
		}
		else if(!m_pParInd->CmpPartPath(2, _DOType, 1) && !strcmp(element, "SDO"))
		{
			CDOType *pDoType = (CDOType*) m_pParInd->GetCurElement();
			SDO *pSdo = (SDO*) sclMem.AllocMem(sizeof(SDO));
			pSdo->initSDO();
			pDoType->listSDOs.push_back(pSdo);
			m_pParInd->Push(pSdo, TAG_SDO);
			GetSclAttribs(attrs);
			pSdo->lineNo = m_locator->getLineNumber();
		}
		else if(!m_pParInd->CmpPartPath(2, _DOType, 1) && !strcmp(element, "DA"))
		{
			CDOType *pDoType = (CDOType*) m_pParInd->GetCurElement();
			CDA *pDa = new CDA;
			pDoType->listDAs.push_back(pDa);
			m_pParInd->Push(pDa, TAG_DA);
			GetSclAttribs(attrs);
			pDa->lineNo = m_locator->getLineNumber();
			if(strncmp(pDa->name,"dataNs",strlen(pDa->name)) == 0)
			{
				pDoType->bStandardNameSpace = false;
			}
		}
		else if(!m_pParInd->CmpPathR(_DA, 1) && !strcmp(element, "Val"))
		{
			CDA *pDa = (CDA*) m_pParInd->GetCurElement();
			ValType *pVal = (ValType*) sclMem.AllocMem(sizeof(ValType));
			pVal->initValType();
			pDa->listVals.push_back(pVal);
			m_pParInd->Push(pVal, TAG_Val);
			GetSclAttribs(attrs);
			pVal->lineNo = m_locator->getLineNumber();
		}
		else if(!strcmp(element, "DAType"))
		{
			CDataTypeTemplate * pTemplate = (CDataTypeTemplate*) m_pParInd->GetCurElement();
			CDAType *pDaType = new CDAType;
			pTemplate->listDATypes.push_back(pDaType);
			m_pParInd->Push(pDaType, TAG_DAType);
			GetSclAttribs(attrs);
			pDaType->lineNo = m_locator->getLineNumber();
		}
		else if(!m_pParInd->CmpPartPath(2, _DAType, 1) && !strcmp(element, "BDA"))
		{
			CDAType *pDaType = (CDAType*) m_pParInd->GetCurElement();
			CBDA *pBda = new CBDA;
			pDaType->listBDAs.push_back(pBda);
			m_pParInd->Push(pBda, TAG_BDA);
			GetSclAttribs(attrs);
			pBda->lineNo = m_locator->getLineNumber();
		}
		else if(!m_pParInd->CmpPartPath(2, _DAType_BDA, 2) && !strcmp(element, "Val"))
		{
			CBDA *pBda = (CBDA*) m_pParInd->GetCurElement();
			ValType *pVal = (ValType*) sclMem.AllocMem(sizeof(ValType));
			pVal->initValType();
			pBda->listVals.push_back(pVal);
			m_pParInd->Push(pVal, TAG_Val);
			GetSclAttribs(attrs);
			pVal->lineNo = m_locator->getLineNumber();
		}
		else if(!strcmp(element, "EnumType"))
		{
			CDataTypeTemplate * pTemplate = (CDataTypeTemplate*) m_pParInd->GetCurElement();
			CEnumType *pEnumType = new CEnumType;
			pTemplate->listEnumTypes.push_back(pEnumType);
			m_pParInd->Push(pEnumType, TAG_EnumType);
			GetSclAttribs(attrs);
			//printf("EnumVal %s\n",pEnumType->id);
			pEnumType->lineNo = m_locator->getLineNumber();
		}
		else if(!m_pParInd->CmpPartPath(2, _EnumType, 1) && !strcmp(element, "EnumVal"))
		//else if(!strcmp(element,"EnumVal"))
		{
			//printf("EnumVal=%s\n",element);
			CEnumType *pEnumType = (CEnumType*) m_pParInd->GetCurElement();
			EnumVal *pEnumVal = (EnumVal*) sclMem.AllocMem(sizeof(EnumVal));
			pEnumVal->initEnumVal();
			pEnumType->listEnumVals.push_back(pEnumVal);
			m_pParInd->Push(pEnumVal, TAG_EnumVal);
			GetSclAttribs(attrs);
			//printf("order=%d lineNo =%d content=%s\n",pEnumVal->ord,pEnumVal->lineNo,pEnumVal->content);

			pEnumVal->lineNo = m_locator->getLineNumber();
		}
		else
			m_pParInd->Push(NULL, TAG_NULL);
	}	
	else{
		m_pParInd->Push(NULL, TAG_NULL);
	}

    XMLString::release(&element);
}


void SclSAX2Handler::characters(const     XMLCh* const    chars
                                  , const   XMLSize_t    length)
{
    char* text = XMLString::transcode(chars);
	DeleteUnvisibleChar(text);
    //cout << "I saw element: "<< text << endl;

	if(strlen(text) == 0)
	{
		XMLString::release(&text);
		return;
	}
	

	m_strList.push_back((string)text);

	//if (!m_pParInd->CmpPartPath(2, _SubNetwork_BitRate, 2))
	//{
	//	CSubNetwork *pSubNet = (CSubNetwork*) m_pParInd->GetElementByOffset(-1);
	//	pSubNet->bitRate = atoi(text);
	//}
	//else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP_Address_P, 4))
	//{
	//	Address *pAddress = (Address*) m_pParInd->GetElementByOffset(-1);

	//	if (!strcmp(curPType, "IP"))
	//		pAddress->ip = sclMem.AllocAndCopy(text);
	//	else if(!strcmp(curPType, "IP-SUBNET"))
	//		pAddress->ip_subnet = sclMem.AllocAndCopy(text);
	//	else if(!strcmp(curPType, "IP-GATEWAY"))
	//		pAddress->ip_gateway = sclMem.AllocAndCopy(text);
	//	else if(!strcmp(curPType, "OSI-NSAP"))
	//		pAddress->osi_nsap = sclMem.AllocAndCopy(text);
	//	else if(!strcmp(curPType, "OSI-TSEL"))
	//		pAddress->osi_tsel = sclMem.AllocAndCopy(text);
	//	else if(!strcmp(curPType, "OSI-SSEL"))
	//		pAddress->osi_ssel = sclMem.AllocAndCopy(text);
	//	else if(!strcmp(curPType, "OSI-PSEL"))
	//		pAddress->osi_psel = sclMem.AllocAndCopy(text);
	//	else if(!strcmp(curPType, "OSI-AP-Title"))
	//		pAddress->osi_ap_title = sclMem.AllocAndCopy(text);
	//	else if(!strcmp(curPType, "OSI-AP-Invoke"))
	//		pAddress->osi_ap_invoke = sclMem.AllocAndCopy(text);
	//	else if(!strcmp(curPType, "OSI-AE-Qualifier"))
	//		pAddress->osi_ae_qualifier = sclMem.AllocAndCopy(text);
	//	else if(!strcmp(curPType, "OSI-AE-Invoke"))
	//		pAddress->osi_ae_invoke = sclMem.AllocAndCopy(text);

	//	if(curPType)
	//		XMLString::release(&curPType);
	//}
	//else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP_GSE_Address_P, 5)
	//	|| !m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP_SMV_Address_P, 5))
	//{
	//	Address *pAddress = (Address*) m_pParInd->GetElementByOffset(-1);
	//	
	//	if (!strcmp(curPType, "VLAN-ID"))
	//		pAddress->vlan_id = sclMem.AllocAndCopy(text);
	//	else if (!strcmp(curPType, "VLAN-PRIORITY"))
	//		pAddress->vlan_priority = sclMem.AllocAndCopy(text);
	//	else if(!strcmp(curPType, "MAC-Address"))
	//		pAddress->mac_address = sclMem.AllocAndCopy(text);
	//	else if(!strcmp(curPType, "APPID"))
	//		pAddress->appid = sclMem.AllocAndCopy(text);

	//	if(curPType)
	//		XMLString::release(&curPType);
	//}
	//else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP_GSE_MinTime, 4))
	//{
	//	GSE * pGSE = (GSE*) m_pParInd->GetElementByOffset(-1);
	//	pGSE->minTime = atoi(text);
	//}
	//else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP_GSE_MaxTime, 4))
	//{
	//	GSE * pGSE = (GSE*) m_pParInd->GetElementByOffset(-1);
	//	pGSE->maxTime = atoi(text);
	//}
	//else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP_PhysConn_P, 4))
	//{
	//	PhysConn * pPhysConn = (PhysConn*) m_pParInd->GetElementByOffset(-1);

	//	if (!strcmp(curPType, "Type"))
	//		pPhysConn->p_type = sclMem.AllocAndCopy(text);
	//	else if (!strcmp(curPType, "Plug"))
	//		pPhysConn->p_plug = sclMem.AllocAndCopy(text);
	//	else if (!strcmp(curPType, "Cable"))
	//		pPhysConn->p_cable = sclMem.AllocAndCopy(text);
	//	else if (!strcmp(curPType, "Port"))
	//		pPhysConn->p_port = sclMem.AllocAndCopy(text);
	//}
	//else if(!m_pParInd->CmpPartPath(6, _GSEControl_IEDName, 2))
	//{
	//	CGSEControl *pGSEControl = (CGSEControl*) m_pParInd->GetElementByOffset(-1);
	//	char * name = sclMem.AllocAndCopy(text);
	//	pGSEControl->listIedNames.push_back(name);
	//}
	//else if(!m_pParInd->CmpPartPath(6, _SampledValueControl_IEDName, 2))
	//{
	//	CSMVControl *pSmvControl = (CSMVControl*) m_pParInd->GetElementByOffset(-1);
	//	char * name = sclMem.AllocAndCopy(text);
	//	pSmvControl->listIedNames.push_back(name);
	//}
	//else if(!m_pParInd->CmpPathR(_Val, 1))
	//{
	//	ValType *pVal = (ValType*) m_pParInd->GetCurElement();
	//	pVal->val =	sclMem.AllocAndCopy(text);
	//}
	//else if(!m_pParInd->CmpPathR(_EnumVal, 1))
	//{
	//	EnumVal *pEnumVal = (EnumVal*) m_pParInd->GetCurElement();
	//	pEnumVal->content = sclMem.AllocAndCopy(text);
	//}

	XMLString::release(&text);
	//printf("startElement end\n");
}

void SclSAX2Handler::endElement(
		const XMLCh* const uri,
		const XMLCh* const localname,
		const XMLCh* const qname)
{
//	printf("endElement start\n");
	if(m_strList.size()>0){
		std::list<string>::iterator Iter;
		string textStr = "";
		for(Iter = m_strList.begin();Iter != m_strList.end();Iter++)
		{
			string str = *Iter;
			if(str.length()==0){
				continue;
			}
			textStr += str;;
		}
		if(textStr.length()>0){
			char* text = (char*)(textStr.c_str());
			//printf("text is %s\n",text);
			if (!m_pParInd->CmpPartPath(2, _SubNetwork_BitRate, 2))
			{
				//printf("_SubNetwork_BitRate\n");
				CSubNetwork *pSubNet = (CSubNetwork*) m_pParInd->GetElementByOffset(-1);
				pSubNet->bitRate = atoi(text);
			}
			else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP_Address_P, 4))
			{
				//printf("2,_SubNetwork_ConnectedAP_Address\n");
				Address *pAddress = (Address*) m_pParInd->GetElementByOffset(-1);

				if (!strcmp(curPType, "IP"))
					pAddress->ip = sclMem.AllocAndCopy(text);
				else if(!strcmp(curPType, "IP-SUBNET"))
					pAddress->ip_subnet = sclMem.AllocAndCopy(text);
				else if(!strcmp(curPType, "IP-GATEWAY"))
					pAddress->ip_gateway = sclMem.AllocAndCopy(text);
				else if(!strcmp(curPType, "OSI-NSAP"))
					pAddress->osi_nsap = sclMem.AllocAndCopy(text);
				else if(!strcmp(curPType, "OSI-TSEL"))
					pAddress->osi_tsel = sclMem.AllocAndCopy(text);
				else if(!strcmp(curPType, "OSI-SSEL"))
					pAddress->osi_ssel = sclMem.AllocAndCopy(text);
				else if(!strcmp(curPType, "OSI-PSEL"))
					pAddress->osi_psel = sclMem.AllocAndCopy(text);
				else if(!strcmp(curPType, "OSI-AP-Title"))
					pAddress->osi_ap_title = sclMem.AllocAndCopy(text);
				else if(!strcmp(curPType, "OSI-AP-Invoke"))
					pAddress->osi_ap_invoke = sclMem.AllocAndCopy(text);
				else if(!strcmp(curPType, "OSI-AE-Qualifier"))
					pAddress->osi_ae_qualifier = sclMem.AllocAndCopy(text);
				else if(!strcmp(curPType, "OSI-AE-Invoke"))
					pAddress->osi_ae_invoke = sclMem.AllocAndCopy(text);

				if(curPType)
					XMLString::release(&curPType);
			}
			else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP_GSE_Address_P, 5)
				|| !m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP_SMV_Address_P, 5))
			{
				//printf("!!!!!!!!!!!!!!!!\n");
				Address *pAddress = (Address*) m_pParInd->GetElementByOffset(-1);

				if (!strcmp(curPType, "VLAN-ID"))
					pAddress->vlan_id = sclMem.AllocAndCopy(text);
				else if (!strcmp(curPType, "VLAN-PRIORITY"))
					pAddress->vlan_priority = sclMem.AllocAndCopy(text);
				else if(!strcmp(curPType, "MAC-Address"))
					pAddress->mac_address = sclMem.AllocAndCopy(text);
				else if(!strcmp(curPType, "APPID"))
					pAddress->appid = sclMem.AllocAndCopy(text);

				if(curPType)
					XMLString::release(&curPType);
			}
			else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP_GSE_MinTime, 4))
			{
				//printf("~~~~~~~~~~~~~~~~~~~~\n");
				GSE * pGSE = (GSE*) m_pParInd->GetElementByOffset(-1);
				pGSE->minTime = atoi(text);
			}
			else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP_GSE_MaxTime, 4))
			{
				//printf("1\n");
				GSE * pGSE = (GSE*) m_pParInd->GetElementByOffset(-1);
				pGSE->maxTime = atoi(text);
			}
			else if(!m_pParInd->CmpPartPath(2, _SubNetwork_ConnectedAP_PhysConn_P, 4))
			{
				//printf("2\n");
				PhysConn * pPhysConn = (PhysConn*) m_pParInd->GetElementByOffset(-1);

				if (!strcmp(curPType, "Type"))
					pPhysConn->p_type = sclMem.AllocAndCopy(text);
				else if (!strcmp(curPType, "Plug"))
					pPhysConn->p_plug = sclMem.AllocAndCopy(text);
				else if (!strcmp(curPType, "Cable"))
					pPhysConn->p_cable = sclMem.AllocAndCopy(text);
				else if (!strcmp(curPType, "Port"))
					pPhysConn->p_port = sclMem.AllocAndCopy(text);
			}
			else if(!m_pParInd->CmpPartPath(6, _GSEControl_IEDName, 2))
			{
				//printf("_GSEControl_IEDName\n");
				CGSEControl *pGSEControl = (CGSEControl*) m_pParInd->GetElementByOffset(-1);
				char * name = sclMem.AllocAndCopy(text);
				pGSEControl->listIedNames.push_back(name);
			}
			else if(!m_pParInd->CmpPartPath(6, _SampledValueControl_IEDName, 2))
			{
				//printf("_SampledValueControl_IEDName\n");
				CSMVControl *pSmvControl = (CSMVControl*) m_pParInd->GetElementByOffset(-1);
				char * name = sclMem.AllocAndCopy(text);
				pSmvControl->listIedNames.push_back(name);
			}
			else if(!m_pParInd->CmpPathR(_Val, 1))
			{
				//printf("_Val\n");
				ValType *pVal = (ValType*) m_pParInd->GetCurElement();
				pVal->val =	sclMem.AllocAndCopy(text);
			}
			else if(!m_pParInd->CmpPathR(_EnumVal, 1))
			{
				//printf("_EnumVal\n");
				EnumVal *pEnumVal = (EnumVal*) m_pParInd->GetCurElement();
				if(pEnumVal)
				pEnumVal->content = sclMem.AllocAndCopy(text);
			}
			else
                        {
                               //printf("else\n");
                        }       
		}
	}	
	m_pParInd->Pop();
	m_preTag = "";
	//printf("endElement end\n");
}

void SclSAX2Handler::setDocumentLocator(const Locator* const locator)
{
	m_locator = locator;
}

void SclSAX2Handler::fatalError(const SAXParseException& exception)
{
    char* message = XMLString::transcode(exception.getMessage());
    cout << "Fatal Error: " << message
  //       << " at line: " << exception.getLineNumber()
         << endl;
    XMLString::release(&message);
}



