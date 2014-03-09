
#include "Object.h"
#include <vector>
#include <algorithm>

namespace spe
{

Object::Object(const char* name) : _name(name), _solid(false), _inDream(true), _inReal(true), _harmful(false), _player(false) {}

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
