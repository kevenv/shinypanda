
#include "SplashScreen.h"
#include "Engine.h"
#include "Game.h"

namespace spe
{

SplashScreen::SplashScreen()
{
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

void SplashScreen::update(float dt)
{
}

void SplashScreen::render(Engine* engine)
{
	sf::RenderWindow* window = engine->getWindow();

	sf::RectangleShape square(sf::Vector2f(30,30));
	square.setFillColor(sf::Color::Red);
	window->draw(square);
}

}