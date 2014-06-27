#ifndef SPE_PLAYER_H
#define SPE_PLAYER_H

#include "Character.h"

namespace spe
{

class Player : public Character
{
public:
    /**
    @param[in] fileSprite Path of the file containing the sprites.
    @param[in] filePosition Path of the file containing the infos of the sprites.
    @param[in] filePositionVersion Last version of the positionf file.
    @param[in] direction Direction of the sprite in the file. True = right, false = left.
    @param[in] x,y Initial position of the player.
    */
    Player(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, bool direction, int x = 0, int y = 0);

    virtual void updateStatus(float dt) override;
	virtual void collide(Object& obj) override;

    virtual void jump() override;
    virtual void run() override;
    virtual void walk() override;

protected:
	virtual void refreshAnimation(float dt) override;
};

}

#endif
