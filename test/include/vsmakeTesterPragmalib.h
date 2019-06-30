/*********************************************************************************************
 *	Name		: vsmakeTesterPragmalib
 *	Description	: Dependencies of the tester
 ********************************************************************************************/


#ifdef _DEBUG 
#define END_LIB_STD "d.lib"
#else
#define END_LIB_STD ".lib"
#endif


#ifdef WIN32
 // Libraries the project needs
#pragma comment(lib, "libvsmake" END_LIB_STD)
#endif
