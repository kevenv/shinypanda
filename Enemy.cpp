/**
    @file Enemy.cpp
    @author Vincent Girard <vin100_jrare@hotmail.com>
    @version 1.0

    @section LICENSE



    @section DESCRIPTION

    This file is the source of a class representing an enemy character.
*/

#include "Enemy.h"
#include "Character.h"
#include "MovingObject.h"
#include "IDs.h"
#include "Player.h"
#include "CollisionEvent.h"

#include <vector>

namespace spe
{

Enemy::Enemy(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, bool direction, int x, int y, bool inDream, bool inReal)
                                : Character(name, fileSprite, filePosition, filePositionVersion, direction, x, y, inDream, inReal)
{

}

void Enemy::collide(std::vector<CollisionEvent*>& events, MovingObject& object)
{
    if (object.getID()%PLAYER == 0)
        events.push_back(new CollisionEvent(KILL_PLAYER)); // TODO (vincent#1#): Make it less ugly? ( *(new...) )
}

}
