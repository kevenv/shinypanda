
#include "Object.h"

namespace spe
{

Object::Object(const char* name, bool inDream, bool inReal, bool solid)
:
	_name(name),
	_solid(solid),
	_inReal(inReal),
	_inDream(inDream)
{

}

}
