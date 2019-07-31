/*********************************************************************************************
 *	Name		: solutionLoader.cpp
 *	Description	: Loads the solution file to memory
 ********************************************************************************************/


#include <fstream>
#include <sstream>
#include <string>

#include "utils.h"
#include "solution.h"
#include "solution_privatedata.h"
#include "project.h"
#include "project_privatedata.h"
#include "solutionLoader.h"


 //--------------  local defines  --------------
enum SolutionFileState
{
	FIRST_LINE = 1,
	FILE_FORMAT_LINE = 2,
	INSIDE_PROJECT = 3,
	INSIDE_PROJECT_SECTION = 4,
	WAITING_PROJECT = 5
};


/***********************************************************************************************
 * Load a Visual studio solution
 * \param    [in]   solutionPath   Full path of the solution file
 * \param    [out]  solution       Solution class where we store the data parsed
 * \return  Error code of the operation. VSMAKE_ALL_OK if all was ok
 ***********************************************************************************************/
VsMakeErrorCode SolutionLoader::loadSolution (const char *solutionPath, Solution & solution)
{
	std::ifstream ifs;
	ifs.open (solutionPath, std::ifstream::in);

	if (!ifs.is_open ())
	{
		return VSMAKE_SOLUTION_FILE_NOT_FOUND;
	}
	else
	{
		setFilePath (solutionPath, solution.pd->solutionPath);

		VsMakeErrorCode retVal = parseSolutionFile (ifs, solution);
		ifs.close ();
		return retVal;
	}
}


/***********************************************************************************************
 * Parses the solution file
 * \param    [in]   solutionFile   Opened file of the solution
 * \param    [out]  solution       Solution class where we store the data parsed
 * \return  Error code of the operation. VSMAKE_ALL_OK if all was ok
 ***********************************************************************************************/
VsMakeErrorCode SolutionLoader::parseSolutionFile (std::ifstream  &ifs, Solution & solution)
{
	VsMakeErrorCode retVal = VSMAKE_NOT_SET;
	SolutionFileState nextsolutionFileState = FIRST_LINE;

	Project currentProject; //if we are reading a project, we will use this var

	std::string line;

	//The solution file in VS2010 and vs2017 have the same format
	while ((retVal == VSMAKE_NOT_SET) && std::getline (ifs, line))
	{
		switch (nextsolutionFileState)
		{
		case FIRST_LINE: //First line contains the byte order mark (BOM)
			nextsolutionFileState = FILE_FORMAT_LINE;
			break;
		case FILE_FORMAT_LINE: //Second line contains the version file
			if (std::string::npos != line.find (SOLUTION_FILE_MARK))
			{
				parseSolutionFormatVersion (line);
				nextsolutionFileState = WAITING_PROJECT;
			}
			else
			{
				retVal = VSMAKE_SOLUTION_FILE_BAD_FORMAT;
			}
			break;
		case WAITING_PROJECT:
			if (std::string::npos != line.find (SOLUTION_PROJECT_START))
			{
				currentProject.clear ();
				std::vector<std::string> lineChunks = split (line, '"');
				cleanSolutionUuid (lineChunks [SOLUTION_PROJ_UUID_POS]);

				currentProject.setProjectNameAndPath (lineChunks [SOLUTION_PROJ_NAME_POS].c_str (),
													  lineChunks [SOLUTION_PROJ_PATH_POS].c_str (),
													  lineChunks [SOLUTION_PROJ_UUID_POS].c_str (),
													  solution.pd->solutionPath.c_str ());
				if (lineChunks [SOLUTION_PROJ_PATH_POS].find (".vcxproj") != std::string::npos)
				{
					nextsolutionFileState = INSIDE_PROJECT;
				}
				else
				{
					//not a solution section. Must be ignored
				}


				retVal = currentProject.loadProject ();
				if (retVal == VSMAKE_ALL_OK)
				{
					//The project was loaded succesfully, we continue processing the file
					retVal = VSMAKE_NOT_SET;
				}

			}
			else if (std::string::npos != line.find (SOLUTION_END_PARSE_ZONE))
			{
				retVal = VSMAKE_ALL_OK;
			}
			break;

		case INSIDE_PROJECT:
			if (std::string::npos != line.find (SOLUTION_PROJECT_END))
			{
				solution.pd->projects.push_back (currentProject);
				nextsolutionFileState = WAITING_PROJECT;
			}
			else if (std::string::npos != line.find (SOLUTION_PROJECT_DEP_START))
			{
				nextsolutionFileState = INSIDE_PROJECT_SECTION;
			}
			break;

		case INSIDE_PROJECT_SECTION:
			if (std::string::npos != line.find (SOLUTION_PROJECT_DEP_END))
			{
				nextsolutionFileState = INSIDE_PROJECT;
			}
			else
			{
				//TODO: Buscar project ID
				std::vector<std::string> lineChunks = split (line, '{');
				cleanSolutionUuid (lineChunks [SOLUTION_PROJ_DEP_POS]);
				currentProject.pd->dependencies.push_back (lineChunks [SOLUTION_PROJ_DEP_POS]);
			}
			break;

			//default: retVal = VSMAKE_NOT_IMPLEMENTED;
		}
	}

	return retVal;
}



/***********************************************************************************************
 * Parses the line with the version number and returns the version
 * \param    [in]   versionLine       String containing the version number
 * \return The format version number, or 0 if error
 ***********************************************************************************************/
int SolutionLoader::parseSolutionFormatVersion (std::string & versionLine)
{
	std::string versionMark = SOLUTION_FILE_MARK;

	size_t pos = versionLine.find (versionMark);
	pos += versionMark.size ();
	std::string versionStr = versionLine.substr (pos);
	versionStr.erase (versionStr.find ("."), 1);
	return std::stoi (versionStr);
}


/***********************************************************************************************
 * Trim all trash chars that the solution line/chunk may contain
 * \param    [in,out]   uuid       String from the solution file
 ***********************************************************************************************/
void SolutionLoader::cleanSolutionUuid (std::string & uuidChunk)
{
	//Erase the initial trash chars
	size_t charPos = uuidChunk.find_last_of ('{');
	if (charPos != std::string::npos)
	{
		uuidChunk.erase (0, charPos + 1);
	}

	//Erase the final trash chars
	charPos = uuidChunk.find_first_of ('}');
	if (charPos != std::string::npos)
	{
		uuidChunk.erase (charPos);
	}
}





//-------------------- Load Project --------------------

/***********************************************************************************************
 * Load a Visual studio solution
 * \param    [in]   solutionPath   Full path of the solution file
 * \param    [out]  solution       Solution class where we store the data parsed
 * \return  Error code of the operation. VSMAKE_ALL_OK if all was ok
 ***********************************************************************************************/
VsMakeErrorCode SolutionLoader::loadProject (const char *projectPath, Project & project)
{

	//return VSMAKE_ALL_OK;
	return VSMAKE_NOT_IMPLEMENTED;
}
