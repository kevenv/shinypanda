#ifndef SPE_PARALLAX_LAYER_H
#define SPE_PARALLAX_LAYER_H

#include <SFML/Graphics.hpp>

#include "TileMap.h"

namespace spe
{

class ParallaxLayer {
public:
	ParallaxLayer(float depth);
	~ParallaxLayer();

	void update(const sf::View& cameraView);
	void setView(const sf::View& cameraView) { _view = cameraView; }

	TileMap& getTileMap() { return _map; }
	const sf::View& getView() const { return _view; }

private:
	TileMap _map;
	sf::Texture _texture;

	float _depth;
	sf::View _view;
};

}

#endif