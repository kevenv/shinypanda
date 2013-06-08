
#include "Camera.h"
#include "Character.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace spe
{

Camera::Camera(int w, int h, int x, int y)
:_speed(1,1)
{
	_view.reset(sf::FloatRect(x, y, w, h));
}

void Camera::follow(Character& character)
{
	sf::Vector2f pos = character.getSprite().getPosition();
	sf::IntRect size = character.getSprite().getTextureRect();

	int windowX = _view.getSize().x;
	int windowY = _view.getSize().y;

	float x = pos.x + size.width/2;// - windowX/2;
	float y = pos.y + size.height/2;// - windowY/2;

	std::cout << pos.x << ", " << pos.y << std::endl;
	int offset = 200;
	sf::Rect<int> limits(-100+windowX/2, 0+windowY/2, 1000/2, 1000/2+offset);

	if(x < limits.left) {
		x = limits.left;
	}
	else if(x > limits.height) {
		x = limits.height;
	}

	if(y < limits.top) {
		y = limits.top;
	}
	else if(y > limits.width) {
		y = limits.width;
	}

	_view.setCenter(x, y);
}

}