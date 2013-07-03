#ifndef SPE_GAME_H
#define SPE_GAME_H

#include "GameState.h"
#include "Camera.h"
#include "World.h"
#include "CollisionEvent.h"

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
	std::vector<CollisionEvent*> _collisionEvents; ///< A dynamic array containing all the events related to collisions in a frame.

    /**
    Call every movingObject's updateStatus() function.
    */
    void moveObjects(float dt);
    /**
    Verify every possible collision for every object and if there is a collision, call the function needed to resolve it.
    At the end, it calls handleCollisionEvents.
    */
    void handleCollision();
    /**
    Handle the events related to this frame's collisions, call the related function and then clear the array of events.
    Usually called by handleCollision().
    */
    void handleCollisionEvents();
};

}

#endif
