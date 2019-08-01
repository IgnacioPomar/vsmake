/*********************************************************************************************
 *	Name		: solutionLoader.cpp
 *	Description	: Loads the solution file to memory
 ********************************************************************************************/


#pragma once
#ifndef _VSMAKE_SOLUTION_LOADER_H_
#define _VSMAKE_SOLUTION_LOADER_H_


#include "vsmake_cfg.h"
#include "vsmake_constants.h"


class Solution;

class VSMAKE_LOCAL SolutionLoader
{
private:
	static constexpr const char * SOLUTION_FILE_MARK = "Microsoft Visual Studio Solution File, Format Version";
	static constexpr const char * SOLUTION_PROJECT_START = "Project(";
	static constexpr const char * SOLUTION_PROJECT_DEP_START = "ProjectSection(ProjectDependencies)";
	static constexpr const char * SOLUTION_PROJECT_DEP_END = "EndProjectSection";
	static constexpr const char * SOLUTION_PROJECT_END = "EndProject";
	static constexpr const char * SOLUTION_END_PARSE_ZONE = "Global";

	static constexpr const int SOLUTION_PROJ_NAME_POS = 3;
	static constexpr const int SOLUTION_PROJ_PATH_POS = 5;
	static constexpr const int SOLUTION_PROJ_UUID_POS = 7;
	static constexpr const int SOLUTION_PROJ_DEP_POS = 2;


	static VsMakeErrorCode parseSolutionFile (std::ifstream  &ifs, Solution & solution);

	static void cleanSolutionUuid (std::string & uuid);
	static int parseSolutionFormatVersion (std::string & versionLine);

public:
	static VsMakeErrorCode loadSolution (const char *solutionPath, Solution & solution);

};

#endif //_VSMAKE_SOLUTION_LOADER_H_
