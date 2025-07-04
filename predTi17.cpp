//
// MATLAB Compiler: 7.0.1 (R2019a)
// Date: Mon Dec 13 17:05:13 2021
// Arguments:
// "-B""macro_default""-W""cpplib:predTi17""-T""link:lib""predictionTi17.m""-C"
//

#define EXPORTING_predTi17 1
#include "predTi17.h"

static HMCRINSTANCE _mcr_inst = NULL;

#if defined( _MSC_VER) || defined(__LCC__) || defined(__MINGW64__)
#ifdef __LCC__
#undef EXTERN_C
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#define NOMINMAX
#include <windows.h>
#undef interface

static char path_to_dll[_MAX_PATH];

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, void *pv)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        if (GetModuleFileName(hInstance, path_to_dll, _MAX_PATH) == 0)
            return FALSE;
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
    }
    return TRUE;
}
#endif
#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultPrintHandler(const char *s)
{
    return mclWrite(1 /* stdout */, s, sizeof(char)*strlen(s));
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultErrorHandler(const char *s)
{
    int written = 0;
    size_t len = 0;
    len = strlen(s);
    written = mclWrite(2 /* stderr */, s, sizeof(char)*len);
    if (len > 0 && s[ len-1 ] != '\n')
        written += mclWrite(2 /* stderr */, "\n", sizeof(char));
    return written;
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_predTi17_C_API
#define LIB_predTi17_C_API /* No special import/export declaration */
#endif

LIB_predTi17_C_API 
bool MW_CALL_CONV predTi17InitializeWithHandlers(
    mclOutputHandlerFcn error_handler,
    mclOutputHandlerFcn print_handler)
{
    int bResult = 0;
    if (_mcr_inst != NULL)
        return true;
    if (!mclmcrInitialize())
        return false;
    if (!GetModuleFileName(GetModuleHandle("predTi17"), path_to_dll, _MAX_PATH))
        return false;
    bResult = mclInitializeComponentInstanceNonEmbeddedStandalone(&_mcr_inst,
                                                                  path_to_dll,
                                                                  "predTi17",
                                                                  LibTarget,
                                                                  error_handler, 
                                                                  print_handler);
    if (!bResult)
    return false;
    return true;
}

LIB_predTi17_C_API 
bool MW_CALL_CONV predTi17Initialize(void)
{
    return predTi17InitializeWithHandlers(mclDefaultErrorHandler, mclDefaultPrintHandler);
}

LIB_predTi17_C_API 
void MW_CALL_CONV predTi17Terminate(void)
{
    if (_mcr_inst != NULL)
        mclTerminateInstance(&_mcr_inst);
}

LIB_predTi17_C_API 
void MW_CALL_CONV predTi17PrintStackTrace(void) 
{
    char** stackTrace;
    int stackDepth = mclGetStackTrace(&stackTrace);
    int i;
    for(i=0; i<stackDepth; i++)
    {
        mclWrite(2 /* stderr */, stackTrace[i], sizeof(char)*strlen(stackTrace[i]));
        mclWrite(2 /* stderr */, "\n", sizeof(char)*strlen("\n"));
    }
    mclFreeStackTrace(&stackTrace, stackDepth);
}


LIB_predTi17_C_API 
bool MW_CALL_CONV mlxPredictionTi17(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
    return mclFeval(_mcr_inst, "predictionTi17", nlhs, plhs, nrhs, prhs);
}

LIB_predTi17_CPP_API 
void MW_CALL_CONV predictionTi17(int nargout, mwArray& Y, const mwArray& X)
{
    mclcppMlfFeval(_mcr_inst, "predictionTi17", nargout, 1, 1, &Y, &X);
}

