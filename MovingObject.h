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

#include "CollisionEvent.h"

#include <vector>

#include "Object.h"
#include "IDs.h"

#include "SpeedVector2.h"

#include <vector>
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
    int _nbCldPoints; ///< The number of collision points.
    sf::Vector2i* _cldPoints; ///< Dynamic array of collision points.
    std::vector<MovingObject*> _collided; ///< Dynamic array of all the Object already collided this frame.

	bool _initialDirection; ///< Direction the sprite is facing in the file. True = right, false = left.
    sf::Texture _sprites; ///< The textures where our sprite is. This variable is useless if _transparent is true.
	sf::Sprite _sprite; ///< The sprite of our object.
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
    MovingObject(const char* name, const char* fileName, bool direction, int x = 0, int y = 0, bool inDream = true, bool inReal = true, bool solid = true);

    /**
    Update the object for the next frame.
    */
    void update(float dt);

    /**
    Check all possible change of status and move the object if needed.

    @param[in] dt Time elapsed since the last update.
    */
    virtual void updateStatus(float dt) = 0;
    /**
    Add dt to the time of the animation and refresh it. Usually called by update.

    @param[in] dt Time elapsed since the last refresh.
    */
    virtual void refreshAnimation(float dt) = 0;
	/**
    Get the sprite associated with this object.

    @return the sprite of the object.
    */
    sf::Sprite getSprite() { return _sprite; }
    /**
    Refresh the sprite with the current status. Usually called by refreshAnimation.
    */
    virtual void refreshSprite() = 0;
    /**
    Change the direction of the object.
    */
    virtual void switchDirection() = 0;

	    /**
    Verify whether a coordinates are considered "inside" the object.

    This function doesn't take into account whether the object is solid or not.

    See also: isColliding(sf::Vector2i& vect).
    @param[in] x,y The coordinates to verify.
    @return True if the coordinates are inside the object.
    */
    virtual bool isColliding(int x, int y) = 0;
    /**
    Verify whether a coordinates are considered "inside" the object.

    This function doesn't take into account whether the object is solid or not.

    See also: isColliding(int x, int y).

    @param[in] vect The coordinates to verify.
    @return True if the coordinates are inside the object.
    */
    bool isColliding(sf::Vector2i& vect) { return isColliding(vect.x, vect.y); }

    /**
    Perform the reactions of our object associated with the collision.

    This function doesn't move any object, even if overlapsing.

    @param[out] events The current array of event to add new events resulting of the collision.
    @param[in] object The object colliding with our one.
    */
    virtual void collide(std::vector<CollisionEvent*>& events, MovingObject& object) = 0;


    virtual bool isColliding(MovingObject& object);

    /**
    Verify if our object has already collided with this object in the current frame.

    @param[in] object The object with which we verify.
    @return True if a collision has already occured, false otherwise.
    */
    bool hasCollided(MovingObject& object);

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
    virtual sf::Vector2f getPosition() = 0;

    /**
    Get the size of the dynamic array containing the collision points.

    @return the number of collision points.
    */
    int getNbCldPoints() { return _nbCldPoints; }

    /**
    Get a dynamic array containing the collision points.

    To get the size of this array, use the function getNbCldPoints().

    @return The collision points.
    */
    sf::Vector2i* getCldPoints() { return _cldPoints; }

	/**
    This function is there for when you want to verify if an object inherits a certain class.
    It should return the ID associated with that class, multiplied with the ID of the class it inherites.

    Every class inheriting MUST redefine this method, even if already redefined.
    */
    virtual int getID() { return MOVING_OBJECT * 1; }

	SpeedVector2<float>& getSpeed() { return _speed; }
};

}

#endif
