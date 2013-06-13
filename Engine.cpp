
#include "Engine.h"

#include "GameState.h"
#include "Game.h"
#include "SplashScreen.h"
#include "Log.h"
#include "Config.h"
#include <stack>
#include <string>
#include <sstream>

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
	char* configFilePath = "shinypanda.cfg";
	if(_config.parse(configFilePath)) {
        Log() << "Config: file '" << configFilePath << "' parsed successfully" << std::endl;
        //init SFMLs
        int windowWidth = _config.getValue<int>("engine.window.width");
        int windowHeight = _config.getValue<int>("engine.window.height");

        sf::Uint32 windowOptions = 0;
        int fpsLimit = _config.getValue<int>("engine.fps");
        bool vsyncEnable = _config.getValue<bool>("engine.vsync");
        _window.create(sf::VideoMode(windowWidth, windowHeight), windowTitle);//, windowOptions);

        if(vsyncEnable) {
            _window.setVerticalSyncEnabled(true);
        }
        else {
            _window.setFramerateLimit(fpsLimit);
        }
        _running = true;

        Log() << "window = " << windowWidth << "x" << windowHeight << std::endl;
        Log() << "FPS = " << fpsLimit << " vsync = " << vsyncEnable << std::endl;
	}
	else {
        _running = false;
	}
}

Engine::~Engine()
{
}

int Engine::run()
{
	_debugScreen.init();
	changeState(new SplashScreen());

	sf::Clock clock;
	float elapsedTime = 0;

	while(_running) {
		handleEvents();

		_states.top()->update(this, elapsedTime);
		_debugScreen.update(this, elapsedTime);

		_window.clear(sf::Color::Black);

		_states.top()->render(this);
		_debugScreen.render(this);

		_window.display();
		elapsedTime = clock.restart().asSeconds();
	}

	clear();
	_debugScreen.clear();

	return 0;
}

void Engine::handleEvents()
{
	while (_window.pollEvent(_event))
    {
		_states.top()->handleEvents(this);
		_debugScreen.handleEvents(this);
	}
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
