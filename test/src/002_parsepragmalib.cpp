/*********************************************************************************************
 *	Name        : 002_parsepragmalib.cpp
 *  Description : Unit test to check the pragmalib directive resolutiosn
 ********************************************************************************************/

#include <algorithm>
#include <TinyCppUnit/TinyCppUnit.h>

#include "dbgHelper.h"
#include "parsepragmalib.h"


class vPragmas : public DbgHelper
{
public:
	std::vector <std::string> pragmalibs;
	void putStr (const char * lib);
	bool checkContains (const char * lib);

};

void vPragmas::putStr (const char * lib)
{
	pragmalibs.push_back (lib);
}

bool vPragmas::checkContains (const char * lib)
{
	return std::find (pragmalibs.begin (), pragmalibs.end (),lib) != pragmalibs.end ();
}


UNIT_TEST_CASE (parsePragmalib)
{

	//First case: without defines
	{
		ParsePragmaLibTester parser;
		vPragmas pragmas;
		
		UNIT_REQUIRE (0 == parser.parseFile ("../testdata/examplepragmalib.h"));
		parser.dbgGetLibs (&pragmas);

		UNIT_CHECK (pragmas.checkContains("always.lib"));
		UNIT_CHECK (!pragmas.checkContains ("invalid.lib"));

		UNIT_CHECK (pragmas.checkContains ("./std/lib/release/library1r.lib"));
	}
	
	//Second case: using _DEBUG
	{
		ParsePragmaLibTester parser;
		vPragmas pragmas;
		
		parser.addDefine ("_DEBUG", "");
		UNIT_REQUIRE (0 == parser.parseFile ("../testdata/examplepragmalib.h"));
		parser.dbgGetLibs (&pragmas);
		
		UNIT_CHECK (pragmas.checkContains ("always.lib"));
		UNIT_CHECK (!pragmas.checkContains ("invalid.lib"));

		UNIT_CHECK (pragmas.checkContains ("./std/lib/debug/library1d.lib"));
		UNIT_CHECK (pragmas.checkContains ("./std/lib/debug/library3d.lib"));
	}

	//Lastly: using _DEBUG and _CUSTOM
	{
		ParsePragmaLibTester parser;
		vPragmas pragmas;
		
		parser.addDefine ("_DEBUG", "");
		parser.addDefine ("_CUSTOM", "");
		UNIT_REQUIRE (0 == parser.parseFile ("../testdata/examplepragmalib.h"));
		parser.dbgGetLibs (&pragmas);
		
		UNIT_CHECK (pragmas.checkContains ("always.lib"));
		UNIT_CHECK (!pragmas.checkContains ("invalid.lib"));
		UNIT_CHECK (pragmas.checkContains ("custom_debug.lib")  );

		UNIT_CHECK (pragmas.checkContains ("./custom/lib/debug/library1d.lib"));
		UNIT_CHECK (pragmas.checkContains ("./custom/lib/debug/library3d.lib"));
		
	}
	
}