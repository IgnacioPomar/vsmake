/*********************************************************************************************
 *	Name		: project_privatedata.h
 *	Description	: Class to opaque pointer to store the Project's private data
 ********************************************************************************************/

#pragma once
#ifndef _PROJECT_PRIVATEDATA_H_
#define _PROJECT_PRIVATEDATA_H_

#include <map>
#include <list>
#include <string>
#include "vsmake_cfg.h"


enum ProjectType { app, lib, shared };


class VSMAKE_LOCAL ProjectConfiguration
{
private:

public:
	ProjectConfiguration (std::string &name);

	//Project global settings
	ProjectType type;
	std::string name; //$(Configuration)|$(Platform)
	std::string configuration;
	std::string platform;

	std::string objDir;
	std::string targetDir;
	std::string targetName;

	//Project compiler settings
	std::string includePath;
	std::string cppLang;		//TODO: Transform to enum
	std::string preprocessorDefinitions;
	std::string optimizations; //TODO: Transform to enum

	//Project linker settings
	std::string libraryPath;
	std::string dbgFile;
	std::string dbgType; //TODO: transform into a enum

public:
	void setProperty (const char * prop, const char * value);
	void setCompilerProperty (const char * prop, const char * value);
	void setLinkerProperty (const char * prop, const char * value);

};

class VSMAKE_LOCAL Project_PrivateData
{
public:
	std::string projectFile;
	std::string projectPath;
	std::string projectId;
	std::string projectName;
	std::list <std::string> dependencies;


	std::map<std::string, ProjectConfiguration> confs;
	//std::string projectName;

	void setProperty (const char * prop, const char * value);

public:

};

#endif  //_PROJECT_PRIVATEDATA_H_
