/**
    @file Player.h
    @author Vincent Girard <vin100_jrare@hotmail.com>
    @version 1.0

    @section LICENSE



    @section DESCRIPTION

    This file is the header of a class representing the player.
*/
#ifndef SPE_PLAYER_H
#define SPE_PLAYER_H

#include "Character.h"
#include "Object.h"
#include "IDs.h"
#include "CollisionEvent.h"

#include <vector>

namespace spe
{

/**
    @class Player Player.h "Player.h"
    @brief The player.

    This class represents the player. It inherites of Character.
*/
class Player : public Character
{
protected:
    virtual void refreshAnimation(float dt);
public:
    /**
    Main constructor for the class.

    @param[in] name Name of the player.
    @param[in] fileSprite Path of the file containing the sprites.
    @param[in] filePosition Path of the file containing the infos of the sprites.
    @param[in] filePositionVersion Last version of the positionf file.
    @param[in] direction Direction of the sprite in the file. True = right, false = left.
    @param[in] x,y Initial position of the player.
    @param[in] inDream,inReal If the object is in the Dream/Real World or not.
    */
    Player(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, bool direction, int x = 0, int y = 0, bool inDream = true, bool inReal = true);
    virtual void updateStatus(float dt);
    virtual void jump();
    virtual void run();
    virtual void walk();
    virtual void collide(std::vector<CollisionEvent*>& events, Object& object);
    virtual int getID() { return PLAYER * Character::getID(); }
};

}

#endif
