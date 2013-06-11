/**
    @file Character.h
    @author Vincent Girard <vin100_jrare@hotmail.com>
    @version 1.0

    @section LICENSE



    @section DESCRIPTION

    This file is the header of a class representing a character.
*/
#ifndef SPE_CHARACTER_H
#define SPE_CHARACTER_H

#include "SpeedVector2.h"
#include "Object.h"

#include <SFML/Graphics.hpp> //For the graphics

namespace spe
{
/**
    @enum CHARACTER_STATE
    @brief Each of the value represents of possible state of the character.
*/
enum CHARACTER_STATE
{
    STAND, ///< The character isn't moving.
    WALK, ///< The character is walking.
    RUN, ///< The character is running.
    JUMP, ///< The character is making a jump.
    FALL, ///< The character is falling or finished a jump.
    DUCK, ///< The character has ducked.
    DEAD, ///< The character died.
};

const int NB_CHARACTER_STATES = 7; ///< Number of states possibles.

/**
    @class Character Character.h "Character.h"
    @brief A character.

    This is an abstract class which represents a character moving on the map, like the player or an ennemy.
    It inherites Object.
*/
class Character : public Object
{
protected:
    SpeedVector2<float> _speed; ///< Current momentum of the character.
    CHARACTER_STATE _state; ///< Current state of the character.
    int _states[NB_CHARACTER_STATES][2]; /**< \brief Statix array containing information about the states.
                                        For each states, the first int is the first rect of the state and the second int is the number of rects.*/
    int _direction; ///< The direction of the character. -1: left, 1: right.
    float _animationTime; ///< Current time of the animation.
    bool _dead; ///< If the character is dead.
    int _currentOffset; ///< Index of current offset.
    sf::IntRect* _spriteRects; ///< Dynamic array of the sprite rectangles.
    sf::Vector2i* _offsets; ///< Dynamic array of offsets.
    /**
    Add dt to the time of the animation and refresh it. Usually called by update.

    @param[in] dt Time elapsed since the last refresh.
    */
    virtual void refreshAnimation(float dt) = 0;
    /**
    Refresh the sprite with the current status. Usually called by refreshAnimation.
    */
    virtual void refreshSprite();
    /**
    Change the direction of the Character.
    */
    virtual void switchDirection();
    /**
    Get the index of the sprite IntRect associated with the current status.

    @return The index of the current sprite Rect.
    */
    virtual int getSpriteRect();

private:
    /**
    Read the file containing all the informations for the sprites: Number of images,
        position and size of the Sprite rectangles, offsets and
        index of first image and number of images for each state.

    @param[in] file Path of the file.
    @param[in] fileVersion Last version of the file.
    */
    void readPosition(const char* file, const int fileVersion);

public:
    /**
    Main constructor for the class.

    @param[in] name Name of the character.
    @param[in] fileSprite Path of the file containing the sprites.
    @param[in] filePosition Path of the file containing the infos of the sprites.
    @param[in] filePositionVersion Last version of the positionf file.
    @param[in] x,y Initial position of the character.
    @param[in] inDream,inReal If the object is in the Dream/Real World or not.
    */
    Character(const char* name, const char* fileSprite, const char* filePosition, const int filePositionVersion, int x = 0, int y = 0, bool inDream = true, bool inReal = true);
    /**
    Destructor.

    Free all ressources attached to the character.
    */
    ~Character();

    /**
    Change the status of the character's death.
    */
    void switchDeath() { _dead = !_dead;}

    /**
    Check all possible change of status and move the character if needed.

    @param[in] dt Time elapsed since the last update.
    */
    virtual void update(float dt) = 0;
    /**
    Make the character jump.
    */
    virtual void jump() = 0;
    /**
    Change the character to run mode.
    */
    virtual void run() = 0;
    /**
    Change the character to walk mode.
    */
    virtual void walk() = 0;

    /**
    Verify if the speed of the last update was non-null.

    @return True if the character has moved, false otherwise.
    */
    virtual bool hasMoved() { return _speed.isMoving(); }

    /**
    Get the position of the center of the character.

    The center is calculated for a fixed point of the character to make sur the animation is fluid.
    It may be different from the position of the center of the sprite rectangle.

    @return Position of the center, in pixels.
    */
    virtual sf::Vector2f getPosition();
};

}

#endif
