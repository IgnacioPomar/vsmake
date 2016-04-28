/*********************************************************************************************
 *	Name        : 001_solutionload.cpp
 *  Copyright	(C) 2016 Ignacio Pomar Ballestero
 *  License     : MIT License (see LICENSE.txt)
 *  Description : Unit test to check the correct load of the solution
 ********************************************************************************************/


#include <boost/test/unit_test.hpp>
#include "vsmake.h"

BOOST_AUTO_TEST_CASE (solutionLoad)
{
	Solution sol;
	

	BOOST_CHECK_EQUAL (sol.loadSolution("../inexistent_solution.sln"), VSMAKE_SOLUTION_FILE_NOT_FOUND);
	BOOST_CHECK_EQUAL (sol.loadSolution("../include/vsmake.h"), VSMAKE_SOLUTION_FILE_BAD_FORMAT);
	BOOST_CHECK_EQUAL (sol.loadSolution("../vsmake.sln"), VSMAKE_ALL_OK);

}