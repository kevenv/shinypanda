
#include "Level.h"

#include <string>
#include <iostream>
#include <sstream>
#include "tinyxml2.h"
#include "MovingObject.h"
#include "Camera.h"
#include "World.h"
#include "Player.h"

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
    for(int i = 0; i < SPE_NB_LAYERS; i++) {
        setVertices(_mapReal._vertices[i], _mapReal._map[i], _mapReal._sizeX, _mapReal._sizeY);
    }
    //setVertices(_mapReal._vertices, _mapReal._map, _mapReal._sizeX, _mapReal._sizeY);
    //setVertices(_mapDream._vertices, _mapDream._map, _mapDream._sizeX, _mapDream._sizeY);

	//Load camera(s)
	sf::Vector2i windowSize = _world->getWindowSize();
	_mainCamera.setWindowSize(windowSize.x, windowSize.y);
    _mainCamera.setWorldLimits(sf::Rect<int>(0,0, getMapSizeX()*_tileSize, getMapSizeY()*_tileSize));
	const float cameraSpeed = 0.8;
	_mainCamera.setCenter(windowSize.x/2, windowSize.y/2);
    _mainCamera.setSpeed(sf::Vector2f(cameraSpeed,cameraSpeed));

	_parallaxView = _mainCamera.getView();
	_parallaxView2 = _parallaxView;
	_parallaxView3 = _parallaxView;
	//_parallaxView.zoom(0.8);
	//_parallaxView.setSpeed(sf::Vector2f(cameraSpeed/2.0,cameraSpeed/2.0));
	//_parallaxCamera.setWorldLimits(sf::Rect<int>(0,0,0,0));

    return true;
}

bool Level::loadLevelFile(const char* filePath)
{
    std::string path = filePath;
    if(path.find(".tmx") != std::string::npos) {
        loadTMXFile(filePath);
    }
    else if(path.find(".level") != std::string::npos) {
        loadINIFile(filePath);
    }

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

    //load map layers
    tinyxml2::XMLElement* layerElement = mapElement->FirstChildElement("layer");
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
    Map& currentDimension = getMap(dimension);

    //Get layer dimensions
    currentDimension._sizeX = (*layerElement)->FirstAttribute()->Next()->IntValue();
    currentDimension._sizeY = (*layerElement)->FirstAttribute()->Next()->Next()->IntValue();

    //alloc layer
    //Tile*** _map[3];
    currentDimension._map[layerId] = new Tile**[currentDimension._sizeY];
    for(int i = 0; i < currentDimension._sizeY ; i++) {
        currentDimension._map[layerId][i] = new Tile*[currentDimension._sizeX];
    }

    //load layer
    tinyxml2::XMLElement* dataElement = (*layerElement)->FirstChildElement("data");
    tinyxml2::XMLElement* tileElement = dataElement->FirstChildElement("tile");
    for(int y = 0; y < currentDimension._sizeY; y++) {
        for(int x = 0; x < currentDimension._sizeX; x++) {
			//create tile
            const int tileId = tileElement->FirstAttribute()->IntValue();
			Tile* tile = new Tile(x, y, tileId);
            currentDimension._map[layerId][y][x] = tile;
			_tilesPool.push_back(tile); //todo: HOW DO WE KNOW WICH OBJECT IS SHARED OR NOT???
            tileElement = tileElement->NextSiblingElement("tile");
        }
    }

    //check if layer is correcly loaded
    for(int y = 0; y < currentDimension._sizeY; y++) {
        for(int x = 0; x < currentDimension._sizeX; x++) {
            std::cout << currentDimension._map[layerId][y][x]->_tileId << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

bool Level::loadINIFile(const char* filePath)
{
    if(!_levelFile.parse(filePath)) {
        return false;
    }
    //load map properties
    _tilesetFilePath = _levelFile.getValue<std::string>("level.tilesetFilePath");

    //load real map
    std::string rawMapReal = _levelFile.getArray("mapReal.mapReal");
    std::cout << rawMapReal << std::endl;

    _mapReal._sizeX = _levelFile.getValue<int>("mapReal.x");
    std::cout << _mapReal._sizeX << std::endl;

    _mapReal._sizeY = _levelFile.getValue<int>("mapReal.y");
    std::cout << _mapReal._sizeY << std::endl;

    //load dream map
    std::string rawMapDream = _levelFile.getArray("mapDream.mapDream");
    std::cout << rawMapDream << std::endl;

    _mapDream._sizeX = _levelFile.getValue<int>("mapDream.x");
    std::cout << _mapDream._sizeX << std::endl;

    _mapDream._sizeY = _levelFile.getValue<int>("mapDream.y");
    std::cout << _mapDream._sizeY << std::endl;

    //setMap(&_mapReal._map, _mapReal._sizeX, _mapReal._sizeY, rawMapReal);
    //setMap(&_mapDream._map, _mapDream._sizeX, _mapDream._sizeY, rawMapDream);
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

void Level::setVertices(sf::VertexArray& vertices, Tile*** map, int sizeX, int sizeY)
{
    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(sizeX * sizeY * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
     for (int i = 0; i < sizeX; ++i) {
        for (int j = 0; j < sizeY; ++j) {
            // on récupère le numéro de tuile courant
            int tileNumber = map[j][i]->_tileId - 1; //In TMX, tileset id start at 1 (0 is reserved)

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
	
	//save game camera
	/*
	for(int i = 0; i < _currentMap->_parallax.size(); i++) {
		//set parallax camera
		float speed = 0.5 _currentMap->_parallaxSpeed[i];
		 _parallaxCamera.setSpeed(speed*_gameCamera.getSpeed());
		target.setView(_parallaxCamera.getView());
		
		//build parallax layer using VertexArray
		
		//draw parallax
		target.draw(_currentMap->_parallax[i], states);
	}*/

	//set parallax camera
	//target.setView(_parallaxCamera.getView());
	//draw parallax layer
	//target.draw(_currentMap->_vertices[BACKGROUND],states);

	target.setView(_parallaxView3);
	target.draw(_currentMap->_vertices[BACKGROUND],states);

	target.setView(_parallaxView2);
	target.draw(_currentMap->_vertices[BACKGROUND],states);
	
	target.setView(_parallaxView);
	target.draw(_currentMap->_vertices[BACKGROUND],states);

	//set main camera
	target.setView(_mainCamera.getView());
	
    //target.draw(_currentMap->_vertices[BACKGROUND], states);
    target.draw(_currentMap->_vertices[PLAYGROUND], states);
    //draw MovingObjects
    for(std::size_t i = 0; i < _movingObjectsPool.size(); i++) {
		target.draw(_currentMap->_movingObjects[i]->getSprite());
    }
    target.draw(_currentMap->_vertices[FOREGROUND], states);
}
 
void Level::update(float dt)
{
    for(std::size_t i = 0; i < _movingObjectsPool.size(); i++) {
        _currentMap->_movingObjects[i]->update(dt);
    }

	float scale3 = 0.1;
	sf::Vector2f vct3(_mainCamera.getView().getCenter().x * scale3, _mainCamera.getView().getCenter().y);
	_parallaxView3.setCenter(vct3);

	float scale2 = 0.3;
	sf::Vector2f vct2(_mainCamera.getView().getCenter().x * scale2, _mainCamera.getView().getCenter().y);
	_parallaxView2.setCenter(vct2);
	
	float scale = 0.5;
	sf::Vector2f vct(_mainCamera.getView().getCenter().x * scale, _mainCamera.getView().getCenter().y);
	_parallaxView.setCenter(vct);

	//_parallaxCamera.follow(*_player, dt);
	//_parallaxCamera.follow(*_player);
	//_parallaxCamera.setCenter(_player->getPosition().x, _player->getPosition().y);
}

void Level::addMovingObject(MovingObject* movingObject)
{
    if(movingObject) {
        _movingObjectsPool.push_back(movingObject);
		_currentMap->_movingObjects.push_back(movingObject);
    }
}

Map::Map()
{
	_sizeX = -1;
	_sizeY = -1;
	
	for(int i = 0; i < SPE_NB_LAYERS; i++) {
		_map[i] = NULL;
	}
}

Map::~Map()
{
	//Delete all layers
	//Does not delete the actual Tiles, this is handled by the ~Level()
	//Because another map could be using the same Tiles
	for(int layerId = 0; layerId < SPE_NB_LAYERS; layerId++) {
		for(int y = 0; y < _sizeY; y++) {
			delete[] _map[layerId][y];
		}
		delete[] _map[layerId];
	}
}

}
