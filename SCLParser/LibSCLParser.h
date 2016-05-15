//#ifndef _LIBSCLPARSER_H_
//#define _LIBSCLPARSER_H_

#ifdef LIBSCL_EXPORTS
#define SCL_API __declspec(dllexport)
#else
#define SCL_API __declspec(dllimport)
#endif

#ifndef WIN32
#undef  SCL_API
#define SCL_API
#endif

//#ifdef WIN32
//#pragma   warning(disable   :   4251)
//#endif

//#endif
