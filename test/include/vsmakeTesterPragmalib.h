/*********************************************************************************************
 *	Name		: vsmakeTesterPragmalib.h
 *	Description	: Dependencies of the tester
 ********************************************************************************************/


#ifdef _DEBUG 
#define END_LIB_STD "d.lib"
#else
#define END_LIB_STD ".lib"
#endif


 // Libraries the project needs
#pragma comment(lib, "TinyCppUnit" END_LIB_STD)
#pragma comment(lib, "libvsmake" END_LIB_STD)
