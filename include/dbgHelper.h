/********************************************************************
 * Name        : dbgHelper.h
 * Description : Pure Abstract Class to help the unit test
 ********************************************************************/


#pragma once
#ifndef _DBG_HELPER_H_
#define _DBG_HELPER_H_

class DbgHelper
{
public:
	virtual void putStr (const char *) = 0;
};

#endif //_DBG_HELPER_H_
