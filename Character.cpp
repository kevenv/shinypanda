/**
    @file Character.cpp
    @author Vincent Girard <vin100_jrare@hotmail.com>
    @version 1.0

    @section LICENSE



    @section DESCRIPTION

    This file is the source of a class representing a character.
*/
#include "Character.h"
#include "Log.h"
#include "SpeedVector2.h"

#include <SFML/Graphics.hpp> //For the graphics
#include <iostream> //For cout tests
#include <fstream> //For reading files

#define ABS(x) ((x) < 0 ? -(x) : (x)) //Absolute value function

namespace spe
{

Character::Character(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, int x, int y)
            : _speed(SpeedVector2<float>()), _name(name), _state(STAND), _direction(1), _animationTime(0), _dead(false)
{
    readPosition(filePosition, filePositionVersion);
    if(!_sprites.loadFromFile(fileSprite))
    {
        Log(ERROR) << "Unable to load image file for " << _name  << ".";
    }
    _sprite.setTexture(_sprites);
    _sprite.setPosition(x,y);
    _currentOffset = getSpriteRect();
    _sprite.move(sf::Vector2f(-_offsets[_currentOffset].x,-_spriteRects[_currentOffset].height));
    refreshSprite();
}

void Character::readPosition(const char* file, const int fileVersion)
{
    std::ifstream  inf (file);

    if (!inf)
    {
        Log(ERROR) << "Unable to load position file for " << _name << ".";
    }

    int version;
    inf >> version;

    if(version != fileVersion)
    {
        Log(ERROR) << "Position file for " << _name << " is out of date.";
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
    int lastOffset = _currentOffset;
    _currentOffset = getSpriteRect();
    sf::IntRect* rect = &_spriteRects[_currentOffset];
    if(_direction < 0) // If the direction if left, do a reflection to the rectangle.
        rect = new sf::IntRect(rect->left+rect->width, rect->top, -rect->width, rect->height);
    _sprite.setTextureRect(*rect);
    // If right: +lastXOffset-currentXOffset, if left: -lastXOffset+lastWidth+currentXOffset-currentWidth.
    _sprite.move(sf::Vector2f(_direction*(_offsets[lastOffset].x - _offsets[_currentOffset].x) + (_direction < 0 ? _spriteRects[lastOffset].width + rect->width : 0), _spriteRects[lastOffset].height - rect->height));
    if(_direction < 0)
        delete rect; // Delete the new rectangle we made.
}

int Character::getSpriteRect()
{
    int time = 20*_animationTime;
    switch(_state)
    {
        case DEAD:
        case DUCK:
        case JUMP: // TODO (vincent#1#): JUMP
            return _states[_state][0] + (time/2 >= _states[_state][1] ? _states[_state][1]-1 : time/2);
        case STAND:
        case WALK:
        case RUN:
        case FALL:
            return _states[_state][0] + (time)%_states[_state][1];
    }
    return -1; //Never gonna happen as long as state stay within the constants.
}

void Character::switchDirection()
{
    //If changing for right: +width-2xOffset, if changing left: +2xOffset-width
    _sprite.move(sf::Vector2f(_direction*(2*_offsets[_currentOffset].x-_spriteRects[_currentOffset].width),0));
    _direction *= -1;
}

const char* Character::getName()
{
    return _name;
}

sf::Sprite& Character::getSprite()
{
    return _sprite;
}

sf::Vector2f Character::getPosition()
{
    // If right: +width-xOffset, if left: +xOffset
    return _sprite.getPosition() + sf::Vector2f(_direction < 0 ? _spriteRects[_currentOffset].width - _offsets[_currentOffset].x : _offsets[_currentOffset].x, _spriteRects[_currentOffset].height);
}

Character::~Character()
{
    delete[] _spriteRects;
}

}
