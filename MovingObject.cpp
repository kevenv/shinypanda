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

MovingObject::MovingObject(const char* name, const char* fileName, bool direction, int x, int y, bool inDream, bool inReal, bool solid)
    : Object(name, inDream, inReal, solid), _speed(SpeedVector2<float>()), _direction(direction ? 1 : -1), _initialDirection(direction)
{
	if (fileName != NULL && *fileName != '\0') // If the name is not empty
	{
		if(!_sprites.loadFromFile(fileName)) // If it can't load the file.
		{
			Log(ERROR) << "Can't load the sprite sheet for " << _name << ".";
		}
		_sprite.setTexture(_sprites);
	}
	_sprite.setPosition(x,y);
}

void MovingObject::update(float dt)
{
    _collided.clear();
    refreshAnimation(dt);
}

bool MovingObject::isColliding(MovingObject& object)
{
    for(int i = 0; i < _nbCldPoints; i++)
        if(object.isColliding(_cldPoints[i]))
            return true;
    return false;
}

bool MovingObject::hasCollided(MovingObject& object)
{
    std::vector<MovingObject*>::iterator end = _collided.end();
    return std::find(_collided.begin(), end, &object) != end;
}

}

