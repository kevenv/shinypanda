/*
Log

Log file service. Write errors, information and debug messages to a text file.

Author: Keven Villeneuve
*/
/*
Format:

single line
[LOG TYPE IDENTIFIER][DATE TIME] MESSAGE

multi lines
[LOG TYPE IDENTIFIER][DATE TIME] MESSAGE 1
								 MESSAGE 2

Log type identifier:
*	DEBUG	-- Only printed if compiled in debug mode
?	INFO
!	WARNING
X	ERROR
*/
#ifndef SPE_LOG_H
#define SPE_LOG_H

#include <ostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>

namespace spe
{

//Log message type
enum LOG_TYPE
{
	NO_TYPE = -1,
	DEBUG,
	INFO,
	WARNING,
	ERROR,
};

class Log
{
public:
	/*
	Create new log message
	logType : log message type
	*/
	Log(enum LOG_TYPE logType = INFO);
	~Log();

	friend const Log& operator<<(const Log& log, int n);
	friend const Log& operator<<(const Log& log, long n);
	friend const Log& operator<<(const Log& log, float n);
	friend const Log& operator<<(const Log& log, double n);
	friend const Log& operator<<(const Log& log, char c);
	friend const Log& operator<<(const Log& log, char* str);
	friend const Log& operator<<(const Log& log, std::string& str);
	friend const Log& operator<<(const Log& log, std::ostream& (*endl)(std::ostream&));

	/*
	Init the logger
	fileName : file name of the log file
	printToConsole : true if log messages are written to console too
	*/
	static bool init(const char* fileName, bool printToConsole = true);

	/*
	Close the logger
	*/
	static void close();

private:
	static std::ofstream* _file; //log file
	static std::stringstream _buffer; //message buffer
	static enum LOG_TYPE _logType; //current log message type
	static char _logTypeStr[]; //log message type identifier-character

	static bool _initialized; //true if logger is already initialized
	static bool _newLine; //true if next message is on a new line

	static bool _printToConsole; //true if log message are printed on console
	static bool _debugMode; //true if debug messages are printed

	static void writeHeader();
	static void writePadding();
	static void writeLog();
	inline static char getLogTypeStr() { return Log::_logTypeStr[Log::_logType]; }
	static const struct tm *const getTime();
};

}

#endif
