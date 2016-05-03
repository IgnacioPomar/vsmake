/*********************************************************************************************
 *	Name		: solutionLoader.cpp
 *	Description	: Loads the solution file to memory
 *  License     : MIT License (see LICENSE.txt)
 *	Copyright	(C) 2016 Ignacio Pomar Ballestero
 ********************************************************************************************/


#pragma once
#ifndef _VSMAKE_SOLUTION_LOADER_H_
#define _VSMAKE_SOLUTION_LOADER_H_


#include "vsmake_cfg.h"
#include "vsmake_constants.h"

//PIMPL classes
class Solution;
class Project;


// Evitamos incluir cabeceras de libxml2
struct _xmlTextReader;
typedef struct _xmlTextReader xmlTextReader;
typedef xmlTextReader* xmlTextReaderPtr;


class VSMAKE_LOCAL SolutionLoader
{
private:
	static VsMakeErrorCode parseSolutionFile (FILE * solutionFile, Solution & solution);
public:
	static VsMakeErrorCode loadSolution (const char *solutionPath, Solution & solution);
	static VsMakeErrorCode loadProject  (const char *projectPath, Project & project);
};

#endif //_VSMAKE_SOLUTION_LOADER_H_

