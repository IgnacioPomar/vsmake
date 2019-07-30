/*********************************************************************************************
 *	Name		: vsmake_pragmalib.h
 *	Description	: header with the libs used in this project
 ********************************************************************************************/

#ifndef _PRAGMA_LIB_VSMAKE_H_
#define _PRAGMA_LIB_VSMAKE_H_

#ifdef _MSC_VER //we will need preinclude


#ifndef SIMPLE_END_LIB
#define SIMPLE_END_LIB ".lib" 
#ifdef _DEBUG 
#define END_LIB_STD "d" SIMPLE_END_LIB
#define END_LIB_CUSTOM "d" SIMPLE_END_LIB
#else
#define END_LIB_STD SIMPLE_END_LIB
#define END_LIB_CUSTOM "r" SIMPLE_END_LIB
#endif
#endif




 //#pragma comment(lib, "dencrypt" END_LIB_STD)

#endif // _MSC_VER
#endif // _PRAGMA_LIB_VSMAKE_H_
