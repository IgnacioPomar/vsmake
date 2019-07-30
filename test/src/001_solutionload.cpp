/*********************************************************************************************
 *	Name        : 001_solutionload.cpp
 *  Description : Unit test to check the correct load of the solution
 ********************************************************************************************/


#include <TinyCppUnit/TinyCppUnit.h>
#include "vsmake.h"
#include "project.h"

 //Access the private data of the classes
#include "solution_privatedata.h"
#include "project_privatedata.h"


#include "strCollector.h"


UNIT_TEST_CASE (solutionLoad)
{
	Solution sol;

	UNIT_CHECK (sol.loadSolution ("../inexistent_solution.sln") == VSMAKE_SOLUTION_FILE_NOT_FOUND);
	UNIT_CHECK (sol.loadSolution ("../include/vsmake.h") == VSMAKE_SOLUTION_FILE_BAD_FORMAT);
	UNIT_CHECK (sol.loadSolution ("../vsmake.sln") == VSMAKE_ALL_OK);

	//Check the loaded data
	UNIT_CHECK (sol.getNumberOfProjects () == 3);

	Project * pjVsmake = sol.getProject ("vsmake");
	Project * pjLibvsmake = sol.getProject ("libvsmake");


	const char * projId = pjLibvsmake->getId ();
	StrCollector dependencies;
	pjVsmake->dbgGetDependencies (&dependencies);

	//Check project data from the solution
	UNIT_CHECK (dependencies.contains (projId));


	//TODO: Check the project data




	//pj->clear();

	//BOOST_CHECK_EQUAL (pj.pd, NULL);

}
