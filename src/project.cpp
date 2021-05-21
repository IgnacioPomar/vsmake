/*********************************************************************************************
 *	Name		: project.cpp
 *	Description	:
 ********************************************************************************************/


#include "utils.h"
#include "project.h"
#include "project_privatedata.h"
#include "ProjectLoader.h"







Project::Project (const char * projectName, const char * projectPath, const char * projectId, const char * solutionPath)
{
	this->pd = new Project_PrivateData ();
	this->setProjectNameAndPath (projectName, projectPath, projectId, solutionPath);
}

Project::Project (const Project & project)
{
	*this = project;
	this->pd = new Project_PrivateData (*project.pd);
}


Project::~Project ()
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
	this->pd->projectName = (projectName == nullptr) ? "" : projectName;
	this->pd->projectId = (projectId == nullptr) ? "" : projectId;

	const char * tmpProjectPath = (projectPath == nullptr) ? "" : projectPath;


	if (hasAbsolutePath (tmpProjectPath))
	{
		setFilePath (tmpProjectPath, this->pd->projectPath);
		this->pd->projectFile = tmpProjectPath;
	}
	else
	{
		std::string tmpPath = (solutionPath == nullptr) ? "" : solutionPath;
		tmpPath.append (tmpProjectPath);

		this->pd->projectFile = tmpPath;
		setFilePath (tmpPath.c_str (), this->pd->projectPath);
	}
}


VsMakeErrorCode Project::loadProject ()
{
	return ProjectLoader::loadProject (*this->pd);
}


//-------------------------- TEST SECTION -------------------------
#include "dbgHelper.h"

/**
 * DEBUG: for unit test use
 * retrieves the project ID
 * \param [in]   dbgHelper  listener class
 */
const char * Project::getId ()
{
	return pd->projectId.c_str ();
}


/**
 * DEBUG: for unit test use
 * Send all the dependencies
 *
 * \param [in]   dbgHelper  listener class
 */
void Project::dbgGetDependencies (DbgHelper * dbgHelper)
{

	for (const std::string &str : this->pd->dependencies)
	{
		dbgHelper->putStr (str.c_str ());
	}
}
