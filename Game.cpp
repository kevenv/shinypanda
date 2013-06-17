
#include "Game.h"

#include "GameState.h"
#include "Engine.h"
#include "Player.h"
#include "Camera.h"
#include "Log.h"
#include "PauseScreen.h"
#include "World.h"
#include <SFML/Graphics.hpp>

namespace spe
{

Game::Game(Engine* engine)
:
_player(Player("Player", "sprites.png", "sprites.txt", 2, true, engine->getWindowSize().x/2, engine->getWindowSize().y/2)),
_panda(Panda("Panda", "panda.jpg", "panda.txt", 1, false, engine->getWindowSize().x*3/4, engine->getWindowSize().y/2)),
_camera(engine->getWindowSize().x, engine->getWindowSize().y, sf::Rect<int>(0,0,0,0))
{
}

Game::~Game()
{
}

void Game::init()
{
    _world.load("test.world");
    int tileSize = 64;
    _camera.setWorldLimits(sf::Rect<int>(0,0,_world.getWorldSizeX()*tileSize, _world.getWorldSizeY()*tileSize));
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
	sf::Event event = engine->getEvent();

    switch(event.type)
    {
	case sf::Event::LostFocus:
		engine->pushState(new PauseScreen(engine));
		break;
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
	}
}

void Game::update(Engine* engine, float dt)
{
	_player.update(dt);
	_panda.update(dt);
	_camera.follow(_player, dt);
}

void Game::render(Engine* engine)
{
	sf::RenderWindow* window = engine->getWindow();

	window->setView(_camera.getView());

	window->draw(_world);
	window->draw(_player.getSprite());
	window->draw(_panda.getSprite());
}

}
