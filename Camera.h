/**
    @file Camera.h
    @author Keven Villeneuve <kev.v@hotmail.com>
    @version 1.0

    @section LICENSE



    @section DESCRIPTION

    Represent and control the game world's Camera.
*/
#ifndef SPE_CAMERA_H
#define SPE_CAMERA_H

#include <SFML/Graphics.hpp>
#include "Character.h"

namespace spe
{
/**
    @class Camera Camera.h "Camera.h"
    @brief The game world's Camera

	This is the class to control the game's Camera.
*/
class Camera
{
public:
	/**
	Default constructor

	Build a Camera with the view not setted.
	After this call the Camera isn't ready to be used, you must define it's parameters first.
	*/
    Camera();

    /**
    Main constructor

    Build a Camera with all it's parameters defined.
    After this call the Camera is ready to be used.

    @param[in] w 			Width of the Camera's view.
    @param[in] h 			Height of the Camera's view.
    @param[in] worldLimits 	Game World limits.
    @param[in] x 			Position x of the center of the Camera.
    @param[in] y 			Position y of the center of the Camera.
    */
	Camera(int w, int h, sf::Rect<int> worldLimits, int x = 0, int y = 0);

	/**
	Make the Camera follow a Character.
	The camera instantly follow the character.

	@param[in] character 	The character to follow.
	*/
	void follow(Character& character);

	/**
	Make the Camera gradually follow a Character.
	The Camera is going to follow the Character at a constant speed;

	@param[in] character 	The character to follow.
	@param[in] dt 			Delta of time.
	*/
	void follow(Character& character, float dt);


	/**
	Set the position of the center of the camera.

	@param[in] x 	New x position of the center of the camera.
	@param[in] y 	New y position of the center of the camera.
	*/
    inline void setCenter(int x, int y) { _view.setCenter(x, y); }

    /**
    Set the window size/view size.

    @param[in] w 	New window width.
    @param[in] h 	New window height.
	*/
    inline void setWindowSize(int w, int h) { _view.setSize(sf::Vector2f(w,h)); }

    /**
    Set the game world limits.

    @param[in] limits 	New game world limits.
	*/
	void setWorldLimits(const sf::Rect<int>& limits);

	/**
	Set the camera's scrolling speed.

	@param[in] speed 	New scrolling speed.
	*/
	inline void setSpeed(const sf::Vector2f& speed) { _speed = speed; }


	/**
	View getter.

	@return The view handled by the camera.
	*/
	inline const sf::View& getView() const { return _view; }

	/**
	Camera's center position getter.

	@return The camera's center position.
	*/
	inline const sf::Vector2f& getCenter() const { return _view.getCenter(); }

	/**
	Camera's window size getter.
	
	@return The camera's window size.
	*/
	inline const sf::Vector2f& getWindowSize() const { return _view.getSize(); }

	/** 
	World limits getter.

	@return The game world limits.
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

	/**
	Camera's scroll speed vector getter.

	@return The camera's scroll speed vector.
	*/
	inline const sf::Vector2f& getSpeed() const { return _speed; }

	/**
	Camera assignement operator
	*/
	Camera& operator=(const Camera& camera);

private:
	sf::View      _view; 		///< SFML view modified by the camera.
	sf::Vector2f  _speed; 		///< Scrolling speed vector of the camera.
	sf::Rect<int> _worldLimits; ///< Limits of the game world (level dimensions).

	bool _stopScrollingX; ///< If true scrolling stop on x world limits
	bool _stopScrollingY; ///< If true scrolling stop on y world limits

	/**
	Get the position to center the camera, taking into account the scrolling of the screen.
	
    @param[in] x 		x position from wich to adjust the scrolling.
    @param[in] y 		y position from wich to adjust the scrolling.
    @param[in] targetX 	adjusted x position to center camera and scroll screen.
    @param[in] targetY 	adjusted y position to center camera and scroll screen.
    */
	void scroll(int x, int y, int& targetX, int& targetY) const;
};

}

#endif
