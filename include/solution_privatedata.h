/*********************************************************************************************
 *	Name		: solution_privatedata.h
 *	Description	: Class to opaque pointer to store the Solution's private data
 ********************************************************************************************/


#pragma once
#ifndef _SOLUTION_PRIVATEDATA_H_
#define _SOLUTION_PRIVATEDATA_H_

#include <vector>
#include <string>
#include "vsmake_cfg.h"
#include "project.h"


class VSMAKE_LOCAL Solution_PrivateData
{
public:
	std::string solutionPath;
	std::vector <Project> projects;
};

#endif //_SOLUTION_PRIVATEDATA_H_
