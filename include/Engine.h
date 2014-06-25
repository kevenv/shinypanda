#ifndef SPE_ENGINE_H
#define SPE_ENGINE_H

#include <stack>
#include <string>
#include <SFML/Graphics.hpp>
#include "DebugScreen.h"
#include "Config.h"

namespace spe
{

class GameState;

class Engine
{
public:
	Engine(int argc, char* argv[]);
	~Engine();

	int run();
	void handleEvents();

	void pushState(GameState* gameState);
	void popState();
	void changeState(GameState* gameState);

	void clear();

	inline sf::RenderWindow& getWindow() { return _window; }
	inline const sf::Event& getEvent() const { return _event; }
	inline const Config& getConfig() const { return _config; }
	inline void quit() { _running = false; }
	inline const sf::Vector2u& getWindowSize() const { return _window.getSize(); }

private:
	sf::RenderWindow _window;
	sf::Event _event;
	Config _config;

	std::stack<GameState*> _states;
	DebugScreen _debugScreen;
	bool _running;
	static std::string _version;
};

}

#endif
