/**
    @file MovingObject.cpp
    @author Vincent Girard <vin100_jrare@hotmail.com>
    @version 1.0

    @section LICENSE



    @section DESCRIPTION

    This file is the source of a class representing a moving object.
*/

#include "MovingObject.h"
#include "Object.h"
#include "Log.h"

#include <iostream>

namespace spe
{

MovingObject::MovingObject(const char* name, int x, int y) : Object(name), _speed(SpeedVector2<float>()), _drawObject(nullptr)
{
	_collideBox.set(x, y, 0, 0);
}

MovingObject::MovingObject(const char* name, int x, int y, int w, int h) : Object(name), _speed(SpeedVector2<float>()), _drawObject(nullptr)
{
	_collideBox.set(x, y, w, h);
}

void MovingObject::collide(Object& obj)
{

}

}
