
#include "Level.h"

#include <string>
#include <iostream>
#include <sstream>
#include "tinyxml2.h"
#include "MovingObject.h"
#include "Camera.h"
#include "World.h"
#include "Player.h"
#include "ParallaxLayer.h"

namespace spe
{

Level::Level(World* world)
:	_world(world),
	_player(NULL)
{
	_tileSize = 64;
    _currentDimension = REAL;
	_currentMap = &_mapReal;
}

Level::~Level()
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
    for(int i = 0; i < SPE_NB_LAYERS-1; i++) {
		_mapReal._map[i].setVertices(_tileset, _tileSize);
    }
	_mapReal._map[2].setVertices(_tileset, _tileSize, sf::Color(180,180,180));

	for(int i = 0; i < _mapReal._parallaxLayers.size(); i++) {
		_mapReal._parallaxLayers[i]->getTileMap().setVertices(_tileset, _tileSize, sf::Color(128,128,128));
    }
    //setVertices(_mapReal._vertices, _mapReal._map, _mapReal._sizeX, _mapReal._sizeY);
    //setVertices(_mapDream._vertices, _mapDream._map, _mapDream._sizeX, _mapDream._sizeY);

	//set camera
	sf::Vector2i windowSize = _world->getWindowSize();
	_mainCamera.setWindowSize(windowSize.x, windowSize.y);
    _mainCamera.setWorldLimits(sf::Rect<int>(0, 0, getMapSizeX()*_tileSize, getMapSizeY()*_tileSize));
	_mainCamera.setFollowMode(true);
	_mainCamera.setCenter(windowSize.x/2, windowSize.y/2);
    _mainCamera.setSpeed(sf::Vector2f(5,5));

	//set parallax views
	for(int i = 0; i < _mapReal._parallaxLayers.size(); i++) {
		_mapReal._parallaxLayers[i]->setView(_mainCamera.getView());
    }

    return true;
}

bool Level::loadLevelFile(const char* filePath)
{
    std::string path = filePath;
	
	loadTMXFile(filePath);

    if(!_mapReal._map) {
        std::cout << "WARNING: Real Map hasn't been laoded!" << std::endl;
    }

    if(!_mapDream._map) {
        std::cout << "WARNING: Dream Map hasn't been laoded!" << std::endl;
    }

    return true;
}

/*
    --- TEMPORARY FUNCTION ---
*/
bool Level::loadTMXFile(const char* filePath)
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
	_mapReal._sizeX = layerElement->FirstAttribute()->Next()->IntValue();
    _mapReal._sizeY = layerElement->FirstAttribute()->Next()->Next()->IntValue();
	
	for(int i = 0; i < 3; i++) {
		//const int layerId = SPE_NB_LAYERS-i+3; //load map in reverse order (background to foreground)
		ParallaxLayer* layer = new ParallaxLayer(i+1);//layerId);
        _mapReal._parallaxLayers.push_back(layer);
		layer->getTileMap().load(_mapReal._sizeX, _mapReal._sizeY, &layerElement);
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
void Level::loadTMXLayer(tinyxml2::XMLElement** layerElement, int layerId, enum DIMENSION dimension)
{
    Dimension& currentDimension = getMap(dimension);

    //Get layer dimensions
    /*currentDimension._sizeX = (*layerElement)->FirstAttribute()->Next()->IntValue();
    currentDimension._sizeY = (*layerElement)->FirstAttribute()->Next()->Next()->IntValue();*/
	
	currentDimension._map[layerId].load(currentDimension._sizeX, currentDimension._sizeY, layerElement);

    //check if layer is correcly loaded
    for(int y = 0; y < currentDimension._sizeY; y++) {
        for(int x = 0; x < currentDimension._sizeX; x++) {
            std::cout << currentDimension._map[layerId](x,y)->_tileId << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &_tileset;
    target.clear(sf::Color(0,0,0));
	
	//draw parallax layers
	for(int i = 0; i < _currentMap->_parallaxLayers.size(); i++) {
		target.setView(_currentMap->_parallaxLayers[i]->getView());
		target.draw(_currentMap->_parallaxLayers[i]->getTileMap().getVertices(), states);
	}

	//set main camera
	target.setView(_mainCamera.getView());
	
	//draw tilemap layers
	target.draw(_currentMap->_map[BACKGROUND], states);
    target.draw(_currentMap->_map[BACKGROUND], states);
    target.draw(_currentMap->_map[PLAYGROUND], states);
    //draw MovingObjects
    for(std::size_t i = 0; i < _movingObjectsPool.size(); i++) {
		target.draw(_currentMap->_movingObjects[i]->getSprite());
    }
    target.draw(_currentMap->_map[FOREGROUND], states);
}
 
void Level::update(float dt)
{
    for(std::size_t i = 0; i < _movingObjectsPool.size(); i++) {
        _currentMap->_movingObjects[i]->update(dt);
    }
	
	for(int i = 0; i < _currentMap->_parallaxLayers.size(); i++) {
		_currentMap->_parallaxLayers[i]->update(_mainCamera.getView());
	}
}

void Level::addMovingObject(MovingObject* movingObject)
{
    if(movingObject) {
        _movingObjectsPool.push_back(movingObject);
		_currentMap->_movingObjects.push_back(movingObject);
    }
}

}
