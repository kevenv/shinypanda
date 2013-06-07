#ifndef SPE_CAMERA_H
#define SPE_CAMERA_H

#include <SFML/Graphics.hpp>
#include "Character.h"

namespace spe
{

class Camera
{
public:
	Camera(int w, int h, int x = 0, int y = 0);
	void move(int x, int y, int dt);
	void follow(Character& character);
	inline const sf::View& getView() const { return _view; }

private:
	sf::View _view;
	sf::Vector2f _speed;
};

}

#endif