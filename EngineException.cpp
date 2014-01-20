
#include "EngineException.h"
#include <string>

namespace spe
{

EngineException::EngineException(const std::string& msg)
{
	this->msg = "EngineException: " + msg;
}

const char* EngineException::what() const
{
	return msg.c_str();
}

}