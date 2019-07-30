/*********************************************************************************************
 *	Name		: main.cpp
 *	Description	: Parse the command line parameters to work the same way than MSBuild.exe for Visual Studio
 ********************************************************************************************/


#ifdef _DEBUG 
#define END_LIB_STD "d.lib"
#else
#define END_LIB_STD ".lib"
#endif


#ifdef WIN32
 // Libraries the project needs
#pragma comment(lib, "libvsmake" END_LIB_STD)
#endif

#include <stdio.h>


int main (int argc, char * argv [])
{



	return 1;
}
