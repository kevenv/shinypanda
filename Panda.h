/**
    @file Panda.h
    @author Vincent Girard <vin100_jrare@hotmail.com>
    @version 1.0

    @section LICENSE



    @section DESCRIPTION

    This file is the header of a class representing an enemy panda.
*/
#ifndef SPE_PANDA_H
#define SPE_PANDA_H

#include "Enemy.h"
#include "IDs.h"

namespace spe
{

/**
    @class Panda Panda.h "Panda.h"
    @brief A panda.

    This class represents a panda. It inherites of Enemy.
*/
class Panda : public Enemy
{
protected:
    virtual void refreshAnimation(float dt);
public:
    /**
    Main constructor for the class.

    @param[in] name Name of the panda.
    @param[in] fileSprite Path of the file containing the sprites.
    @param[in] filePosition Path of the file containing the infos of the sprites.
    @param[in] filePositionVersion Last version of the positionf file.
    @param[in] direction Direction of the sprite in the file. True = right, false = left.
    @param[in] x,y Initial position of the panda.
    @param[in] inDream,inReal If the object is in the Dream/Real World or not.
    */
    Panda(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, bool direction, int x = 0, int y = 0, bool inDream = true, bool inReal = true);
    virtual void updateStatus(float dt);
    virtual void jump();
    virtual void run();
    virtual void walk();
    virtual int getID() { return PANDA * Enemy::getID(); }
};

}

#endif
