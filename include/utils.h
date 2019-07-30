/*********************************************************************************************
 *	Name		: utils.h
 *	Description	: Bunch of headers from utilitis cpp
 ********************************************************************************************/
#pragma once
#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <vector>

 //From stackoverflowcode.cpp
std::vector<std::string> split (const std::string &s, char delim);


//Inside winutils.cpp
char *dirname (const char *path);
char *realpath (const char *name, char *resolved = NULL);


#endif //_UTILS_H_
