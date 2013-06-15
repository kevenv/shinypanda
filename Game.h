#ifndef SPE_GAME_H
#define SPE_GAME_H

#include "GameState.h"

#include "Player.h"
#include "Camera.h"
#include "Panda.h"
#include "World.h"

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
    Panda _panda;
	Camera _camera;
	World _world;
};

}

#endif
