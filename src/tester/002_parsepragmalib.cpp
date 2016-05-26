/*********************************************************************************************
 *	Name        : 002_parsepragmalib.cpp
 *  Copyright	(C) 2016 Ignacio Pomar Ballestero
 *  License     : MIT License (see LICENSE.txt)
 *  Description : Unit test to check the pragmalib directive resolutiosn
 ********************************************************************************************/
#define protected public

#include <algorithm>
#include <boost/test/unit_test.hpp>

#include "parsepragmalib.h"



BOOST_AUTO_TEST_CASE (parsePragmalib)
{

	//First case: without defines
	{
		ParsePragmaLibTester parser;
		std::vector <std::string> &pragmalibs = parser.pd->pragmaLibs;
		
		int retVal = parser.parseFile ("../testdata/examplepragmalib.h");
		BOOST_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "always.lib")  != pragmalibs.end() );
		BOOST_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "invalid.lib") == pragmalibs.end() );

		BOOST_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "./std/lib/release/library1r.lib")  != pragmalibs.end() );
	}
	
	//Second case: using _DEBUG
	{
		ParsePragmaLibTester parser;
		std::vector <std::string> &pragmalibs = parser.pd->pragmaLibs;
		
		parser.addDefine ("_DEBUG", "");
		int retVal = parser.parseFile ("../testdata/examplepragmalib.h");
		
		BOOST_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "always.lib")  != pragmalibs.end() );
		BOOST_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "invalid.lib") == pragmalibs.end() );

		BOOST_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "./std/lib/debug/library1d.lib")  != pragmalibs.end() );
		BOOST_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "./std/lib/debug/library3d.lib")  != pragmalibs.end() );
	}

	//Lastly: using _DEBUG and _CUSTOM
	{
		ParsePragmaLibTester parser;
		std::vector <std::string> &pragmalibs = parser.pd->pragmaLibs;
		
		parser.addDefine ("_DEBUG", "");
		parser.addDefine ("_CUSTOM", "");
		int retVal = parser.parseFile ("../testdata/examplepragmalib.h");
		
		BOOST_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "always.lib")  != pragmalibs.end() );
		BOOST_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "invalid.lib") == pragmalibs.end() );
		BOOST_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "custom_debug.lib")  != pragmalibs.end() );

		BOOST_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "./custom/lib/debug/library1d.lib")  != pragmalibs.end() );
		BOOST_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "./custom/lib/debug/library3d.lib")  != pragmalibs.end() );
		
	}
	
}