
#include "Game.h"
#include "Engine.h"
#include "PauseScreen.h"
#include "World.h"
#include "Camera.h"
#include "Player.h"
#include "Panda.h"
#include "MovingObject.h"
#include "CollisionEvent.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#define MAX_ITERATION_COLLISION 3

namespace spe
{

Game::Game(Engine* engine)
{
    _player = NULL;
}

Game::~Game()
{
    for(std::size_t i = 0; i < _collisionEvents.size(); i++)
    {
        delete _collisionEvents[i];
    }
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
    moveObjects(dt);
    handleCollision();
    _world.getCurrentLevel().update(dt);
	_camera.follow(*_player, dt);
}

void Game::moveObjects(float dt)
{
    std::vector<MovingObject*> objects = _world.getCurrentLevel().getMovingObjects();
    for(std::size_t i = 0; i < objects.size(); i++)
    {
        objects[i]->updateStatus(dt);
    }
}

void Game::handleCollision()
{
    std::vector<MovingObject*> objects = _world.getCurrentLevel().getMovingObjects();
    for(std::size_t i = 0; i < objects.size(); i++)
    {
        MovingObject* obj = objects[i];
        if(obj->hasMoved())
        {
            bool moved = true;
            for(int j = 0; moved && j < MAX_ITERATION_COLLISION; j++)
            {
                // TODO (vincent#1#): for(all tiles) verifyCollision;
                for(std::size_t k = 0; k < objects.size(); k++)
                {
                    MovingObject* obj2 = objects[k];
                    if(i != k && obj->isColliding(*obj2))
                    {
                        // TODO (vincent#1#): if(obj->needToMove()) obj->move();
                        if(!obj->hasCollided(*obj2)) obj->collide(_collisionEvents, *obj2);
                        if(!obj2->hasCollided(*obj)) obj2->collide(_collisionEvents, *obj);
                    }
                }
            }
        }
    }
    handleCollisionEvents();
}

void Game::handleCollisionEvents()
{
    for(std::size_t i = 0; i < _collisionEvents.size(); i++)
    {
        switch(_collisionEvents[i]->getType())
        {
        case KILL_PLAYER:
            _player->kill();
            break;
        default:
            break;
        }
        delete _collisionEvents[i];
    }
    _collisionEvents.clear();
}

void Game::render(Engine* engine)
{
	sf::RenderWindow* window = engine->getWindow();

	window->setView(_camera.getView());
	window->draw(_world);
}

}
