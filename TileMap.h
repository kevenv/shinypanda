#ifndef SPE_TILEMAP_H
#define SPE_TILEMAP_H

#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include "Object.h"

namespace spe
{

class StaticObject : public Object
{

public:
	StaticObject(int x, int y, int tileId)
	{
		_x = x;
		_y = y;
		_tileId = tileId;
		_active = true;
	}

	int _tileId;

private:


	int _x;
	int _y;

	bool _active;
};

class AnimatedTile : public StaticObject
{
public:
	AnimatedTile();

private:

};

class TileMap: public sf::Drawable, public sf::Transformable
{
public:
	TileMap();
	~TileMap();

	void load(int sizeX, int sizeY, tinyxml2::XMLElement** layerElement);
	void setVertices(sf::Texture tileset, int tileSize, sf::Color color = sf::Color::White);
	StaticObject* operator()(int x, int y);

	const sf::VertexArray& getVertices() const { return _vertices; }

private:
	StaticObject*** _map; //2D Array of Tile*
	int _sizeX;
	int _sizeY;

	sf::VertexArray _vertices;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}

#endif