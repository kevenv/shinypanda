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

#include "IDs.h"
#include "CollisionEvent.h"

#include <vector>
#include <SFML/Graphics.hpp>

namespace spe
{

/**
    @class Object Object.h "Object.h"
    @brief An object in the map.

    This is an abstract class that represents all the possible objects in a map.
*/
class Object
{
protected:
    const char* _name; ///< Name of the object.
    bool _solid; ///< Whether the object if tangible or not. If false, we can pass through it.
    bool _transparent; ///< Wheter the object is transparent or not. If true, we don't draw it.
    bool _inReal; /**< \brief Whether the object exist in the Real World or not.
                    This variable does nothing if _collidable is false and _transparent is true. */
    bool _inDream; /**< \brief Whether the object exist in the Dream World or not.
                    This variable does nothing if _collidable is false and _transparent is true. */
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
    Object(const char* name, const char* fileName, bool direction, int x = 0, int y = 0, bool inDream = true, bool inReal = true, bool transparent = false, bool solid = true);

    /**
    Destructor.

    Free all ressources attached to the object.
    */
    virtual ~Object(){}

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
    virtual void collide(std::vector<CollisionEvent*>& events, Object& object) = 0;

    /**
    Tells whether the object is solid or not.

    @return True if the object is solid, false otherwise.
    */
    bool isSolid() { return _solid; }
    /**
    Tells whether the object is transparent or not.

    @return True if the object is transparent, false otherwise.
    */
    bool isTransparent() { return _transparent; }
    /**
    Tells whether the object exists in the Real World.

    @return True if the object is in the Real World, false otherwise.
    */
    bool isInReal() { return _inReal; }
    /**
    Tells whether the object exists in the Dream World.

    @return True if the object is in the Dream World, false otherwise.
    */
    bool isInDream() { return _inDream; }
    /**
    Get the name of the object.

    The name of the Object is given at initialization to the constructor and never changes.

    @return the name of the object.
    */
    const char* getName() { return _name; }
    /**
    Get the sprite associated with this object.

    @return the sprite of the object.
    */
    sf::Sprite getSprite() { return _sprite; }

    /**
    This function is there for when you want to verify if an object inherits a certain class.
    It should return the ID associated with that class, multiplied with the ID of the class it inherites.

    Every class inheriting MUST redefine this method, even if already redefined.
    */
    virtual int getID() { return 1; }
};

}

#endif
