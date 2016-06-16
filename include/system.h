/*********************************************************************************************
 *	Name        : system.h
 *  Copyright	(C) 2016 Ignacio Pomar Ballestero
 *  License     : MIT License (see LICENSE.txt)
 *  Description : Calls to the system
 ********************************************************************************************/

#include "vsmake_cfg.h"

class SystemCallData;

class VSMAKE_API SystemCall
{
private:
	SystemCallData * pd;
public:
	SystemCall ();
	~SystemCall ();

	int exec (const char * command);
	bool isGccWarning ();
	bool isGccError ();
	const char * getCommandLine ();
	const char * getMessage ();
};