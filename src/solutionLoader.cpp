/*********************************************************************************************
 *	Name		: solutionLoader.cpp
 *	Description	: Loads the solution file to memory
 *  License     : MIT License (see LICENSE.txt)
 *	Copyright	(C) 2016 Ignacio Pomar Ballestero
 ********************************************************************************************/

#include <string.h>
#include <stdio.h>
#include "solution.h"
#include "solution_privatedata.h"
#include "solutionLoader.h"


#define MAX_BUFF_SIZE	1024

#define SOLUTION_FILE_MARK         "Microsoft Visual Studio Solution File, Format Version"
#define SOLUTION_PROJECT_START     "Project"
#define SOLUTION_PROJECT_DEP_START "ProjectSection(ProjectDependencies)"
#define SOLUTION_PROJECT_DEP_END   "EndProjectSection"
#define SOLUTION_PROJECT_END       "EndProject"


enum SolutionFileState
{
	FIRST_LINE = 1,
	FILE_FORMAT_LINE = 2,
	INSIDE_PROJECT = 3,
	INSIDE_PROJECT_SECTION = 4,
	WAITING_PROJECT = 5
};

/***********************************************************************************************
 * Parses the solution file
 * \param    [in]   solutionFile   Opened file of the solution
 * \param    [out]  solution       Solution class where we store the data parsed
 * \return  Error code of the operation. VSMAKE_ALL_OK if all was ok
 ***********************************************************************************************/
VsMakeErrorCode SolutionLoader::parseSolutionFile (FILE * solutionFile, Solution & solution)
{
	VsMakeErrorCode retVal = VSMAKE_NOT_SET;
	char line [MAX_BUFF_SIZE];
	SolutionFileState nextsolutionFileState = FIRST_LINE;
	
	//Next comes the project entries

	//The solution file in VS2010 and vs2015 have the same format

	while ((retVal == VSMAKE_NOT_SET) && ((fgets (line, MAX_BUFF_SIZE, solutionFile)) != NULL))
	{
		switch (nextsolutionFileState)
		{
		case FIRST_LINE: //First line contains the byte order mark (BOM)
			nextsolutionFileState = FILE_FORMAT_LINE;
			break;
		case FILE_FORMAT_LINE: //Second line contains the version file
			if (strstr (line, SOLUTION_FILE_MARK))
			{
				char * versionPos = &line [strlen (SOLUTION_FILE_MARK)];
				solution.solutionFormatVersion = 100 * atoi (versionPos);
				versionPos = strstr (versionPos,".");
				solution.solutionFormatVersion += atoi (++versionPos);
				nextsolutionFileState = WAITING_PROJECT;
			}
			else
			{
				retVal = VSMAKE_SOLUTION_FILE_BAD_FORMAT;
			}
			break;
		case WAITING_PROJECT:
			retVal = VSMAKE_NOT_IMPLEMENTED;
			break;
			
		case INSIDE_PROJECT:
			retVal = VSMAKE_NOT_IMPLEMENTED;
			break;
			
		case INSIDE_PROJECT_SECTION:
			retVal = VSMAKE_NOT_IMPLEMENTED;
			break;


		default: 
			retVal = VSMAKE_NOT_IMPLEMENTED;
		}
	}

	return retVal;
}



/***********************************************************************************************
 * Load a Visual studio solution
 * \param    [in]   solutionPath   Full path of the solution file
 * \param    [out]  solution       Solution class where we store the data parsed
 * \return  Error code of the operation. VSMAKE_ALL_OK if all was ok
 ***********************************************************************************************/
VsMakeErrorCode SolutionLoader::loadSolution (char *solutionPath, Solution & solution)
{
	FILE * solutionFile;
	solutionFile = fopen (solutionPath,"r");
	if (solutionFile == NULL)
	{
		return VSMAKE_SOLUTION_FILE_NOT_FOUND;
	}
	else
	{
		VsMakeErrorCode retVal = parseSolutionFile (solutionFile, solution);
		fclose (solutionFile);
		return retVal;
	}
	return VSMAKE_NOT_IMPLEMENTED;
}

