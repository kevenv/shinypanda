
#include "ParallaxLayer.h"

namespace spe
{

ParallaxLayer::ParallaxLayer(float depth)
{
	_depth = depth / 10.0;
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