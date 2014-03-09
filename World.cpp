
#include "World.h"

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "tinyxml2.h"
#include "Config.h"
#include "MovingObject.h"
#include "Camera.h"
#include "Player.h"
#include "Panda.h"
#include "ParallaxLayer.h"
#include "Dimension.h"
#include "RenderSystem.h"
#include "DebugDude.h"

namespace spe
{

World::World()
:
	_player(NULL),
	_tileSize(-1),
	_currentDimension(REAL),
	_currentMap(&_mapReal)
{
}

World::~World()
{
    //clear movingObjectsPool
    for(std::size_t i = 0; i < _movingObjectsPool.size(); i++) {
        delete _movingObjectsPool[i];
    }
    //objects are now invalid

	//clear tilesPool
	for(std::size_t i = 0; i < _tilesPool.size(); i++) {
		delete _tilesPool[i];
	}
	//tiles are now invalid
}

bool World::load(const char* filePath)
{
    //load level file
    if(!loadLevelFile(filePath)) {
        return false;
    }

	//set camera
	_mainCamera.setWindowSize(_windowSize.x, _windowSize.y);
    _mainCamera.setWorldLimits(sf::Rect<int>(0, 0, getMapSizeX()*_tileSize, getMapSizeY()*_tileSize));
	_mainCamera.setFollowMode(true);
	_mainCamera.setCenter(_windowSize.x/2, _windowSize.y/2);
    _mainCamera.setSpeed(sf::Vector2f(5,5));

	//load objects
	_player = new Player("Player", "sprites.png", "sprites.txt", 2, true, _windowSize.x/2, _windowSize.y/2);
	addMovingObject(_player);
	setPlayer(_player);
	Panda* panda = new Panda("Panda", "panda.jpg", "panda.txt", 1, false, _windowSize.x*3/4, _windowSize.y/2);
	addMovingObject(panda);

	DebugDude* dude = new DebugDude(0, 0, 100, 100, sf::Color::Magenta);
	addMovingObject(dude);
	dude = new DebugDude(100, 100, 10, 80, sf::Color::Cyan, false);
	addMovingObject(dude);

    return true;
}

bool World::loadLevelFile(const char* filePath)
{
	loadTMXFile(filePath);

    if(!_mapReal.getTileMaps()) {
        std::cout << "WARNING: Real Map hasn't been loaded!" << std::endl;
    }

    if(!_mapDream.getTileMaps()) {
        std::cout << "WARNING: Dream Map hasn't been loaded!" << std::endl;
    }

    return true;
}

/*
    --- TEMPORARY FUNCTION ---
*/
bool World::loadTMXFile(const char* filePath)
{
    //load tmx
    tinyxml2::XMLDocument doc;
    doc.LoadFile(filePath);
    tinyxml2::XMLElement* mapElement = doc.FirstChildElement("map");

    //load tileset path
    const tinyxml2::XMLElement* tilesetElement = mapElement->FirstChildElement("tileset");
    const tinyxml2::XMLElement* tilesetPathElement = tilesetElement->FirstChildElement("image");
    _tilesetFilePath = tilesetPathElement->FirstAttribute()->Value();

    //load tileSize
    const tinyxml2::XMLAttribute* tileSizeAttr = tilesetElement->FirstAttribute()->Next()->Next();
    _tileSize = tileSizeAttr->IntValue();

	//load parallax layers
	tinyxml2::XMLElement* layerElement = mapElement->FirstChildElement("layer");
	_mapReal.setSizeX(layerElement->FirstAttribute()->Next()->IntValue());
    _mapReal.setSizeY(layerElement->FirstAttribute()->Next()->Next()->IntValue());

	for(int i = 0; i < 3; i++) {
		//const int layerId = SPE_NB_LAYERS-i+3; //load map in reverse order (background to foreground)
		ParallaxLayer* layer = new ParallaxLayer(i+1, _mapReal.getSizeX(), _mapReal.getSizeY(), &layerElement);//layerId);
        _mapReal.getParallaxLayers().push_back(layer);
        layerElement = layerElement->NextSiblingElement("layer");
    }

    //load map layers
    for(int i = 0; i < SPE_NB_LAYERS; i++) {
        const int layerId = SPE_NB_LAYERS-i-1; //load map in reverse order (background to foreground)
        loadTMXLayer(&layerElement, layerId, REAL);
        layerElement = layerElement->NextSiblingElement("layer");
    }

    return true;
}

/*
    --- TEMPORARY FUNCTION ---
*/
void World::loadTMXLayer(tinyxml2::XMLElement** layerElement, int layerId, enum DIMENSION dimension)
{
    Dimension& currentDimension = getMap(dimension);

    //Get layer dimensions
    /*currentDimension._sizeX = (*layerElement)->FirstAttribute()->Next()->IntValue();
    currentDimension._sizeY = (*layerElement)->FirstAttribute()->Next()->Next()->IntValue();*/

	currentDimension.getTileMaps()[layerId].load(currentDimension.getSizeX(), currentDimension.getSizeY(), layerElement);

    //check if layer is correcly loaded
    for(int y = 0; y < currentDimension.getSizeY(); y++) {
        for(int x = 0; x < currentDimension.getSizeX(); x++) {
            std::cout << currentDimension.getTileMaps()[layerId](x,y)->getTileId() << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void World::update(float dt)
{
    for(std::size_t i = 0; i < _movingObjectsPool.size(); i++) {
        _currentMap->getMovingObjects()[i]->update(dt); //TODO: might want to move this into Renderer since its animation related
    }

	for(std::size_t i = 0; i < _currentMap->getParallaxLayers().size(); i++) {
		_currentMap->getParallaxLayers()[i]->update(_mainCamera.getView());
	}
}

void World::addMovingObject(MovingObject* movingObject)
{
    if(movingObject) {
        _movingObjectsPool.push_back(movingObject);
		_currentMap->getMovingObjects().push_back(movingObject);
    }
}

void World::positionToTileCoords(float posX, float posY, int& tileX, int& tileY) const
{
	tileX = posX / _tileSize;
	tileY = posY / _tileSize;
}

int World::positionToTileCoords(float pos) const
{
	return pos / _tileSize;
}

}
