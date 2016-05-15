//#ifndef _PROGRESS_NOTIFIER_INCLUDE_
//#define _PROGRESS_NOTIFIER_INCLUDE_
#include "LibSCLParser.h"
/*若需要实现进度指示，请从该类派生具体的实现类，处理进度信息*/
class  CProgressNotifier
{
public:
	virtual ~CProgressNotifier(){}
	virtual void UpdateProgress(const char* step_info,int percent) = 0;//用户必须实现，step_info为进度指示信息,percent为进度百分数。 
};


//#endif
