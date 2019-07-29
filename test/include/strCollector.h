/********************************************************************
 * Name        : strCollector.h
 * Description : Implementation of the DbgHelper for the unit tests
 ********************************************************************/



#pragma once
#ifndef _STR_COLLECTOR_H_
#define _STR_COLLECTOR_H_

#include <vector>
#include "dbgHelper.h"

class StrCollector : public DbgHelper
{
public:
	std::vector <std::string> strCollection;
	void putStr (const char * str);
	bool contains (const char * str);

};

#endif //_DBG_HELPER_H_