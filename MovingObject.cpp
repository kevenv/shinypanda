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

namespace spe
{

MovingObject::MovingObject(const char* name, const char* fileName, bool direction, int x, int y, bool inDream, bool inReal, bool transparent, bool solid)
    : Object(name, fileName, direction, x, y, inDream, inReal, transparent, solid), _speed(SpeedVector2<float>()), _direction(direction ? 1 : -1)
{

}

void MovingObject::update(float dt)
{
    _collided.clear();
    updateStatus(dt);
}

}

