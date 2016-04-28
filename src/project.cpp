/*********************************************************************************************
 *	Name		: project.cpp
 *	Description	: 
 *  License     : MIT License (see LICENSE.txt)
 *	Copyright	(C) 2016 Ignacio Pomar Ballestero
 ********************************************************************************************/



#include "project.h"
#include "project_privatedata.h"


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


