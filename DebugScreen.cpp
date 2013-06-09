
#include "DebugScreen.h"

#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

namespace spe
{

DebugScreen::DebugScreen()
{
	_font.loadFromFile("arial.ttf");

	_fpsText.setString("0 FPS");
	_fpsText.setCharacterSize(20);
	_fpsText.setPosition(10,10);
	_fpsText.setColor(sf::Color::Red);
	_fpsText.setFont(_font);

	_active = false;
}

DebugScreen::~DebugScreen()
{
}

void DebugScreen::init()
{
}

void DebugScreen::clear()
{
}

void DebugScreen::handleEvents(Engine* engine)
{
	sf::Event event = engine->getEvent();

    switch(event.type)
    {
	case sf::Event::KeyPressed:
		if(event.key.code == sf::Keyboard::F3) {
			_active = !_active;
		}
		break;
	default:
		break;
    }
}

void DebugScreen::update(Engine* engine, float dt)
{
	_fps = (int)1/dt;
}

void DebugScreen::render(Engine* engine)
{
	if(_active) {
		sf::RenderWindow* window = engine->getWindow();
		window->setView(window->getDefaultView());

		std::stringstream sstream;
		sstream << _fps;
		_fpsText.setString(sstream.str() + " FPS");

		window->draw(_fpsText);
	}
}

}
