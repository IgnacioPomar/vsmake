/*********************************************************************************************
 *	Name        : system.cpp
 *  Description : Calls to the system
 ********************************************************************************************/

#include <sstream> 
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "system.h"

#ifdef WIN32
#define popen _popen
#define pclose _pclose
#endif

#define BUFF_SIZE   256

#ifdef WIN32
#define OPEN_ATTRS	"rt"
#else
#define OPEN_ATTRS	"r"
#endif

 //Just to pimpl std::string
class VSMAKE_LOCAL SystemCallData
{
public:
	std::string commandLine;
	std::string txtReturned;
	int retVal;
};

//constructor, only pimpl
SystemCall::SystemCall ()
{
	this->pd = new SystemCallData ();
}

//destructor, only pimpl
SystemCall::~SystemCall ()
{
	delete this->pd;
}


/***********************************************************************************************
 * checks if there was a warning
 * \return  Returns true if there is any warning. false if it was error or if no error nor warning
 ***********************************************************************************************/
bool SystemCall::isGccWarning ()
{
	return ((pd->retVal == 0) && (pd->txtReturned.size () != 0));
}


/***********************************************************************************************
 * checks if there was a error
 * \return  Returns 1 if there is any error, else 0
 ***********************************************************************************************/
bool SystemCall::isGccError ()
{
	return (pd->retVal != 0);
}


/***********************************************************************************************
 * opens a process creating a pipe, and storing in the class the results
 * \param    [in]   command   Command to be executed.
 * \return  Returns the exit status of the terminating command, or –1 if an error occurs.
 ***********************************************************************************************/
int SystemCall::exec (const char * command)
{
	char   buffer [BUFF_SIZE];
	FILE   *pipe;
	std::ostringstream outBuffer;

	pd->commandLine = command;
	pd->txtReturned.empty (); //if we are reusing...

	if ((pipe = popen (command, OPEN_ATTRS)) == NULL)
	{
		return pd->retVal = -1;
	}


	while (fgets (buffer, BUFF_SIZE, pipe))
	{
		outBuffer << buffer << std::endl;
	}

	pd->txtReturned = outBuffer.str ();

	if (feof (pipe))
	{
		return pd->retVal = pclose (pipe);
	}
	else
	{
		return pd->retVal = -1;
	}

}


//returns the last command line used
const char * SystemCall::getCommandLine ()
{
	return pd->commandLine.c_str ();
}

//returns the last message returned by a system call
const char * SystemCall::getMessage ()
{
	return pd->txtReturned.c_str ();
}
