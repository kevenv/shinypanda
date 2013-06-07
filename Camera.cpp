
#include "Camera.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace spe
{

Camera::Camera(int w, int h, int x, int y)
:_speed(1,1)
{
	_view.reset(sf::FloatRect(x, y, w, h));
}

void Camera::move(int x, int y, int dt)
{
	//_view.move(sf::Vector2f(x*dt, y*dt));
	sf::Vector2f pos = _view.getSize();	
	float cx = x+100;
	float cy = y+100;
	_view.setCenter((pos.x-cx)/2, (pos.y-cy)/2);
}

void Camera::follow(Character& character)
{
	sf::Vector2f pos = character.getSprite().getPosition();
	sf::IntRect size = character.getSprite().getTextureRect();

	int scrollX = 0;
	int scrollY = 0;

	if(!character.isMoved()) {
		return;
	}

	if(pos.x < 0) {
		std::cout << "collide -X" << std::endl;
		scrollX = -1;
	}
	else if(pos.x+size.width > 800) {
		std::cout << "collide X" << std::endl;
		scrollX = 1;
	}

	if(pos.y < 0) {
		std::cout << "collide Y" << std::endl;
		scrollY = -1;
	}
	else if(pos.y+size.height > 600) {
		std::cout << "collide Y" << std::endl;
		scrollY = 1;
	}

	if(scrollX != 0 || scrollY != 0) {
		_view.move(sf::Vector2f(scrollX * _speed.x, scrollY * _speed.y));
	}

	/*float cX = pos.x + size.width/2;
	float cY = pos.y + size.height/2;

	float wX = _view.getSize().x/2;
	float wY = _view.getSize().y/2;

	float x = 800/2;//wX-cX;
	float y = 600/2;//wY-cY;

	_view.setCenter(x,y);*/
}

}