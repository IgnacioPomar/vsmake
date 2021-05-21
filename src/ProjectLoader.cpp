/*********************************************************************************************
 *	Name		: projectLoader.cpp
 *	Description	: Loads the project file to memory
 ********************************************************************************************/

#include "tinyxml2.h"

#include "project_privatedata.h"
#include "projectLoader.h"




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


/***********************************************************************************************
 * Load a Visual studio solution
 * \param    [in]   solutionPath   Full path of the solution file
 * \param    [out]  solution       Solution class where we store the data parsed
 * \return  Error code of the operation. VSMAKE_ALL_OK if all was ok
 ***********************************************************************************************/
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
	XMLElement* projConfList;

	//-------------- Project configuration itself ------------
	for (XMLElement* e = root->FirstChildElement ("PropertyGroup"); e != nullptr; e = e->NextSiblingElement ("PropertyGroup"))
	{
		const char * lbl = e->Attribute ("Label");
		if (lbl != nullptr)
		{
			std::string label (lbl);
			if (label.compare ("Globals"))
			{
				for (XMLElement* a = e->FirstChildElement (); a != nullptr; a = a->NextSiblingElement ())
				{
					project.setProperty (a->Name (), a->GetText ());
					break;
				}
			}
		}
	}

	//-------------- Buscamos las configuraciones ------------
	for (XMLElement* e = root->FirstChildElement ("ItemGroup"); e != nullptr; e = e->NextSiblingElement ("ItemGroup"))
	{
		std::string label = e->Attribute ("Label");
		if (label.compare ("ProjectConfigurations") == 0)
		{
			projConfList = e;
			break;
		}
	}

	for (XMLElement* e = projConfList->FirstChildElement ("ProjectConfiguration"); e != nullptr; e = e->NextSiblingElement ("ProjectConfiguration"))
	{

		std::string conf = e->Attribute ("Include");

		project.confs.emplace (conf, conf);
	}


	//-------------- Cargamos las propiedades de ProjectConfiguration ------------
	for (XMLElement* e = root->FirstChildElement ("PropertyGroup"); e != nullptr; e = e->NextSiblingElement ("PropertyGroup"))
	{
		const char * condition = e->Attribute ("Condition");
		if (condition != nullptr)
		{
			std::string confName = getConfNameFromConfition (condition);

			auto search = project.confs.find (confName);
			if (search != project.confs.end ())
			{
				for (XMLElement* a = e->FirstChildElement (); a != nullptr; a = a->NextSiblingElement ())
				{

					search->second.setProperty (a->Name (), a->GetText ());
				}
			}
		}
	}

	for (XMLElement* e = root->FirstChildElement ("ItemDefinitionGroup"); e != nullptr; e = e->NextSiblingElement ("ItemDefinitionGroup"))
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


			XMLElement* compilerParams = e->FirstChildElement ("ClCompile");
			if (compilerParams != nullptr)
			{
				for (XMLElement* param = compilerParams->FirstChildElement (); param != nullptr; param = param->NextSiblingElement ())
				{

					prjConf->second.setCompilerProperty (param->Name (), param->GetText ());
				}
			}

			XMLElement* linkerParams = e->FirstChildElement ("Link");
			if (linkerParams != nullptr)
			{
				for (XMLElement* param = linkerParams->FirstChildElement (); param != nullptr; param = param->NextSiblingElement ())
				{

					prjConf->second.setLinkerProperty (param->Name (), param->GetText ());
				}
			}
		}



	}
	//-------------- Cargamos los ficheros a compilar ------------



//return VSMAKE_ALL_OK;
	return VSMAKE_NOT_IMPLEMENTED;
}
