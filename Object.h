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

/**
    @class Object Object.h "Object.h"
    @brief An object in the map.

    This is an abstract class that represents all the possible objects in a map (except characters).
*/
class Object
{
protected:
    bool _collidable; ///< Whether the object if tangible or not. If false, we can pass through it.
    bool _transparent; ///< Wheter the object is transparent or not. If true, we don't draw it.
    bool _inReal; /**< \brief Whether the object exist in the Real World or not.
                    This variable does nothing if _collidable is false and _transparent is true. */
    bool _inDream; /**< \brief Whether the object exist in the Dream World or not.
                    This variable does nothing if _collidable is false and _transparent is true. */
public:
    /**
    Main constructor of the class.

    @param[in] inDream,inReal If the object is in the Dream/Real World or not.
    @param[in] transparent If the is transparent.
    @param[in] collidable If the object can't be passed through.
    */
    Object(bool inDream = true, bool inReal = true, bool transparent = false, bool collidable = true);
    /**
    Verify whether a coordinate is considered "inside" the object.

    This function doesn't take into account whether the object is collidable or not.

    @param[in] x,y The coordinate to verify.
    @return True if the coordinate is inside the object.
    */
    virtual bool isColliding(int x, int y) = 0;

    bool isCollidable() { return _collidable; }
    bool isTransparent() { return _transparent; }
    bool isInReal() { return _inReal; }
    bool isInDream() { return _inDream; }
};

}

#endif
