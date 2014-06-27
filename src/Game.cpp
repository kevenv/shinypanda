
#include "Game.h"

#include "Engine.h"
#include "PauseScreen.h"
#include "World.h"
#include "Camera.h"
#include "Player.h"
#include "MovingObject.h"
#include "RenderSystem.h"
#include "PhysicSystem.h"

namespace spe
{

Game::Game(Engine* engine)
:	_camera(nullptr),
	_player(nullptr)
{
}

Game::~Game()
{
	_camera = nullptr;
	_player = nullptr;
}

void Game::init(Engine* engine)
{
	_world.setWindowSize(engine->getWindowSize().x, engine->getWindowSize().y);
    _world.load("test.tmx");

	_player = _world.accessPlayerPtr();
	_camera = _world.accessCameraPtr();

	_renderSystem.init(engine->accessWindow(), _world);
	//_physicSystem.init();
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
	const sf::Event& event = engine->getEvent();

    switch(event.type) {
	case sf::Event::LostFocus:
		engine->pushState(new PauseScreen(engine));
		break;
    case sf::Event::Closed:
        engine->accessWindow().close();
        engine->quit();
        break;
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::LShift)
            _player->run();
		else if(event.key.code == sf::Keyboard::Escape)
			engine->quit();
		if(event.key.code == sf::Keyboard::Q)
			_renderSystem.setDebugOverlayEnabled(!_renderSystem.getDebugOverlayEnabled());
        break;
    case sf::Event::KeyReleased:
        if(event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::LShift)
            _player->walk();
        break;
	}
}

void Game::update(Engine* engine, float dt)
{
	_physicSystem.update(_world, dt);
    _world.update(dt);
	_camera->follow(*_player, dt);
}

void Game::render(Engine* engine)
{
	_renderSystem.render(_world);
}

}
