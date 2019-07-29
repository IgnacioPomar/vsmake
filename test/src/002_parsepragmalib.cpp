/*********************************************************************************************
 *	Name        : 002_parsepragmalib.cpp
 *  Description : Unit test to check the pragmalib directive resolutiosn
 ********************************************************************************************/

#include <algorithm>
#include <TinyCppUnit/TinyCppUnit.h>

#include "parsepragmalib.h"

#include "strCollector.h"

#define EXAMPLE_PRAGMAFILE "../test/data/examplepragmalib.h"

UNIT_TEST_CASE (parsePragmalib)
{

	//First case: without defines
	{
		ParsePragmaLibTester parser;
		StrCollector pragmas;
		
		UNIT_REQUIRE (0 == parser.parseFile (EXAMPLE_PRAGMAFILE));
		parser.dbgGetLibs (&pragmas);

		UNIT_CHECK (pragmas.contains ("always.lib"));
		UNIT_CHECK (!pragmas.contains ("invalid.lib"));

		UNIT_CHECK (pragmas.contains ("./std/lib/release/library1r.lib"));
	}
	
	//Second case: using _DEBUG
	{
		ParsePragmaLibTester parser;
		StrCollector pragmas;
		
		parser.addDefine ("_DEBUG", "");
		UNIT_REQUIRE (0 == parser.parseFile (EXAMPLE_PRAGMAFILE));
		parser.dbgGetLibs (&pragmas);
		
		UNIT_CHECK (pragmas.contains ("always.lib"));
		UNIT_CHECK (!pragmas.contains ("invalid.lib"));

		UNIT_CHECK (pragmas.contains ("./std/lib/debug/library1d.lib"));
		UNIT_CHECK (pragmas.contains ("./std/lib/debug/library3d.lib"));
	}

	//Lastly: using _DEBUG and _CUSTOM
	{
		ParsePragmaLibTester parser;
		StrCollector pragmas;
		
		parser.addDefine ("_DEBUG", "");
		parser.addDefine ("_CUSTOM", "");
		UNIT_REQUIRE (0 == parser.parseFile (EXAMPLE_PRAGMAFILE));
		parser.dbgGetLibs (&pragmas);
		
		UNIT_CHECK (pragmas.contains ("always.lib"));
		UNIT_CHECK (!pragmas.contains ("invalid.lib"));
		UNIT_CHECK (pragmas.contains ("custom_debug.lib")  );

		UNIT_CHECK (pragmas.contains ("./custom/lib/debug/library1d.lib"));
		UNIT_CHECK (pragmas.contains ("./custom/lib/debug/library3d.lib"));
		
	}
	
}