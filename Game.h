#ifndef SPE_GAME_H
#define SPE_GAME_H

#include "GameState.h"

#include "Player.h"
#include "Camera.h"
#include <SFML/Graphics.hpp>

namespace spe
{

class Engine;

class Game : public GameState
{
public:
	Game(Engine* engine);
	~Game();

	void init();
	void clear();

	void pause();
	void resume();

	void handleEvents(Engine* engine);
	void update(Engine* engine, float dt);
	void render(Engine* engine);

private:
    Player _player;
	Camera _camera;
	int _fps;
	sf::Text _fpsText;
	sf::Font _font;
	sf::RectangleShape _square;
	sf::Texture _img;
};

}

#endif
