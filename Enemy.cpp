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

namespace spe
{

Enemy::Enemy(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, int x, int y, bool inDream, bool inReal)
                                : Character(name, fileSprite, filePosition, filePositionVersion, x, y)
{

}

}
