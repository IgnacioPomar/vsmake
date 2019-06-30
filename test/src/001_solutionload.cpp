/*********************************************************************************************
 *	Name        : 001_solutionload.cpp
 *  Description : Unit test to check the correct load of the solution
 ********************************************************************************************/

#define protected public

#include <boost/test/unit_test.hpp>
#include "vsmake.h"
#include "project.h"

//Access the private data of the classes
#include "solution_privatedata.h"
#include "project_privatedata.h"



BOOST_AUTO_TEST_CASE (solutionLoad)
{
	Solution sol;
	

	BOOST_CHECK_EQUAL (sol.loadSolution("../inexistent_solution.sln"), VSMAKE_SOLUTION_FILE_NOT_FOUND);
	BOOST_CHECK_EQUAL (sol.loadSolution("../include/vsmake.h"),        VSMAKE_SOLUTION_FILE_BAD_FORMAT);
	BOOST_CHECK_EQUAL (sol.loadSolution("../vsmake.sln"),              VSMAKE_ALL_OK);

	//Check the loaded data
	BOOST_CHECK_EQUAL (sol.getNumberOfProjects(), 3);

	Project * pjVsmake    = sol.getProject ("vsmake");
	Project * pjLibvsmake = sol.getProject ("libvsmake");

	//Check project data from the solution
	BOOST_CHECK (pjLibvsmake->pd->projectId == std::string("6D4E6593-45E1-44A8-B568-450BD4CAE52A"));
	BOOST_CHECK (pjLibvsmake->pd->projectId == pjVsmake->pd->dependencies.front());


	//TODO: Check the project data
	




	//pj->clear();

	//BOOST_CHECK_EQUAL (pj.pd, NULL);
	
}