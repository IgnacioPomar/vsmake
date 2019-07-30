/*********************************************************************************************
 *	Name		: project.h
 *	Description	:
 ********************************************************************************************/

#pragma once
#ifndef _PROJECT_H_
#define _PROJECT_H_

#include "vsmake_cfg.h"
#include "vsmake_constants.h"

 //Forward declaration
class DbgHelper;

//PIMPL 
class Project_PrivateData;

class VSMAKE_API Project
{
	friend class SolutionLoader;
	friend class Solution;
public:
	Project ();
	Project (const Project & project);
	~Project ();

	void clear ();
	void setProjectNameAndPath (const char * projectName, const char * projectPath, const char * projectId, const char * solutionPath);
	VsMakeErrorCode loadProject ();

	//function to use in the unit tests
	const char * getId ();
	void dbgGetDependencies (DbgHelper * dbgHelper);

protected:
	Project_PrivateData * pd;
};

#endif //_PROJECT_H_
