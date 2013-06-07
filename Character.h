#ifndef SPE_CHARACTER_H
#define SPE_CHARACTER_H

#include <SFML/Graphics.hpp>

namespace spe
{

class Character
{
protected:
    sf::Texture _sprites;
    sf::Sprite _sprite;
    const char* _name;
    int _height, _length, _x, _y;
public:
    Character(const char* name, const char* file, int nbcol, int nbLig, int x = 0, int y = 0);

    virtual void update(float dt) = 0;

    virtual void jump() = 0;

    virtual const char* getName();
};

}

#endif
