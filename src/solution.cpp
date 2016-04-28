/*********************************************************************************************
 *	Name		: solution.cpp
 *	Description	: 
 *  License     : MIT License (see LICENSE.txt)
 *	Copyright	(C) 2016 Ignacio Pomar Ballestero
 ********************************************************************************************/



#include "solution.h"
#include "solution_privatedata.h"
#include "solutionLoader.h"


VsMakeErrorCode Solution::loadSolution (char * solutionFile)
{
	return SolutionLoader::loadSolution (solutionFile, *this);
}



Solution::Solution ()
{
	this->solutionFormatVersion = 0;
	this->pd = new Solution_PrivateData ();
}

Solution::Solution (const Solution &solution)
{
	*this = solution;
	this->pd = new Solution_PrivateData (*solution.pd);
}

Solution::~Solution ()
{
	delete this->pd;
}

