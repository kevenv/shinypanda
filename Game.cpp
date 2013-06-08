
#include "Game.h"

#include "GameState.h"
#include "Engine.h"
#include "Player.h"
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Log.h"

namespace spe
{

Game::Game(Engine* engine)
:
_player(Player("Player", "sprites.png", 8, 9, 800/2, 600/2)),
_camera(engine->getWindowSize().x, engine->getWindowSize().y)
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

void Game::update(Engine* engine, float dt)
{
	_fps = 1/dt;
	_player.update(dt);
	_camera.follow(_player);
	//_camera.move(_player.getPos().x, _player.getPos().y, dt);
}

void Game::render(Engine* engine)
{
	sf::RenderWindow* window = engine->getWindow();

	sf::RectangleShape square(sf::Vector2f(1000,1000));
	square.setFillColor(sf::Color::Green);
	square.setPosition(-100,0);

	window->setView(_camera.getView());

	window->draw(square);
	window->draw(_player.getSprite());

	std::stringstream sstream;
	sstream << _fps;
	_fpsText.setString(sstream.str());

	window->draw(_fpsText);
}

}
