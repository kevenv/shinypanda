/**
    @file SpeedVector2.h
    @author Vincent Girard <vin100_jrare@hotmail.com>
    @version 1.0

    @section LICENSE



    @section DESCRIPTION

    This file is the header/source of a class template representing a Vector with a maximum speed.
*/
#ifndef SPE_SPEED_VECTOR_2_H
#define SPE_SPEED_VECTOR_2_H

#include <SFML/Graphics.hpp> //For the graphics

#define ABS(x) ((x) < 0 ? -(x) : (x)) //Absolute value function
#define SGN(x) ((x) < 0 ? -1 : ((x) > 0 ? 1 : 0)) //Sign function

namespace spe
{

/**
    @class SpeedVector2 SpeedVector2.h "SpeedVector2.h"
    @brief A vector.

    This is a template class which represents a two-dimensional vector with the possibility of having a maximum absolute value for x and/or y.
*/
template < typename T >
class SpeedVector2
{
private:
    T _x; ///< X coordinate of the vector.
    T _y; ///< Y coordinate ofthe vector
    T _xMax; ///< Maximum absolute value of x. If the value is negative, it means there is no maximum value.
    T _yMax; ///< Maximum absolute value of y. If the value is negative, it means there is no maximum value.
    /**
    Verify if the values of x and y are within the maximal values.
    If not, change the value for the maximum value of the same sign.

    @return True if the values are within range, false otherwise.
    */
    bool verifMax();
public:
    /**
    Main constructor of the class.

    @param[in] x,y Initiale coordinates of the vector.
    @param[in] xMax,yMax Maximum absolute values of coordinates the vector.
    */
    SpeedVector2(T x = 0, T y = 0, T xMax = -1, T yMax = -1);
    /**
    Move the vector by a given offset then calls verifMax().

    @param[in] x,y Offsets.
    @return True if the new coordinates were within range, false otherwise.
    */
    bool move(T x, T y);
    /**
    Move the vector by a given offset then calls verifMax().

    @param[in] vector Offset.
    @return True if the new coordinates were within range, false otherwise.
    */
    bool move(const sf::Vector2<T> &vector);
    /**
    Reduce the absolute value of x by a given offset.
    The value given must be positive or the function has no effect.
    If the value is higher than x's absolute value, then x take the value 0.

    @param[in] x Offset.
    */
    void slowX(T x);
    /**
    Reduce the absolute value of y by a given offset.
    The value given must be positive or the function has no effect.
    If the value is higher than y's absolute value, then y take the value 0.

    @param[in] y Offset.
    */
    void slowY(T y);
    /**
    Set the x coordinate to its maximum value, with the same sign x had.
    If there is no maximum value for x, the function has no effect.
    */
    void maxSpeedX();
    /**
    Return a Vector2<T> object with the same coordinates as this vector.

    This function is mainly used for compatibility with the graphics engine.

    @return The associated Vector2<T> object.
    */
    sf::Vector2<T> getVector2() { return sf::Vector2<T>(_x,_y); }
    /**
    Verify if the coordinates of the vector are not the origin.

    @return False if both coordinates are 0, true otherwise.
    */
    bool isMoving() { return _x != 0 || _y != 0; }
    /**
    Get the direction of x.

    The possible values are: -1, 0 and 1.

    @return The sign of x.
    */
    int getDirectionX() { return SGN(_x); }
    /**
    Get the absolute value of x.

    @return The absolute value of x.
    */
    int getSpeedX() { return ABS(_x); }
    /**
    Get the x coordinate of the vector.

    @return the value of x.
    */
    T getX() { return _x; }
    /**
    Get the y coordinate of the vector.

    @return the value of y.
    */
    T getY() { return _y; }
    /**
    Get the maximum value of the x coordinate of the vector.

    If the value is negative, it means there are no maximum value for x.

    @return the maximum value of x.
    */
    T getXMax() { return _xMax; }
    /**
    Get the maximum value of the y coordinate of the vector.

    If the value is negative, it means there are no maximum value for x.

    @return the maximum value of y.
    */
    T getYMax() { return _yMax; }
    /**
    Set the new value of xMax then call verifMax().

    A strictly negative value means no maximum value for x.

    @param[in] xMax The new value of xMax.
    */
    void setXMax(T xMax);
    /**
    Set the new value of yMax then call verifMax().

    A strictly negative value means no maximum value for y.

    @param[in] yMax The new value of yMax.
    */
    void setYMax(T yMax);
    /**
    Set the new value of xMax and yMax then call verifMax().

    A strictly negative value means no maximum value for x/y.

    @param[in] xMax The new value of xMax.
    @param[in] yMax The new value of yMax.
    */
    void setMax(T xMax, T yMax);
};

template <typename T>
SpeedVector2<T>::SpeedVector2(T x, T y, T xMax, T yMax) : _x(x), _y(y), _xMax(xMax), _yMax(yMax)
{
    verifMax();
}

template <typename T>
bool SpeedVector2<T>::verifMax()
{
    bool inRange = true;
    if (_xMax >= 0 && ABS(_x) > _xMax)
    {
        _x = SGN(_x)*_xMax;
        inRange = false;
    }
    if (_yMax >= 0 && ABS(_y) > _yMax)
    {
        _y = SGN(_y)*_yMax;
        inRange = false;
    }
    return inRange;
}

template <typename T>
bool SpeedVector2<T>::move(T x, T y)
{
    _x += x;
    _y += y;
    return verifMax();
}

template <typename T>
bool SpeedVector2<T>::move(const sf::Vector2<T> &vector)
{
    _x += vector.x;
    _y += vector.y;
    return verifMax();
}

template <typename T>
void SpeedVector2<T>::slowX(T x)
{
    if (x > 0)
    {
        if (ABS(x) >= ABS(_x))
            _x = 0;
        else
            _x -= SGN(_x)*x;
    }
}

template <typename T>
void SpeedVector2<T>::slowY(T y)
{
	if (y > 0)
    {
        if (ABS(y) >= ABS(_y))
            _y = 0;
        else
            _y -= SGN(_y)*y;
    }
}

template <typename T>
void SpeedVector2<T>::maxSpeedX()
{
    if (_xMax > 0 && ABS(_x) != _xMax)
    {
        _x = SGN(_x)*_xMax;
    }
}

template <typename T>
void SpeedVector2<T>::setXMax(T xMax)
{
    _xMax = xMax;
    verifMax();
}

template <typename T>
void SpeedVector2<T>::setYMax(T yMax)
{
    _yMax = yMax;
    verifMax();
}

template <typename T>
void SpeedVector2<T>::setMax(T xMax, T yMax)
{
    _xMax = xMax;
    _yMax = yMax;
    verifMax();
}

}

#endif
