#ifndef SPE_SPEED_VECTOR_2_H
#define SPE_SPEED_VECTOR_2_H

#include <SFML/Graphics.hpp>

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define SGN(x) ((x) < 0 ? -1 : ((x) > 0 ? 1 : 0))

namespace spe
{

template < typename T >
class SpeedVector2
{
private:
    T _x;
    T _y;
    T _xMax;
    T _yMax;

    /*
    Verify if the values of x and y are within the maximal values
    If not, change the value for the maximum value of the same sign
    */
    bool verifMax();

public:
    SpeedVector2(T x = 0, T y = 0, T xMax = -1, T yMax = -1);

    bool move(T x, T y);
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

    inline sf::Vector2<T> getVector2() const { return sf::Vector2<T>(_x,_y); }

    /**
	TODO : THE FUCK IS THAT??
    Verify if the coordinates of the vector are not the origin.

    @return False if both coordinates are 0, true otherwise.
    */
	inline bool isMoving() const { return _x != 0 || _y != 0; }

    /*
    Get the direction of x.
	The possible values are: -1, 0 and 1.
    */
	inline int getDirectionX() const { return SGN(_x); }

	/*
	TODO : THE FUCK IS THAT??
	*/
	inline int getSpeedX() const { return (int)ABS(_x); }

	inline T getX() const { return _x; }
	inline T getY() const { return _y; }
    inline T getXMax() const { return _xMax; }
	void setXMax(T xMax);
	inline T getYMax() const { return _yMax; }
    void setYMax(T yMax);
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
