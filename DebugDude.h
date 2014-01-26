
#ifndef SPE_DEBUG_DUDE_H
#define SPE_DEBUG_DUDE_H

#include <SFML/Graphics.hpp>
#include "MovingObject.h"

namespace spe
{

/*
Simple moving object controllable by keyboard, used for debug ONLY
*/
class DebugDude : public MovingObject
{
public:
	DebugDude(int x, int y, int w, int h, const sf::Color& color, bool move = true);

    virtual void update(float dt) override;
    virtual void updateStatus(float dt) override;

	virtual const sf::Vector2f& getPosition() const override;
	virtual int getWidth() const override;
	virtual int getHeight() const override;

private:
	sf::RectangleShape _shape;
	static const int _maxSpeed = 2;
	bool _move;
};

}

#endif