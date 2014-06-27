
#include "Enemy.h"

#include "Character.h"

namespace spe
{

Enemy::Enemy(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, bool direction, int x, int y):
	Character(name, fileSprite, filePosition, filePositionVersion, direction, x, y)
{

}

}
