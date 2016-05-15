#ifndef _CHECK_NOTIFIER_INCLUDE_
#define _CHECK_NOTIFIER_INCLUDE_
#include "LibSCLParser.h"
/*若需要实现进度指示，请从该类派生具体的实现类，处理进度信息*/
class SCL_API CCheckNotifier
{
public:
	CCheckNotifier(){
		m_nErrorCount =0;
		m_nWarningCount=0;
		m_nRemindCount=0;

		m_nXsdChkErrCnt=0;
		m_nDoiSdiDaiChkErrCnt=0;
		m_nDaiValErrCnt=0;
		m_nDsChkErrCnt=0;
		m_nInputExtChkErrCnt=0;
		m_nSgccChkErrCnt=0;
		m_nCommCfgErrCnt=0;
		m_nInternalChkErrCnt=0;
		m_nDataSetErrCnt=0;
		m_nServerErrCnt=0;
		m_nControlErrCnt=0;
		m_nLNErrCnt=0;
		m_nStdDttChkErrCnt_LNodeType=0;
		m_nStdDttChkErrCnt_DOType=0;
		m_nStdDttChkErrCnt_DAType=0;
		m_nStdDttChkErrCnt_EnumType=0;
		m_nStdDttChkErrCnt_DO=0;
		m_nStdDttChkErrCnt_DA=0;
		m_nStdDttChkErrCnt_SDO=0;
		m_nStdDttChkErrCnt_BDA=0;
		m_nStdDttChkErrCnt_ENUM=0;
		m_nSgccDttChkRemindCnt=0;
		m_nCommuniciaonErrCnt=0;
		m_nDeviceErrCnt=0;

		m_bEnableRemindShow = true;
		m_bEnableWarningShow = true;
		m_bEnableErrorShow = true;
	}
	virtual ~CCheckNotifier(){}
	virtual void NotifyCheckInfo(char* check_info) = 0;//用户必须实现，check_info为一条Check的提示信息
	int m_nErrorCount;
	int m_nWarningCount;
	int m_nRemindCount;
	bool m_bEnableRemindShow;
	bool m_bEnableWarningShow;
	bool m_bEnableErrorShow;
	
	//
	int m_nXsdChkErrCnt;
	int m_nDoiSdiDaiChkErrCnt;
	int m_nDaiValErrCnt;
	int m_nDsChkErrCnt;
	int m_nInputExtChkErrCnt;
	int m_nSgccChkErrCnt;
	int m_nCommCfgErrCnt;
	int m_nDataSetErrCnt;
	int m_nServerErrCnt;
	int m_nControlErrCnt;
	int m_nLNErrCnt;
	int m_nDeviceErrCnt;
	int m_nInternalChkErrCnt;
	int m_nCommuniciaonErrCnt;
	int m_nStdDttChkErrCnt_LNodeType;
	int m_nStdDttChkErrCnt_DOType;
	int m_nStdDttChkErrCnt_DAType;
	int m_nStdDttChkErrCnt_EnumType;
	int m_nStdDttChkErrCnt_DO;
	int m_nStdDttChkErrCnt_DA;
	int m_nStdDttChkErrCnt_SDO;
	int m_nStdDttChkErrCnt_BDA;
	int m_nStdDttChkErrCnt_ENUM;
	int m_nSgccDttChkRemindCnt;

};


#endif
