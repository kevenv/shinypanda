
#include "MovingObject.h"

#include "Object.h"

namespace spe
{

MovingObject::MovingObject(const char* name, int x, int y):
	Object(name),
	_speed(SpeedVector2<float>()),
	_drawObject(nullptr)
{
	_collideBox.set(x, y, 0, 0);
}

MovingObject::MovingObject(const char* name, int x, int y, int w, int h):
	Object(name),
	_speed(SpeedVector2<float>()),
	_drawObject(nullptr)
{
	_collideBox.set(x, y, w, h);
}

}
