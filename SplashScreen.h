#ifndef SPE_SPLASH_SCREEN
#define SPE_SPLASH_SCREEN

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameState.h"

namespace spe
{

class Engine;

class SplashScreen : public GameState
{
public:
	SplashScreen();
	~SplashScreen();

	void init();
	void clear();

	void pause();
	void resume();

	void handleEvents(Engine* engine);
	void update(Engine* engine, float dt);
	void render(Engine* engine);

private:
	sf::Clock _timer;
	sf::Texture _logo;
	sf::RectangleShape _square;
	int _transparency;
	sf::Music _thunder;
};

}

#endif
