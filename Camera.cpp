/**
    @file Camera.h
    @author Keven Villeneuve <kev.v@hotmail.com>
    @version 1.0

    @section LICENSE



    @section DESCRIPTION

    Represent and control the game world's Camera.
*/
#include "Camera.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"

namespace spe
{

Camera::Camera():
	_stopScrollingX(false),
	_stopScrollingY(false),
    _speed(0,0),
    _worldLimits(0,0,0,0)
{
    _view.reset(sf::FloatRect(0, 0, 0, 0));
}

Camera::Camera(int w, int h, sf::Rect<int> worldLimits, int x, int y)
:
	_speed(5,5),
	_worldLimits(0,0,0,0)
{
	_view.reset(sf::FloatRect(x, y, w, h));
	setWorldLimits(worldLimits);
}

Camera& Camera::operator=(const Camera& camera)
{
	sf::Vector2f center = camera.getCenter();
	sf::Vector2f windowSize = camera.getWindowSize();

	_view.reset(sf::FloatRect(center.x, center.y, windowSize.x, windowSize.y));

	_speed = camera.getSpeed();
	_worldLimits = camera.getWorldLimits();

	return *this;
}

void Camera::follow(Character& character)
{
    int x = 0;
    int y = 0;
    sf::Vector2f pos = character.getPosition();

    scroll(pos.x, pos.y, x, y);
	_view.setCenter(x, y);
}

void Camera::follow(Character& character, float dt)
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
	//if(!_stopScrollingX) return;
	if(x < _worldLimits.left) {
		targetX = _worldLimits.left;
	}
	else if(x > _worldLimits.width) {
		targetX = _worldLimits.width;
	}

	//if(!_stopScrollingY) return;
	if(y < _worldLimits.top) {
		targetY = _worldLimits.top;
	}
	else if(y > _worldLimits.height) {
		targetY = _worldLimits.height;
	}
}

void Camera::setWorldLimits(const sf::Rect<int>& limits)
{
	const int windowX = _view.getSize().x;
	const int windowY = _view.getSize().y;

	/*if(limits.left == 0 && limits.width == 0) {
		_stopScrollingX = true;
		_worldLimits.left = 0;
		_worldLimits.width = 0;
	}
	else {*/
		_worldLimits.left = limits.left + windowX/2;
		_worldLimits.width = limits.width - windowX/2;
	//}

	/*if(limits.top == 0 && limits.height == 0) {
		_stopScrollingY = true;
		_worldLimits.top = 0;
		_worldLimits.height = 0;
	}
	else {*/
		_worldLimits.top = limits.top + windowY/2;
		_worldLimits.height = limits.height - windowY/2;
	//}
}

}
