#ifndef SPE_ENGINE_H
#define SPE_ENGINE_H

#include <stack>
#include <string>
#include <SFML/Graphics.hpp>

namespace spe
{

class GameState;

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

	inline sf::RenderWindow* getWindow() { return &_window; }
	inline void quit() { _running = false; }

private:
	bool _running;
	std::stack<GameState*> _states;
	static std::string _version;
	sf::RenderWindow _window;
};

}

#endif