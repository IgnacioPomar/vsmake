/*********************************************************************************************
 *	Name		: project_privatedata.h
 *	Description	: Class to opaque pointer to store the Project's private data 
 ********************************************************************************************/

#pragma once
#ifndef _PROJECT_PRIVATEDATA_H_
#define _PROJECT_PRIVATEDATA_H_


#include <list>
#include <string>
#include "vsmake_cfg.h"


class VSMAKE_LOCAL Project_PrivateData
{
public:
	std::string projectPath;
	std::string projectId;
	std::string projectName;
	std::list <std::string> dependencies;
};

#endif  //_PROJECT_PRIVATEDATA_H_