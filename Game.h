#ifndef SPE_GAME_H
#define SPE_GAME_H

#include "GameState.h"

namespace spe
{

class Game : public GameState
{
public:
	Game();
	~Game();

	void init();
	void clear();

	void pause();
	void resume();

	void handleEvents();
	void update(float dt);
	void render();
};

}

#endif