#ifndef SPE_DEBUG_SCREEN_H
#define SPE_DEBUG_SCREEN_H

#include "GameState.h"
#include <SFML/Graphics.hpp>

namespace spe
{

class Engine;

class DebugScreen : public GameState
{
public:
	DebugScreen();
	~DebugScreen();

	void init();
	void clear();

	void pause() {}
	void resume() {}

	void handleEvents(Engine* engine);
	void update(Engine* engine, float dt);
	void render(Engine* engine);

private:
	int _fps;
	sf::Text _fpsText;
	sf::Font _font;

	bool _active;
};

}

#endif