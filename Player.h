#ifndef SPE_PLAYER_H
#define SPE_PLAYER_H

#include "Character.h"

namespace spe
{

class Player : virtual public Character
{
public:
    Player(const char* name, const char* file, int nbCol, int nbLig, int x = 0, int y = 0);
    virtual void update(float dt);
    virtual void jump();
};

}

#endif
