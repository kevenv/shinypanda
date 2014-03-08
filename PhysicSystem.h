#ifndef SPE_PHYSIC_SYSTEM
#define SPE_PHYSIC_SYSTEM

#include <vector>

namespace spe
{
class World;
class MovingObject;
class StaticObject;

//Collision box
class AABB
{
public:
	int _x;
	int _y;
	int _w;
	int _h;

	AABB();
	AABB(int x, int y, int w, int h);

	inline void set(int x, int y, int w, int h)
	{
		_x = x;
		_y = y;
		_w = w;
		_h = h;
	}

	inline void set(int x, int y)
	{
		_x = x;
		_y = y;
	}

	inline bool isColliding(const AABB& box) const
	{
		return _x <= (box._x + box._w) &&
			   box._x <= (_x + _w) &&
			   _y <= (box._y + box._h) &&
			   box._y <= (_y + _h);
	}

	inline bool isValid() const
	{
		return _x != -1 && _y != -1 && _w != -1 && _h != -1;
	}
};

//Detect and handle collisions:
//static collisions (tilemap grid collision)
//dynamic collisions (AABB)
//simulate forces such as, gravity, friction, ...
class PhysicSystem
{
public:
	PhysicSystem();

	void update(World& world, float dt);

private:
	bool isColliding(int x, int y, const StaticObject* staticObject, const World& world) const;
	std::vector<StaticObject*> isColliding(const MovingObject* movingObject, World& world) const;
};

}

#endif