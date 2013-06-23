/**
    @file MovingObject.h
    @author Vincent Girard <vin100_jrare@hotmail.com>
    @version 1.0

    @section LICENSE



    @section DESCRIPTION

    This file is the header of a class representing a moving object.
*/
#ifndef SPE_MOVING_OBJECT_H
#define SPE_MOVING_OBJECT_H

#include "Object.h"

#include "SpeedVector2.h"

#include <SFML/Graphics.hpp>

namespace spe
{

/**
    @class MovingObject MovingObject.h "MovingObject.h"
    @brief A moving object.

    This is an abstract class that represents all the moving objects.
    It inherites Object.
*/
class MovingObject : public Object
{
protected:
    SpeedVector2<float> _speed; ///< Current momentum of the object.
    int _direction; ///< The direction of the object. -1: left, 1: right.
public:
    /**
    Main constructor of the class.

    If fileName points to an empty string, no texture is loaded.

    @param[in] name Name of the object.
    @param[in] fileName Path of the file containing the sprite(s).
    @param[in] direction Direction the sprite is facing in the file. true = right, false = left.
    @param[in] x,y Position of the object.
    @param[in] inDream,inReal If the object is in the Dream/Real World or not.
    @param[in] transparent If the is transparent.
    @param[in] solid If the object can't be passed through.
    */
    MovingObject(const char* name, const char* fileName, bool direction, int x = 0, int y = 0, bool inDream = true, bool inReal = true, bool transparent = false, bool solid = true);

    /**
    Check all possible change of status and move the object if needed.

    @param[in] dt Time elapsed since the last update.
    */
    virtual void update(float dt) = 0;

    /**
    Verify if the speed of the last update was non-null.

    @return True if the object has moved, false otherwise.
    */
    virtual bool hasMoved() { return _speed.isMoving(); }

    /**
    Get the position of the center of the object.

    The center is calculated for a fixed point of the object to make sure the animation is fluid.
    It may be different from the position of the center of the sprite rectangle.

    @return Position of the center, in pixels.
    */
    virtual sf::Vector2f getPosition() = 0;
};

}

#endif
