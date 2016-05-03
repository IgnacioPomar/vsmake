/*********************************************************************************************
 *	Name		: project.cpp
 *	Description	: 
 *  License     : MIT License (see LICENSE.txt)
 *	Copyright	(C) 2016 Ignacio Pomar Ballestero
 ********************************************************************************************/



#include "project.h"
#include "project_privatedata.h"
#include "solutionLoader.h"


#define WIN_SLASH	'\\'


Project::Project ()
{
	this->pd = new Project_PrivateData ();
}

Project::Project (const Project & project)
{
	*this = project;
	this->pd = new Project_PrivateData (*project.pd);
}


Project::~Project()
{
	delete this->pd;
}



void Project::clear ()
{
	//TODO: delete the project specific data
	this->pd->projectName.clear ();
	this->pd->projectPath.clear ();
	this->pd->projectId.clear ();
	this->pd->dependencies.clear ();
}

void Project::setProjectNameAndPath (const char * projectName, const char * projectPath, const char * projectId, const char * solutionPath)
{
	this->pd->projectName = projectName;
	this->pd->projectId = projectId;
	this->pd->projectPath = solutionPath;

	//TODO: When using C++11, we will use the back member function
	if (!this->pd->projectPath.empty())
	{
		char lastChar = *this->pd->projectPath.rbegin();
		if (lastChar != WIN_SLASH)
		{
			this->pd->projectPath.push_back (WIN_SLASH);
		}
	}

	this->pd->projectPath.append (projectPath);
}


VsMakeErrorCode Project::loadProject ()
{
	return SolutionLoader::loadProject (this->pd->projectPath.c_str(), *this);
	//return VSMAKE_NOT_IMPLEMENTED;
}


