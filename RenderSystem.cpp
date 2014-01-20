
#include "RenderSystem.h"

#include <SFML/Graphics.hpp>
#include "World.h"
#include "ParallaxLayer.h"
#include "EngineException.h"

namespace spe
{

RenderSystem::RenderSystem()
{

}

void RenderSystem::init(sf::RenderWindow& window, World& world)
{
	_window = &window;
	_tilesetFilePath = world.getTileSetFilePath();
	_tileSize = world.getTileSize();

	//load tileset
	if(!_tileset.loadFromFile(_tilesetFilePath)) {
		throw EngineException("Can't load tileset '" + _tilesetFilePath + "'");
	}

	Dimension& mapReal = world.getMap(REAL);
	//set vertices
	for(int i = 0; i < SPE_NB_LAYERS; i++) {
		mapReal._map[i].setVertices(_tileset, _tileSize);
	}

	for(std::size_t i = 0; i < mapReal._parallaxLayers.size(); i++) {
		mapReal._parallaxLayers[i]->getTileMap().setVertices(_tileset, _tileSize, sf::Color(128,128,128));
	}

	//set parallax views
	const sf::View cameraView = world.getCamera().getView();
	for(std::size_t i = 0; i < mapReal._parallaxLayers.size(); i++) {
		mapReal._parallaxLayers[i]->setView(cameraView);
	}
}

void RenderSystem::render(const World& world)
{
	sf::RenderStates states = sf::RenderStates::Default;
	states.texture = &_tileset;

	_window->clear(sf::Color(0,0,0));
	
	//draw parallax layers
	const Dimension& map = world.getCurrentMap();
	
	for(std::size_t i = 0; i < map._parallaxLayers.size(); i++) {
		ParallaxLayer* parallaxLayer = map._parallaxLayers[i];
		_window->setView(parallaxLayer->getView());
		_window->draw(parallaxLayer->getTileMap().getVertices(), states);
	}
	
	//set main camera
	const Camera& camera = world.getCamera();
	_window->setView(camera.getView());

	//draw tilemap layers
	_window->draw(map._map[BACKGROUND], states);
	_window->draw(map._map[BACKGROUND], states);
	_window->draw(map._map[PLAYGROUND], states);

	//draw MovingObjects
	
	for(std::size_t i = 0; i < map._movingObjects.size(); i++) {
		_window->draw(map._movingObjects[i]->getSprite(), states);
	}
	_window->draw(map._map[FOREGROUND], states);
}

}