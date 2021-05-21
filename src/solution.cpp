/*********************************************************************************************
 *	Name		: solution.cpp
 *	Description	:
 ********************************************************************************************/

#include "solution.h"
#include "solution_privatedata.h"
#include "project_privatedata.h"
#include "solutionLoader.h"


 /***********************************************************************************************
  * Default constructor. Set the PIMPL memory
  ***********************************************************************************************/
Solution::Solution ()
{
	this->solutionFormatVersion = 0;
	this->pd = new Solution_PrivateData ();
}

/***********************************************************************************************
 * Copy constructor. Copy the PIMPL memory
 ***********************************************************************************************/
Solution::Solution (const Solution &solution)
{
	*this = solution;
	this->pd = new Solution_PrivateData (*solution.pd);
}

/***********************************************************************************************
 * Destructor.
 ***********************************************************************************************/
Solution::~Solution ()
{
	delete this->pd;
}


/***********************************************************************************************
 * Loads the solution from file
 * \param    [in]   solutionFile       Solution's file
 * \return VSMAKE_ALL_OK if the solution was loaded, or the error code if not
 ***********************************************************************************************/
VsMakeErrorCode Solution::loadSolution (const char * solutionFile)
{
	return SolutionLoader::loadSolution (solutionFile, *this);
}

/***********************************************************************************************
 * Returns the numbre of projects in this solution
 * \return number of projects
 ***********************************************************************************************/
int Solution::getNumberOfProjects ()
{
	return (int)this->pd->projects.size ();
}

/***********************************************************************************************
 * Get the project in the index position
 * \param    [in]   projectIdx       Project index position
 * \return Pointer to the project
 ***********************************************************************************************/
Project* Solution::getProject (int projectIdx)
{
	return &this->pd->projects[projectIdx];
}


/***********************************************************************************************
 * Get the project wich matchs the name
 * \param    [in]   projectIdx       Project name
 * \return Pointer to the project
 ***********************************************************************************************/
Project* Solution::getProject (const char *  projectName)
{
	Project* pj = NULL;
	std::vector<Project>::iterator it;

	for (it = this->pd->projects.begin (); it < this->pd->projects.end (); it++)
	{
		if (it->pd->projectName == projectName)
		{
			pj = &(*it);
			break;
		}
	}

	return pj;
}

/**
* Loads all the projects inside the solution
*/
VsMakeErrorCode Solution::loadProjects ()
{
	for (Project &pj : this->pd->projects)
	{
		VsMakeErrorCode ret = pj.loadProject ();
		if (ret != VSMAKE_ALL_OK)
		{
			return ret;
		}
	}

	return VSMAKE_ALL_OK;
}
