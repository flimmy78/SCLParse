// ErrorPrintHandler.h: interface for the CErrorPrintHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ERRORPRINTHANDLER_H__DCD24BEB_07CF_4D05_890A_3CA5BFB07949__INCLUDED_)
#define AFX_ERRORPRINTHANDLER_H__DCD24BEB_07CF_4D05_890A_3CA5BFB07949__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

#include <iostream>

using namespace std;
using namespace xercesc;

#include "scl.h"
#include "StrX.hpp"

class CErrorPrintHandler :public DefaultHandler
{
public:
	CErrorPrintHandler();
	CErrorPrintHandler(CScl * pScl);
	CErrorPrintHandler(CLNInfo * pScl);
	virtual ~CErrorPrintHandler();

    bool getSawErrors() const
    {
        return fSawErrors;
    }

	void warning(const SAXParseException& exc);
    void error(const SAXParseException& exc);
    void fatalError(const SAXParseException& exc);
    void resetErrors();

private:
    bool    fSawErrors;
	CScl * m_pScl;
	CLNInfo* m_pLnInfo;
	int m_fileType;
};

#endif // !defined(AFX_ERRORPRINTHANDLER_H__DCD24BEB_07CF_4D05_890A_3CA5BFB07949__INCLUDED_)
