/*********************************************************************************************
 *	Name		: stackoverflowcode.cpp
 *	Description	: Bunch of code from stack overflow
 ********************************************************************************************/



#include <string>
#include <sstream>
#include <vector>

 //Code contributed to StackOverflow before February 1, 2016

 //---------------------------- Split a string in C++  ----------------------------
 //License : CC BY-SA 3.0 (http://creativecommons.org/licenses/by-sa/3.0/)
 //See     : http://stackoverflow.com/a/236803/74785
 //author  : Evan Teran (http://stackoverflow.com/users/13430/evan-teran)

std::vector<std::string> &split (const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss (s);
	std::string item;
	while (std::getline (ss, item, delim))
	{
		elems.push_back (item);
	}
	return elems;
}


std::vector<std::string> split (const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split (s, delim, elems);
	return elems;
}
