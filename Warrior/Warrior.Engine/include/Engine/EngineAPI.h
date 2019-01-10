#ifndef WARRIOR_ENGINE_ENGINEAPI_H
#define WARRIOR_ENGINE_ENGINEAPI_H

#ifdef WE_BUILD_DLL
#define WE_API __declspec(dllexport)
#else
#define WE_API __declspec(dllimport)
#endif

#endif