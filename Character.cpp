
#include "Character.h"
#include "Log.h"
#include "SpeedVector2.h"

#include <SFML/Graphics.hpp>
#include <fstream>

namespace spe
{

Character::Character(const char* name, const char* fileSprite, const char* filePosition, SpeedVector2<float> speed, int x, int y) : _speed(speed), _name(name), _direction(1)
{
    readPosition(filePosition);
    if(!_sprites.loadFromFile(fileSprite))
    {
        Log(ERROR) << "Unable to load image file for " << _name  << ".";
    }
    _sprite.setTexture(_sprites);
    sf::IntRect* rect = &_spriteRects[_states[STAND][0]];
    _sprite.setTextureRect(*rect);
    _sprite.setPosition(x-rect->width/2,y-rect->height/2);
}

void Character::readPosition(const char* file)
{
    std::ifstream  inf (file);

    if (!inf)
    {
        Log(ERROR) << "Unable to load position file for " << _name << ".";
    }

    int n;
    inf >> n;

    _spriteRects = new sf::IntRect[n];

    int x, y, length, height;

    for(int i = 0; i < n; i++)
	{
	    inf >> x >> y >> length >> height;
        _spriteRects[i] = sf::IntRect(x, y, length, height);
	}

	for (int i = 0; i < NB_CHARACTER_STATES; i++)
        for (int j = 0; j < 2; j++)
            inf >> _states[i][j];

	inf.close();
}

const char* Character::getName()
{
    return _name;
}

sf::Sprite Character::getSprite()
{
    return _sprite;
}

Character::~Character()
{

}

}
