/*********************************************************************************************
 *	Name		: project_privatedata.h
 *	Description	: Class to opaque pointer to store the Project's private data
 ********************************************************************************************/

#include "project_privatedata.h"



void Project_PrivateData::setProperty (const char * prop, const char * value)
{
	std::string propkey (prop);
	if (0 == propkey.compare ("RootNamespace"))
	{
		this->projectName = value;
	}
}





ProjectConfiguration::ProjectConfiguration (std::string &name) : name (name)
{
}

void ProjectConfiguration::setProperty (const char * prop, const char * value)
{
	std::string propkey (prop);
	if (0 == propkey.compare ("ConfigurationType"))
	{
		std::string ConfigurationType (value);
		if (0 == ConfigurationType.compare ("Application"))
		{
			this->type = ProjectType::app;
		}
		else if (0 == ConfigurationType.compare ("StaticLibrary"))
		{
			this->type = ProjectType::lib;
		}
		else if (0 == ConfigurationType.compare ("DynamicLibrary"))
		{
			this->type = ProjectType::shared;
		}
	}
	else if (0 == propkey.compare ("OutDir"))
	{
		this->targetDir = value;
	}
	else if (0 == propkey.compare ("IntDir"))
	{
		this->objDir = value;
	}
	else if (0 == propkey.compare ("TargetName"))
	{
		this->targetName = value;
	}
	else if (0 == propkey.compare ("IncludePath"))
	{
		this->includePath = value;
	}
	else if (0 == propkey.compare ("LibraryPath"))
	{
		this->libraryPath = value;
	}

	//TargetExt is ignored

}


void ProjectConfiguration::setCompilerProperty (const char * prop, const char * value)
{
	std::string propkey (prop);

	if (0 == propkey.compare ("Optimization"))
	{
		this->optimizations = value;
	}
	else if (0 == propkey.compare ("PreprocessorDefinitions"))
	{
		this->preprocessorDefinitions = value;
	}
	else if (0 == propkey.compare ("LanguageStandard"))
	{
		this->cppLang = value;
	}
}

void ProjectConfiguration::setLinkerProperty (const char * prop, const char * value)
{
	std::string propkey (prop);

	if (0 == propkey.compare ("GenerateDebugInformation"))
	{
		this->dbgType = value;
	}
	else if (0 == propkey.compare ("ProgramDatabaseFile"))
	{
		this->dbgFile = value;
	}
}
