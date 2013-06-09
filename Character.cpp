
#include "Character.h"
#include "Log.h"
#include "SpeedVector2.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#define ABS(x) ((x) < 0 ? -(x) : (x))

namespace spe
{

Character::Character(const char* name, const char* fileSprite, const char* filePosition, SpeedVector2<float> speed, int x, int y)
            : _speed(speed), _name(name), _state(STAND), _direction(1), _animationTime(0)
{
    readPosition(filePosition);
    if(!_sprites.loadFromFile(fileSprite))
    {
        Log(ERROR) << "Unable to load image file for " << _name  << ".";
    }
    _sprite.setTexture(_sprites);
    _sprite.setPosition(x,y);
    _actualOffset = getSpriteRect();
    _sprite.move(sf::Vector2f(-_offsets[_actualOffset].x,-_spriteRects[_actualOffset].height));
    refreshSprite();
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
    _offsets = new sf::Vector2i[n];

    int x, y, length, height, offsetX, offsetY;

    for(int i = 0; i < n; i++)
	{
	    inf >> x >> y >> length >> height >> offsetX >> offsetY;
        _spriteRects[i] = sf::IntRect(x, y, length, height);
        _offsets[i] = sf::Vector2i(offsetX, offsetY);
	}

	for (int i = 0; i < NB_CHARACTER_STATES; i++)
        for (int j = 0; j < 2; j++)
            inf >> _states[i][j];

	inf.close();
}

void Character::refreshSprite()
{
    int lastOffset = _actualOffset;
    _actualOffset = getSpriteRect();
    sf::IntRect* rect = &_spriteRects[_actualOffset];
    if(_direction < 0)
        rect = new sf::IntRect(rect->left+rect->width, rect->top, -rect->width, rect->height);
    _sprite.setTextureRect(*rect);
    _sprite.move(sf::Vector2f(_direction*(_offsets[lastOffset].x - _offsets[_actualOffset].x) + (_direction < 0 ? _spriteRects[lastOffset].width + rect->width : 0), _spriteRects[lastOffset].height - rect->height));
    if(_direction < 0)
        delete rect;
}

int Character::getSpriteRect()
{
    int time = 20*_animationTime;
    switch(_state)
    {
        case DEAD:
        case DUCK:
        case JUMP: //TODO JUMP
            return _states[_state][0] + (time > _states[_state][1] ? _states[_state][1] : time);
        case STAND:
        case WALK:
        case RUN:
        case FALL:
            return _states[_state][0] + time%_states[_state][1];
    }
    return -1; //Never gonna happen as long as state stay within the constants.
}

void Character::switchDirection()
{
    _sprite.move(sf::Vector2f(_direction*(2*_offsets[_actualOffset].x-_spriteRects[_actualOffset].width),0));
    _direction *= -1;
}

const char* Character::getName()
{
    return _name;
}

sf::Sprite Character::getSprite()
{
    return _sprite;
}

sf::Vector2f Character::getPosition()
{
    return _sprite.getPosition() + sf::Vector2f(_direction < 0 ? _spriteRects[_actualOffset].width - _offsets[_actualOffset].x : _offsets[_actualOffset].x, _spriteRects[_actualOffset].height);
}

Character::~Character()
{
    delete[] _spriteRects;
}

}
