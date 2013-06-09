
#include "Camera.h"

#include "Character.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace spe
{

Camera::Camera(int w, int h, sf::Rect<int> worldLimits, int x, int y)
:
	_speed(0,0),
	_worldLimits(0,0,0,0)
{
	_view.reset(sf::FloatRect(x, y, w, h));
	setWorldLimits(worldLimits);
}

void Camera::follow(Character& character)
{
	sf::Vector2f pos = character.getSprite().getPosition();
	sf::IntRect size = character.getSprite().getTextureRect();

	float x = pos.x + size.width/2;
	float y = pos.y + size.height/2;

	//L T W H

	//	 T
	// L  W
	//   H
	if(x < _worldLimits.left) {
		x = _worldLimits.left;
	}
	else if(x > _worldLimits.width) {
		x = _worldLimits.width;
	}

	if(y < _worldLimits.top) {
		y = _worldLimits.top;
	}
	else if(y > _worldLimits.height) {
		y = _worldLimits.height;
	}

	_view.setCenter(x, y);
}

void Camera::follow(Character& character, float dt)
{
	sf::Vector2f pos = character.getSprite().getPosition();
	sf::IntRect size = character.getSprite().getTextureRect();

	float x = pos.x + size.width/2;
	float y = pos.y + size.height/2;

	//L T W H

	//	 T
	// L  W
	//   H
	if(x < _worldLimits.left) {
		x = _worldLimits.left;
	}
	else if(x > _worldLimits.width) {
		x = _worldLimits.width;
	}

	if(y < _worldLimits.top) {
		y = _worldLimits.top;
	}
	else if(y > _worldLimits.height) {
		y = _worldLimits.height;
	}

	float camX = _view.getCenter().x;
	float camY = _view.getCenter().y;
	
	//std::cout << x << "," << y << "| " << camX << "," << camY << std::endl;

	//std::cout << _speed.x << std::endl;

	if(abs(x-camX) <= 1 && abs(y-camY) <= 1) { //(int)x == (int)camX && (int)y == (int)camY) {
		_speed.x = 0;//*= 0.5;
		_speed.y = 0;//*= 0.5;
		_view.setCenter(x, y);
		//std::cout << "stop" << std::endl;
	}
	else {
		if(abs(_speed.x) < 100) {
			int xSpeed = (x - camX) > 0 ? 1 : -1;
			_speed.x += 4 * xSpeed;
		}
		if(abs(_speed.y) < 100) {
			int ySpeed = (y - camY) > 0 ? 1 : -1;
			_speed.y += 4 * ySpeed;
		}

		camX += _speed.x * dt;
		camY += _speed.y * dt;

		_view.setCenter(camX, camY);
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