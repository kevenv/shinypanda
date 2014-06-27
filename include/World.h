#ifndef SPE_LEVEL_H
#define SPE_LEVEL_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Config.h"
#include "tinyxml2.h"
#include "Camera.h"
#include "Dimension.h"

namespace spe
{
class MovingObject;
class Player;

enum class DIMENSION
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
	inline int getMapSizeX() const { return (_currentMap->getSizeX()); }
	inline int getMapSizeY() const { return (_currentMap->getSizeY()); }

	void positionToTileCoords(float posX, float posY, int& tileX, int& tileY) const;
	int positionToTileCoords(float pos) const;

	inline Dimension& accessMap(DIMENSION dimension) { return (dimension == DIMENSION::REAL) ? _mapReal : _mapDream; }
	inline const Dimension& getMap(DIMENSION dimension) const { return (dimension == DIMENSION::REAL) ? _mapReal : _mapDream; }
	inline Dimension& accessCurrentMap() { return *_currentMap; }
	inline const Dimension& getCurrentMap() const { return *_currentMap; }
	inline void setDimension(DIMENSION dimension)
	{
		_currentDimension = dimension;
		_currentMap = _currentDimension == DIMENSION::REAL ? &_mapReal : &_mapDream;
	}

	inline Camera& accessCamera() { return _mainCamera; }
	inline const Camera& getCamera() const { return _mainCamera; }
	inline Camera* accessCameraPtr() { return &_mainCamera; }
	inline Player* accessPlayerPtr() { return _player; }
	inline const Player* getPlayerPtr() const { return _player; }
	inline void setPlayer(Player* player) { _player = player; }

    void addMovingObject(MovingObject* movingObject);
    const std::vector<MovingObject*>& getMovingObjects() const { return _currentMap->getMovingObjects(); }

private:
    Config _levelFile;
    
	sf::Vector2i _windowSize;
    std::string _tilesetFilePath;
    int _tileSize;

    std::vector<MovingObject*> _movingObjectsPool; //clear this one
	std::vector<StaticObject*> _tilesPool; //clear this one

    Dimension _mapReal;
    Dimension _mapDream;

    DIMENSION _currentDimension;
	Dimension* _currentMap;

	Camera _mainCamera;
	Player* _player;	//ptr to player in movingObject list

    bool loadLevelFile(const char* filePath);
    bool loadTMXFile(const char* filePath);
    void loadTMXLayer(tinyxml2::XMLElement** layerElement, int layerId, DIMENSION dimension);
};

}

#endif
