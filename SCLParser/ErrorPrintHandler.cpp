// ErrorPrintHandler.cpp: implementation of the CErrorPrintHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ErrorPrintHandler.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CErrorPrintHandler::CErrorPrintHandler():fSawErrors(false)
{
	m_pScl = NULL;
	m_fileType = 1;
}

CErrorPrintHandler::CErrorPrintHandler(CScl * pScl):fSawErrors(false)
{
	m_pScl = pScl;
	m_fileType = 1;
}

CErrorPrintHandler::CErrorPrintHandler(CLNInfo * pScl):fSawErrors(false)
{
	m_pLnInfo = pScl;
	m_fileType = 2;
}

CErrorPrintHandler::~CErrorPrintHandler()
{

}

// ---------------------------------------------------------------------------
//  SCMPrintHandler: Overrides of the SAX ErrorHandler interface
// ---------------------------------------------------------------------------
void CErrorPrintHandler::error(const SAXParseException& e) 
{
    fSawErrors = true;
	char info[256];

	if(m_fileType==1){
		if(!m_pScl)
			return;

		if(!(m_pScl->m_pCheckNotifier))
			return;

		sprintf(info,"**错误 : 第%d行,第%d列, %s\n",(int)e.getLineNumber(),(int)e.getColumnNumber(),StrX(e.getMessage()));
		if(m_pScl->m_pCheckNotifier){
			if(m_pScl->m_pCheckNotifier->m_bEnableErrorShow){
				m_pScl->m_pCheckNotifier->NotifyCheckInfo(info);			
			}
			m_pScl->m_pCheckNotifier->m_nErrorCount++;
			m_pScl->m_pCheckNotifier->m_nXsdChkErrCnt++;
		}
	}
	else{
		if(!m_pLnInfo)
			return;

		if(!(m_pLnInfo->m_pCheckNotifier))
			return;


		sprintf(info,"**错误 : 第%d行,第%d列, %s\n",(int)e.getLineNumber(),(int)e.getColumnNumber(),StrX(e.getMessage()));
		if(m_pLnInfo->m_pCheckNotifier){
			if(m_pLnInfo->m_pCheckNotifier->m_bEnableErrorShow){
				m_pLnInfo->m_pCheckNotifier->NotifyCheckInfo(info);			
			}
			m_pLnInfo->m_pCheckNotifier->m_nErrorCount++;
			m_pLnInfo->m_pCheckNotifier->m_nXsdChkErrCnt++;
		}
	}

//	sprintf(g_remind_info_line,"Error\t\t\t:row = %d,col = %d,message = %s\n",(int)e.getLineNumber(),(int)e.getColumnNumber(),StrX(e.getMessage()));
 //   fprintf(g_fpError,g_remind_info_line);
//	g_err_count++;

//	AfxMessageBox(str);
	XERCES_STD_QUALIFIER cerr << "\nError at file " << StrX(e.getSystemId())<< XERCES_STD_QUALIFIER endl;
//		 << ", line " << e.getLineNumber()
//		 << ", char " << e.getColumnNumber()
//         << "\n  Message: " << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl;
}

void CErrorPrintHandler::fatalError(const SAXParseException& e)
{
    fSawErrors = true;

	char info[256];
/*	if(!m_pScl)
		return;

	if(!(m_pScl->m_pCheckNotifier))
		return;
*/
	
	sprintf(info,"**错误 : 第%d行,第%d列, %s\n",(int)e.getLineNumber(),(int)e.getColumnNumber(),StrX(e.getMessage()));
	if(m_fileType==1){
		if(!m_pScl){
			return;
		}

		if(m_pScl->m_pCheckNotifier){
			if(m_pScl->m_pCheckNotifier->m_bEnableErrorShow){
				m_pScl->m_pCheckNotifier->NotifyCheckInfo(info);
			}
			m_pScl->m_pCheckNotifier->m_nErrorCount++;
		}
	}
	else{
		if(!m_pLnInfo){
			return;
		}

		if(m_pLnInfo->m_pCheckNotifier){
			if(m_pLnInfo->m_pCheckNotifier->m_bEnableErrorShow){
				m_pLnInfo->m_pCheckNotifier->NotifyCheckInfo(info);
			}
			m_pLnInfo->m_pCheckNotifier->m_nErrorCount++;
		}
	}
	


    XERCES_STD_QUALIFIER cerr << "\nFatal Error at file " << StrX(e.getSystemId())<< XERCES_STD_QUALIFIER endl;
//		 << ", line " << e.getLineNumber()
//		 << ", char " << e.getColumnNumber()
 //        << "\n  Message: " << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl;
}

void CErrorPrintHandler::warning(const SAXParseException& e)
{
//	sprintf(g_remind_info_line,"Warning\t\t:row = %d,col = %d,message = %s\n",(int)e.getLineNumber(),(int)e.getColumnNumber(),StrX(e.getMessage()));
//	fprintf(g_fpError,g_remind_info_line);
//	g_warning_count++;

    XERCES_STD_QUALIFIER cerr << "\nWarning at file " << StrX(e.getSystemId())<< XERCES_STD_QUALIFIER endl;
//		 << ", line " << e.getLineNumber()
//		 << ", char " << e.getColumnNumber()
//         << "\n  Message: " << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl;

	char info[256];
	if(m_fileType==1){
		if(!m_pScl)
			return;

		if(!(m_pScl->m_pCheckNotifier))
			return;


		sprintf(info,"*警告 : 第%d行,第%d列, %s\n",(int)e.getLineNumber(),(int)e.getColumnNumber(),StrX(e.getMessage()));
		if(m_pScl->m_pCheckNotifier)
		{
			if(m_pScl->m_pCheckNotifier->m_bEnableWarningShow){
				m_pScl->m_pCheckNotifier->NotifyCheckInfo(info);
			}
			m_pScl->m_pCheckNotifier->m_nWarningCount++;
		}	
	}
	else{
		if(!m_pLnInfo)
			return;

		if(!(m_pLnInfo->m_pCheckNotifier))
			return;


		sprintf(info,"*警告 : 第%d行,第%d列, %s\n",(int)e.getLineNumber(),(int)e.getColumnNumber(),StrX(e.getMessage()));
		if(m_pLnInfo->m_pCheckNotifier)
		{
			if(m_pLnInfo->m_pCheckNotifier->m_bEnableWarningShow){
				m_pLnInfo->m_pCheckNotifier->NotifyCheckInfo(info);
			}
			m_pLnInfo->m_pCheckNotifier->m_nWarningCount++;
		}	
	}	
}

void CErrorPrintHandler::resetErrors()
{
    fSawErrors = false;

	if(m_fileType==1){
		if(!m_pScl)
			return;
		if(!(m_pScl->m_pCheckNotifier))
			return;
	}
	else{
		if(!m_pLnInfo)
			return;
		if(!(m_pLnInfo->m_pCheckNotifier))
			return;
	}
}
