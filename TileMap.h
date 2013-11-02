#ifndef SPE_TILEMAP_H
#define SPE_TILEMAP_H

#include <SFML/Graphics.hpp>
#include "tinyxml2.h"

namespace spe
{

class Tile;

class TileMap: public sf::Drawable, public sf::Transformable
{
public:
	TileMap();
	~TileMap();

	void load(int sizeX, int sizeY, tinyxml2::XMLElement** layerElement);
	void setVertices(sf::Texture tileset, int tileSize, sf::Color color = sf::Color::White);
	Tile* operator()(int x, int y);

	const sf::VertexArray& getVertices() const { return _vertices; }

private:
	Tile*** _map; //2D Array of Tile*
	int _sizeX;
	int _sizeY;

	sf::VertexArray _vertices;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}

#endif