#pragma once

#ifdef ST_PLATFORM_WINDOWS
#ifdef ST_BUILD_DLL
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
#else
#error Stellar Engine only supports Windows!
#endif