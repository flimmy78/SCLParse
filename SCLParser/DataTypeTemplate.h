#ifndef _DATATYPETEMPLATE_H_
#define _DATATYPETEMPLATE_H_


#include <list>
#include <memory.h> 
#include <string.h>
#include <stdio.h>


class CDAType;
class CDOType;

#define SMALL_STR_LEN 30
#define MIDDLE_STR_LEN 100
#define MAX_STR_LEN 256
#define LN_CLASS_LEN 5
//#define LN_CLASS_LEN 4
#define FC_LEN 2
#define IP_LEN 4
#define MAC_ADDR_LEN 6


//
/*BaseDaType 基本数据属性类型*/
#define  BDT_NULL			-1
#define  BDT_BOOLEAN		0	/*布尔值*/
#define  BDT_INT8			1	/*-128 ~ 127*/
#define  BDT_INT16			2	/*-32,768 ~ 32,767*/
#define  BDT_INT24			3	/*- 8388608 ~ 8388607  时标类型*/
#define  BDT_INT32			4	/*-2,147,483,648 ~ 2,147,483,647*/
#define  BDT_INT128			5	/*-2**127 ~ (2**127)-1  计数器所需要*/
#define  BDT_INT8U			6	/*无符号整数 0 ~ 255*/
#define  BDT_INT16U			7	/*无符号整数0 ~ 65,535*/
#define  BDT_INT24U			8	/*无符号整数0 ~ 16,777,215*/
#define  BDT_INT32U			9	/*无符号整数0 ~ 4,294,967,295*/
#define  BDT_FLOAT32		10	/*值域和精度为 IEEE754单精度浮点数	*/
#define  BDT_FLOAT64		11	/*值域和精度为 IEEE754双精度浮点数	*/
#define  BDT_ENUMERATED		12	/*值的有序集，采用类型的定义	允许用户扩展*/
#define  BDT_CODEDENUM		13	/*值的有序集，采用类型的定义,不允许用户扩展。类型映射到	*/
#define  BDT_OCTETSTRING	14	/*An element of type OCTET STRING can contain any string of bits. */
#define  BDT_VISIBLESTRING	15	/*An element of type VISIBLE STRING can contain ASCII characters. This set of characters does not include diacritic characters, special European characters, etc. */
#define  BDT_UNICODESTRING	16
#define  BDT_BITSTRING		17	/*位串*/
#define  BDT_VOID			20	/*无符号类型*/
#define  BDT_TimeStamp		21	/*时标*/
#define  BDT_ENTRYTIME		22	/*条目时间*/
#define  BDT_PACKEDLIST		23	/*压缩列表类型*/

#define BDT_BITSTRING2		24	/*2位位串*/
#define BDT_VISIBLESTRING32 25
#define BDT_VISIBLESTRING64 26
#define BDT_VISIBLESTRING255 27

typedef struct EnumVal
{
	int ord;
	char * content;
	unsigned int lineNo; 
	void initEnumVal(){
		ord = -1;
		content = "";
		lineNo = -1;
	}
};
typedef std::list<EnumVal*> ListOfEnumVal; 

class CEnumType 
{
public:
	CEnumType() : id(""),desc(""),bUsed(false),lineNo(-1),nCheckFlag(-1){}
	virtual ~CEnumType(){}

	char * id;
	char * desc;
	unsigned int lineNo;    //在原始SCl文件中的行号
	ListOfEnumVal listEnumVals;
	bool bUsed;				//用于校验，表示该EnumType被其他Da引用过
	int nCheckFlag;//用于校验，初始化为-1, 标准化校验通过为1，标准化校验不通过为0;
};
typedef std::list<CEnumType*> ListOfEnumType;

typedef struct ValType
{
	char * val;
	unsigned int sGroup;    //for setting, expresses setting group number
	unsigned int lineNo;
	void initValType(){
		val = "";
		sGroup = -1;
		lineNo = -1;
	}
};

typedef enum{
	Spec=3, Conf=2, RO=1, Set=0
}ValKindEnum;

class CBDA
{
public:
	CBDA() : desc(""),name(""),sAddr(""),type(""),bType(""),lineNo(-1),m_nStdNo(-1),m_nExistType(-1){
		count = 0;
		valKind = Set;
		pDAType = NULL;
		pEnumType = NULL;
	}
	virtual ~CBDA(){};

	char * desc;
	char * name;
	char * sAddr;
	char * type;
	char * bType;
	ValKindEnum valKind;
	unsigned int count;
	std::list<ValType*> listVals;
	unsigned int lineNo;      //在原始SCl文件中的行号
	CDAType * pDAType;
	CEnumType* pEnumType;   //用于建立EnumType的索引
	short m_nStdNo; //此Do在标准DoType中Do列表的序号
	short m_nExistType;	//存在强制性，0,1,2对应M,O,C
};
typedef std::list<CBDA*> ListOfBDA;

class CDAType
{
public:
	CDAType() : id(""),desc(""),iedType(""),bUsed(false),lineNo(-1){}
	virtual ~CDAType(){
		std::list<CBDA*>::iterator iter;
		iter = listBDAs.begin();
		for(; iter != listBDAs.end(); iter++)
			delete *iter;
	}

	char * id;
	char * desc;
	char * iedType;
	std::list<CBDA*> listBDAs;
	unsigned int lineNo;//在原始SCl文件中的行号
	bool bUsed;     //用于校验，表示该DAType被其他Do引用过
};
typedef std::list<CDAType*> ListOfDAType;


class CDA
{
public:
	CDA() : desc(""),name(""),sAddr(""),type(""),bType(""),lineNo(-1),m_nExistType(-1),m_nStdNo(-1){
		count = 0;
		valKind = Set;
		dchg = qchg = dupd = false;
		pDAType = NULL;
		pEnumType = NULL;
		strcpy(fc,"");
	}
	virtual ~CDA(){}

	char * desc;
	char * name;
	char * sAddr;
	char * type;
	char * bType;
	ValKindEnum valKind;
	unsigned int count;
	char fc[4];
	bool dchg;
	bool qchg;
	bool dupd;
	std::list<ValType*> listVals;
	unsigned int lineNo;      //在原始SCl文件中的行号
	CDAType * pDAType;         //用于建立datype索引
	CEnumType* pEnumType;      //用于建立EnumType的索引
	short m_nExistType;
	short m_nStdNo; //此Da在标准DaType中Da列表的序号
};
typedef std::list<CDA*> ListOfDa; 


typedef struct SDO
{
	char * desc;
	char * name;
	char * type;
	unsigned int lineNo;
	CDOType * pDOType;
	short m_nExistType;
	short m_nStdNo; //此sDo在标准LnType中Do列表的序号
	void initSDO(){
		desc = "";
		name = "";
		type = "";
		lineNo = -1;
		pDOType = NULL;
		m_nExistType = -1;
		m_nStdNo = -1;
	}
};

class CDOType
{
public:
	CDOType() : desc(""),id(""),cdc(""),iedType(""),bUsed(false),bStandardNameSpace(true),lineNo(-1),bCdcChecked(false){}
	virtual ~CDOType(){
		std::list<CDA*>::iterator iter = listDAs.begin();
		for(; iter != listDAs.end(); iter++)
			delete *iter;
	}

	char * desc;
	char * id;
	char * cdc;
	char * iedType;
	unsigned int lineNo;  //在原始SCl文件中的行号	
	std::list<SDO*> listSDOs;
	std::list<CDA*> listDAs;
	bool bUsed;           //用于校验，表示该DOType被其他Ln引用过
	bool bStandardNameSpace;
	bool bCdcChecked; //cdc是否已经检查过
};
typedef std::list<CDOType*> ListOfDOType;

typedef struct DO
{
	DO() : desc(""),name(""),type(""),accessControl(""),transient(false),m_nExistType(-1),lineNo(-1),pDOType(0),m_nStdNo(-1){}
	char * desc;
	char * name;
	char * type;
	char * accessControl;
	bool transient;
	short m_nExistType;
	unsigned int lineNo;    //此do在原始SCl文件中的行号
	CDOType* pDOType;        //用于建立dotype索引
	int m_nStdNo;
	void initDO(){
		desc = "";
		name = "";
		type = "";
		accessControl = "";
		transient = false;
		m_nExistType = -1;
		lineNo = 0;    //此do在原始SCl文件中的行号
		pDOType = NULL;        //用于建立dotype索引
		m_nStdNo = -1;
	}
};
typedef std::list<DO*> ListOfDo; 

class CLNodeType
{
public:
	CLNodeType() : desc(""),id(""),lnClass(""),iedType(""),bUsed(false),lineNo(-1),pSgccLN(NULL),pIecLN(NULL),hasC(false){}
	virtual ~CLNodeType(){}

	char * desc;
	char * id;
	char * lnClass;
	char * iedType;
	std::list<DO*> listDOs;
	unsigned int lineNo;   //在原始SCl文件中的行号
	bool bUsed;            //用于校验，表示该LnType被其他实例引用过
	CLNodeType* pSgccLN;
	CLNodeType* pIecLN;
	bool hasC;
};
typedef std::list<CLNodeType*> ListOfLNodeType; 

class CDictElement
{
public:
	char Key;
	ListOfDo list_Do;
};
typedef std::list<CDictElement*> ListofDictElement; 

//do字典，对应于IEC61850-7-3 A6
class CDoDict
{
public:
	char m_NameSpace[256];
	ListofDictElement ListElement;
};

typedef std::list<CDoDict*> ListofDoDict; 

class CDataTypeTemplate
{
public:
	CDataTypeTemplate(){}
	virtual ~CDataTypeTemplate();

	ListOfLNodeType listLnTypes;
	ListOfDOType listDOTypes;
	ListOfDAType listDATypes;
	ListOfEnumType listEnumTypes;
};

inline CDataTypeTemplate::~CDataTypeTemplate()
{
	ListOfLNodeType::iterator lnIter = listLnTypes.begin();
	for(; lnIter != listLnTypes.end(); lnIter++)
		delete *lnIter;

	ListOfDOType::iterator doIter = listDOTypes.begin();
	for(; doIter != listDOTypes.end(); doIter++)
		delete *doIter;

	ListOfDAType::iterator daIter = listDATypes.begin();
	for(; daIter != listDATypes.end(); daIter++)
		delete *daIter;

	ListOfEnumType::iterator enumIter = listEnumTypes.begin();
	for(; enumIter != listEnumTypes.end(); enumIter++)
		delete *enumIter;
}

#endif