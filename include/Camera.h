#ifndef SPE_CAMERA_H
#define SPE_CAMERA_H

#include <SFML/Graphics.hpp>
#include "Character.h"

namespace spe
{

class Camera
{
public:
    Camera(); //After this call the Camera isn't ready to be used, you must define it's parameters first.
	Camera(int w, int h, sf::Rect<int> worldLimits, int x = 0, int y = 0);
	Camera& operator=(const Camera& camera);

	void follow(Character& character);
	void follow(Character& character, float dt);

	inline const sf::View& getView() const { return _view; }

	inline const sf::Vector2f& getCenter() const { return _view.getCenter(); }
    inline void setCenter(int x, int y) { _view.setCenter(x, y); }

	inline const sf::Vector2f& getWindowSize() const { return _view.getSize(); }
    inline void setWindowSize(int w, int h) { _view.setSize(sf::Vector2f(w,h)); }

	/**
	sf::Rect Left Top Width Height
	Limits   Left Top Right Bottom

	TOP

	-----------
	-		  -
	LEFT  -  WORLD  -  WIDTH
	-		  -
	-----------

	HEIGHT
	*/
	inline const sf::Rect<int>& getWorldLimits() const { return _worldLimits; }
	void setWorldLimits(const sf::Rect<int>& limits);

	inline const sf::Vector2f& getSpeed() const { return _speed; }
	inline void setSpeed(const sf::Vector2f& speed) { _speed = speed; }

	inline void setFollowMode(bool cinematicMode) { _followMode = cinematicMode; }

private:
	sf::View      _view; 		///< SFML view modified by the camera.
	sf::Vector2f  _speed; 		///< Scrolling speed vector of the camera.
	sf::Rect<int> _worldLimits; ///< Limits of the game world (level dimensions).
	bool _followMode;

	void scroll(int x, int y, int& targetX, int& targetY) const;
	void followNormal(Character& character, float dt);
	void followCinematic(Character& character, float dt);
};

}

#endif
