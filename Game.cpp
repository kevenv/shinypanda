
#include "Game.h"

#include "GameState.h"
#include "Engine.h"

namespace spe
{

Game::Game()
{
}

Game::~Game()
{
}

void Game::init()
{
}

void Game::clear()
{
}

void Game::pause()
{
}

void Game::resume()
{
}

void Game::handleEvents(Engine* engine)
{
	sf::Event event;
    while (engine->getWindow()->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            engine->getWindow()->close();
			engine->quit();
		}
    }
}

void Game::update(float dt)
{
}

void Game::render(Engine* engine)
{
	sf::RenderWindow* window = engine->getWindow();

	sf::RectangleShape square(sf::Vector2f(30,30));
	square.setFillColor(sf::Color::Green);
	square.setPosition(40,40);
	window->draw(square);
}

}