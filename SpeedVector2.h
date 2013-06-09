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
    T _x, _y;
    bool verifMax();
public:
    T _xMax, _yMax;
    SpeedVector2(T x = 0, T y = 0, T xMax = -1, T yMax = -1);
    bool move(T x, T y);
    bool move(const sf::Vector2<T> &vector);
    void slow(T x);
    sf::Vector2<T> getVector2() { return sf::Vector2<T>(_x,_y); }
    bool isMoving() { return _x != 0 || _y != 0; }
    int getDirectionX() { return SGN(_x); }
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
void SpeedVector2<T>::slow(T x)
{
    if (x > 0)
    {
        if (ABS(x) >= ABS(_x))
            _x = 0;
        else
            _x -= SGN(_x)*x;
    }
}

}

#endif
