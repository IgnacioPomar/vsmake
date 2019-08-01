/*********************************************************************************************
 *	Name		: utils.cpp
 *	Description	: Generic utilities
 ********************************************************************************************/

#include <filesystem>

#include "utils.h"

#ifdef _MSC_VER
#if (_MSC_VER >= 1910 && _MSC_VER <= 1916)
 // Visual Studio 2017
namespace fs = std::experimental::filesystem::v1;
#elif (_MSC_VER > 1916)
namespace fs = std::filesystem;
#else
#error *** Not suported version of Visual studio ***
#endif
#else //_MSC_VER
namespace fs = std::filesystem;
#endif //_MSC_VER


constexpr auto WIN_SLASH = '\\';
constexpr auto STD_SLASH = '/';


/***
 * We need this While waiting for C++20 to arrive
 * Checks if the string ends with the given suffix
 * \see https://en.cppreference.com/w/cpp/string/basic_string/ends_with
 * \param    [in/out]   str
 * \param    [in/out]   suffix
 * \return true if the string ends with the provided suffix, false otherwise.
 */
bool endsWith (const std::string& str, const std::string& suffix)
{
	return str.size () >= suffix.size () && 0 == str.compare (str.size () - suffix.size (), suffix.size (), suffix);
}


/***
 * Set in the dest var the real path in wich is the file
 * \param    [in/out]   filename
 * \param    [in/out]   dest
 */
void setFilePath (const char * filename, std::string & dest)
{
	fs::path p = filename;
	p = fs::canonical (p);
	dest = p.parent_path ().string ();

	char lastChar = dest.back ();
	if ((lastChar != WIN_SLASH) || (lastChar != STD_SLASH))
	{
		dest.push_back (STD_SLASH);
	}
}


bool hasAbsolutePath (const char * filename)
{
	fs::path p = filename;
	return p.is_absolute ();
}
