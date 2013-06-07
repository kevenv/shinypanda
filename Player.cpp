#include "Player.h"
#include "Character.h"

#include <SFML/Graphics.hpp>

namespace spe
{

Player::Player(const char* name, const char* file, int nbCol, int nbLig, int x, int y) : Character(name, file, nbCol, nbLig, x, y)
{

}

void Player::update(float dt)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        _x--;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        _x++;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        jump();

}

void Player::jump()
{

}

}
