/*********************************************************************************************
 *	Name		: vsmake_cfg.h
 *	Description	: Configuration of the project
 ********************************************************************************************/

#pragma once
#ifndef _VSMAKE_CFG_H_
#define _VSMAKE_CFG_H_

 //If the solution is a dinamic library (dll), we need the next macro
#define VSMAKE_DLL

//IMPORTANT: the project who exports must have the preprocessor macro VSMAKE_DLL_EXPORTS

//see http://gcc.gnu.org/wiki/Visibility

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
#define VSMAKE_HELPER_DLL_IMPORT __declspec(dllimport)
#define VSMAKE_HELPER_DLL_EXPORT __declspec(dllexport)
#define VSMAKE_HELPER_DLL_LOCAL
#else
#if __GNUC__ >= 4
#define VSMAKE_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
#define VSMAKE_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
#define VSMAKE_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#define VSMAKE_HELPER_DLL_IMPORT
#define VSMAKE_HELPER_DLL_EXPORT
#define VSMAKE_HELPER_DLL_LOCAL
#endif
#endif

// Now we use the generic helper definitions above to define VSMAKE_API and VSMAKE_LOCAL.
// VSMAKE_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// VSMAKE_LOCAL is used for non-api symbols.

#ifdef VSMAKE_DLL // defined if VSMAKE is compiled as a DLL
#ifdef LIBVSMAKE_EXPORTS // defined if we are building the VSMAKE DLL (instead of using it)
#define VSMAKE_API VSMAKE_HELPER_DLL_EXPORT
#else
#define VSMAKE_API VSMAKE_HELPER_DLL_IMPORT
#endif // VSMAKE_DLL_EXPORTS
#define VSMAKE_LOCAL VSMAKE_HELPER_DLL_LOCAL
#else // VSMAKE_DLL is not defined: this means VSMAKE is a static lib.
#define VSMAKE_API
#define VSMAKE_LOCAL
#endif // VSMAKE_DLL


#endif //_VSMAKE_CFG_H_
