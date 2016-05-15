#ifndef _LIBSCL_H_
#define _LIBSCL_H_

#if defined(SCL_DLL_EXPORT) // inside DLL
#define SCLDLLPORT   __declspec(dllexport)
#else // outside DLL
#define SCLDLLPORT   __declspec(dllimport)
#endif

#endif
