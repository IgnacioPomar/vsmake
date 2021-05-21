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
namespace tinyxml2
{
	class XMLElement;
}


/**
 *	\see	//https://docs.microsoft.com/en-us/cpp/build/reference/vcxproj-file-structure?view=msvc-160
 */
class VSMAKE_LOCAL ProjectLoader
{
private:
	static std::string getConfNameFromConfition (const char * condition);
	static void loadProjectProperties (Project_PrivateData & project, tinyxml2::XMLElement * root);
	static void loadProjectConfigurations (Project_PrivateData & project, tinyxml2::XMLElement * root);
	static void loadConfigurationsProperties (Project_PrivateData & project, tinyxml2::XMLElement * root);
	static void loadSourceFiles (Project_PrivateData & project, tinyxml2::XMLElement * root);
public:
	static VsMakeErrorCode loadProject (Project_PrivateData & project);
};

#endif //_VSMAKE_PROJECT_LOADER_H_
