#ifndef SPE_LEVEL_H
#define SPE_LEVEL_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Config.h"
#include "tinyxml2.h"
#include "Camera.h"

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
		_active = true;
    }

private:
    int _tileId;

    int _x;
    int _y;
	
	bool _active;
};

class AnimatedTile : public Tile
{
public:
    AnimatedTile();

private:

};

class Map
{
	friend Level;
	
public:
    Map();
    ~Map();
	
private:
    //This might look like some crazy shit but
    //it mean to be used like this: Tile* tile = _map[layerId][y][x];
    //then it makes sense
    Tile*** _map[SPE_NB_LAYERS];
    int _sizeX;
    int _sizeY;
    sf::VertexArray _vertices[SPE_NB_LAYERS];
    std::vector<MovingObject*> _movingObjects;
    std::vector<AnimatedTile*> _animatedTiles;
};

class Level: public sf::Drawable, public sf::Transformable
{
public:
    Level();
    ~Level();

    bool load(const char* filePath);
    void update(float dt);

	inline int getMapSizeX() const { return (_currentMap->_sizeX); }
	inline int getMapSizeY() const { return (_currentMap->_sizeY); }

    inline struct Map& getMap(enum DIMENSION dimension) { return (dimension == REAL) ? _mapReal : _mapDream; }
    inline struct Map& getCurrentMap() { return *_currentMap; }
    inline void setDimension(enum DIMENSION dimension)
	{
		_currentDimension = dimension;
		_currentMap = _currentDimension == REAL ? &_mapReal : &_mapDream;
	}

    void addMovingObject(MovingObject* movingObject);
    std::vector<MovingObject*>& getMovingObjects() { return _currentMap->_movingObjects; }

private:
    Config _levelFile;
    sf::Texture _tileset;
    std::string _tilesetFilePath;
    int _tileSize;

    std::vector<MovingObject*> _movingObjectsPool; //clear this one
	std::vector<Tile*> _tilesPool; //clear this one
    std::vector<AnimatedTile*> _animatedTiles; //do not empty this one

    Map _mapReal;
    Map _mapDream;

    enum DIMENSION _currentDimension;
	Map* _currentMap;
	
	Camera _parallaxCamera;

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
