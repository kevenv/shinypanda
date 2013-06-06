#ifndef SPE_ENGINE_H
#define SPE_ENGINE_H

#include <stack>
#include "GameState.h"

namespace spe
{

class Engine
{
public:
	Engine(int argc, char* argv[]);
	~Engine();

	int run();

	void pushState(GameState* gameState);
	void popState();
	void changeState(GameState* gameState);

	void clear();

private:
	bool _running;
	std::stack<GameState*> _states;
};

}

#endif