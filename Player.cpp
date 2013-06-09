#include "Player.h"
#include "Character.h"
#include "Log.h"
#include "SpeedVector2.h"

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace spe
{

Player::Player(const char* name, const char* fileSprite, const char* filePosition, int x, int y)
            : Character(name, fileSprite, filePosition, SpeedVector2<float>(0,0,5), x, y)
{

}

void Player::update(float dt)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
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

}

void Player::jump()
{
    std::cout << "Boing!\n";
}

}
