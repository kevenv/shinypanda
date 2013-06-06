
#include "Engine.h"

#include "GameState.h"
#include "Game.h"
#include "Log.h"
#include <stack>

namespace spe
{

Engine::Engine(int argc, char* argv[])
{
	Log() << "test";
	//load config
	//init SFML
}

Engine::~Engine()
{
}

int Engine::run()
{
	changeState(new Game());

	while(_running) {
		_states.top()->handleEvents();
		_states.top()->update(30.0);
		_states.top()->render();
		//flip buffer
		//sleep
	}

	clear();

	return 0;
}

void Engine::changeState(GameState* gameState)
{
	popState();
	pushState(gameState);
}

void Engine::popState()
{
	if(!_states.empty()) {
		_states.top()->clear(); 
		delete _states.top();
		_states.pop();
	}

	if(!_states.empty()) {
		_states.top()->resume();
	}
}

void Engine::pushState(GameState* gameState)
{
	if(!_states.empty()) {
		_states.top()->pause();
	}

	_states.push(gameState);
	_states.top()->init();
}

void Engine::clear()
{
	while(!_states.empty()) {
		_states.top()->clear();
		delete _states.top();
		_states.pop();
	}
}

}