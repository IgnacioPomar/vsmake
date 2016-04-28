/*********************************************************************************************
 *	Name		: main.cpp
 *	Description	: Parse the command line parameters to work the same way than MSBuild.exe for Visual Studio
 *  License     : MIT License (see LICENSE.txt)
 *  Copyright	(C) 2016 Ignacio Pomar Ballestero
 ********************************************************************************************/




//Documentation about MSBuild.exe
// https://msdn.microsoft.com/es-es/library/ms164311.aspx

/*
 * Command that shoudl work in the first version:
 *	/nologo
 *	/vervosity
	/m
	/consoleloggerparameters
	/property

 */


#include <stdio.h>

#ifdef _DEBUG 
	#define END_LIB_STD "d.lib"
#else
	#define END_LIB_STD ".lib"
#endif


// Libraries the project needs
#pragma comment(lib, "libvsmake" END_LIB_STD)



int main (int argc, char * argv []) 
{
	return 1;
}