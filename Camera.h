#ifndef SPE_CAMERA_H
#define SPE_CAMERA_H

#include <SFML/Graphics.hpp>
#include "Character.h"

namespace spe
{

class Camera
{
public:
	Camera(int w, int h, sf::Rect<int> worldLimits, int x = 0, int y = 0);

	void follow(Character& character);
	void follow(Character& character, float dt);

	void setWorldLimits(sf::Rect<int> limits);
	inline void setWindowSize(int w, int h) { _view.setSize(sf::Vector2f(w,h)); }
	inline void setCenter(int x, int y) { _view.setCenter(x, y); }

	inline const sf::View getView() const { return _view; }
	inline const sf::Vector2f getCenter() const { return _view.getCenter(); }
	inline const sf::Vector2f getWindowSize() const { return _view.getSize(); }
	inline const sf::Rect<int> setWorldLimits() const { return _worldLimits; }

private:
	sf::View _view;
	sf::Vector2f _speed;
	sf::Rect<int> _worldLimits;
};

}

#endif