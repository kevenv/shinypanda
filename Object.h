/**
    @file Object.h
    @author Vincent Girard <vin100_jrare@hotmail.com>
    @version 1.0

    @section LICENSE



    @section DESCRIPTION

    This file is the header of a class representing an object in the map.
*/
#ifndef SPE_OBJECT_H
#define SPE_OBJECT_H

namespace spe
{

class Object
{
protected:
    bool _collidable, _transparent, _inReal, _inDream;
public:
    Object(bool inDream = true, bool inReal = true, bool transparent = false, bool collidable = true);
    virtual bool isColliding(int x, int y) = 0;

    bool isCollidable() { return _collidable; }
    bool isTransparent() { return _transparent; }
    bool isInReal() { return _inReal; }
    bool isInDream() { return _inDream; }
};

}

#endif
