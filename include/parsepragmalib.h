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

typedef struct _MacroLevelStat 
{
	bool isActiveCode; 
	bool wasMacroIfActived;
} MacroLevelStat;

//To allow the tester have access the class data
class VSMAKE_LOCAL ParsePragmaLibData
{
protected:
	bool isBlockComment;			///<  if we are inside a block comment
	bool isActiveCode;				///<  if the current code is active
	bool wasMacroIfActived;			///<  if the if macro was active sometime
	
	std::vector <MacroLevelStat>        macroLevelStatus;

	std::map <std::string,std::string>  defines;
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
	bool isPositiveCondition			(std::string condition);
	bool isDefined          			(std::string define);
	void addMacroLevel                  (bool newStatus);
	bool isWordCharSeparator            (char c);
	
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

