#ifndef SPE_PLAYER_H
#define SPE_PLAYER_H

#include "Character.h"

namespace spe
{

class Player : public Character
{
protected:
    virtual void refreshAnimation(float dt);
public:
    Player(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, int x = 0, int y = 0);
    virtual void update(float dt);
    virtual void jump();
    virtual void run();
    virtual void walk();
};

}

#endif
