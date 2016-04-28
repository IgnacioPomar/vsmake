/*********************************************************************************************
 *	Name		: solution.cpp
 *	Description	: 
 *  License     : MIT License (see LICENSE.txt)
 *	Copyright	(C) 2016 Ignacio Pomar Ballestero
 ********************************************************************************************/


#include <string>

#include "vsmake_cfg.h"
#include "vsmake_constants.h"


//PIMPL clases
class Solution_PrivateData; 


class VSMAKE_API Solution
{
	friend class SolutionLoader;
public:
	Solution ();
	Solution (const Solution &solution);
	~Solution ();

	VsMakeErrorCode loadSolution (char * solutionFile);
protected:
	Solution_PrivateData * pd;

private:
	int solutionFormatVersion;
};

