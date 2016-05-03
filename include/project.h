/*********************************************************************************************
 *	Name		: project.h
 *	Description	: 
 *  License     : MIT License (see LICENSE.txt)
 *	Copyright	(C) 2016 Ignacio Pomar Ballestero
 ********************************************************************************************/

#pragma once
#ifndef _PROJECT_H_
#define _PROJECT_H_

#include "vsmake_cfg.h"
#include "vsmake_constants.h"



class Project_PrivateData; //PIMPL 

class VSMAKE_API Project
{
	friend class SolutionLoader;
public:
	Project ();
	Project (const Project & project);
	~Project();

	void clear ();
	void setProjectNameAndPath (const char * projectName, const char * projectPath, const char * projectId, const char * solutionPath);
	VsMakeErrorCode loadProject ();
protected:
	Project_PrivateData * pd;
};

#endif //_PROJECT_H_