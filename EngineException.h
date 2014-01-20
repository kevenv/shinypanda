#ifndef SPE_ENGINE_EXCEPTION
#define SPE_ENGINE_EXCEPTION

#include <string>
#include <exception>

namespace spe
{

class EngineException : public std::exception
{
private:
	std::string msg;

public:
	EngineException(const std::string& msg);

	virtual const char* what() const;
};

}

#endif