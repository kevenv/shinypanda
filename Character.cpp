/**
    @file Character.cpp
    @author Vincent Girard <vin100_jrare@hotmail.com>
    @version 1.0

    @section LICENSE



    @section DESCRIPTION

    This file is the source of a class representing a character.
*/
#include "Character.h"
#include "MovingObject.h"
#include "Log.h"
#include "SpeedVector2.h"

#include <SFML/Graphics.hpp> //For the graphics
#include <iostream> //For cout tests
#include <fstream> //For reading files

#define ABS(x) ((x) < 0 ? -(x) : (x)) //Absolute value function

namespace spe
{

Character::Character(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, bool direction, int x, int y)
            : MovingObject(name, x, y), _state(STAND), _animationTime(0), _dead(false), _direction(direction ? 1 : -1), _initialDirection(direction)
{
	if (fileSprite != NULL && *fileSprite != '\0') // If the name is not empty
	{
		if(!_sprites.loadFromFile(fileSprite)) // If it can't load the file.
		{
			Log(ERROR) << "Can't load the sprite sheet for " << _name << ".";
		}
		_sprite.setTexture(_sprites);
	}
	_sprite.setPosition(x,y);

    readPosition(filePosition, filePositionVersion);
    _currentOffset = getSpriteRect();
    _sprite.move(sf::Vector2f(-_offsets[_currentOffset].x,-_spriteRects[_currentOffset].height));
    refreshSprite();

	_collideBox.set(x,y,_sprite.getTextureRect().width, _sprite.getTextureRect().height);

	_drawObject = &_sprite;
}

Character::~Character()
{
    delete[] _offsets;
    delete[] _spriteRects;
}

void Character::readPosition(const char* file, const int fileVersion)
{
    std::ifstream inf (file);

    if (!inf) // If it can't load the file.
    {
        Log(ERROR) << "Unable to load position file for " << _name << ".";
    }

    int version;
    inf >> version;

    if(version != fileVersion)
    {
        Log(ERROR) << "Position file for " << _name << " is out of date.";
    }

    inf >> _lCldSide >> _rCldSide;

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

void Character::changeState(CHARACTER_STATE state)
{
    _state = state;
}

void Character::refreshSprite()
{
    int direction = _initialDirection ? _direction : -_direction;
    int lastOffset = _currentOffset;
    _currentOffset = getSpriteRect();
    sf::IntRect* rect = &_spriteRects[_currentOffset];
    if(direction < 0) // If the direction if left, do a reflection to the rectangle.
        rect = new sf::IntRect(rect->left+rect->width, rect->top, -rect->width, rect->height); //TODO: THE FUCK IS THAT SERIOUSLY???
    _sprite.setTextureRect(*rect); //TODO: w & h might be negative to do texture reflection, cause problem with collisions & rendering
    // If right: +lastXOffset-currentXOffset, if left: -lastXOffset+lastWidth+currentXOffset-currentWidth.
	float dx = direction*(_offsets[lastOffset].x - _offsets[_currentOffset].x) + (direction < 0 ? _spriteRects[lastOffset].width + rect->width : 0);
	float dy = _spriteRects[lastOffset].height - rect->height;
    _sprite.move(sf::Vector2f(dx, dy));
    if(direction < 0)
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
    int direction = _initialDirection ? _direction : -_direction;
    //If changing for right: +width-2xOffset, if changing left: +2xOffset-width
	float newX = direction*(2*_offsets[_currentOffset].x-_spriteRects[_currentOffset].width);

    _sprite.move(sf::Vector2f(newX,0));
    _direction *= -1;
}

const sf::Vector2f& Character::getPosition() const
{
    // If right: +width-xOffset, if left: +xOffset TODO: position use for camera following, might be useless
    //return _sprite.getPosition() + sf::Vector2f((_initialDirection == (_direction < 0)) ? _spriteRects[_currentOffset].width - _offsets[_currentOffset].x : _offsets[_currentOffset].x, _spriteRects[_currentOffset].height);
	return _sprite.getPosition();
}

void Character::update(float dt)
{
	refreshAnimation(dt);

	int w = getWidth();
	int h = getHeight();

	_collideBox.set(_sprite.getPosition().x, _sprite.getPosition().y, w, h);
}

}
