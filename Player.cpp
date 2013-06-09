/**
    @file Player.cpp
    @author Vincent Girard <vin100_jrare@hotmail.com>
    @version 1.0

    @section LICENSE



    @section DESCRIPTION

    This file is the source of a class representing the player.
*/
#include "Player.h"
#include "Character.h"
#include "Log.h"
#include "SpeedVector2.h"

#include <iostream> //For cout tests
#include <SFML/Graphics.hpp> //For the graphics

#define WALK_MAX 5 //Maximum speed when walking
#define RUN_MAX 10 //Maximum speed when running

namespace spe
{

Player::Player(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, int x, int y)
            : Character(name, fileSprite, filePosition, filePositionVersion, x, y)
{
    walk();
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
    std::cout << "Boing!\n"; // TODO (vincent#1#): Jump
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
