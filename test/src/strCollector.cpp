/********************************************************************
 * Name        : strCollector.cpp
 * Description : Implementation of the DbgHelper for the unit tests
 ********************************************************************/

#include "strCollector.h"




void StrCollector::putStr (const char * lib)
{
	strCollection.push_back (lib);
}

bool StrCollector::contains (const char * lib)
{
	return std::find (strCollection.begin (), strCollection.end (), lib) != strCollection.end ();
}
