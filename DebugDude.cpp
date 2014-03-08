
#include "DebugDude.h"

namespace spe
{

DebugDude::DebugDude(int x, int y, int w, int h, const sf::Color& color, bool move)
	:MovingObject("Debug Dude", x, y),
	_shape(sf::Vector2f(w,h)),
	_move(move)
{
	_shape.setPosition(x, y);
	_shape.setSize(sf::Vector2f(w,h));
	_shape.setFillColor(color);

	_collideBox.set(x, y, w, h);
	_drawObject = &_shape;
}

void DebugDude::update(float dt)
{
	//no animation
}

void DebugDude::updateStatus(float dt)
{
	if(!_move) return;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		_shape.move(-_maxSpeed, 0);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		_shape.move(_maxSpeed, 0);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		_shape.move(0, -_maxSpeed);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		_shape.move(0, _maxSpeed);
	}

	_collideBox.set(_shape.getPosition().x, _shape.getPosition().y, _shape.getSize().x, _shape.getSize().y);
}

const sf::Vector2f& DebugDude::getPosition() const
{
	return _shape.getPosition();
}

int DebugDude::getWidth() const
{
	return _shape.getSize().x;
}

int DebugDude::getHeight() const
{
	return _shape.getSize().y;
}

}