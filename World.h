#ifndef SPE_WORLD_H
#define SPE_WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Level.h"

namespace spe
{
class Camera;

class World : public sf::Drawable
{
public:
    World(int windowSizeX, int windowSizeY);
    ~World();

    bool load(const char* filePath);
    bool loadLevel(const char* filePath);
    //void changeLevel(int levelId);

    inline int getWorldSizeX() const { return getCurrentLevel().getMapSizeX(); }
    inline int getWorldSizeY() const { return getCurrentLevel().getMapSizeY(); }
    inline Level& getCurrentLevel() const { return *_levels[_currentLevelId]; }
    //switch between dimension (real/dream)
    //inline void setDimension(enum DIMENSION dimension) { getCurrentLevel()->setDimension(dimension); }
	inline Camera* getCamera() { return getCurrentLevel().getCamera(); }
	inline const sf::Vector2i& getWindowSize() const { return _windowSize; }

private:
    std::vector<Level*> _levels;
    int _currentLevelId;

	sf::Vector2i _windowSize;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}

#endif
