/*********************************************************************************************
 *	Name		: maintester.cpp
 *	Description	: Configure the boost test suite
 *  License     : MIT License (see LICENSE.txt)
 *  Copyright	(C) 2016 Ignacio Pomar Ballestero
 ********************************************************************************************/

// CHANGE THIS: Change the following define to match the test project name
/// \warning this define will set a filename, so, beaware of special chars (as ':', '/', etc...).
#define BOOST_TEST_MODULE "Unit tests vsmake"

#ifdef _DEBUG 
	#define END_LIB_STD "d.lib"
#else
	#define END_LIB_STD ".lib"
#endif


// Libraries the project needs
#pragma comment(lib, "libvsmake" END_LIB_STD)

//>>>>>>>>>>>>>>>>>>>>>>>>>>  Unit test config <<<<<<<<<<<<<<<<<<<<<<<<<
// Use WITH_TEE to create a logfile. Beware, the testlogs folder must exist (and it has a relative path)
//#define WITH_TEE

// Use XML_FORMAT, to show results in XML format
//#define XML_FORMAT

// If REPORT_ALL is set, it will show also the succesful tests
//#define REPORT_ALL

//If STOP_ON_FAIL is set, the debugger will stop on fails
//#define STOP_ON_FAIL

//If STOP_AT_END is set, the program will wait the user at the end of the program
#define STOP_AT_END

#ifdef WIN32
// Path that will be used to store the tests logs if WITH_TEE is enabled
#define LOG_PATH    "./../testlogs/"
#else
#define LOG_PATH    "./../testlogs/"
#endif

#ifndef WIN32
// We need this before unit_test.hpp in GCC
#define BOOST_TEST_DYN_LINK
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>> includes section <<<<<<<<<<<<<<<<<<<<<<<<<
#define _CRT_SECURE_NO_WARNINGS
#include <boost/test/unit_test.hpp>
#include <boost/test/test_observer.hpp>



#include <boost/filesystem.hpp>
#include <boost/assert.hpp>
#include <iostream>
#ifdef WITH_TEE
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/tee.hpp>
#include <fstream>
#include <streambuf>
#include <string>
#endif

#include <iostream>  // std::cout
#include <ctime>
#include <cstdio> // getchar();

#ifdef WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h> // IsDebuggerPresent


#else // in linux, we set a breakpoint programatically
#include <csignal>

// Generate an interrupt
#define EMBED_BREAKPOINT std::raise(SIGINT);
//see http://mainisusuallyafunction.blogspot.com.es/2012/01/embedding-gdb-breakpoints-in-c-source.html
//#define EMBED_BREAKPOINT \
	//     asm("0:"                              \
	//         ".pushsection embed-breakpoints;" \
	//         ".quad 0b;"                       \
	//         ".popsection;")


#endif // #ifdef WIN32

static unsigned long int totalTests = 0;
static unsigned long int failedTests = 0;

//>>>>>>>>>>>>>>>>>>>>>>>>>> Changes the current directory  <<<<<<<<<<<<<<<<<<<<<<<<<
#ifdef WIN32
static void change_current_directory_to_exe()
{
	char exe_path[MAX_PATH];
	::GetModuleFileName (NULL, exe_path, MAX_PATH);
	boost::filesystem::path path (exe_path);;
	SetCurrentDirectory (path.parent_path().string().c_str());
}
#else
//TODO: make this someday
//see: http://stackoverflow.com/questions/606041/how-do-i-get-the-path-of-a-process-in-unix-linux/625523#625523
static void change_current_directory_to_exe()
{
}
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>> Show critical ERROR  <<<<<<<<<<<<<<<<<<<<<<<<<
static void showCriticalError (std::string message)
{
	std::cerr << "CRITICAL ERROR:"  << message << std::endl;
#ifdef WIN32
	MessageBoxA (NULL, message.c_str(), "CRITICAL ERROR",  MB_ICONERROR);
#endif
}


//>>>>>>>>>>>>>>>>>>>>>>>>>> Here we apply the configuration <<<<<<<<<<<<<<<<<<<<<<<<<
struct CustomConfig : boost::unit_test::test_observer
{
#ifdef WITH_TEE
	typedef boost::iostreams::tee_device<std::ostream, std::ofstream> Tee;
	typedef boost::iostreams::stream<Tee> TeeStream;

	std::ofstream logFile;
	Tee* tee;// (std::cout, logFile);
	TeeStream bothLogs;
#endif

	/******************************************************************************
	*  Constructor. Here comes the magic
	*****************************************************************************/
	CustomConfig()
	{
		//We set the time
		char timeString [22];
		{
			time_t t;
			struct tm* tim;

			t = std::time (0);
			tim = std::localtime (&t);
			std::strftime (timeString, sizeof (timeString), "%Y-%m-%d_%H-%M-%S", tim);
		}

		//----------  Set the output -------
#ifdef WITH_TEE
		change_current_directory_to_exe();
		
		std::string path = LOG_PATH;
		
		// Check the log folder
		boost::filesystem::path directorioLogs (path);
		if (false == boost::filesystem::is_directory (directorioLogs) || false == boost::filesystem::exists (directorioLogs))
		{	
			std::string message = "Logs folder \"" + path + "\" does not exist.\n\n";
			showCriticalError (message);
			exit (-1);
		}

		
		//Set the log filename
		std::string unitName = BOOST_TEST_MODULE;
		replace (unitName.begin(), unitName.end(), ' ', '_');
		unitName.append ("_");
		path.append (unitName);
		path.append (timeString);
		path.append (".log");
		

		logFile.open (path.c_str());

		// BOOST_ASSERT(logFile.good ());
		if (!logFile.good())
		{
			std::string mensaje = "Unable to open log file \"" + path + "\"\n\n";
			showCriticalError (message);
			exit (-1);
		}

		tee = new Tee (std::cout, logFile);
		bothLogs.open (*tee);
		boost::unit_test::unit_test_log.set_stream (bothLogs);
#else
		boost::unit_test::unit_test_log.set_stream (std::cout);
#endif

#ifdef XML_FORMAT
		boost::unit_test::unit_test_log.set_format (boost::unit_test::XML);
#endif

#ifdef REPORT_ALL
		boost::unit_test::unit_test_log.set_threshold_level (boost::unit_test::log_successful_tests);
#else
		boost::unit_test::unit_test_log.set_threshold_level (boost::unit_test::log_test_units);
#endif
		//we need to register to add counters
		boost::unit_test::framework::register_observer (*this);

		BOOST_TEST_MESSAGE ("--------------------------------------------------");
		BOOST_TEST_MESSAGE ("Starting unit test");
		BOOST_TEST_MESSAGE ("Date/time: " << timeString);
		BOOST_TEST_MESSAGE ("--------------------------------------------------");
	}

	/******************************************************************************
	* Destructor. clean all... and pause if is set
	*****************************************************************************/
	~CustomConfig()
	{
		//Show results
		std::ostringstream resultadosStr;
		resultadosStr << "Unit test finished. Tests with errors " << failedTests << " of " << totalTests << ".";
		BOOST_TEST_MESSAGE ("--------------------------------------------------");
		BOOST_TEST_MESSAGE (resultadosStr.str());
		BOOST_TEST_MESSAGE ("--------------------------------------------------");

#ifdef STOP_AT_END
		std::cout << "Press any intro to finish"  << std::endl;
		getchar();
#endif
		boost::unit_test::framework::deregister_observer (*this);

#ifdef WITH_TEE
		tee->flush();
		tee->close();
		delete (tee);
		//As we close the stream... we need again the console stream
		boost::unit_test::unit_test_log.set_stream (std::cout);
#endif
	}

	/******************************************************************************
	* this method is called each time a test is finished
	* \param   passed    true is it was a successful test
	*****************************************************************************/
	virtual void assertion_result (bool passed /* passed */)
	{
		totalTests++;

		if (!passed)
		{
#ifdef STOP_ON_FAIL
			BreakIfInDebugger();
#endif
			failedTests++;
		}
	}

	/******************************************************************************
	* this mehod is called for each exception
	*****************************************************************************/
	virtual void    exception_caught (boost::execution_exception const &)
	{
#ifdef STOP_ON_FAIL
		BreakIfInDebugger();
#endif
	}

	/******************************************************************************
	* Add dinamic breakpoint
	*****************************************************************************/
	void BreakIfInDebugger()
	{
#ifdef WIN32

		if (IsDebuggerPresent())
		{
			//If we get here debugging... a test has failed: check the call stack
			_CrtDbgBreak();
		}
#else
		EMBED_BREAKPOINT;
#endif
	}
};


// we make effective all
BOOST_GLOBAL_FIXTURE (CustomConfig);
