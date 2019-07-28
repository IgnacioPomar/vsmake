/********************************************************************
 * Name        : parsepragmalib.h
 * Description : The parser itself
 ********************************************************************/
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "dbgHelper.h"

#include "parsepragmalib.h"

#define SIZE_COMMENT_CHAR	2
#define SIZE_DEFINE         7


/**
 * Constructor
 */
ParsePragmaLib::ParsePragmaLib ()
{
	isBlockComment = false;
	wasMacroIfActived = isActiveCode = true;
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
 * Check if the char is a word separator char
 * \param [in]   c  the char we want to check
 * \return true if is a separator char
 */
bool ParsePragmaLib::isWordCharSeparator (char c)
{
	switch (c)
	{
	case ' ':
	case '"':
	case '(':
	case ')':
	case '\t':
	case '\'':
		return true;
		break;		
	default:
		return false;
	}
}

/**
 * Swap the values by its defined value. if there are strings delimited by "", it will join them
 * \param [in]   line  the line we are parsing
 * \return The line with only valid code.
 */
//YAGNI: check if the macro is inside quotes
//YAGNI: ¿check quotes when joining with another one? (currently we are removing them in addDefine)
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
			if ((macroPos != 0) && (!isWordCharSeparator (preProcessedLine [macroPos - 1])))
			    continue; //Something in the left side, isnt a macro
			size_t endPos = macroPos + iter->first.length() - 1;
			if ((endPos != preProcessedLine.length ()) && 
				(!isWordCharSeparator (preProcessedLine [endPos + 1])))
				continue; //Something in the right side, isnt a macro
	

			//Find the fusion limit in the right
			size_t nextLimit = preProcessedLine.find_first_not_of (" \t", endPos + 1);
			if (nextLimit != std::string::npos)
			{
				if (preProcessedLine [nextLimit] == '"') 
					nextLimit++;//If there is a quote, we will fuson it
					
				replaceLen = nextLimit - macroPos;
			}
			else replaceLen = iter->first.length();

			//Find the fusion limit in the left
			size_t prevoiusLimit = preProcessedLine.find_last_not_of (" \t", macroPos - 1);
			if (prevoiusLimit != std::string::npos)
			{
				if (preProcessedLine [prevoiusLimit] != '"')
					prevoiusLimit++;
				replacePos = prevoiusLimit;
				replaceLen+= macroPos - prevoiusLimit;
			}
			else replacePos = macroPos;

			//finally... replace
			preProcessedLine.replace (replacePos, replaceLen, iter->second);

			//TODO: check if there are more ocurrences
			//macroPos = preProcessedLine.find (iter->first, macroPos + 1);
		}
	}

	return preProcessedLine;
}



/**
 * Cleans the conditional position leaving only the condition
 * \param [in]   line                     the line we are parsing
 * \param [in]   conditionarDirectivePos  Position containing the conditional directctive
 * \return The line with only valid code.
 */
std::string ParsePragmaLib::cleanMacroCondition   (std::string line, size_t conditionarDirectivePos)
{
	size_t requiredDefinePos;

	//find condition start position
	requiredDefinePos = line.find_first_of (" ", conditionarDirectivePos);
	requiredDefinePos = line.find_first_not_of (" ", requiredDefinePos);
	
	//trim
	std::string condition = line.substr (requiredDefinePos);
	condition.erase (condition.find_last_not_of(" \n\r\t")+1);

	return condition;
}


/**
 * Check if the condition is valid
 * \param [in]   condition   Condition to check
 * \return True if the condition is valid
 */
bool ParsePragmaLib::isPositiveCondition (std::string condition)
{
	//YAGNI?: Evaluate complex conditions, for example, the defined directive
	if (atoi(condition.c_str ()))
	{
		return true;
	}
	else
	{
		return false;
	}
}


/**
 * Check if the define exists
 * \param [in]   define   define to check
 * \return True if the define exists
 */
bool ParsePragmaLib::isDefined (std::string define)
{
	return (defines.find(define) != defines.end());
}


/**
 * Takes the current level and stores it before changing the new level
 * \param [in]   newStatus   Status of isActiveCode of the new block 
 */
void ParsePragmaLib::addMacroLevel (bool newStatus)
{
	MacroLevelStat ml;
	ml.isActiveCode = isActiveCode;
	ml.wasMacroIfActived = wasMacroIfActived;
	macroLevelStatus.push_back (ml);
	if (isActiveCode)
	{
		wasMacroIfActived = isActiveCode = newStatus;
	}
	else //If the parent was disabled... then the childs cant get enabled
	{
		isActiveCode = false;
		wasMacroIfActived = true;
	}
}


/**
 * Check if in the line we have a conditional directives, and if we have one it is evaluated
 * \param [in]  line   the line we must process
 */
void  ParsePragmaLib::parseConditionalDirectives (std::string line)
{
	size_t conditionarDirectivePos;

	if (std::string::npos != (conditionarDirectivePos = line.find ("#if ")))
	{
		std::string condition = cleanMacroCondition (line, conditionarDirectivePos);
		addMacroLevel (isPositiveCondition (condition));
	}
	else if (std::string::npos != (conditionarDirectivePos = line.find ("#ifdef ")))
	{
		std::string define = cleanMacroCondition (line, conditionarDirectivePos);
		addMacroLevel (isDefined (define));
	}
	else if (std::string::npos != (conditionarDirectivePos = line.find ("#ifndef ")))
	{
		std::string define = cleanMacroCondition (line, conditionarDirectivePos);
		addMacroLevel (!isDefined (define));
	}
	else if (std::string::npos != (conditionarDirectivePos = line.find ("#else")))
	{
		//YAGNI: Check if we are inside a condition
		if (isActiveCode)
		{
			isActiveCode = false;
		}
		else if (!wasMacroIfActived)
		{
			isActiveCode = wasMacroIfActived = true;
		}
	}
	else if (std::string::npos != (conditionarDirectivePos = line.find ("#elif ")))
	{
		//YAGNI: Check if we are inside a condition
		if (isActiveCode)
		{
			isActiveCode = false;
		}
		else if (!wasMacroIfActived)
		{
			std::string condition = cleanMacroCondition (line, conditionarDirectivePos);
			if (isPositiveCondition (condition))
			{
				isActiveCode = wasMacroIfActived = true;
			}
		}
	}
	else if (std::string::npos != (conditionarDirectivePos = line.find ("#endif")))
	{
		//YAGNI: Check if we are inside a condition
		MacroLevelStat ml = macroLevelStatus.back ();
		macroLevelStatus.pop_back ();
		isActiveCode = ml.isActiveCode;
		wasMacroIfActived = ml.wasMacroIfActived;
	}
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
	//YAGNI: we dont check if the sintax is correct
	//BUG: Corta si no hay comillas la libreria
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
				lib = removeQuotes (line.substr (pragmaPos,  parenthesesPos - pragmaPos));
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


/**
 * DEBUG: for unit test use
 *
 * \param [in]   dbgHelper  listener class
 */
void ParsePragmaLibTester::dbgGetLibs (DbgHelper * dbgHelper)
{
	for (const std::string &str : this->pd->pragmaLibs)
	{
		dbgHelper->putStr (str.c_str ());
	}
}



