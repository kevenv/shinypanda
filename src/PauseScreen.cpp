
#include "PauseScreen.h"

#include <SFML/Graphics.hpp>
#include "Engine.h"

namespace spe
{

PauseScreen::PauseScreen(Engine*const engine):
	_transparency(255)
{
	_font.loadFromFile("arial.ttf");

	_text.setString("PAUSE");
	_text.setCharacterSize(80);
	_text.setColor(sf::Color(255,255,255,_transparency));
	_text.setFont(_font);
	_text.setPosition(engine->getWindowSize().x/2-130, engine->getWindowSize().y/2-60);
}

PauseScreen::~PauseScreen()
{

}

void PauseScreen::init(Engine* engine)
{

}

void PauseScreen::clear()
{

}

void PauseScreen::handleEvents(Engine* engine)
{
	const sf::Event event = engine->getEvent();

    if(event.type == sf::Event::GainedFocus) {
		engine->popState();
	}
}

void PauseScreen::update(Engine* engine, float dt)
{
	static bool downMode = true;

	if(_transparency == 255 || downMode) {
		_transparency -= 4;
		downMode = true;
	}
	if(_transparency == 0) {
		_transparency += 3;
		downMode = false;
	}

	_text.setColor(sf::Color(255,255,255,_transparency));
}

void PauseScreen::render(Engine* engine)
{
    sf::RenderWindow& window = engine->accessWindow();
	window.setView(window.getDefaultView());
	window.clear(sf::Color::Black);

	window.draw(_text);
}

}
