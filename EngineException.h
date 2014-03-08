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

#ifdef __GNUC__
    virtual const char* what() const  _GLIBCXX_USE_NOEXCEPT;
#else
    virtual const char* what() const;
#endif
};

}

#endif
