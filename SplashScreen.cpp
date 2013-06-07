
#include "SplashScreen.h"
#include "Engine.h"
#include "Game.h"

namespace spe
{

SplashScreen::SplashScreen()
{
	_timer.restart();
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::init()
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
	sf::Event event;
    while (engine->getWindow()->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            engine->changeState(new Game());
		}
    }
}

void SplashScreen::update(Engine* engine, float dt)
{
	if(_timer.getElapsedTime().asSeconds() >= 3) {
		engine->changeState(new Game());
	}
}

void SplashScreen::render(Engine* engine)
{
	sf::RenderWindow* window = engine->getWindow();

	sf::RectangleShape square(sf::Vector2f(30,30));
	square.setFillColor(sf::Color::Red);
	window->draw(square);

	sf::Texture logo;
	logo.loadFromFile("logo.png");

	sf::RectangleShape logoR(sf::Vector2f(logo.getSize().x, logo.getSize().y));
	logoR.setPosition((800-logo.getSize().x)/2, (600-logo.getSize().y)/2);
	logoR.setTexture(&logo);
	window->draw(logoR);
}

}