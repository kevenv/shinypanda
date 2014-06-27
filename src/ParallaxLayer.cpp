
#include "ParallaxLayer.h"

#include <SFML/Graphics.hpp>

namespace spe
{

ParallaxLayer::ParallaxLayer(float depth, int sizeX, int sizeY, tinyxml2::XMLElement** layerElement):
	_depth(depth / 10.0f)
{
	_map.load(sizeX, sizeY, layerElement);
}

ParallaxLayer::~ParallaxLayer()
{
}

void ParallaxLayer::update(const sf::View& cameraView)
{
	sf::Vector2f newCenter(cameraView.getCenter().x * _depth, cameraView.getCenter().y);
	_view.setCenter(newCenter);
}

}