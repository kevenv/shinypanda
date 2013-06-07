
#include "Engine.h"

#include "GameState.h"
#include "Game.h"
#include "Log.h"
#include <stack>
#include <string>
#include <sstream>

#include "SplashScreen.h"

namespace spe
{

std::string Engine::_version = "0.1.0";

Engine::Engine(int argc, char* argv[])
{
	std::stringstream sstream;
	sstream << _version;
	std::string windowTitle = "Shiny Panda Engine v" + sstream.str();

	Log() << windowTitle;
	//parseArgs(argc, argv);
	//load config
	//init SFML
	int windowWidth = 800;
	int windowHeight = 600;

	sf::Uint32 windowOptions = 0;
	int fpsLimit = 60;

	_window.create(sf::VideoMode(windowWidth, windowHeight), windowTitle);//, windowOptions);

	//_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(fpsLimit);
}

Engine::~Engine()
{
}

int Engine::run()
{
	changeState(new SplashScreen());

	sf::Clock clock;
	float elapsedTime = 0;

	while(_running) {
		_states.top()->handleEvents(this);
		_states.top()->update(this, elapsedTime);
		_window.clear();
		_states.top()->render(this);
		_window.display();
		elapsedTime = clock.restart().asSeconds();
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
