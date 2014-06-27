#ifndef SPE_RENDER_SYSTEM_H
#define SPE_RENDER_SYSTEM_H

#include <SFML/Graphics.hpp>
#include <string>
#include "World.h"
#include "Dimension.h"

namespace spe
{

class AnimatedTile;

class RenderSystem
{
public:
	RenderSystem();

	void init(sf::RenderWindow& window, World& world);
	void render(const World& world);

	inline bool getDebugOverlayEnabled() const { return _debugOverlayEnabled; }
	inline void setDebugOverlayEnabled(bool debugOverlayEnabled) { _debugOverlayEnabled = debugOverlayEnabled; }

private:
	sf::RenderWindow* _window;
	sf::Texture _tileset;
	std::string _tilesetFilePath;
	int _tileSize;

	std::vector<AnimatedTile*> _animatedTiles; //do not empty this one

	bool _debugOverlayEnabled;

	void drawDebugStaticCollisions(const Dimension& map, LAYER layerID, const sf::Color& color);
	void drawDebugDynamicCollisions(const Dimension& map);
	void drawDebugGrid(int startX, int startY, int w, int h, const sf::Color color);
	void drawDebugRectangle(int x, int y, int w, int h, const sf::Color& color);
	void drawDebugPoint(int x, int y, const sf::Color& color);
};

}

#endif