
#include "Character.h"
#include "Log.h"

#include <SFML/Graphics.hpp>

namespace spe
{

Character::Character(const char* name, const char* file, int nbCol, int nbLig, int x, int y) : _name(name)
{
    if(!_sprites.loadFromFile(file))
    {
        Log(ERROR) << "Can't find image file for " << _name  << ".\n";
    }
    sf::Vector2u size = _sprites.getSize();
    _height = size.y/nbLig;
    _length = size.x/nbCol;
    _sprite.setTexture(_sprites);
    _sprite.setTextureRect(sf::IntRect(0, 0, _length, _height));
    _sprite.setPosition(x,y);
}

const char* Character::getName()
{
    return _name;
}

sf::Sprite Character::getSprite()
{
    return _sprite;
}

}
