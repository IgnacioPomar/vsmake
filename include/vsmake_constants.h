﻿/*********************************************************************************************
 *	Name		: vsmake_constants.h
 *	Description	: Enums used alongside this libary
 ********************************************************************************************/

#pragma once
#ifndef _VSMAKE_CONSTANTS_H_
#define _VSMAKE_CONSTANTS_H_


 /***********************************************************************************************
  * Error code list
  ***********************************************************************************************/
enum VsMakeErrorCode
{
	//Loading Errors
	VSMAKE_SOLUTION_FILE_NOT_FOUND = 1,
	VSMAKE_SOLUTION_FILE_BAD_FORMAT = 2,
	VSMAKE_SOLUTION_FILE_UNSUPPORTED_VERSION = 3,

	VSMAKE_PROJECT_FILE_NOT_FOUND = 4,
	VSMAKE_PROJECT_FILE_BAD_FORMAT = 2,


	//Not real errors
	VSMAKE_NOT_IMPLEMENTED = 9999,
	VSMAKE_NOT_SET = -1,
	VSMAKE_ALL_OK = 0
};

#endif //_VSMAKE_CONSTANTS_H_
