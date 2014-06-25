
#include "SplashScreen.h"
#include "Engine.h"
#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>

namespace spe
{

SplashScreen::SplashScreen()
{
	_timer.restart();
	_logo.loadFromFile("logo.png");
	_square.setSize(sf::Vector2f(_logo.getSize().x, _logo.getSize().y));
	_square.setPosition((800-_logo.getSize().x)/2, (600-_logo.getSize().y)/2);
	_transparency = 0;
	_square.setTexture(&_logo);

	_thunder.openFromFile("thunder.wav");
	_thunder.play();
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::init(Engine* engine)
{
}

void SplashScreen::clear()
{
}

void SplashScreen::pause()
{
}

void SplashScreen::resume()
{
}

void SplashScreen::handleEvents(Engine* engine)
{
	sf::Event event = engine->getEvent();

    if (event.type == sf::Event::Closed) {
        engine->changeState(new Game(engine));
	}
	else if(event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape) {
			engine->changeState(new Game(engine));
		}
	}
}

void SplashScreen::update(Engine* engine, float dt)
{
	float upTime = 4;
	float waitTime = 2;
	float downTime = 4;

	if(_timer.getElapsedTime().asSeconds() < upTime && _transparency < 255) {
		_transparency += 1;
		_square.setFillColor(sf::Color(255,255,255,_transparency));
	}
	else if(_timer.getElapsedTime().asSeconds() > (upTime + waitTime) &&
		    _timer.getElapsedTime().asSeconds() < (upTime + waitTime + downTime) &&
			_transparency > 0) {
		_transparency -= 1;
		_square.setFillColor(sf::Color(255,255,255,_transparency));
	}
	else if (_timer.getElapsedTime().asSeconds() > (upTime + waitTime + downTime)) {
		engine->changeState(new Game(engine));
	}
}

void SplashScreen::render(Engine* engine)
{
	sf::RenderWindow& window = engine->getWindow();
	window.clear(sf::Color::Black);

	window.draw(_square);
}

}
