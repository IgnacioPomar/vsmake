/*********************************************************************************************
 *	Name		: projectLoader.cpp
 *	Description	: Loads the project file to memory
 ********************************************************************************************/

#include "tinyxml2.h"

#include "project_privatedata.h"
#include "projectLoader.h"




 /**
  * Gets the configuration name from a condition atribute value
  * \param    [in]   condition   condition atribute value
  * \return  The configuration name
  */
std::string ProjectLoader::getConfNameFromConfition (const char * condition)
{
	if (nullptr == condition) return "";

	std::string cond (condition);
	std::size_t equalPos = cond.find ("'=='");

	if (equalPos != std::string::npos)
	{
		std::size_t confPos = equalPos + 4;
		std::size_t confend = cond.find ("'", confPos);


		return  cond.substr (confPos, confend - confPos);
	}
	else
	{
		return "";
	}
}


/**
 * Load properties of the project from the project itsel
 * \param    [in/out]   project		project  private data
 * \param    [in]		root		root elemet of the XML project file
 */
void ProjectLoader::loadProjectProperties (Project_PrivateData & project, tinyxml2::XMLElement * root)
{
	for (tinyxml2::XMLElement* e = root->FirstChildElement ("PropertyGroup"); e != nullptr; e = e->NextSiblingElement ("PropertyGroup"))
	{
		const char * lbl = e->Attribute ("Label");
		if (lbl != nullptr)
		{
			std::string label (lbl);
			if (0 == label.compare ("Globals"))
			{
				for (tinyxml2::XMLElement* a = e->FirstChildElement (); a != nullptr; a = a->NextSiblingElement ())
				{
					project.setProperty (a->Name (), a->GetText ());
					break;
				}
			}
		}
	}
}


/**
 * Load existing project configurations
 * \param    [in/out]   project		project  private data
 * \param    [in]		root		root elemet of the XML project file
 */
void ProjectLoader::loadProjectConfigurations (Project_PrivateData & project, tinyxml2::XMLElement * root)
{
	//Find the section with the configurations
	tinyxml2::XMLElement* projConfList;
	for (tinyxml2::XMLElement* e = root->FirstChildElement ("ItemGroup"); e != nullptr; e = e->NextSiblingElement ("ItemGroup"))
	{
		std::string label = e->Attribute ("Label");
		if (label.compare ("ProjectConfigurations") == 0)
		{
			projConfList = e;
			break;
		}
	}

	//Add each configuration
	for (tinyxml2::XMLElement* e = projConfList->FirstChildElement ("ProjectConfiguration"); e != nullptr; e = e->NextSiblingElement ("ProjectConfiguration"))
	{

		std::string conf = e->Attribute ("Include");

		project.confs.emplace (conf, conf);
	}
}

/**
 * Load properties of each defined configuration
 * \param    [in/out]   project		project  private data
 * \param    [in]		root		root elemet of the XML project file
 */
void ProjectLoader::loadConfigurationsProperties (Project_PrivateData & project, tinyxml2::XMLElement * root)
{
	//Load direct properties
	for (tinyxml2::XMLElement* e = root->FirstChildElement ("PropertyGroup"); e != nullptr; e = e->NextSiblingElement ("PropertyGroup"))
	{
		const char * condition = e->Attribute ("Condition");
		if (condition != nullptr)
		{
			std::string confName = getConfNameFromConfition (condition);

			auto search = project.confs.find (confName);
			if (search != project.confs.end ())
			{
				for (tinyxml2::XMLElement* a = e->FirstChildElement (); a != nullptr; a = a->NextSiblingElement ())
				{

					search->second.setProperty (a->Name (), a->GetText ());
				}
			}
		}
	}


	//Load properties in groups
	for (tinyxml2::XMLElement* e = root->FirstChildElement ("ItemDefinitionGroup"); e != nullptr; e = e->NextSiblingElement ("ItemDefinitionGroup"))
	{
		const char * condition = e->Attribute ("Condition");
		if (condition != nullptr)
		{
			std::string confName = getConfNameFromConfition (condition);
			auto prjConf = project.confs.find (confName);

			if (prjConf == project.confs.end ())
			{
				continue;
			}

			//Load compiler properties
			tinyxml2::XMLElement* compilerParams = e->FirstChildElement ("ClCompile");
			if (compilerParams != nullptr)
			{
				for (tinyxml2::XMLElement* param = compilerParams->FirstChildElement (); param != nullptr; param = param->NextSiblingElement ())
				{
					prjConf->second.setCompilerProperty (param->Name (), param->GetText ());
				}
			}

			//load linker properties
			tinyxml2::XMLElement* linkerParams = e->FirstChildElement ("Link");
			if (linkerParams != nullptr)
			{
				for (tinyxml2::XMLElement* param = linkerParams->FirstChildElement (); param != nullptr; param = param->NextSiblingElement ())
				{
					prjConf->second.setLinkerProperty (param->Name (), param->GetText ());
				}
			}
		}
	}
}


/**
* Load the list of files to compile
* \param[in/out]	project		project  private data
* \param[in]		root		root elemet of the XML project file
*/
void ProjectLoader::loadSourceFiles (Project_PrivateData & project, tinyxml2::XMLElement * root)
{

}


/**
 * Load a Visual studio solution
 * \param    [in]   solutionPath   Full path of the solution file
 * \param    [out]  solution       Solution class where we store the data parsed
 * \return  Error code of the operation. VSMAKE_ALL_OK if all was ok
 */
VsMakeErrorCode ProjectLoader::loadProject (Project_PrivateData & project)
{

	using namespace tinyxml2;

	//Las dependencias estámn en la solución
	//NOTA: No se puede usar el mismo XMLDocument para varios documentos distintos
	XMLError err;

	XMLDocument doc;
	err = doc.LoadFile (project.projectFile.c_str ());
	if (err != XMLError::XML_SUCCESS)
	{
		if (err == XMLError::XML_ERROR_PARSING)
		{
			return VsMakeErrorCode::VSMAKE_PROJECT_FILE_BAD_FORMAT;
		}
		else
		{
			return VsMakeErrorCode::VSMAKE_PROJECT_FILE_NOT_FOUND;
		}
	}

	XMLElement * root = doc.FirstChildElement ("Project");

	loadProjectProperties (project, root);
	loadProjectConfigurations (project, root);
	loadConfigurationsProperties (project, root);
	loadSourceFiles (project, root);

	//return VSMAKE_ALL_OK;
	return VSMAKE_NOT_IMPLEMENTED;
}
