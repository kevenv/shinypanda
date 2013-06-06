#ifndef SPE_GAME_STATE_H
#define SPE_GAME_STATE_H

namespace spe
{

class Engine;

class GameState
{
public:
	GameState() { }
	virtual ~GameState() { }

	virtual void init() = 0;
	virtual void clear() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void handleEvents(Engine* engine) = 0;
	virtual void update(float dt) = 0;
	virtual void render(Engine* engine) = 0;
};

}

#endif