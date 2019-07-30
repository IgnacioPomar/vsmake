/*********************************************************************************************
 *	Name        : system.h
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
