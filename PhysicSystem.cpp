
#include "PhysicSystem.h"
#include <vector>
#include "World.h"

namespace spe
{

AABB::AABB()
:	_x(-1),
	_y(-1),
	_w(-1),
	_h(-1)
{

}

AABB::AABB(int x, int y, int w, int h)
:	_x(x),
	_y(y),
	_w(w),
	_h(h)
{

}

PhysicSystem::PhysicSystem()
{

}

void PhysicSystem::update(World& world, float dt)
{
	Dimension& map = world.getCurrentMap();
	std::vector<MovingObject*>& movingObjects = map.getMovingObjects();

	for(std::size_t i = 0; i < movingObjects.size(); i++) {
		//move objects
		movingObjects[i]->updateStatus(dt);

		//clear objects collisions
		movingObjects[i]->clearCurrentlyColliding();
	}

	//clear static objects collisions
	StaticObject*** rawMap = map.getPlaygroundMap();
	for(int y = 0; y < map.getSizeY(); y++)
	{
		for(int x = 0; x < map.getSizeX(); x++)
		{
			rawMap[y][x]->clearCurrentlyColliding();
		}
	}

	//collision detection (static object)
	for(std::size_t i = 0; i < movingObjects.size(); i++) {
		MovingObject* object = movingObjects[i];

		std::vector<StaticObject*> collideList = isColliding(object, world); //will NEVER contain dynamic objects
		for(int j = 0; j < collideList.size(); j++) {
			StaticObject* staticObject = collideList[j];
			staticObject->addCurrentlyColliding(object);
			object->addCurrentlyColliding(staticObject);
		}
	}

	//collision detection (dynamic objects)
	for(std::size_t i = 0; i < movingObjects.size(); i++) {
		MovingObject* objectA = movingObjects[i];

		//dynamic objects
		for(std::size_t j = 0; j < movingObjects.size(); j++) {
			MovingObject* objectB = movingObjects[j];

			if(i == j) continue; //skip collision on self

			if(objectA->isColliding(*objectB)) {
				objectA->addCurrentlyColliding(objectB);
			}
		}
	}
}

std::vector<StaticObject*> PhysicSystem::isColliding(const MovingObject* movingObject, World& world) const
{
	std::vector<StaticObject*> collideList;
	Dimension& map = world.getCurrentMap();
	StaticObject*** rawMap = map.getPlaygroundMap();
	int x = movingObject->getPosition().x;
	int y = movingObject->getPosition().y;
	int w = movingObject->getWidth();
	int h = movingObject->getHeight();

    int minX = world.positionToTileCoords(x);
    int maxX = world.positionToTileCoords(x+w);
    int minY = world.positionToTileCoords(y);
    int maxY = world.positionToTileCoords(y+h);

    for(int indexX = minX; indexX <= maxX; indexX++) {
        for(int indexY = minY; indexY <= maxY; indexY++) {
            if(map.inRange(indexX,indexY)) {
                StaticObject* staticObject = rawMap[indexY][indexX];
                if(isColliding(indexX, indexY, staticObject, world)) {
                    collideList.push_back(staticObject);
                }
            }
        }
    }

	return collideList;
}

bool PhysicSystem::isColliding(int x, int y, const StaticObject* staticObject, const World& world) const
{
	return staticObject->isSolid();
}

}
