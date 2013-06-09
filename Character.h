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
    bool _dead; //If the character is dead
    int _actualOffset; //Index of actual offset.
    sf::IntRect* _spriteRects; //Dynamic array of IntRect
    sf::Vector2i* _offsets; //Dynamic array of offsets
    virtual void refreshAnimation(float dt) = 0;
    virtual void refreshSprite();
    virtual void switchDirection();
    virtual int getSpriteRect();

private:
    void readPosition(const char* file, const int fileVersion);

public:
    Character(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, SpeedVector2<float> speed, int x = 0, int y = 0);
    ~Character();

    void switchDeath() { _dead = !_dead;}

    virtual void update(float dt) = 0;
    virtual void jump() = 0;
    virtual void run() = 0;
    virtual void walk() = 0;

    virtual bool hasMoved() { return _speed.isMoving(); }

    virtual sf::Vector2f getPosition();
    virtual const char* getName();
    virtual sf::Sprite getSprite();

	inline const sf::Vector2f getPos() const { return _sprite.getPosition(); }
};

}

#endif
