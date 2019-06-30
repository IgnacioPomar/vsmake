/*********************************************************************************************
 *	Name		: maintester.cpp
 *	Description	: Configure the boost test suite
 ********************************************************************************************/

// CHANGE THIS: Change the following define to match the test project name
/// \warning this define will set a filename, so, beaware of special chars (as ':', '/', etc...).
#include "vsmakeTesterPragmalib.h"
#define BOOST_TEST_MODULE "Unit tests para vsMake"


//>>>>>>>>>>>>>>>>>>>>>>>>>>  Unit test config <<<<<<<<<<<<<<<<<<<<<<<<<
//If STOP_AT_END is set, the program will wait the user at the end of the program
#define STOP_AT_END

#ifndef _WIN32
// We need this before unit_test.hpp in GCC
#define BOOST_TEST_DYN_LINK
#endif

#define _CRT_SECURE_NO_WARNINGS

//>>>>>>>>>>>>>>>>>>>>>>>>>> includes section <<<<<<<<<<<<<<<<<<<<<<<<<
#include <boost/test/unit_test.hpp>
#include <boost/assert.hpp>
#include <boost/filesystem.hpp>
#include <iostream> //Para getline
#ifdef _WIN32
#include <Windows.h>
#else
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>> Stats class <<<<<<<<<<<<<<<<<<<<<<<<<
//TODO: Ver por que falla al usar esto
class TestStatsObserver : boost::unit_test::test_observer
{

public:
	unsigned long int totalTests;
	unsigned long int failedTests;

	/******************************************************************************
	* this method is called each time a test is finished
	* \param   passed    true is it was a successful test
	*****************************************************************************/
	virtual void assertion_result (bool passed)
	{
		totalTests++;

		if (!passed)
		{
			failedTests++;
		}
	}

	TestStatsObserver ()
	{
		totalTests = 0;
		failedTests = 0;
	}
};

TestStatsObserver  obs;

//>>>>>>>>>>>>>>>>>>>>>>>>>> Changes the current directory  <<<<<<<<<<<<<<<<<<<<<<<<<
#ifdef _WIN32
static void change_current_directory_to_exe ()
{
	char exe_path [MAX_PATH];
	::GetModuleFileName (NULL, exe_path, MAX_PATH);
	boost::filesystem::path path (exe_path);;
	SetCurrentDirectory (path.parent_path ().string ().c_str ());
}
#else
//TODO: make this someday
//see: http://stackoverflow.com/questions/606041/how-do-i-get-the-path-of-a-process-in-unix-linux/625523#625523
static void change_current_directory_to_exe ()
{
}
#endif


//>>>>>>>>>>>>>>>>>>>>>>>>>> Apply the configuration <<<<<<<<<<<<<<<<<<<<<<<<<
class TesterCfg
{
public:
	TesterCfg ()
	{
		change_current_directory_to_exe ();
		boost::unit_test::unit_test_log.set_threshold_level (boost::unit_test::log_test_units);
		//boost::unit_test::unit_test_log.set_stream (std::cout);
		//boost::unit_test::framework::register_observer (obs2);
	}
	~TesterCfg ()
	{
		//boost::unit_test::unit_test_log.set_stream (std::cout);
		//boost::unit_test::framework::deregister_observer (obs2);
	}
};

BOOST_TEST_GLOBAL_CONFIGURATION (TesterCfg);




//>>>>>>>>>>>>>>>>>>>>>>>>>> Show Test resuluts INFO <<<<<<<<<<<<<<<<<<<<<<<<<
struct ShowTestInfo
{
public:
	ShowTestInfo ()
	{

		time_t now = time (NULL);
		struct tm tstruct;
		char strDate [40];
		tstruct = *localtime (&now);
		//format: day DD-MM-YYYY
		strftime (strDate, sizeof (strDate), "%F %T", &tstruct);

		BOOST_TEST_MESSAGE ("--------------------------------------------------");
		BOOST_TEST_MESSAGE ("Starting unit test");
		BOOST_TEST_MESSAGE ("Date/time: " << strDate);
		BOOST_TEST_MESSAGE ("--------------------------------------------------");

	}
	void setup ()
	{
		//Nothing
	}
	void teardown ()
	{
		//Nothing
	}

	~ShowTestInfo ()
	{

		std::ostringstream resultadosStr;
		//resultadosStr << "Unit test finished. Tests with errors " << obs.failedTests << " of " << obs.totalTests << ".";
		resultadosStr << "Unit test finished.";
		BOOST_TEST_MESSAGE ("--------------------------------------------------");
		BOOST_TEST_MESSAGE (resultadosStr.str ());
		BOOST_TEST_MESSAGE ("--------------------------------------------------");

#ifdef STOP_AT_END
		BOOST_TEST_MESSAGE ("Press enter to exit");
		std::string sGot;
		getline (std::cin, sGot);
#endif
	}
};


BOOST_TEST_GLOBAL_FIXTURE (ShowTestInfo);

