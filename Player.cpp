#include "Player.h"
#include "Character.h"
#include "Log.h"

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace spe
{

Player::Player(const char* name, const char* fileSprite, const char* filePosition, int x, int y)
            : Character(name, fileSprite, filePosition, x, y)
{

}

void Player::update(float dt)
{
	int v = 250;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        _sprite.move(-1*v*dt,0);
	}
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _sprite.move(1*v*dt,0);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		_sprite.move(0,-1*v*dt);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		_sprite.move(0,1*v*dt);
	}
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        jump();

}

void Player::jump()
{
    std::cout << "Boing!\n";
}

}
