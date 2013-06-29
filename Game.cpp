
#include "Game.h"

#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "PauseScreen.h"
#include "World.h"
#include "Camera.h"
#include "Player.h"
#include "Panda.h"

namespace spe
{

Game::Game(Engine* engine)
{
    _player = NULL;
}

Game::~Game()
{
}

void Game::init(Engine* engine)
{
    //init world
    _world.load("test.world");
    int tileSize = 64;

    //init moving objects
    Level& level = _world.getCurrentLevel();
    _player = new Player("Player", "sprites.png", "sprites.txt", 2, true, engine->getWindowSize().x/2, engine->getWindowSize().y/2);
    level.addMovingObject(_player);
    Panda* _panda = new Panda("Panda", "panda.jpg", "panda.txt", 1, false, engine->getWindowSize().x*3/4, engine->getWindowSize().y/2);
    level.addMovingObject(_panda);

    //init camera
    _camera.setWindowSize(engine->getWindowSize().x, engine->getWindowSize().y);
    _camera.setWorldLimits(sf::Rect<int>(0,0,_world.getWorldSizeX()*tileSize, _world.getWorldSizeY()*tileSize));
    _camera.setSpeed(sf::Vector2f(5,5));
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
            _player->run();
		else if(event.key.code == sf::Keyboard::Escape)
			engine->quit();
        break;
    case sf::Event::KeyReleased:
        if(event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::LShift)
            _player->walk();
        break;
	}
}

void Game::update(Engine* engine, float dt)
{
    _world.getCurrentLevel().update(dt);
	_camera.follow(*_player, dt);
}

void Game::render(Engine* engine)
{
	sf::RenderWindow* window = engine->getWindow();

	window->setView(_camera.getView());
	window->draw(_world);
}

}
