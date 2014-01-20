#ifndef SPE_LEVEL_H
#define SPE_LEVEL_H

#include <string>
#include <vector>
#include "Config.h"
#include "tinyxml2.h"
#include "Camera.h"
#include "Dimension.h"

namespace spe
{
class MovingObject;
class Player;

enum DIMENSION
{
    REAL,
    DREAM
};

//load world
//world logic -> "model"
//not game logic
//not rendering
class World
{
public:
    World();
    ~World();

    bool load(const char* filePath);
    void update(float dt);

	inline void setWindowSize(int windowSizeX, int windowSizeY)
	{	
		_windowSize.x = windowSizeX;
		_windowSize.y = windowSizeY;
	}
	inline const std::string& getTileSetFilePath() const { return _tilesetFilePath; }

	inline int getTileSize() const { return _tileSize; }
	inline int getMapSizeX() const { return (_currentMap->_sizeX); }
	inline int getMapSizeY() const { return (_currentMap->_sizeY); }

    inline Dimension& getMap(enum DIMENSION dimension) { return (dimension == REAL) ? _mapReal : _mapDream; }
	inline const Dimension& getMap(enum DIMENSION dimension) const { return (dimension == REAL) ? _mapReal : _mapDream; }
    inline Dimension& getCurrentMap() { return *_currentMap; }
	inline const Dimension& getCurrentMap() const { return *_currentMap; }
    inline void setDimension(enum DIMENSION dimension)
	{
		_currentDimension = dimension;
		_currentMap = _currentDimension == REAL ? &_mapReal : &_mapDream;
	}

	inline Camera& getCamera() { return _mainCamera; }
	inline const Camera& getCamera() const { return _mainCamera; }
	inline Player* getPlayer() { return _player; }
	inline void setPlayer(Player* player) { _player = player; }

    void addMovingObject(MovingObject* movingObject);
    std::vector<MovingObject*>& getMovingObjects() { return _currentMap->_movingObjects; }

private:
    Config _levelFile;
    
	sf::Vector2i _windowSize;
    std::string _tilesetFilePath;
    int _tileSize;

    std::vector<MovingObject*> _movingObjectsPool; //clear this one
	std::vector<StaticObject*> _tilesPool; //clear this one

    Dimension _mapReal;
    Dimension _mapDream;

    enum DIMENSION _currentDimension;
	Dimension* _currentMap;

	Camera _mainCamera;
	Player* _player;	//ptr to player in movingobject list

    bool loadLevelFile(const char* filePath);
    bool loadTMXFile(const char* filePath);
    void loadTMXLayer(tinyxml2::XMLElement** layerElement, int layerId, enum DIMENSION dimension);
};

}

#endif
