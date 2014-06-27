#ifndef SPE_MOVING_OBJECT_H
#define SPE_MOVING_OBJECT_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "Object.h"
#include "SpeedVector2.h"
#include "PhysicSystem.h"

namespace spe
{

class MovingObject : public Object
{
protected:
    SpeedVector2<float> _speed;
	AABB _collideBox;
	sf::Drawable* _drawObject;

public:
    MovingObject(const char* name, int x = 0, int y = 0);
	MovingObject(const char* name, int x, int y, int w, int h);

    virtual void update(float dt) = 0;
    /*
    Check all possible change of status and move the object if needed
    */
    virtual void updateStatus(float dt) = 0;

    /*
    Verify if the speed of the last update was non-null
    @return True if the object has moved, false otherwise
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

	inline const SpeedVector2<float>& getSpeed() const { return _speed; }

	inline const AABB& getCollideBox() const { return _collideBox; }
	inline bool isColliding(const MovingObject& object ) const
	{
		const AABB& box = object.getCollideBox();
		return _collideBox.isColliding(box);
	}
	inline bool isColliding(const AABB& box) const
	{
		return _collideBox.isColliding(box);
	}
};

}

#endif
