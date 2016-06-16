/********************************************************************
 * Name        : progressInfo.h
 * Copyright	(C) 2016 Ignacio Pomar Ballestero
 * License     : MIT License (see LICENSE.txt)
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
	char * solutionName;
	Status projects;

	char * projectName;
	Status sourceFiles;

	char * sourceFileName;

	ProgressInfo ();

};


class VSMAKE_API DisplayProgressIndicator
{
private:
	int getScreenWidth (void);
	char getIterateChar (void);
public:
	ProgressInfo progressInfo;
	void printErrorMessage (char * message);
	void printProgress (void);
};