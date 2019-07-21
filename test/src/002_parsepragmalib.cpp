/*********************************************************************************************
 *	Name        : 002_parsepragmalib.cpp
 *  Description : Unit test to check the pragmalib directive resolutiosn
 ********************************************************************************************/

#include <algorithm>
#include <TinyCppUnit/TinyCppUnit.h>

#include "parsepragmalib.h"



UNIT_TEST_CASE (parsePragmalib)
{

	//First case: without defines
	{
		ParsePragmaLibTester parser;
		std::vector <std::string> &pragmalibs = parser.pd->pragmaLibs;
		
		int retVal = parser.parseFile ("../testdata/examplepragmalib.h");
		UNIT_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "always.lib")  != pragmalibs.end() );
		UNIT_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "invalid.lib") == pragmalibs.end() );

		UNIT_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "./std/lib/release/library1r.lib")  != pragmalibs.end() );
	}
	
	//Second case: using _DEBUG
	{
		ParsePragmaLibTester parser;
		std::vector <std::string> &pragmalibs = parser.pd->pragmaLibs;
		
		parser.addDefine ("_DEBUG", "");
		int retVal = parser.parseFile ("../testdata/examplepragmalib.h");
		
		UNIT_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "always.lib")  != pragmalibs.end() );
		UNIT_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "invalid.lib") == pragmalibs.end() );

		UNIT_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "./std/lib/debug/library1d.lib")  != pragmalibs.end() );
		UNIT_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "./std/lib/debug/library3d.lib")  != pragmalibs.end() );
	}

	//Lastly: using _DEBUG and _CUSTOM
	{
		ParsePragmaLibTester parser;
		std::vector <std::string> &pragmalibs = parser.pd->pragmaLibs;
		
		parser.addDefine ("_DEBUG", "");
		parser.addDefine ("_CUSTOM", "");
		int retVal = parser.parseFile ("../testdata/examplepragmalib.h");
		
		UNIT_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "always.lib")  != pragmalibs.end() );
		UNIT_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "invalid.lib") == pragmalibs.end() );
		UNIT_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "custom_debug.lib")  != pragmalibs.end() );

		UNIT_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "./custom/lib/debug/library1d.lib")  != pragmalibs.end() );
		UNIT_CHECK (std::find(pragmalibs.begin(), pragmalibs.end(), "./custom/lib/debug/library3d.lib")  != pragmalibs.end() );
		
	}
	
}