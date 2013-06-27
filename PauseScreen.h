#ifndef SPE_PAUSE_SCREEN_H
#define SPE_PAUSE_SCREEN_H

#include "GameState.h"
#include <SFML/Graphics.hpp>

namespace spe
{

class Engine;

class PauseScreen : public GameState
{
public:
	PauseScreen(Engine*const engine);
	~PauseScreen();

	void init(Engine* engine);
	void clear();

	void pause() {}
	void resume() {}

	void handleEvents(Engine* engine);
	void update(Engine* engine, float dt);
	void render(Engine* engine);

private:
	sf::Font _font;
	sf::Text _text;
	int _transparency;
};

}
#endif
