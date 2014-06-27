#ifndef SPE_CHARACTER_H
#define SPE_CHARACTER_H

#include <SFML/Graphics.hpp>
#include "SpeedVector2.h"
#include "MovingObject.h"

namespace spe
{

const int NB_CHARACTER_STATES = 7;
enum class CHARACTER_STATE
{
    STAND,
    WALK,
    RUN,
    JUMP,
    FALL,
    DUCK,
    DEAD,
};

class Character : public MovingObject
{
public:
	/*
	@param[in] fileSprite Path of the file containing the sprites.
	@param[in] filePosition Path of the file containing the infos of the sprites.
	@param[in] filePositionVersion Last version of the positionf file.
	@param[in] direction Direction of the sprite in the file. True = right, false = left.
	@param[in] x,y Initial position of the character.
	*/
	Character(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, bool direction, int x = 0, int y = 0);
	~Character();

	virtual void jump() = 0;
	virtual void run() = 0;
	virtual void walk() = 0;
	inline void kill() { _dead = true; }

	virtual const sf::Vector2f& getPosition() const override;

protected:
	int _direction; ///< The direction of the object. -1: left, 1: right.
	bool _initialDirection; ///< Direction the sprite is facing in the file. True = right, false = left.

	sf::Texture _sprites; ///< The textures where our sprite is. This variable is useless if _transparent is true.
	sf::Sprite _sprite; ///< The sprite of our object.

    CHARACTER_STATE _state; ///< Current state of the character.
    int _states[NB_CHARACTER_STATES][2]; /**< \brief Statix array containing information about the states.
                                        For each states, the first int is the first rect of the state and the second int is the number of rects.*/
    float _animationTime; ///< Current time of the animation.
    bool _dead; ///< If the character is dead.
    int _currentOffset; ///< Index of current offset.
    sf::IntRect* _spriteRects; ///< Dynamic array of the sprite rectangles.
    sf::Vector2i* _offsets; ///< Dynamic array of offsets.
    int _lCldSide; ///< the distance between the left side of the collision box and the hot spot. A negative number meaning the side is to the left of the hot spot.
    int _rCldSide; ///< the distance between the right side of the collision box and the hot spot. A negative number meaning the side is to the left of the hot spot.

	void update(float dt) override;

	virtual int getWidth() const override
	{
		int w = _sprite.getTextureRect().width;
		w = w < 0 ? -w : w; //TODO: Quickfix, texture rect shouldnt be negative..
		return w;
	}

	virtual int getHeight() const override
	{
		int h = _sprite.getTextureRect().height;
		h = h < 0 ? -h : h;//TODO: Quickfix, texture rect shouldnt be negative..
		return h;
	}

    /**
    Add dt to the time of the animation and refresh it. Usually called by update.

    @param[in] dt Time elapsed since the last refresh.
    */
    virtual void refreshAnimation(float dt) = 0;

    /**
    Get the index of the sprite IntRect associated with the current status.

    @return The index of the current sprite Rect.
    */
    int getSpriteRect();

	/**
	Refresh the sprite with the current status. Usually called by refreshAnimation.
	*/
	void refreshSprite();
	/**
	Change the direction of the object.
	*/
	void switchDirection();

	inline void changeState(CHARACTER_STATE state) { _state = state; }

	inline const sf::Sprite getSprite() const { return _sprite; } 

private:
    /**
    Read the file containing all the informations for the sprites: Number of images,
        position and size of the Sprite rectangles, offsets and
        index of first image and number of images for each state.

    @param[in] file Path of the file.
    @param[in] fileVersion Last version of the file.
    */
    void readPosition(const char* file, const int fileVersion);
};

}

#endif
