
#include "DebugScreen.h"

#include <SFML/Graphics.hpp>
#include <sstream>
#include "Engine.h"

namespace spe
{

DebugScreen::DebugScreen():
	_active(true),
	_fps(0)
{
	_font.loadFromFile("arial.ttf");

	_fpsText.setString("0 FPS");
	_fpsText.setCharacterSize(20);
	_fpsText.setPosition(10,10);
	_fpsText.setColor(sf::Color::Red);
	_fpsText.setFont(_font);
}

DebugScreen::~DebugScreen()
{

}

void DebugScreen::init(Engine* engine)
{

}

void DebugScreen::clear()
{

}

void DebugScreen::handleEvents(Engine* engine)
{
	const sf::Event event = engine->getEvent();

    if(event.type == sf::Event::KeyPressed) {
		if(event.key.code == sf::Keyboard::F3) {
			_active = !_active;
		}
    }
}

void DebugScreen::update(Engine* engine, float dt)
{
	_fps = (int)(1/dt);
}

void DebugScreen::render(Engine* engine)
{
	if(_active) {
		sf::RenderWindow& window = engine->accessWindow();
		window.setView(window.getDefaultView());

		std::stringstream sstream;
		sstream << _fps;
		_fpsText.setString(sstream.str() + " FPS");

		window.draw(_fpsText);
	}
}

}
