
#include "World.h"

#include "Config.h"
#include "Engine.h"
#include <iostream>
#include <SFML/Graphics.hpp>

namespace spe
{

World::World()
{
    _map = NULL;
    _mapSizeX = -1;
    _mapSizeY = -1;

    _tileSize = 100;

    _tiles[0].setFillColor(sf::Color::Blue);
    _tiles[1].setFillColor(sf::Color::Green);
    _tiles[2].setFillColor(sf::Color::Red);

    for(int i = 0; i < 3; i++) {
        _tiles[i].setSize(sf::Vector2f(_tileSize, _tileSize));
    }
}

World::~World()
{
    for(int i = 0; i < _mapSizeY; i++)
        delete[] _map[i];
    delete[] _map;
}

bool World::load(const char* filePath)
{
    if(_config.parse(filePath)) {
        std::string rawMap = _config.getArray("mapReal.mapReal");
        std::cout << rawMap << std::endl;

        _mapSizeX = _config.getValue<int>("mapReal.x");
        std::cout << _mapSizeX << std::endl;

        _mapSizeY = _config.getValue<int>("mapReal.y");
        std::cout << _mapSizeY << std::endl;

        std::stringstream sstream;
        sstream << rawMap;
        char crap;

        _map = new int*[_mapSizeY];
        for(int i = 0; i < _mapSizeY ; i++)
            _map[i] = new int[_mapSizeX];

        //_map[_mapSizeY][_mapSizeX];
        for(int j = 0; j < _mapSizeY; j++) {
            for(int i = 0; i < _mapSizeX; i++) {
               sstream >> _map[j][i];
               std::cout << _map[j][i] << " ";
            }
            sstream >> crap;
            std::cout << std::endl;
        }

        return true;
    }
    else {
        return false;
    }
}

void World::render(Engine* engine)
{
    sf::RenderWindow* window = engine->getWindow();

    for(int y = 0; y < _mapSizeY; y++) {
        for(int x = 0; x < _mapSizeX; x++) {
            renderTile(window, x, y, _map[y][x]);
        }
    }
}

void World::renderTile(sf::RenderWindow* window, int x, int y, int tileID)
{
    _tiles[tileID].setPosition(sf::Vector2f(x*_tileSize, y*_tileSize));
    window->draw(_tiles[tileID]);
}

}
