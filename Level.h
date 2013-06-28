#ifndef SPE_LEVEL_H
#define SPE_LEVEL_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Config.h"
#include "tinyxml2.h"

#define SPE_NB_LAYERS 3

namespace spe
{
class MovingObject;
class Map;
class Level;

enum DIMENSION
{
    REAL,
    DREAM
};

enum LAYER
{
    FOREGROUND,
    PLAYGROUND,
    BACKGROUND
};

class Tile
{
    friend Map;
    friend Level;

public:
    Tile(int x, int y, int tileId)
    {
        _x = x;
        _y = y;
        _tileId = tileId;
    }

private:
    int _tileId;

    int _x;
    int _y;
};

class AnimatedTile : public Tile
{
public:
    AnimatedTile();

private:

};

typedef struct Map;
struct Map
{
    //This might look like some crazy shit but
    //it mean to be used like this: Tile* tile = _map[layerId][y][x];
    //then it makes sense
    Tile*** _map[SPE_NB_LAYERS];
    int _sizeX;
    int _sizeY;
    sf::VertexArray _vertices[SPE_NB_LAYERS];
    std::vector<MovingObject*> _movingObjects;
    std::vector<AnimatedTile*> _animatedTiles;

    Map()
    {
        for(int i = 0; i < SPE_NB_LAYERS; i++) {
            _map[i] = NULL;
        }
        _sizeX = -1;
        _sizeY = -1;
    }

    ~Map()
    {
        //Some DELETE madness...
        for(int layerId = 0; layerId < SPE_NB_LAYERS; layerId++) {
            for(int y = 0; y < _sizeY; y++) {
                for(int x = 0; x < _sizeX; x++) {
                    delete _map[layerId][y][x]; //TODO: do not delete HERE ???
                }
                delete[] _map[layerId][y];
            }
            delete[] _map[layerId];
        }
    }
};

class Level: public sf::Drawable, public sf::Transformable
{
public:
    Level();
    ~Level();

    bool load(const char* filePath);
    void update(float dt);

    int getMapSizeX() const;
    int getMapSizeY() const;
    inline struct Map& getMap(enum DIMENSION dimension) { return (dimension == REAL) ? _mapReal : _mapDream; }
    inline struct Map& getCurrentMap() { return getMap(_currentDimension); }
    inline void setDimension(enum DIMENSION dimension) { _currentDimension = dimension; }

    void addMovingObject(MovingObject* movingObject);
    std::vector<MovingObject*>& getMovingObjects() { return _movingObjectsPool; }

private:
    Config _levelFile;
    sf::Texture _tileset;
    std::string _tilesetFilePath;
    int _tileSize;

    std::vector<MovingObject*> _movingObjectsPool; //clear this one
    std::vector<AnimatedTile*> _animatedTiles; //do not empty this one
    //st::vector<Tile*> _tilesPool; //clear this one

    struct Map _mapReal;
    struct Map _mapDream;

    enum DIMENSION _currentDimension;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    bool loadLevelFile(const char* filePath);
    bool loadTMXFile(const char* filePath);
    void loadTMXLayer(tinyxml2::XMLElement** layerElement, int layerId, enum DIMENSION dimension);
    bool loadINIFile(const char* filePath);
    void setVertices(sf::VertexArray& vertices, Tile*** map, int sizeX, int sizeY);
    void setMap(int*** map, int sizeX, int sizeY, std::string& rawMap);
};

}

#endif
