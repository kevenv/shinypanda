#include "Player.h"
#include "Character.h"
#include "Log.h"
#include "SpeedVector2.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#define WALK_MAX 5
#define RUN_MAX 10

namespace spe
{

Player::Player(const char* name, const char* fileSprite, const char* filePosition, int x, int y)
            : Character(name, fileSprite, filePosition, SpeedVector2<float>(0,0,WALK_MAX), x, y)
{

}

void Player::refreshAnimation(float dt)
{
    if(_dead)
    {
        if(_state != DEAD)
        {
            _animationTime = dt;
            _state = DEAD;
        }
        else
            _animationTime += dt;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if(_state != DUCK)
        {
            _animationTime = dt;
            _state = DUCK;
        }
        else
            _animationTime += dt;
    }
    else if(_speed.getDirectionX() != 0)
    {
        if(_speed.getSpeedX() > WALK_MAX)
        {
            if(_state != RUN)
            {
                _animationTime = dt;
                _state = RUN;
            }
            else _animationTime += dt;
        }
        else if(_state != WALK)
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        _dead = false;
    else if(_dead)
        _speed.slow(50*dt);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
        _dead = true;
    else
    {
        bool run = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            _speed.slow(50*dt);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                _speed.slow(50*dt);
            else
                _speed.move(-(run?100:50)*dt,0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _speed.move((run?100:50)*dt,0);
        }
        else
            _speed.slow(50*dt);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            jump();
    }
    _sprite.move(_speed.getVector2());
    refreshAnimation(dt);
}

void Player::jump()
{
    std::cout << "Boing!\n";
}

void Player::run()
{
    _speed.setXMax(RUN_MAX);
}

void Player::walk()
{
    _speed.setXMax(WALK_MAX);
}

}
