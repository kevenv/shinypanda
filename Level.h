#ifndef SPE_LEVEL_H
#define SPE_LEVEL_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Config.h"

namespace spe
{

enum DIMENSION
{
    REAL,
    DREAM
};

class Level: public sf::Drawable, public sf::Transformable
{
public:
    Level();
    ~Level();

    bool load(const char* filePath);

    int getMapSizeX() const;
    int getMapSizeY() const;
    inline void setDimension(enum DIMENSION dimension) { _currentDimension = dimension; }

private:
    sf::VertexArray _verticesMapReal;
    sf::VertexArray _verticesMapDream;
    sf::Texture _tileset;

    Config _levelFile;
    std::string _tilesetFilePath;

    int _tileSize;

    int** _mapReal;
    int _mapRealSizeX;
    int _mapRealSizeY;

    int** _mapDream;
    int _mapDreamSizeX;
    int _mapDreamSizeY;

    enum DIMENSION _currentDimension;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    bool loadLevelFile(const char* filePath);
    void setVertices(sf::VertexArray& vertices, int** map, int sizeX, int sizeY);
    void setMap(int** map, int sizeX, int sizeY, std::string& rawMap);
};

}

#endif
