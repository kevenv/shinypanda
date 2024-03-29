#ifndef SPE_ENEMY_H
#define SPE_ENEMY_H

#include "Character.h"

namespace spe
{

class Enemy : public Character
{
public:
    /*
    @param[in] fileSprite Path of the file containing the sprites.
    @param[in] filePosition Path of the file containing the infos of the sprites.
    @param[in] filePositionVersion Last version of the positionf file.
    @param[in] direction Direction of the sprite in the file. True = right, false = left.
    @param[in] x,y Initial position of the enemy.
    */
    Enemy(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, bool direction, int x = 0, int y = 0);
};

}

#endif
