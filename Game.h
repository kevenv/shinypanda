#ifndef SPE_GAME_H
#define SPE_GAME_H

#include "GameState.h"
#include "Camera.h"
#include "World.h"

namespace spe
{

class Engine;
class Player;

class Game : public GameState
{
public:
	Game(Engine* engine);
	~Game();

	void init(Engine* engine);
	void clear();

	void pause();
	void resume();

	void handleEvents(Engine* engine);
	void update(Engine* engine, float dt);
	void render(Engine* engine);

private:
    World _world;
	Camera _camera;
	Player* _player;
};

}

#endif
