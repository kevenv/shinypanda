#ifndef SPE_WORLD_H
#define SPE_WORLD_H

#include "Config.h"
#include <SFML/Graphics.hpp>

namespace spe
{

class Engine;

class World
{
public:
    World();
    ~World();

    bool load(const char* filePath);

    void render(Engine* engine);
    void renderTile(sf::RenderWindow* window, int x, int y, int tileID);

    inline int getWorldSizeX() const { return _mapSizeX; }
    inline int getWorldSzieY() const { return _mapSizeY; }

private:
    Config _config;
    int** _map;
    int _mapSizeX;
    int _mapSizeY;

    int _tileSize;

    sf::RectangleShape _tiles[3];
    //sf::Texture _textures[3];
};

}

#endif
