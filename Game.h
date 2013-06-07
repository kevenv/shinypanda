#ifndef SPE_GAME_H
#define SPE_GAME_H

#include "GameState.h"
#include <SFML/Graphics.hpp>

namespace spe
{

class Engine;

class Game : public GameState
{
public:
	Game();
	~Game();

	void init();
	void clear();

	void pause();
	void resume();

	void handleEvents(Engine* engine);
	void update(float dt);
	void render(Engine* engine);
private:
	int _fps;
	sf::Text _fpsText;
	sf::Font _font;
};

}

#endif