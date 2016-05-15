#ifndef _MYSAX2HANDER_HPP_
#define _MYSAX2HANDER_HPP_
#include "scl.h"
#include "LibSCLParser.h"
#include <xercesc/sax/Locator.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include  <xercesc/sax/SAXParseException.hpp>
#include <xercesc/util/regx/RegularExpression.hpp>

#include <iostream>
using namespace std;
using namespace xercesc;


typedef enum{
	TAG_NULL=0, TAG_SCL=1,  
	TAG_PRIVATE,TAG_NARI_VOL,TAG_NARI_BAY,TAG_NARI_IED,
	TAG_Header, TAG_History, TAG_Hitem,
	TAG_Substation, TAG_VoltageLevel, TAG_Function,
	TAG_Bay, TAG_ConductingEquipment, TAG_ConnectivityNode, TAG_Terminal, TAG_SubEquipment,
	TAG_GeneralEquipment, TAG_PowerTransformer, TAG_LNode,
	TAG_TransformerWinding, TAG_TapChanger,
	TAG_SubFunction,
	TAG_Communication, TAG_SubNetwork, TAG_ConnectedAP,
	TAG_Address, TAG_P, TAG_GSE, TAG_MinTime, TAG_MaxTime,
	TAG_SMV, TAG_PhysConn, TAG_BitRate,
	TAG_IED, TAG_Service, TAG_AccessPoint,
	TAG_DynAssociation, TAG_SettingGroups, TAG_SGEdit, TAG_ConfSG,
	TAG_GetDirectory, TAG_GetDataObjectDefinition, TAG_DataObjectDirectory,
	TAG_GetDataSetValue, TAG_SetDataSetValue, TAG_DataSetDirectory,
	TAG_ConfDataSet, TAG_DynDataSet, TAG_ReadWrite, TAG_TimerActivatedControl,
	TAG_ConfReportControl, TAG_GetCBValues, TAG_ConfLogControl,
	TAG_ReportSettings, TAG_LogSettings, TAG_GSESettings, TAG_SMVSettings, TAG_SmpRate,
	TAG_GSEDir, TAG_GOOSE, TAG_GSSE, TAG_FileHandling, TAG_ConfLNs,
	TAG_Server, TAG_Authentication, TAG_LDevice, TAG_Association,
	TAG_LN0, TAG_LN, TAG_AccessControl,
	TAG_DataSet, TAG_FCDA, TAG_ReportControl, TAG_TrgOps, TAG_OptFields,
	TAG_RptEnabled, TAG_ClientLN,
	TAG_LogControl, TAG_DOI, TAG_SDI, TAG_DAI, TAG_Val,
	TAG_Inputs, TAG_ExtRef,
	TAG_GSEControl, TAG_SampledValueControl, TAG_SettingControl,
	TAG_SCLControl, TAG_Log, TAG_IEDName, TAG_SmvOpts,
	TAG_DataTypeTemplates, TAG_LNodeType, TAG_DOType, TAG_DAType, TAG_EnumType,
	TAG_DO, TAG_SDO, TAG_DA, TAG_BDA, TAG_EnumVal,TAG_ClientServices,
}SCL_TAG;

class SCL_API CParserInd
{
public:
	CParserInd(){
		ind = 0xffffffff;
		memset(elemType, 0, 32*sizeof(SCL_TAG));
		memset(pElement, 0, 32*sizeof(void*));
	}
	~CParserInd(){}
	void Push(void* pEle, SCL_TAG tag);
	void * Pop();
	int CmpPath(const SCL_TAG* path, unsigned int level);
	int CmpPartPath(int begin, const SCL_TAG* path, unsigned int level);  //begin: from 0
	int CmpPathR(const SCL_TAG* path, unsigned int level);
	void * GetCurElement(){return pElement[ind];}
	void * GetElementByOffset(int off){return pElement[ind+off];}
	unsigned int GetLevel(){return ind + 1;}

public:
	void * pElement[32];
	SCL_TAG elemType[32];
	int ind;
};


class SCL_API SclSAX2Handler : public DefaultHandler
{
public:
	SclSAX2Handler(CScl *pScl,int parseType);
	~SclSAX2Handler();

    void startElement(
        const   XMLCh* const    uri,
        const   XMLCh* const    localname,
        const   XMLCh* const    qname,
        const   Attributes&     attrs
    );

	void endElement(
		const XMLCh* const uri,
		const XMLCh* const localname,
		const XMLCh* const qname
	);
	
	void characters(const XMLCh* const chars, const XMLSize_t length);
    void fatalError(const SAXParseException&);
	void setDocumentLocator(const Locator* const locator);

	char * GetAttribVal(const Attributes& attrs,char* attr_name);
	void GetAttribVals(const Attributes& attrs, char** names, char** vals, int num);
	void GetAttribValsWithMemAlloc(const Attributes& attrs, char** names, char*** ppVars, int num);
	void ReleaseXmlString(char** p, int num);
	void GetSclAttribs(const Attributes& attrs);


protected:
	const Locator* m_locator;
	CScl * m_pScl;
	CParserInd *m_pParInd;
	char * curPType;
	int m_parseType;
	bool m_hasCon;
	string m_preTag;
	std::list<string> m_strList;
};


#endif

