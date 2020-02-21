/********************************************************************
 * Name        : progressInfo.cpp
 * Description : show in console the progress status
 ********************************************************************/

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/ioctl.h>
#endif

#include <stdio.h>
#include <string>
#include <iostream>

#include "progressInfo.h"

 // enough to hold all numbers up to 64-bits
#define MAX_BUFF_SIZE	21



/**
 * A "Private" function. Is here to avoid the warning when exporting std::string
 * Formats a progressbar in the specified width
 * \param   [in]   itemStat     the status we are evaluating
 * \param   [in]   barWidth     max bar width
 * \param   [in]   iterateChar  Char of the advance
 * \return  formated ProgressBar
 */
std::string getProgressBar (Status itemStat, int barWidth, char iterateChar)
{
	std::string retVal;

	//-------- cases witout space left -----------
	if (barWidth < 1) return "";
	else if (barWidth < 4)
	{
		retVal = iterateChar;
	}
	else if (itemStat.count == 0)
	{
		retVal = iterateChar;
	}
	else
	{
		//-------- we have a bit of space left -----------
		char chProgress [6];
		double progress = itemStat.id;
		progress /= itemStat.count;

		//Now formating the percent in number
		sprintf (chProgress, "%d%% ", int (progress * 100));

		barWidth -= 7; //we substracto de % space and the [] space


		//-------- we have plenty of space -----------
		if (barWidth > 7)
		{
			//Now the graphic
			retVal = "[";
			int pos = int (barWidth  * progress);
			for (int i = 0; i < barWidth; ++i)
			{
				if (i < pos) retVal += "=";
				else if (i == pos) retVal += iterateChar;
				else retVal += " ";
			}
			retVal += "]";
		}
		retVal += chProgress;
	}

	return retVal;
}



/**
 * A "Private" function. Is here to avoid the warning when exporting std::string
 * Formats the item name and the item status
 *
 * \param   [in]   itemStat     current status
 * \param   [in]   itemName     element we are working with
 * \return
 */
std::string formatGroupInfo (Status itemStat, const char* itemName)
{
	std::string retVal;
	char buffer [MAX_BUFF_SIZE];

	//First format the stat part
	if (itemStat.count == 0)
	{
		if (itemStat.id != 0)
		{
			sprintf (buffer, "[%d/?]", itemStat.id);
		}
		else buffer [0] = 0; //returns nothing
	}
	else
	{
		sprintf (buffer, "[%d/%d]", itemStat.id, itemStat.count);
	}

	retVal += buffer;

	if (itemName != NULL)
	{
		retVal += itemName;
	}

	return retVal;
}




/**
 * get the current screen size
 * \return  current screen size
 */
#ifdef WIN32
int DisplayProgressIndicator::getScreenWidth (void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int ret;
	ret = GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &csbi);
	if (ret)
	{
		return csbi.dwSize.X;
	}
	else
		return 60;
}
#else
int DisplayProgressIndicator::getScreenWidth (void)
{
	struct winsize max;
	ioctl (0, TIOCGWINSZ, &max);
	return max.ws_col;
}
#endif



/**
 * Advances the iterator char inside the secuence
 * \return the next iterator char
 */
char DisplayProgressIndicator::getIterateChar (void)
{
	switch (progressInfo.iterateChar++)
	{
	case 0:	return  '/'; break;
	case 1:	return  '-'; break;
	case 2:	return  '\\'; break;
	default:
		progressInfo.iterateChar = 0;
		return '|';
		break;
	}
}


/**
 * Show a simple progress message
 */
void DisplayProgressIndicator::printProgress (void)
{
	int screenWidth = getScreenWidth ();
	char iterateChar = getIterateChar ();

	std::string solutionInfo = formatGroupInfo (progressInfo.solutions, progressInfo.solutionName);
	std::string projectInfo = formatGroupInfo (progressInfo.projects, progressInfo.projectName);
	std::string sourcesInfo = formatGroupInfo (progressInfo.sourceFiles, progressInfo.sourceFileName);
	int textWidth = solutionInfo.size () + projectInfo.size () + sourcesInfo.size ();

	if ((textWidth + 3) <= screenWidth)
	{
		std::cout << solutionInfo << " " << projectInfo << " " << sourcesInfo << " ";
		std::string bar = getProgressBar (progressInfo.sourceFiles, screenWidth - textWidth - 3, iterateChar);
		std::cout << bar;
	}
	else if (textWidth <= screenWidth)
	{
		std::cout << solutionInfo << projectInfo << sourcesInfo;
	}
	else
	{
		//YAGNI: We should cut the final part of each part
		std::string outBuff = solutionInfo;
		outBuff.append (projectInfo);
		outBuff.append (sourcesInfo);

		std::cout << outBuff.substr (0, textWidth);
	}

	std::cout << "\r";
	std::cout.flush ();

}



/**
 * Show a persisntent error mesage
 *
 * \param   [in]   message  the error message than must persist in the screen
 */
void DisplayProgressIndicator::printErrorMessage (const char * message)
{
	printProgress ();
	std::cout << std::endl << message << std::endl;
}


/**
 * Constructor: Set vars to null
 */
Status::Status ()
{
	id = count = 0;
}


/**
 * Constructor: Set vars to null
 */
ProgressInfo::ProgressInfo ()
{
	solutionName = projectName = sourceFileName = NULL;
	iterateChar = 0;
}
