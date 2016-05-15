//#include "testsclparser.h"
//#include <QtGui/QApplication>

#include "scl.h"
#include "SclSAX2Handler.hpp"
#include "xercesc/sax2/SAX2XMLReader.hpp"
#include "xercesc/sax2/XMLReaderFactory.hpp"
#include "xercesc/framework/XMLGrammarPoolImpl.hpp"
#include <time.h>
int main(int argc, char *argv[])
{
//	QApplication a(argc, argv);
// 	testSclParser w;
// 	w.show();
	int seconds = time((time_t*)NULL);
	CScl* pScl= new CScl;
	XMLPlatformUtils::Initialize();
	MemoryManager*       fgMemoryManager = XMLPlatformUtils::fgMemoryManager;
	//XMLGrammarPool* pGrammarPool  = new XMLGrammarPoolImpl(XMLPlatformUtils::fgMemoryManager);
	SAX2XMLReader* parser = XMLReaderFactory::createXMLReader(XMLPlatformUtils::fgMemoryManager);
	SclSAX2Handler*myContentHandler = new SclSAX2Handler(pScl,1);		
	parser->setContentHandler((SclSAX2Handler*)myContentHandler);
	///m_pSclFacty->LoadSclFile();
	parser->parse("yab.scd");//½âÎöxmlÎÄ¼þ	

	int seconds2 = time((time_t*)NULL);

	int SpendTime = seconds2-seconds;

	printf("Reading SCD...%d have elapsed",SpendTime);
	char* strIP = pScl->GetIEDIP("CL1101A","MMS_A");
	char* strManufacture = pScl->GetManufacturer("CL1101A");
	
	printf("CL1101A ip = %s\n",strIP);
	printf("CL1101A manufacture = %s\n",strManufacture);
	return 0;
//	return a.exec();
}
