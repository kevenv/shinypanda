#ifndef SPE_RENDER_SYSTEM_H
#define SPE_RENDER_SYSTEM_H

#include <SFML/Graphics.hpp>
#include <string>
#include "World.h"

namespace spe
{
class AnimatedTile;

enum LAYER
{
	FOREGROUND,
	PLAYGROUND,
	BACKGROUND
};

class RenderSystem
{
public:
	RenderSystem();
	void init(sf::RenderWindow& window, World& world);
	void render(const World& world);

private:
	sf::RenderWindow* _window;
	sf::Texture _tileset;
	std::string _tilesetFilePath;
	int _tileSize;

	std::vector<AnimatedTile*> _animatedTiles; //do not empty this one
};

}

#endif