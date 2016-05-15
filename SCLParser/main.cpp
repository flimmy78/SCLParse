//#include "StdAfx.h"
#include "scl.h"
#include "SclSAX2Handler.hpp"
#include "xercesc/sax2/SAX2XMLReader.hpp"
#include "xercesc/sax2/XMLReaderFactory.hpp"
#include "xercesc/framework/XMLGrammarPoolImpl.hpp"
#include <time.h>
int main(int argc, char *argv[])
{
	int seconds = time((time_t*)NULL);
	CScl* pScl= new CScl;
	XMLPlatformUtils::Initialize();
	printf("after initial\n");
	MemoryManager*       fgMemoryManager = XMLPlatformUtils::fgMemoryManager;
	//XMLGrammarPool* pGrammarPool  = new XMLGrammarPoolImpl(XMLPlatformUtils::fgMemoryManager);
	SAX2XMLReader* parser = XMLReaderFactory::createXMLReader(XMLPlatformUtils::fgMemoryManager);
	SclSAX2Handler*myContentHandler = new SclSAX2Handler(pScl,1);		
	parser->setContentHandler((SclSAX2Handler*)myContentHandler);
	///m_pSclFacty->LoadSclFile();
	printf("before parse\n");
	parser->parse("yab.scd");//解析xml文件	
	printf("after parse\n");
	int seconds2 = time((time_t*)NULL);
	
	int SpendTime = seconds2-seconds;

	printf("Reading SCD...%d have elapsed",SpendTime);
	char* strIP = pScl->GetIEDIP("CL1101A","MMS_A");
	char* strManufacture = pScl->GetManufacturer("CL1101A");
	
	printf("strIP is %s\n",strIP);
	printf("strManufature is %s\n",strManufacture);
	
	return 0;
}
