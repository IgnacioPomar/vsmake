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


//Inside utils.cpp
void setFilePath (const std::string & filename, std::string &dest);
bool hasAbsolutePath (const std::string & filename);


#endif //_UTILS_H_
