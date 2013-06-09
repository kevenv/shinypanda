
#include "Log.h"

#include <ostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <ctime>

namespace spe
{

std::ofstream* Log::_file = NULL;
std::stringstream Log::_buffer;
enum LOG_TYPE Log::_logType = NO_TYPE;
char Log::_logTypeStr[] = {'*','?', '!', 'X'};

bool Log::_initialized = false;
bool Log::_newLine = true;

bool Log::_printToConsole = true;

#ifdef _DEBUG
bool Log::_debugMode = true;
#else
bool Log::_debugMode = false;
#endif

Log::Log(enum LOG_TYPE logType)
{
	if(Log::_newLine) {
		//overwrite the log type only if the message is written on a new line
		//the type is the same if the message is not written on a new line
		Log::_logType = logType;
		writeHeader();
	}
	else {
		writePadding();
	}

	Log::_newLine = true;
}

Log::~Log()
{
	Log::_buffer << std::endl;
	writeLog();
	Log::_buffer.str(std::string()); //clear buffer
}

bool Log::init(const char* fileName, bool printToConsole)
{
	_printToConsole = printToConsole;
	bool initialized = true;

	if(!Log::_initialized) {
		Log::_file = new std::ofstream(fileName, std::ofstream::app);
		if(!Log::_file) {
			initialized = false;
		}
	}
	else {
		initialized = false;
	}

	return initialized;
}

void Log::close()
{
	_file->close();
	delete _file;
}

void Log::writeHeader()
{
	char logTypeStr = getLogTypeStr();

	const struct tm *const time = getTime();
	char dateStr[11];
	strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", time);
	char timeStr[9];
	strftime(timeStr, sizeof(timeStr), "%H:%M:%S", time);

	Log::_buffer << "[" << logTypeStr << "]" << "[" << dateStr << " " << timeStr << "] ";
}

void Log::writePadding()
{
	int paddingSize = 3 + 10 + 9 + 2 + 1;
	std::string padding(paddingSize, ' ');
	Log::_buffer << padding;
}

void Log::writeLog()
{
	if(Log::_logType != DEBUG || Log::_debugMode) {
		*Log::_file << Log::_buffer.str();

		if(Log::_printToConsole) {
			std::cout << Log::_buffer.str();
		}
	}
}

const struct tm *const Log::getTime()
{
	const time_t rawTime = time(NULL);
	if(rawTime == -1) {
		return NULL;
	}

	return localtime(&rawTime);
}

const Log& operator<<(const Log& log, int n)
{
	Log::_buffer << n;
	return log;
}

const Log& operator<<(const Log& log, long n)
{
	Log::_buffer << n;
	return log;
}

const Log& operator<<(const Log& log, float n)
{
	Log::_buffer << n;
	return log;
}

const Log& operator<<(const Log& log, double n)
{
	Log::_buffer << n;
	return log;
}

const Log& operator<<(const Log& log, char c)
{
	Log::_buffer << c;
	return log;
}

const Log& operator<<(const Log& log, char* str)
{
	Log::_buffer << str;
	return log;
}

const Log& operator<<(const Log& log, const char* str)
{
	Log::_buffer << str;
	return log;
}

const Log& operator<<(const Log& log, std::string& str)
{
	Log::_buffer << str;
	return log;
}

const Log& operator<<(const Log& log, std::ostream& (*endl)(std::ostream&))
{
	Log::_newLine = false;
	return log;
}

}
