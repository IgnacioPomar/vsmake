﻿/********************************************************************
 * Name        : progressInfo.h
 * Description : show in console the progress status
 ********************************************************************/

#include "vsmake_cfg.h"

class VSMAKE_API Status
{
public:
	Status ();
	int count; //Number of Elements
	int id;    //current element
};


class VSMAKE_API ProgressInfo
{
public:
	//If we are calling vsmake inside a multiple solution envoirement...
	Status solutions;

	//To iterate in operations witout status
	char iterateChar;

	//ProgressInfo over vsmake
	const char * solutionName;
	Status projects;

	const char * projectName;
	Status sourceFiles;

	const char * sourceFileName;

	ProgressInfo ();

};


class VSMAKE_API DisplayProgressIndicator
{
private:
	int getScreenWidth (void);
	char getIterateChar (void);
public:
	ProgressInfo progressInfo;
	void printErrorMessage (const char * message);
	void printProgress (void);
};
