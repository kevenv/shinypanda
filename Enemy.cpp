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
#include "Object.h"
#include "IDs.h"
#include "Player.h"

namespace spe
{

Enemy::Enemy(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, bool direction, int x, int y, bool inDream, bool inReal)
                                : Character(name, fileSprite, filePosition, filePositionVersion, direction, x, y, inDream, inReal)
{

}

void Enemy::collide(Object& object)
{
    if(object.getID()%PLAYER == 0)
        static_cast<Player*>(&object)->kill();
}

}
