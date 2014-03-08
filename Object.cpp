
#include "Object.h"
#include <vector>
#include <algorithm>

namespace spe
{

Object::Object()
:	_name("unknown"),
	_solid(false),
	_inReal(true),
	_inDream(true)
{

}

Object::Object(const char* name, bool inDream, bool inReal, bool solid)
:
	_name(name),
	_solid(solid),
	_inReal(inReal),
	_inDream(inDream)
{

}

bool Object::isCurrentlyColliding(const Object* object) const
{
	std::vector<Object*>::const_iterator start = _currentlyCollidingObjects.begin();
	std::vector<Object*>::const_iterator end = _currentlyCollidingObjects.end();
	std::vector<Object*>::const_iterator it = std::find(start, end, object);

	return it != end;
}

void Object::addCurrentlyColliding(Object* object)
{
	if(!isCurrentlyColliding(object)) {
		_currentlyCollidingObjects.push_back(object);
	}
}

void Object::removeCurrentlyColliding(const Object* object)
{
	if(_currentlyCollidingObjects.size() > 0) {
		std::vector<Object*>::iterator start = _currentlyCollidingObjects.begin();
		std::vector<Object*>::iterator end = _currentlyCollidingObjects.end();
		std::vector<Object*>::iterator it = std::find(start, end, object);

		if(it != end) {
			_currentlyCollidingObjects.erase(it);
		}
	}
}

void Object::clearCurrentlyColliding()
{
	_currentlyCollidingObjects.clear();
}

}
