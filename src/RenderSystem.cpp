
#include "RenderSystem.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include "World.h"
#include "Dimension.h"
#include "ParallaxLayer.h"
#include "EngineException.h"
#include <cassert>

namespace spe
{

RenderSystem::RenderSystem():
	_debugOverlayEnabled(true)
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

	Dimension& mapReal = world.accessMap(DIMENSION::REAL);
	//set vertices
	for(int i = 0; i < SPE_NB_LAYERS; i++) {
		mapReal.accessTileMaps()[i].setVertices(_tileset, _tileSize);
	}

	for(std::size_t i = 0; i < mapReal.getParallaxLayers().size(); i++) {
		mapReal.getParallaxLayers()[i]->accessTileMap().setVertices(_tileset, _tileSize);//, sf::Color(128,128,128));
	}

	//set parallax views
	const sf::View cameraView = world.getCamera().getView();
	for(std::size_t i = 0; i < mapReal.getParallaxLayers().size(); i++) {
		mapReal.getParallaxLayers()[i]->setView(cameraView);
	}
}

void RenderSystem::render(const World& world)
{
	sf::RenderStates states = sf::RenderStates::Default;
	states.texture = &_tileset;

	_window->clear(sf::Color(208,244,247));
	
	//draw parallax layers
	const Dimension& map = world.getCurrentMap();
	
	for(std::size_t i = 0; i < map.getParallaxLayers().size(); i++) {
		ParallaxLayer* parallaxLayer = map.getParallaxLayers()[i];
		_window->setView(parallaxLayer->getView());
		_window->draw(parallaxLayer->getTileMap().getVertices(), states);
	}
	
	//set main camera
	const Camera& camera = world.getCamera();
	_window->setView(camera.getView());

	//draw tilemap layers
	_window->draw(map.getTileMaps()[(int)LAYER::BACKGROUND], states);
	_window->draw(map.getTileMaps()[(int)LAYER::PLAYGROUND], states);

	const std::vector<MovingObject*>& movingObjects = map.getMovingObjects();

	if(_debugOverlayEnabled) { 
		drawDebugStaticCollisions(map, LAYER::PLAYGROUND, sf::Color::Blue);
		drawDebugDynamicCollisions(map);
		//drawDebugGrid(x,y,3,3,sf::Color::Red);

		for(std::size_t i = 0; i < movingObjects.size(); i++) {
			MovingObject* object = movingObjects[i];
			
			drawDebugPoint((int)object->getPosition().x, (int)object->getPosition().y, sf::Color::Yellow);
		}
	}

	//draw MovingObjects
	for (std::size_t i = 0; i < movingObjects.size(); i++) {
		_window->draw(movingObjects[i]->getDrawObject(), states);
	}
	_window->draw(map.getTileMaps()[(int)LAYER::FOREGROUND], states);
}

void RenderSystem::drawDebugStaticCollisions(const Dimension& map, LAYER layerID, const sf::Color& color)
{
	int sizeX = map.getTileMaps()[(int)layerID].getSizeX();
	int sizeY = map.getTileMaps()[(int)layerID].getSizeY();

	for(int y = 0; y < sizeY; y++) {
		for(int x = 0; x < sizeX; x++) {
			const StaticObject* obj = map.getTileMaps()[(int)layerID](x,y);
			if(obj->isCurrentlyColliding()) {
				drawDebugRectangle(x*_tileSize, y*_tileSize, _tileSize, _tileSize, sf::Color::Red);
			}
			else if(obj->isSolid()) {
				drawDebugRectangle(x*_tileSize, y*_tileSize, _tileSize, _tileSize, color);
			}
		}
	}
}

void RenderSystem::drawDebugDynamicCollisions(const Dimension& map)
{
	const std::vector<MovingObject*>& movingObjects = map.getMovingObjects();

	for(std::size_t i = 0; i < movingObjects.size(); i++) {
		MovingObject* object = movingObjects[i];
		bool colliding = object->isCurrentlyColliding();

		int x = (int)object->getPosition().x;
		int y = (int)object->getPosition().y;
		int w = object->getWidth();
		int h = object->getHeight();

		sf::Color color = colliding ? sf::Color::Red : sf::Color::Green;
		drawDebugRectangle(x, y, w, h, color);
	}
}

void RenderSystem::drawDebugGrid(int startX, int startY, int w, int h, const sf::Color color)
{
	for(int y = 0 ; y < h; y++) {
		for(int x = 0; x < w; x++) {
			drawDebugRectangle((startX + x)*_tileSize, (startY + y)*_tileSize, _tileSize, _tileSize, color);
		}
	}
}

void RenderSystem::drawDebugRectangle(int x, int y, int w, int h, const sf::Color& color)
{
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(color);
	rect.setOutlineThickness(1.0);
	rect.setSize(sf::Vector2f(w, h));
	rect.setPosition(sf::Vector2f(x, y));

	_window->draw(rect);
}

void RenderSystem::drawDebugPoint(int x, int y, const sf::Color& color)
{
	sf::CircleShape point;
	point.setFillColor(color);
	point.setOutlineColor(color);
	point.setOutlineThickness(1.0);
	point.setRadius(1);
	point.setPosition(x-1, y-1);
	point.setPointCount(8);

	_window->draw(point);
}

}