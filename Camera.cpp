
#include "Camera.h"
#include "Character.h"
#include <SFML/Graphics.hpp>

namespace spe
{

Camera::Camera(int w, int h, int x, int y)
{
	_view.reset(sf::FloatRect(x, y, w, h));
}

void Camera::follow(Character& character)
{
	sf::Vector2f pos = character.getSprite().getPosition();
	sf::IntRect size = character.getSprite().getTextureRect();

	int windowX = _view.getSize().x;
	int windowY = _view.getSize().y;

	float x = pos.x + size.width/2 - windowX/2;
	float y = pos.y + size.height/2 - windowY/2;

	//if(x < 0) {
	//	x = 0;
	//}

	//if(y < 0) {
	//	y = 0;
	//}

	//_view.reset(sf::FloatRect(x, y, 800, windowY));
	_view.setCenter(x + windowX/2, y + windowY/2);
}

}