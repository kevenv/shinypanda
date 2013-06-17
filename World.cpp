
#include "World.h"

#include <SFML/Graphics.hpp>

namespace spe
{

World::World()
{
    //_levels.capacity();
    _currentLevelId = -1;
}

World::~World()
{
    for(unsigned int i = 0; i < _levels.size(); i++) {
        delete _levels[i];
    }
}

bool World::load(const char* filePath)
{
    /*if() {
        return true;
    }
    else {
        return false;
    }*/

    loadLevel("test.level");

    return true;
}

bool World::loadLevel(const char* filePath)
{
    Level* level = new Level();
    if(!level) {
        return false;
    }

    if(level->load(filePath)) {
        _levels.push_back(level);
        _currentLevelId++;
        return true;
    }
    else {
        delete level;
        return false;
    }
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(getCurrentLevel(),states);
}

}
