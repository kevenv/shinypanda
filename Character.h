#ifndef SPE_CHARACTER_H
#define SPE_CHARACTER_H

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
    const char* _name;
    int _states[NB_CHARACTER_STATES][2]; //For each states, first int is the first rect of the state, second int is the number of rects.
    int direction; // 0: gauche, 1: droite
    sf::IntRect* _spriteRects;

private:
    void readPosition(const char* file);

public:
    Character(const char* name, const char* fileSprite, const char* filePosition, int x = 0, int y = 0);
    ~Character();

    virtual void update(float dt) = 0;

    virtual void jump() = 0;

    virtual const char* getName();
    virtual sf::Sprite getSprite();

	inline const sf::Vector2f getPos() const { return _sprite.getPosition(); }
};

}

#endif
