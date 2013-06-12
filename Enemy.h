/**
    @file Enemy.h
    @author Vincent Girard <vin100_jrare@hotmail.com>
    @version 1.0

    @section LICENSE



    @section DESCRIPTION

    This file is the header of a class representing an enemy character.
*/
#ifndef SPE_ENEMY_H
#define SPE_ENEMY_H

#include "Character.h"

namespace spe
{

/**
    @class Ennemy Ennemy.h "Ennemy.h"
    @brief An enemy.

    This is an abstract class representing an enemy. It inherites of Character.
*/
class Enemy : public Character
{
public:
    /**
    Main constructor for the class.

    @param[in] name Name of the ennemy.
    @param[in] fileSprite Path of the file containing the sprites.
    @param[in] filePosition Path of the file containing the infos of the sprites.
    @param[in] filePositionVersion Last version of the positionf file.
    @param[in] direction Direction of the sprite in the file. True = right, false = left.
    @param[in] x,y Initial position of the enemy.
    @param[in] inDream,inReal If the object is in the Dream/Real World or not.
    */
    Enemy(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, bool direction, int x = 0, int y = 0, bool inDream = true, bool inReal = true);
};

}

#endif
