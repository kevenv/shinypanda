
#include "TileMap.h"

#include <SFML/Graphics.hpp>
#include "tinyxml2.h"

#include "Level.h"

namespace spe {

TileMap::TileMap():
	_map(NULL),
	_sizeX(0),
	_sizeY(0)
{
}

TileMap::~TileMap()
{
	//Delete all layers
	//Does not delete the actual Tiles, this is handled by the ~Level()
	//Because another map could be using the same Tiles

	for(int y = 0; y < _sizeY; y++) {
		delete[] _map[y];
	}
	delete[] _map;
}

Tile* TileMap::operator()(int x, int y)
{
	return _map[y][x]; //TODO: CHECK BOUNDS??
}

void TileMap::load(int sizeX, int sizeY, tinyxml2::XMLElement** layerElement)
{
	_sizeX = sizeX;
	_sizeY = sizeY;

	//alloc layer
    _map = new Tile**[_sizeY];

    for(int i = 0; i < _sizeY ; i++) {
        _map[i] = new Tile*[_sizeX];
    }

    //load layer
    tinyxml2::XMLElement* dataElement = (*layerElement)->FirstChildElement("data");
    tinyxml2::XMLElement* tileElement = dataElement->FirstChildElement("tile");
    for(int y = 0; y < _sizeY; y++) {
        for(int x = 0; x < _sizeX; x++) {
			//create tile
            const int tileId = tileElement->FirstAttribute()->IntValue();
			Tile* tile = new Tile(x, y, tileId);
            _map[y][x] = tile;
			//_tilesPool.push_back(tile); //todo: HOW DO WE KNOW WICH OBJECT IS SHARED OR NOT???
            tileElement = tileElement->NextSiblingElement("tile");
        }
    }
}

void TileMap::setVertices(sf::Texture tileset, int tileSize, sf::Color color)
{
    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    _vertices.setPrimitiveType(sf::Quads);
    _vertices.resize(_sizeX * _sizeY * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
     for (int i = 0; i < _sizeX; ++i) {
        for (int j = 0; j < _sizeY; ++j) {
            // on r�cup�re le num�ro de tuile courant
            int tileNumber = _map[j][i]->_tileId - 1; //In TMX, tileset id start at 1 (0 is reserved)

            if(tileNumber == 35) continue; //skip tiles without texture

            // on en d�duit sa position dans la texture du tileset
            int tu = tileNumber % (tileset.getSize().x / tileSize);
            int tv = tileNumber / (tileset.getSize().x / tileSize);

            // on r�cup�re un pointeur vers le quad � d�finir dans le tableau de vertex
            sf::Vertex* quad = &_vertices[(i + j * _sizeX) * 4];

            // on d�finit ses quatre coins
            quad[0].position = sf::Vector2f(i * tileSize, j * tileSize);
            quad[1].position = sf::Vector2f((i + 1) * tileSize, j * tileSize);
            quad[2].position = sf::Vector2f((i + 1) * tileSize, (j + 1) * tileSize);
            quad[3].position = sf::Vector2f(i * tileSize, (j + 1) * tileSize);

            // on d�finit ses quatre coordonn�es de texture
            quad[0].texCoords = sf::Vector2f(tu * tileSize, tv * tileSize);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize, tv * tileSize);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize, (tv + 1) * tileSize);
            quad[3].texCoords = sf::Vector2f(tu * tileSize, (tv + 1) * tileSize);
			
			//blend texture with color
			quad[0].color = color;
			quad[1].color = color;
            quad[2].color = color;
            quad[3].color = color;
        }
    }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_vertices, states);
}

}