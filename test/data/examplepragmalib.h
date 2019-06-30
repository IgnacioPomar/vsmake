/********************************************************************
 * Name        : examplepragmalib.h
 * Author      : Ignacio Pomar Ballestero
 * Copyright   : (C) 2013 DATISA (http://www.datisa.es) 
 * Description : this file is for testing pruposes
 * is to parse #pragmalib to allow its use in the vsmake solution
 * we chech the use of #if, #ifdef, #ifndef, #else, #elif and #endif 
 ********************************************************************/

#pragma once    


//>>>>>>>>>>>>> we must ignore this <<<<<<<<<<<<<<<<<
//we must ignore this



//-----------------------------------------
#ifdef _CUSTOM 
#define LIB_PATH_CUSTOM "./custom/lib/"
 
//If we dont ingore the following comments, the program will fail
// #endif
 /* #endif */
 /*
    #endif 
 */
/* nasty, but we will support it*/ #else
#define LIB_PATH_CUSTOM "./std/lib/"
#endif


//-----------------------------------------
#ifdef _DEBUG 
#define LIB_PATH_SYST "" LIB_PATH_CUSTOM "debug/"
#define END_LIB "d.lib"
#else 
#define LIB_PATH_SYST ""  LIB_PATH_CUSTOM "release/"
#define END_LIB "r.lib"
#endif //_DEBUG

//-----------------------------------------
//TODO: support the following directives
//#if  defined (macro1)  || !defined (macro2) || defined (macro3)
//#elif 


//-----------------------------------------
#ifdef _CUSTOM 
	#ifdef _DEBUG  //it should have no efect
		#pragma comment(lib, "custom_debug.lib")
	#endif
#endif

//-----------------------------------------
#if 0	
	#ifdef _DEBUG  //it should have no efect
		#pragma comment(lib, "invalid.lib")
	#endif
#endif

//-----------------------------------------
#if 10
	#pragma comment(lib, "always.lib")
#endif

//-----------------------------------------
#ifdef _DEBUG 
	#pragma comment(lib, LIB_PATH_SYST "library1" END_LIB)

	#pragma comment(lib, LIB_PATH_SYST "library3" END_LIB)
	#ifndef _DEBUG  //it should never happen
		#pragma comment(lib, "invalid.lib")
	#endif
#else
	#pragma comment(lib, LIB_PATH_SYST "library1" END_LIB)
#endif


