/**
    @file Object.cpp
    @author Vincent Girard <vin100_jrare@hotmail.com>
    @version 1.0

    @section LICENSE



    @section DESCRIPTION

    This file is the source of a class representing an object in the map.
*/

#include "Object.h"
#include "Log.h"

namespace spe
{

Object::Object(const char* name, const char* fileName, bool direction, int x, int y, bool inDream, bool inReal, bool transparent, bool collidable)
    : _name(name), _collidable(collidable), _transparent(transparent), _inReal(inReal), _inDream(inDream), _initialDirection(direction)
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

}
