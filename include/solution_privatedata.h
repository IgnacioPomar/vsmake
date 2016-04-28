/*********************************************************************************************
 *	Name		: solution_privatedata.h
 *	Description	: Class to opaque pointer to store the Solution's private data 
 *  License     : MIT License (see LICENSE.txt)
 *	Copyright	(C) 2016 Ignacio Pomar Ballestero
 ********************************************************************************************/

#include <list>
#include "vsmake_cfg.h"
#include "project.h"


class VSMAKE_LOCAL Solution_PrivateData
{
public:
	std::string solotionPath;
	std::list <Project> proyectos;
};

