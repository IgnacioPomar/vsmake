/********************************************************************
 * Name        : parsepragmalib.h
 * Copyright	(C) 2016 Ignacio Pomar Ballestero
 * License     : MIT License (see LICENSE.txt)
 * Description : prototype of the parser
 ********************************************************************/


#pragma once
#ifndef _PARSEPRAGMALIB_H_
#define _PARSEPRAGMALIB_H_

#include "vsmake_cfg.h"

#include <string>
#include <map>
#include <vector>


//If second is 1, then first must exist
typedef std::pair <std::string, unsigned char> macroCondition;

//To allow the tester have access the class data
class VSMAKE_LOCAL ParsePragmaLibData
{
protected:
	bool isBlockComment;			///<  if we are inside a block comment
	bool isActiveCode;				///<  if the current code is active
	bool isInsideMacroCondition;	///<  if we are inside a MacroCondition
	
	std::vector <bool>                  macroLevelStatus;

	std::map <std::string,std::string>  defines;
	std::vector <macroCondition>        macroConditions;
	std::vector <std::string>           pragmaLibs;
};

//BEWARE: Each thread must have its own instance to be therad safe
class VSMAKE_LOCAL ParsePragmaLib: public ParsePragmaLibData
{
private:

	void parseCurrentLine               (std::string line);
	std::string cleanComments           (std::string line);
	std::string cleanMacroCondition     (std::string line, size_t conditionarDirectivePos);
	std::string parsePreprocessorMacros (std::string line);
	std::string replaceDefines          (std::string line);
	void parseNewDefine                 (std::string line);
	void parsePragmaComment             (std::string line);
	void parseConditionalDirectives     (std::string line);
	std::string removeQuotes            (std::string line);
	
public:
	ParsePragmaLib ();
	void addDefine (std::string define, std::string value = "");
	int parseFile (std::string file);
};

//Class to work with the tester
class VSMAKE_API ParsePragmaLibTester
{
public:
	ParsePragmaLibData * pd;

	ParsePragmaLibTester ();
	~ParsePragmaLibTester ();
	
	void addDefine (const char * define, const char * value);
	int parseFile (const char * file);

};

#endif 

