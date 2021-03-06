﻿/*********************************************************************************************
 *	Name        : 003_displaytest.cpp
 *  Description : this will test the console output
 ********************************************************************************************/

#define  _CRT_SECURE_NO_WARNINGS //To avoid warning with standar

 //As long as this test will be visual, we will disable oce tested

#ifdef WIN32
#include <Windows.h>
#define SLEEP_TIME	100
#else
#include <unistd.h>
#define SLEEP_TIME	1000
#define Sleep usleep
#endif

#include <stdio.h>
#include <TinyCppUnit/TinyCppUnit.h>
#include "progressInfo.h"


static constexpr int NUMBER_OF_TEST_PROJECT_FILES = 100;
static constexpr int TEST_ERROR_GENERATED = 26;


UNIT_TEST_CASE (displaytest)
{
	int i;
	DisplayProgressIndicator display;

	//First we will test without data
	display.printProgress ();
	display.printErrorMessage ("Error without info");

	//now we fill the file part
	display.progressInfo.sourceFileName = "xxx_xxxxtest.cpp";
	display.progressInfo.sourceFiles.count = 20;
	display.progressInfo.sourceFiles.id = 15;
	display.printProgress ();

	//now the project data
	display.progressInfo.projectName = "libvsmake";
	display.progressInfo.projects.count = 3;
	display.progressInfo.projects.id = 1;
	display.printProgress ();

	//finally the solution data
	display.progressInfo.solutionName = "vsmake";
	display.progressInfo.solutions.count = 300;
	display.progressInfo.solutions.id = 22;
	display.printProgress ();

	//and at least, we test the progress in a "real" case
	display.progressInfo.sourceFiles.count = NUMBER_OF_TEST_PROJECT_FILES;
	for (i = 0; i <= NUMBER_OF_TEST_PROJECT_FILES; i++)
	{
		char filename [50];
		sprintf (filename, "src_sol_%d.cpp", i);

		display.progressInfo.sourceFiles.id = i;
		display.progressInfo.sourceFileName = filename;

		if (0 == i % TEST_ERROR_GENERATED)
		{
			char errorDescription [80];
			sprintf (errorDescription, "Error with carrier return\nin file ===> %s", filename);
			display.printErrorMessage (errorDescription);
		}
		else
		{
			display.printProgress ();
		}

		Sleep (SLEEP_TIME);
	}

}
