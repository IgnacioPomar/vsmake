/*********************************************************************************************
 *	Name		: project.h
 *	Description	: 
 *  License     : MIT License (see LICENSE.txt)
 *	Copyright	(C) 2016 Ignacio Pomar Ballestero
 ********************************************************************************************/


#include "vsmake_cfg.h"

class Project_PrivateData; //PIMPL 

class VSMAKE_API Project
{
public:
	Project ();
	Project (const Project & project);
	~Project();
private:
	Project_PrivateData * pd;
};

