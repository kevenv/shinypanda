#ifndef SPE_GAME_H
#define SPE_GAME_H

#include "GameState.h"
#include "RenderSystem.h"
#include "PhysicSystem.h"
#include "World.h"

namespace spe
{

class Engine;
class Player;
class Camera;

//Load world, play world,
//manage game logic using game systems
//interact with user inputs
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
	RenderSystem _renderSystem;
	PhysicSystem _physicSystem;

	Camera* _camera;	//ptr to cam in world
	Player* _player;	//ptr to player in objects list in world
};

}

#endif
