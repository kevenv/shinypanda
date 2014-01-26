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

#include <vector>

#include "Object.h"
#include "IDs.h"

#include "SpeedVector2.h"

#include <vector>
#include <SFML/Graphics.hpp>
#include "PhysicSystem.h"

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
	AABB _collideBox;
	sf::Drawable* _drawObject;

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
    MovingObject(const char* name, int x = 0, int y = 0, bool inDream = true, bool inReal = true, bool solid = true);

	MovingObject(const char* name, int x, int y, int w, int h, bool inDream, bool inReal, bool solid);

    /**
    Update the object for the next frame.
    */
    virtual void update(float dt) = 0;

    /**
    Check all possible change of status and move the object if needed.

    @param[in] dt Time elapsed since the last update.
    */
    virtual void updateStatus(float dt) = 0;

    /**
    Verify if the speed of the last update was non-null.

    @return True if the object has moved, false otherwise.
    */
    virtual bool hasMoved() { return _speed.isMoving(); }

    /**
    Get the position of the object's hot spot.

    The hot spot is a fixed point of the object. It is used for collision and to make the animation fluid.
    It may be different from the position of the center of the sprite rectangle.

    @return Position of the object, in pixels.
    */
    virtual const sf::Vector2f& getPosition() const = 0;

	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;

	inline const sf::Drawable& getDrawObject() const { return *_drawObject; }

	SpeedVector2<float>& getSpeed() { return _speed; }

	const AABB& getCollideBox() const { return _collideBox; }
	bool isColliding(const MovingObject& object ) const
	{
		const AABB& box = object.getCollideBox();
		return _collideBox.isColliding(box);
	}
	bool isColliding(const AABB& box) const
	{
		return _collideBox.isColliding(box);
	}
};

}

#endif
