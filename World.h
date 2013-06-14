#ifndef SPE_WORLD_H
#define SPE_WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Level.h"

namespace spe
{

class World : public sf::Drawable
{
public:
    World();
    ~World();

    bool load(const char* filePath);
    bool loadLevel(const char* filePath);
    //void changeLevel(int levelId);

    inline int getWorldSizeX() const { return getCurrentLevel().getMapSizeX(); }
    inline int getWorldSzieY() const { return getCurrentLevel().getMapSizeY(); }

    //switch between dimension (real/dream)
    //inline void setDimension(enum DIMENSION dimension) { getCurrentLevel()->setDimension(dimension); }

private:
    std::vector<Level*> _levels;
    int _currentLevelId;

    inline const Level& getCurrentLevel() const { return *_levels[_currentLevelId]; }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}

#endif
