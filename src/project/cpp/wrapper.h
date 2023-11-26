#ifndef _WRAPPER_H
#define _WRAPPER_H
#include "Model.h"

#ifdef _WIN32
#define API __declspec(dllexport)
#else
#define API
#endif

typedef void (*DataReadyCallback)(double result);

#ifdef __cplusplus
extern "C" {
#endif

char* makeCalc(char* line);

#ifdef __cplusplus
}
#endif

#endif // _WRAPPER_H
