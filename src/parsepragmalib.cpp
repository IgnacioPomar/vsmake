/********************************************************************
 * Name        : parsepragmalib.h
 * Copyright	(C) 2016 Ignacio Pomar Ballestero
 * License     : MIT License (see LICENSE.txt)
 * Description : The parser itself
 ********************************************************************/

#include <iostream>
#include <fstream>

#include "parsepragmalib.h"

#define SIZE_COMMENT_CHAR	2
#define SIZE_DEFINE         7


/**
 * Constructor
 */
ParsePragmaLib::ParsePragmaLib ()
{
	isInsideMacroCondition = false;
	isBlockComment = false;
	isActiveCode = true;
}

/**
 * Clears all the comments in the line. Use isBlockComment to suport multiple lines coments
 * \param  [in]  line  the line we want to clear
 * \return A string without comments.
 */
//TODO: In the future we should check if we have somthing like  "/*" (or worse, in some lines)
std::string ParsePragmaLib::cleanComments (std::string line)
{
	std::string cleanLine = line;
	size_t endCommentBlock = std::string::npos;
	size_t startCommentBlock = cleanLine.find ("/*");

	//Check if we hace previous comment
	if (isBlockComment == 1)
	{
		size_t endCommentPosition = cleanLine.find ("*/");
		if (std::string::npos == endCommentPosition)
		{
			return ""; //we are still inside the block comment
		}
		else
		{
			cleanLine = cleanLine.substr (endCommentPosition + SIZE_COMMENT_CHAR); 
			isBlockComment = 0;
		}
	}

	//Clean Commet blocks
	while (startCommentBlock != std::string::npos)
	{
		size_t endCommentBlock = cleanLine.find ("*/");

		if (endCommentBlock == std::string::npos)
		{
			cleanLine.erase (startCommentBlock);
			isBlockComment = 1;
			startCommentBlock = std::string::npos;
		}
		else
		{
			cleanLine.erase (startCommentBlock, endCommentBlock - startCommentBlock + SIZE_COMMENT_CHAR);
			startCommentBlock = cleanLine.find ("/*");
		}
	}

	//Clean inline comments
	startCommentBlock = cleanLine.find ("//");
	if (startCommentBlock != std::string::npos)
	{
		cleanLine.erase (startCommentBlock);
	}

	return cleanLine;
}


/**
 * Swap the values by its defined value. if there are strings delimited by "", it will join them
 * \param [in]   line  the line we are parsing
 * \return The line with only valid code.
 */
//TODO: check if the macro is inside quotes
//TODO: we should check if the macro is more than one time in the line (do wlie instead of if)
//TODO: ¿check quotes when joining with another one? (currently we are removing them in addDefine)
std::string ParsePragmaLib::replaceDefines (std::string line)
{
	//Considering only one preproccesor directive per line
	size_t macroPos;
	std::string preProcessedLine = line;

	std::map<std::string, std::string>::iterator iter;
	
	for (iter = defines.begin(); iter != defines.end(); ++iter) 
	{
		macroPos = preProcessedLine.find (iter->first);
		if (macroPos != std::string::npos)
		{
			size_t replaceLen;
			size_t replacePos;

			//check if isnt a part of a bigger word
			//TODO: we should recheck if the macro is in the string later... maybe it will resolve itself when checking if there is more than one
			if ((macroPos != 0) && 
				!((preProcessedLine [macroPos - 1] == ' ') || (preProcessedLine [macroPos - 1] == '"'))
			   ) continue;
			if (macroPos != line.length () - iter->first.length())
			{
				//BUG: Repasar la condición final, no va con END_LIB
				size_t endPos = macroPos + iter->first.length();
				if (!((preProcessedLine [endPos] == ' ') || (preProcessedLine [endPos] == '"')))
					continue;
			}

			//check next limit
			size_t nextLimit = preProcessedLine.find_first_not_of (' ', macroPos + iter->first.length());
			if ((nextLimit != std::string::npos) && (preProcessedLine [nextLimit] == '"'))
			{
				replaceLen = nextLimit - macroPos + 1;
			}
			else replaceLen = iter->first.length();

			//check previous limit
			size_t prevoiusLimit = preProcessedLine.find_last_not_of (' ', macroPos - 1);
			if ((prevoiusLimit != std::string::npos) && (preProcessedLine [prevoiusLimit] == '"'))
			{
				replacePos = prevoiusLimit;
				replaceLen+= macroPos - prevoiusLimit;
			}
			else replacePos = macroPos;

			//finally... replace
			preProcessedLine.replace (replacePos, replaceLen, iter->second);
		}
	}

	return preProcessedLine;
}

/*
"#elif "
"#else"
"#endif"
*/


std::string ParsePragmaLib::cleanMacroCondition   (std::string line, size_t conditionarDirectivePos)
{
	size_t requiredDefinePos;

	//find condition start position
	requiredDefinePos = line.find_first_of (" ", conditionarDirectivePos);
	requiredDefinePos = line.find_first_of (" ", requiredDefinePos);
	
	//trim
	std::string condition = line.substr (requiredDefinePos);
	condition.erase (condition.find_last_not_of(" \n\r\t")+1);

	return condition;
}

//TODO: WORKING HERE
void  ParsePragmaLib::parseConditionalDirectives (std::string line)
{
	size_t conditionarDirectivePos;

	if (isInsideMacroCondition)
	{
		//we can only change the flow if we have an else or an end statement
	}
	else 
	{
		bool isPositiveCondition = true;
		bool isDefineCondition = false;

		if (std::string::npos != (conditionarDirectivePos = line.find ("#if ")))
		{
			//TODO: Make a function to evaluate complex conditions
			isInsideMacroCondition = true;
			macroLevelStatus.push_back (isActiveCode);
			std::string condition = cleanMacroCondition (line, conditionarDirectivePos);

			if (atoi(condition.c_str ()))
			{
				isActiveCode = true;
			}
			else
			{
				isActiveCode = false;
			}
		}
		else if (std::string::npos != (conditionarDirectivePos = line.find ("#ifdef ")))
		{
			isDefineCondition = true;
		}
		else if (std::string::npos != (conditionarDirectivePos = line.find ("#ifndef ")))
		{
			isPositiveCondition = false;
			isDefineCondition = true;
		}


		if (isDefineCondition) //we are inside #ifdef or ifndef
		{
			std::string requiredDefine = cleanMacroCondition (line, conditionarDirectivePos);

			macroLevelStatus.push_back (isActiveCode);
			isInsideMacroCondition = true;
			
			if (((defines.find(requiredDefine) == defines.end()) && isPositiveCondition) ||  //#ifdef
				(defines.find(requiredDefine) != defines.end()) //#ifndef
		       )
			{
				isActiveCode = false;
			}
			else
			{
				isActiveCode = true;
			}
		}
	}
		
	
	//bool isActiveCode;
}

/**
 * Check all preprocessor operations. It sets the var isActualCode to 0 if the conditional directives require them.
 * This function does not support comments.
 * \param [in]  line   the line we must process
 * \return The line procesed
 */
std::string ParsePragmaLib::parsePreprocessorMacros (std::string line)
{
	//Only one preproccesor directive per line
	//size_t directivePos;
	std::string preProcessedLine = "";

	parseConditionalDirectives (line);
	
	if (0) //TODO: Comprobar condicionales
	{
		preProcessedLine = line;
	}
	else
	{
		if (isActiveCode)
		{
			preProcessedLine = replaceDefines (line);
			parseNewDefine (preProcessedLine);
		}
	}

	return preProcessedLine;
}


/**
 * Check if is a new define, and if its found, its added to the collection
 * \param [in]  line   the line we are parsing
 */
void ParsePragmaLib::parseNewDefine (std::string line)
{
	size_t definePos;
	if (std::string::npos != (definePos = line.find ("#define ")))
	{
		size_t startDefine = line.find_first_not_of (' ', definePos + SIZE_DEFINE);
		//if startDefine == string::npos  ----> error
		size_t endDefine   = line.find_first_of (' ', startDefine);
		size_t startValue  = line.find_first_not_of (' ', endDefine);

		if (startValue == std::string::npos)
		{
			addDefine (line.substr (startDefine, endDefine - startDefine));
		}
		else
		{
			size_t endValue    = line.find_last_not_of (' ');

			addDefine (line.substr (startDefine, endDefine - startDefine),
				       line.substr (startValue,  endValue  - startValue + 1));
		}
	}

}



/**
 * Calls clean comments, use preprocessor macros, and calls parse
 * \param  [in]   line  The line we want to parse
 */
void ParsePragmaLib::parseCurrentLine (std::string line)
{
	std::string cleanLine;

	cleanLine = cleanComments (line);
	cleanLine = parsePreprocessorMacros (cleanLine);

	if (isActiveCode)
	{
		parsePragmaComment (cleanLine);
	}
}



/**
 * Removes quotes form the start and theend of the string
 * \param [in]  line   String with quotes
 */
std::string ParsePragmaLib::removeQuotes (std::string line)
{
	//TODO: remove spaces
	size_t headOffset = 0;
	size_t tailOffset = 0;

	if (line.length () == 0) return line;

	while (line[headOffset] == ' ') headOffset++;
	while (line[line.length() - tailOffset - 1] == ' ') tailOffset++;

	if (line[headOffset]    == '"') headOffset++;
	if (line[line.length()    - tailOffset - 1] == '"')  tailOffset++;

	if (headOffset || headOffset) return line.substr (headOffset, line.length () - tailOffset - headOffset);
	else return line;
	
}

/**
 * Check if is a new pragma, and if its found, its added to the collection
 * \param [in]  line  the line we are parsing
 */
void ParsePragmaLib::parsePragmaComment (std::string line)
{
	//we dont check if the sintax is correct
	size_t pragmaPos;
	if (std::string::npos != (pragmaPos = line.find ("#pragma ")))
	{
		if (std::string::npos != (pragmaPos = line.find (" comment", pragmaPos)))
		{
			if (std::string::npos != (pragmaPos = line.find ("lib", pragmaPos)))
			{
				size_t parenthesesPos;
				std::string lib;

				pragmaPos = line.find (",", pragmaPos + 1) + 1;
				parenthesesPos = line.find (")", pragmaPos);
				lib = removeQuotes (line.substr (pragmaPos,  parenthesesPos - pragmaPos - 1));
				pragmaLibs.push_back (lib);
			} //lib
		}//comment
	}//define
}


/**
 * Adds a global define
 * \param  [in]  define   new define
 * \param  [in]  value    Value of the define
 */
void ParsePragmaLib::addDefine (std::string define, std::string value)
{
	defines [define] = removeQuotes (value); 
}


/**
 * Read a file and parses all its line
 *
 * \param   [in]   file  file to parser
 * \return 0 - if all ok. 1 - if the file could not been opened.
 */
int ParsePragmaLib::parseFile (std::string file)
{
	std::string line;
	std::ifstream pragmafile (file.c_str());
	
	if (pragmafile.is_open())
	{
		while (pragmafile.good())
		{
			getline (pragmafile, line);
			parseCurrentLine (line);
		}

		pragmafile.close ();
		return 0; //parsing worked ok
	}
	else return 1; // Unable to open file 
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>> To give access to the tester <<<<<<<<<<<<<<<<<<<<

/**
 * Constructor: creates the instance of the real ParsePragmaLib
 */
ParsePragmaLibTester::ParsePragmaLibTester ()
{
	pd = new ParsePragmaLib ();
}

/**
 * Destructor: delete the ParsePragmaLib's instance
 */
ParsePragmaLibTester::~ParsePragmaLibTester ()
{
	delete pd;
}


/**
 * Calls the ParsePragmaLib's parseFile method
 *
 * \param [in]   file  file to parser
 * \return 0 - if all ok. 1 - if the file could not been opened.
 */
int ParsePragmaLibTester::parseFile (const char * file)
{
	return ((ParsePragmaLib*) pd)->parseFile (file);
}


/**
 * Calls the ParsePragmaLib's addDefine method
 *
 * \param [in]   define  new define macro
 * \param [in]   value   value of the macro 
 * \return 0 - if all ok. 1 - if the file could not been opened.
 */
void ParsePragmaLibTester::addDefine (const char * define, const char * value)
{
	((ParsePragmaLib*) pd)->addDefine (define, value);
}




