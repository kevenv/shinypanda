#include "Player.h"

#include <vector>
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "SpeedVector2.h"

#define WALK_MAX 5 //Maximum speed when walking TODO: HEUUNUUU NOOOO !?
#define RUN_MAX 10 //Maximum speed when running

namespace spe
{

Player::Player(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, bool direction, int x, int y):
	Character(name, fileSprite, filePosition, filePositionVersion, direction, x, y)
{
    walk();
}

void Player::updateStatus(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		_dead = false;
	else if (_dead)
		_speed.slowX(50 * dt);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		_dead = true;
	else
	{
		bool run = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
		//TEMPORARY DISACTIVATED FOR DEBUGGING
		/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
		_speed.slowX(50*dt);
		}
		else*/ if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				_speed.slowX(50 * dt);
			else
				_speed.move(-(run ? 100 : 50)*dt, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			_speed.move((run ? 100 : 50)*dt, 0);
		}
		else
			_speed.slowX(50 * dt);
		//TEMPORARY ADDED FOR DEBUGGING
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				_speed.slowY(50 * dt);
			}
			else
				_speed.move(0, -50 * dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			_speed.move(0, 50 * dt);
		}
		else
			_speed.slowY(50 * dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			jump();
	}
	_sprite.move(_speed.getVector2());
}

void Player::collide(Object& obj)
{
	if (obj.isHarmful()) {
		kill();
	}
}

void Player::refreshAnimation(float dt)
{
    if(_dead) {
		if (_state != CHARACTER_STATE::DEAD) {
            _animationTime = dt;
			changeState(CHARACTER_STATE::DEAD);
        }
		else {
			_animationTime += dt;
		}
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
    else if(_speed.getDirectionX() != 0) {
        if(_speed.getSpeedX() > WALK_MAX) {
			if (_state != CHARACTER_STATE::RUN) {
                _animationTime = dt;
				changeState(CHARACTER_STATE::RUN);
            }
			else {
				_animationTime += dt;
			}
        }
		else if (_state != CHARACTER_STATE::WALK) {
            _animationTime = dt;
			changeState(CHARACTER_STATE::WALK);
        }
		else {
			_animationTime += dt;
		}

		if (_speed.getDirectionX() == -_direction) {
			switchDirection();
		}
    }
    else {
		if (_state != CHARACTER_STATE::STAND) {
            _animationTime = dt;
            changeState(CHARACTER_STATE::STAND);
        }
		else {
			_animationTime += dt;
		}
    }

    refreshSprite();
}

void Player::jump()
{

}

void Player::run()
{
    _speed.setXMax(RUN_MAX);
}

void Player::walk()
{
    _speed.setXMax(WALK_MAX);
	_speed.setYMax(WALK_MAX); //TODO : ADDED TEMPORARY FOR DEBUGGING
}

}
