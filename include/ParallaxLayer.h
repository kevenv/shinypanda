#ifndef SPE_PARALLAX_LAYER_H
#define SPE_PARALLAX_LAYER_H

#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include "TileMap.h"

namespace spe
{

class ParallaxLayer
{
public:
	ParallaxLayer(float depth, int sizeX, int sizeY, tinyxml2::XMLElement** layerElement);
	~ParallaxLayer();

	void update(const sf::View& cameraView);
	inline void setView(const sf::View& cameraView) { _view = cameraView; }

	inline TileMap& accessTileMap() { return _map; }
	inline const TileMap& getTileMap() const { return _map; }
	inline const sf::View& getView() const { return _view; }

private:
	TileMap _map;
	//sf::Texture _texture;

	float _depth;
	sf::View _view;
};

}

#endif