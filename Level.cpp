
#include "Level.h"

#include <string>
#include <iostream>
#include <sstream>

namespace spe
{

Level::Level()
{
    _tileSize = 64;

    _mapReal = NULL;
    _mapRealSizeX = -1;
    _mapRealSizeY = -1;

    _mapDream = NULL;
    _mapDreamSizeX = -1;
    _mapDreamSizeY = -1;

     _currentDimension = REAL;
}

Level::~Level()
{
    for(int i = 0; i < _mapRealSizeY; i++)
        delete[] _mapReal[i];
    delete[] _mapReal;

    for(int i = 0; i < _mapDreamSizeY; i++)
        delete[] _mapDream[i];
    delete[] _mapDream;
}

bool Level::load(const char* filePath)
{
    //load level file
    if(!loadLevelFile(filePath)) {
        return false;
    }

    //load tileset
     if(!_tileset.loadFromFile(_tilesetFilePath)) {
        return false;
    }

    //set vertices
    setVertices(_verticesMapReal, _mapReal, _mapRealSizeX, _mapRealSizeY);
    setVertices(_verticesMapDream, _mapDream, _mapDreamSizeX, _mapDreamSizeY);

    return true;
}

bool Level::loadLevelFile(const char* filePath)
{
    if(!_levelFile.parse(filePath)) {
        return false;
    }

    //load map properties
    _tilesetFilePath = _levelFile.getValue<std::string>("level.tilesetFilePath");

    //load real map
    std::string rawMapReal = _levelFile.getArray("mapReal.mapReal");
    std::cout << rawMapReal << std::endl;

    _mapRealSizeX = _levelFile.getValue<int>("mapReal.x");
    std::cout << _mapRealSizeX << std::endl;

    _mapRealSizeY = _levelFile.getValue<int>("mapReal.y");
    std::cout << _mapRealSizeY << std::endl;

    //load dream map
    std::string rawMapDream = _levelFile.getArray("mapDream.mapDream");
    std::cout << rawMapDream << std::endl;

    _mapDreamSizeX = _levelFile.getValue<int>("mapDream.x");
    std::cout << _mapDreamSizeX << std::endl;

    _mapDreamSizeY = _levelFile.getValue<int>("mapDream.y");
    std::cout << _mapDreamSizeY << std::endl;

    setMap(&_mapReal, _mapRealSizeX, _mapRealSizeY, rawMapReal);
    setMap(&_mapDream, _mapDreamSizeX, _mapDreamSizeY, rawMapDream);

    if(!_mapReal) {
        std::cout << "caca r" << std::endl;
    }

    if(!_mapDream) {
        std::cout << "caca d" << std::endl;
    }

    return true;
}

void Level::setMap(int*** map, int sizeX, int sizeY, std::string& rawMap)
{
    std::stringstream sstream;
    sstream << rawMap;
    char crap;

    *map = new int*[sizeY];
    for(int i = 0; i < sizeY ; i++)
        (*map)[i] = new int[sizeX];

    for(int j = 0; j < sizeY; j++) {
        for(int i = 0; i < sizeX; i++) {
           sstream >> (*map)[j][i];
           std::cout << (*map)[j][i] << " ";
        }
        sstream >> crap;
        std::cout << std::endl;
    }
}

void Level::setVertices(sf::VertexArray& vertices, int** map, int sizeX, int sizeY)
{
    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(sizeX * sizeY * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
     for (int i = 0; i < sizeX; ++i) {
        for (int j = 0; j < sizeY; ++j) {
            // on récupère le numéro de tuile courant
            int tileNumber = map[j][i];

            if(tileNumber == 35) continue; //skip tiles without texture

            // on en déduit sa position dans la texture du tileset
            int tu = tileNumber % (_tileset.getSize().x / _tileSize);
            int tv = tileNumber / (_tileset.getSize().x / _tileSize);

            // on récupère un pointeur vers le quad à définir dans le tableau de vertex
            sf::Vertex* quad = &vertices[(i + j * sizeX) * 4];

            // on définit ses quatre coins
            quad[0].position = sf::Vector2f(i * _tileSize, j * _tileSize);
            quad[1].position = sf::Vector2f((i + 1) * _tileSize, j * _tileSize);
            quad[2].position = sf::Vector2f((i + 1) * _tileSize, (j + 1) * _tileSize);
            quad[3].position = sf::Vector2f(i * _tileSize, (j + 1) * _tileSize);

            // on définit ses quatre coordonnées de texture
            quad[0].texCoords = sf::Vector2f(tu * _tileSize, tv * _tileSize);
            quad[1].texCoords = sf::Vector2f((tu + 1) * _tileSize, tv * _tileSize);
            quad[2].texCoords = sf::Vector2f((tu + 1) * _tileSize, (tv + 1) * _tileSize);
            quad[3].texCoords = sf::Vector2f(tu * _tileSize, (tv + 1) * _tileSize);
        }
    }
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &_tileset;
    target.clear(sf::Color(215,215,215));
    target.draw(_currentDimension == REAL ? _verticesMapReal : _verticesMapDream, states);
}

int Level::getMapSizeX() const
{
    return (_currentDimension == REAL ? _mapRealSizeX : _mapDreamSizeX);
}

int Level::getMapSizeY() const
{
    return (_currentDimension == REAL ? _mapRealSizeY : _mapDreamSizeY);
}

}
