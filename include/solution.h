/*********************************************************************************************
 *	Name		: solution.cpp
 *	Description	: 
 ********************************************************************************************/

#pragma once
#ifndef _SOLUTION_H_
#define _SOLUTION_H_


#include <string>

#include "vsmake_cfg.h"
#include "vsmake_constants.h"


//PIMPL clases
class Solution_PrivateData; 
class Project;

class VSMAKE_API Solution
{
	friend class SolutionLoader;
public:
	Solution ();
	Solution (const Solution &solution);
	~Solution ();

	VsMakeErrorCode loadSolution (char * solutionFile);
	int getNumberOfProjects ();
	Project* getProject (int projectIdx);
	Project* getProject (char *  projectName);
protected:
	Solution_PrivateData * pd;
private:
	int solutionFormatVersion;
};

#endif //_SOLUTION_H_

