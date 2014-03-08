
#include "EngineException.h"
#include <string>

namespace spe
{

EngineException::EngineException(const std::string& msg)
{
	this->msg = "EngineException: " + msg;
}

#ifdef __GNUC__
const char* EngineException::what() const _GLIBCXX_USE_NOEXCEPT
#else
const char* EngineException::what() const
#endif
{
	return msg.c_str();
}

}
