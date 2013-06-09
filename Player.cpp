#include "Player.h"
#include "Character.h"
#include "Log.h"
#include "SpeedVector2.h"

#include <iostream>
#include <SFML/Graphics.hpp>

namespace spe
{

Player::Player(const char* name, const char* fileSprite, const char* filePosition, int x, int y)
            : Character(name, fileSprite, filePosition, SpeedVector2<float>(0,0,5), x, y)
{

}

void Player::refreshSprite()
{
    _sprite.setTextureRect(_spriteRects[_states[_state][0] + (int)(20*_animationTime)%_states[_state][1]]);
}

void Player::refreshAnimation(float dt)
{
    if(_speed.getDirectionX() != 0)
    {
        if(_state != WALK)
        {
            _animationTime = dt;
            _state = WALK;
        }
        else
            _animationTime += dt;
        if(_speed.getDirectionX() == -_direction)
            switchDirection();
    }
    else
    {
        if(_state != STAND)
        {
            _animationTime = dt;
            _state = STAND;
        }
        else
            _animationTime += dt;
    }
    refreshSprite();
}

void Player::update(float dt)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            _speed.slow(50*dt);
        else
            _speed.move(-50*dt,0);
	}
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        _speed.move(50*dt,0);
	}
	else
        _speed.slow(50*dt);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		_sprite.move(0,-250*dt);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_sprite.move(0,250*dt);
	}
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        jump();
    _sprite.move(_speed.getVector2());
    refreshAnimation(dt);
}

void Player::jump()
{
    std::cout << "Boing!\n";
}

}
