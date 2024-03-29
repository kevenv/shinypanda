
#include "Camera.h"

#include <SFML/Graphics.hpp>
#include "Character.h"

namespace spe
{

Camera::Camera():
    _speed(0,0),
    _worldLimits(0,0,0,0),
	_view(sf::FloatRect(0, 0, 0, 0)),
	_followMode(true)
{
}

Camera::Camera(int w, int h, sf::Rect<int> worldLimits, int x, int y):
	_speed(1,1),
	_worldLimits(0,0,0,0),
	_view(sf::FloatRect(x, y, w, h)),
	_followMode(true)
{
	setWorldLimits(worldLimits);
}

Camera& Camera::operator=(const Camera& camera)
{
	sf::Vector2f center = camera.getCenter();
	sf::Vector2f windowSize = camera.getWindowSize();

	_view.reset(sf::FloatRect(center.x, center.y, windowSize.x, windowSize.y));

	_speed = camera.getSpeed();
	_worldLimits = camera.getWorldLimits();
	_followMode = camera._followMode;

	return *this;
}

void Camera::follow(Character& character)
{
    int x = 0;
    int y = 0;
    sf::Vector2f pos = character.getPosition();

    scroll((int)pos.x, (int)pos.y, x, y);
	_view.setCenter(x, y);
}

void Camera::follow(Character& character, float dt)
{
	if(_followMode == true) {
		followCinematic(character, dt);
	}
	else {
		followNormal(character, dt);
	}
}

void Camera::followNormal(Character& character, float dt)
{
	if(character.getPosition().x > _view.getSize().x/2 && character.getPosition().x < _worldLimits.width) {
		_view.move(character.getSpeed().getX()*_speed.x, 0);
	}

	if(character.getPosition().y > _view.getSize().y/2 && character.getPosition().y < _worldLimits.height) {
		_view.move(0, character.getSpeed().getY()*_speed.y);
	}
}

void Camera::followCinematic(Character& character, float dt)
{
	const float camX = _view.getCenter().x;
	const float camY = _view.getCenter().y;

	//lerp : V(t) = A + (B-A) * t
	//Linear Interpolation from Camera's center to Character's center
	const sf::Vector2f pos = character.getPosition();
	int x, y;
	x = (int)( camX + (pos.x - camX) * _speed.x*dt );
	y = (int)( camY + (pos.y - camY) * _speed.y*dt );

	scroll(x, y, x, y);
	_view.setCenter(x, y);
}

void Camera::scroll(int x, int y, int& targetX, int& targetY) const
{
    targetX = x;
    targetY = y;

    //L T W H

	//	 T
	// L  W
	//   H
	//stop the scrolling when out of limits
	if(x < _worldLimits.left) {
		targetX = _worldLimits.left;
	}
	else if(x > _worldLimits.width) {
		targetX = _worldLimits.width;
	}

	if(y < _worldLimits.top) {
		targetY = _worldLimits.top;
	}
	else if(y > _worldLimits.height) {
		targetY = _worldLimits.height;
	}
}

void Camera::setWorldLimits(const sf::Rect<int>& limits)
{
	const int windowX = (int)_view.getSize().x;
	const int windowY = (int)_view.getSize().y;

	_worldLimits.left = limits.left + windowX/2;
	_worldLimits.width = limits.width - windowX/2;
	_worldLimits.top = limits.top + windowY/2;
	_worldLimits.height = limits.height - windowY/2;
}

}
