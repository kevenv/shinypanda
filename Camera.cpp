
#include "Camera.h"

#include "Character.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace spe
{

Camera::Camera(int w, int h, sf::Rect<int> worldLimits, int x, int y)
:
	_speed(5,5),
	_worldLimits(0,0,0,0)
{
	_view.reset(sf::FloatRect(x, y, w, h));
	setWorldLimits(worldLimits);
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
	float camX = _view.getCenter().x;
	float camY = _view.getCenter().y;

    //lerp : V(t) = A + (B-A) * t
    sf::Vector2f pos = character.getPosition();
    int x, y;
    int v = 200;
    x = camX;
    y = camY;
    x += v*dt;

    std::cout << x << std::endl;

    //x = (int)( camX + (pos.x - camX) * _speed.x*dt );
    //y = (int)( camY + (pos.y - camY) * _speed.y*dt );

    //scroll(x, y, x, y);
    _view.setCenter(x, y);
}

void Camera::scroll(int x, int y, int& targetX, int& targetY)
{
    targetX = x;
    targetY = y;

    //L T W H

	//	 T
	// L  W
	//   H
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

void Camera::setWorldLimits(sf::Rect<int> limits)
{
	int windowX = _view.getSize().x;
	int windowY = _view.getSize().y;

	_worldLimits.left = limits.left + windowX/2;
	_worldLimits.top = limits.top + windowY/2;
	_worldLimits.width = limits.width - windowX/2;
	_worldLimits.height = limits.height - windowY/2;
}

}
