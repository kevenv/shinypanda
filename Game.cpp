
#include "Game.h"

#include "GameState.h"
#include "Engine.h"
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

namespace spe
{

Game::Game()
{
	_font.loadFromFile("arial.ttf");

	_fpsText.setString("0");
	_fpsText.setCharacterSize(20);
	_fpsText.setColor(sf::Color::Red);
	_fpsText.setFont(_font);
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
    if (engine->getWindow()->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            engine->getWindow()->close();
			engine->quit();
		}
    }
}

void Game::update(float dt)
{
	_fps = 1/dt;
}

void Game::render(Engine* engine)
{
	sf::RenderWindow* window = engine->getWindow();

	sf::RectangleShape square(sf::Vector2f(30,30));
	square.setFillColor(sf::Color::Green);
	square.setPosition(40,40);
	window->draw(square);

	std::stringstream sstream;
	sstream << _fps;
	_fpsText.setString(sstream.str());

	window->draw(_fpsText);
}

}