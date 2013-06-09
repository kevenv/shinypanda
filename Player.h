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
    @param[in] x,y Initial position of the character.
    */
    Player(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, int x = 0, int y = 0);
    virtual void update(float dt);
    virtual void jump();
    virtual void run();
    virtual void walk();
};

}

#endif
