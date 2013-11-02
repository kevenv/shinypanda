#ifndef SPE_LEVEL_H
#define SPE_LEVEL_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Config.h"
#include "tinyxml2.h"
#include "Camera.h"
#include "Dimension.h"

namespace spe
{
class MovingObject;
class Level;
class World;
class Player;

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
    friend class Map;
    friend class Level;

public:
    Tile(int x, int y, int tileId)
    {
        _x = x;
        _y = y;
        _tileId = tileId;
		_active = true;
    }

	int _tileId;

private:
    

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


class Level: public sf::Drawable, public sf::Transformable
{
public:
    Level(World* world);
    ~Level();

    bool load(const char* filePath);
    void update(float dt);

	inline int getMapSizeX() const { return (_currentMap->_sizeX); }
	inline int getMapSizeY() const { return (_currentMap->_sizeY); }

    inline struct Dimension& getMap(enum DIMENSION dimension) { return (dimension == REAL) ? _mapReal : _mapDream; }
    inline struct Dimension& getCurrentMap() { return *_currentMap; }
    inline void setDimension(enum DIMENSION dimension)
	{
		_currentDimension = dimension;
		_currentMap = _currentDimension == REAL ? &_mapReal : &_mapDream;
	}

	inline Camera* getCamera() { return &_mainCamera; }

	inline void setPlayer(Player* player) { _player = player; }

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

    Dimension _mapReal;
    Dimension _mapDream;

    enum DIMENSION _currentDimension;
	Dimension* _currentMap;

	Camera _mainCamera;

	World* _world;	//TODO: Weird, should use Config -> Singleton?
	Player* _player;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    bool loadLevelFile(const char* filePath);
    bool loadTMXFile(const char* filePath);
    void loadTMXLayer(tinyxml2::XMLElement** layerElement, int layerId, enum DIMENSION dimension);
};

}

#endif
