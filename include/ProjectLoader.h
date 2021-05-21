/*********************************************************************************************
 *	Name		: projectLoader.h
 *	Description	: Loads the project file to memory
 ********************************************************************************************/


#pragma once
#ifndef _VSMAKE_PROJECT_LOADER_H_
#define _VSMAKE_PROJECT_LOADER_H_

#include "vsmake_cfg.h"
#include "vsmake_constants.h"

class Project_PrivateData;

// Evitamos incluir cabeceras de libxml2
struct _xmlTextReader;
typedef struct _xmlTextReader xmlTextReader;
typedef xmlTextReader* xmlTextReaderPtr;



class VSMAKE_LOCAL ProjectLoader
{
private:
	static std::string getConfNameFromConfition (const char * condition);
public:
	static VsMakeErrorCode loadProject (Project_PrivateData & project);
};

#endif //_VSMAKE_PROJECT_LOADER_H_
