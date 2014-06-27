#include "Panda.h"

#include <SFML/Graphics.hpp>
#include "SpeedVector2.h"
#include "Character.h"

namespace spe
{

Panda::Panda(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, bool direction, int x, int y):
	Enemy(name, fileSprite, filePosition, filePositionVersion, direction, x, y)
{
    setHarmful(true);
    walk();
    _speed.move(0.1f,0.0f);
}

void Panda::updateStatus(float dt)
{
    sf::Vector2f position = _sprite.getPosition();
	if (position.x < 500) {
		_speed.move(50 * dt, 0);
	}
	else if (position.x > 1500) {
		_speed.move(-50 * dt, 0);
	}
	else {
		_speed.maxSpeedX();
	}

    _sprite.move(_speed.getVector2());
}

void Panda::jump()
{

}

void Panda::run()
{

}

void Panda::walk()
{
    _speed.setXMax(5);
}

void Panda::refreshAnimation(float dt)
{
	if (_dead) {
		if (_state != CHARACTER_STATE::DEAD) {
			_animationTime = dt;
			_state = CHARACTER_STATE::DEAD;
		}
		else {
			_animationTime += dt;
		}
	}
	else if (_speed.getDirectionX() != 0) {
		if (_state != CHARACTER_STATE::WALK) {
			_animationTime = dt;
			_state = CHARACTER_STATE::WALK;
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
			_state = CHARACTER_STATE::STAND;
		}
		else {
			_animationTime += dt;
		}
	}

	refreshSprite();
}

}
