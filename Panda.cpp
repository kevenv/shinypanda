#include "Panda.h"

#include <SFML/Graphics.hpp>
#include <iostream>

namespace spe
{

Panda::Panda(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, bool direction, int x, int y)
            : Enemy(name, fileSprite, filePosition, filePositionVersion, direction, x, y)
{
    setHarmful(true);
    walk();
    _speed.move(0.1f,0.0f);
}

void Panda::refreshAnimation(float dt)
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
    else if(_speed.getDirectionX() != 0)
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

void Panda::updateStatus(float dt)
{
    sf::Vector2f position = _sprite.getPosition();
    if(position.x < 500)
        _speed.move(50*dt, 0);
    else if(position.x > 1500)
        _speed.move(-50*dt,0);
    else
        _speed.maxSpeedX();
    _sprite.move(_speed.getVector2());
}

void Panda::jump()
{
    std::cout << "Boing!\n"; // TODO (vincent#1#): Jump
}

void Panda::run()
{
    // TODO (vincent#1#): Implements running?
}

void Panda::walk()
{
    _speed.setXMax(5);
}

}
