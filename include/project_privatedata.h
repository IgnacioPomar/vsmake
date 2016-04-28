/*********************************************************************************************
 *	Name		: project_privatedata.h
 *	Description	: Class to opaque pointer to store the Project's private data 
 *  License     : MIT License (see LICENSE.txt)
 *	Copyright	(C) 2016 Ignacio Pomar Ballestero
 ********************************************************************************************/

#include <list>
#include "vsmake_cfg.h"


class VSMAKE_LOCAL Project_PrivateData
{
public:
	std::string projectPath;
	std::list <std::string> dependencies;
};

