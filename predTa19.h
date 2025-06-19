//
// MATLAB Compiler: 7.0.1 (R2019a)
// Date: Mon Dec 13 16:46:37 2021
// Arguments:
// "-B""macro_default""-W""cpplib:predTa19""-T""link:lib""predictionTa19.m""-C"
//

#ifndef __predTa19_h
#define __predTa19_h 1

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
#ifndef LIB_predTa19_C_API 
#define LIB_predTa19_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_predTa19_C_API 
bool MW_CALL_CONV predTa19InitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_predTa19_C_API 
bool MW_CALL_CONV predTa19Initialize(void);

extern LIB_predTa19_C_API 
void MW_CALL_CONV predTa19Terminate(void);

extern LIB_predTa19_C_API 
void MW_CALL_CONV predTa19PrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_predTa19_C_API 
bool MW_CALL_CONV mlxPredictionTa19(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#ifdef __cplusplus
}
#endif


/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__MINGW64__)

#ifdef EXPORTING_predTa19
#define PUBLIC_predTa19_CPP_API __declspec(dllexport)
#else
#define PUBLIC_predTa19_CPP_API __declspec(dllimport)
#endif

#define LIB_predTa19_CPP_API PUBLIC_predTa19_CPP_API

#else

#if !defined(LIB_predTa19_CPP_API)
#if defined(LIB_predTa19_C_API)
#define LIB_predTa19_CPP_API LIB_predTa19_C_API
#else
#define LIB_predTa19_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_predTa19_CPP_API void MW_CALL_CONV predictionTa19(int nargout, mwArray& Y, const mwArray& X);

/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */
#endif

#endif
