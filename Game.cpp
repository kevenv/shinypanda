
#include "Game.h"

#include "GameState.h"
#include "Engine.h"
#include "Player.h"
#include "Camera.h"
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Log.h"

namespace spe
{

Game::Game(Engine* engine)
:
_player(Player("Player", "sprites.png", "sprites.txt", engine->getWindowSize().x/2, engine->getWindowSize().y/2)),
_camera(engine->getWindowSize().x, engine->getWindowSize().y, sf::Rect<int>(0,0,1920,1080))
{
	_font.loadFromFile("arial.ttf");

	_fpsText.setString("0");
	_fpsText.setCharacterSize(20);
	_fpsText.setColor(sf::Color::Red);
	_fpsText.setFont(_font);

	if(!_img.loadFromFile("test.png")) {
		Log(ERROR) << "Can't load image 'test.png'";
	}

	_square.setSize(sf::Vector2f(1920,1080));
	_square.setTexture(&_img);
	_square.setPosition(0,0);
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
        switch(event.type)
        {
            case sf::Event::Closed:
                engine->getWindow()->close();
                engine->quit();
                break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::LShift)
                    _player.run();
                break;
            case sf::Event::KeyReleased:
                if(event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::LShift)
                    _player.walk();
                break;
            default:
                break;
        }
    }
}

void Game::update(Engine* engine, float dt)
{
	_fps = (int)1/dt;
	_player.update(dt);
	_camera.follow(_player);
}

void Game::render(Engine* engine)
{
	sf::RenderWindow* window = engine->getWindow();

	window->setView(_camera.getView());

	window->draw(_square);
	window->draw(_player.getSprite());

	std::stringstream sstream;
	sstream << _fps;
	_fpsText.setString(sstream.str());

	window->draw(_fpsText);
}

}
