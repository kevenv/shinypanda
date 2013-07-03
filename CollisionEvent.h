/**
    @file CollisionEvent.h
    @author Vincent Girard <vin100_jrare@hotmail.com>
    @version 1.0

    @section LICENSE



    @section DESCRIPTION

    This file is the header of a class representing a collision.
*/
#ifndef SPE_COLLISION_EVENT_H
#define SPE_COLLISION_EVENT_H

namespace spe
{
/**
    @enum COLLISION_TYPE
    @brief Every possible results of a collision.
*/
enum COLLISION_TYPE
{
    VOID, ///< The collision has no effect.
    KILL_PLAYER, ///< Kill the player.
};

/**
    @class CollisionEvent CollisionEvent.h "CollisionEvent.h"
    @brief A collision.

    This is a class representing a collision. It contains the type of the collision.
*/
class CollisionEvent
{
private:
    COLLISION_TYPE _type;
public:
    /**
    Main constructor for the class.

    @param[in] type The type of the collision.
    */
    CollisionEvent(COLLISION_TYPE type) : _type(type) {}

    /**
    Get the type of the event. Mainly used to apply the effect of the collision.

    @return The type of the collision.
    */
    COLLISION_TYPE getType() { return _type; }
};

}

#endif
