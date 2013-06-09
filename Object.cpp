/**
    @file Object.cpp
    @author Vincent Girard <vin100_jrare@hotmail.com>
    @version 1.0

    @section LICENSE



    @section DESCRIPTION

    This file is the source of a class representing an object in the map.
*/

#include "Object.h"

namespace spe
{

Object::Object(bool inDream, bool inReal, bool transparent, bool collidable)
    : _collidable(collidable), _transparent(transparent), _inReal(inReal), _inDream(inDream)
{

}

}
