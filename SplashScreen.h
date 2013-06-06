#ifndef SPE_SPLASH_SCREEN
#define SPE_SPLASH_SCREEN

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
	void update(float dt);
	void render(Engine* engine);
};

}

#endif