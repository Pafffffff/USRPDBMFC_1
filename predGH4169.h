
 //MATLAB Compiler: 7.0.1 (R2019a)
 //Date: Mon Dec 13 17:22:28 2021
 //Arguments:
 //"-B""macro_default""-W""cpplib:predGH4169""-T""link:lib""predictionGH4169.m""
 //-C"


#ifndef __predGH4169_h
#define __predGH4169_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" {
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_predGH4169_C_API 
#define LIB_predGH4169_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_predGH4169_C_API 
bool MW_CALL_CONV predGH4169InitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_predGH4169_C_API 
bool MW_CALL_CONV predGH4169Initialize(void);

extern LIB_predGH4169_C_API 
void MW_CALL_CONV predGH4169Terminate(void);

extern LIB_predGH4169_C_API 
void MW_CALL_CONV predGH4169PrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_predGH4169_C_API 
bool MW_CALL_CONV mlxPredictionGH4169(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                      *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#ifdef __cplusplus
}
#endif


/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__MINGW64__)

#ifdef EXPORTING_predGH4169
#define PUBLIC_predGH4169_CPP_API __declspec(dllexport)
#else
#define PUBLIC_predGH4169_CPP_API __declspec(dllimport)
#endif

#define LIB_predGH4169_CPP_API PUBLIC_predGH4169_CPP_API

#else

#if !defined(LIB_predGH4169_CPP_API)
#if defined(LIB_predGH4169_C_API)
#define LIB_predGH4169_CPP_API LIB_predGH4169_C_API
#else
#define LIB_predGH4169_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_predGH4169_CPP_API void MW_CALL_CONV predictionGH4169(int nargout, mwArray& Y, const mwArray& X);

/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */
#endif

#endif
