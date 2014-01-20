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
#include "IDs.h"
#include "CollisionEvent.h"

#include <vector>
#include <iostream> //For cout tests
#include <SFML/Graphics.hpp> //For the graphics

#define WALK_MAX 5 //Maximum speed when walking
#define RUN_MAX 10 //Maximum speed when running

namespace spe
{

Player::Player(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, bool direction, int x, int y, bool inDream, bool inReal)
            : Character(name, fileSprite, filePosition, filePositionVersion, direction, x, y, inDream, inReal)
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
            changeState(DEAD);
        }
        else
            _animationTime += dt;
    }
	//TEMPORARY DISACTIVATED FOR DEBUGGING
   /* else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if(_state != DUCK)
        {
            _animationTime = dt;
            changeState(DUCK);
        }
        else
            _animationTime += dt;
    }*/
    else if(_speed.getDirectionX() != 0)
    {
        if(_speed.getSpeedX() > WALK_MAX)
        {
            if(_state != RUN)
            {
                _animationTime = dt;
                changeState(RUN);
            }
            else _animationTime += dt;
        }
        else if(_state != WALK)
        {
            _animationTime = dt;
            changeState(WALK);
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
            changeState(STAND);
        }
        else
            _animationTime += dt;
    }
    refreshSprite();
}

void Player::updateStatus(float dt)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        _dead = false;
    else if(_dead)
        _speed.slowX(50*dt);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
        _dead = true;
    else
    {
        bool run = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
		//TEMPORARY DISACTIVATED FOR DEBUGGING
        /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            _speed.slowX(50*dt);
        }
        else*/ if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                _speed.slowX(50*dt);
            else
                _speed.move(-(run?100:50)*dt,0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _speed.move((run?100:50)*dt,0);
        }
        else
            _speed.slowX(50*dt);
		//TEMPORARY ADDED FOR DEBUGGING
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                _speed.slowY(50*dt);
            } else
                _speed.move(0,-50*dt);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
			_speed.move(0,50*dt);
		}
        else
            _speed.slowY(50*dt);//
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            jump();
    }
    _sprite.move(_speed.getVector2());
}

void Player::collide(std::vector<CollisionEvent*>& events, MovingObject& object)
{

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
	_speed.setYMax(WALK_MAX); //ADDED TEMPORARY FOR DEBUGGING
}

}
