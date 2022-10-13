#pragma once

/* Useful macros. */
#define CHECK_RETURN(input) if (!(input)) { return; } ;

/* Platform definitions. */
#ifdef PLATFORM_WINDOWS
#ifdef EGG_BUILD
#define EGG_API __declspec(dllexport)
#else
#define EGG_API __declspec(dllimport)
#endif
#else 
#error Egg Engine currently only supports windows!
#endif




