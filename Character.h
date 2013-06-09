#ifndef SPE_CHARACTER_H
#define SPE_CHARACTER_H

#include "SpeedVector2.h"

#include <SFML/Graphics.hpp>

namespace spe
{

enum CHARACTER_STATE
{
    STAND,
    WALK,
    RUN,
    JUMP,
    FALL,
    DUCK,
    DEAD,
};

const int NB_CHARACTER_STATES = 7;

class Character
{
protected:
    sf::Texture _sprites;
    sf::Sprite _sprite;
    SpeedVector2<float> _speed;
    const char* _name;
    CHARACTER_STATE _state;
    int _states[NB_CHARACTER_STATES][2]; //For each states, first int is the first rect of the state, second int is the number of rects.
    int _direction; // -1: gauche, 1: droite
    float _animationTime;
    sf::IntRect* _spriteRects; //Dynamic array of IntRect
    virtual void refreshAnimation(float dt) = 0;
    virtual void refreshSprite() = 0;
    virtual void switchDirection();

private:
    void readPosition(const char* file);

public:
    Character(const char* name, const char* fileSprite, const char* filePosition, SpeedVector2<float> speed, int x = 0, int y = 0);
    ~Character();

    virtual void update(float dt) = 0;
    virtual void jump() = 0;

    virtual bool hasMoved() { return _speed.isMoving(); }

    virtual const char* getName();
    virtual sf::Sprite getSprite();

	inline const sf::Vector2f getPos() const { return _sprite.getPosition(); }
};

}

#endif
