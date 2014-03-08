
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

void PhysicSystem::udpate(World& world, float dt)
{
	Dimension& map = world.getCurrentMap();

	//move
	std::vector<MovingObject*> objects = map.getMovingObjects();
	for(std::size_t i = 0; i < objects.size(); i++) {
		objects[i]->updateStatus(dt);
	}

	const std::vector<MovingObject*>& movingObjects = map.getMovingObjects();

	//collision detection (static object)
	for(std::size_t i = 0; i < movingObjects.size(); i++) {
		MovingObject* object = movingObjects[i];

		std::vector<Object*> lastCollidingObjects = object->getCurrentlyCollidingObjects();
		std::vector<StaticObject*> collideList = isColliding(object, world); //will NEVER contain dynamic objects
		for(int j = 0; j < collideList.size(); j++) {
			StaticObject* staticObject = collideList[j];
			staticObject->addCurrentlyColliding(object);
			object->addCurrentlyColliding(staticObject);
		}

		//remove static objects that are not colliding anymore
		for(std::size_t j = 0; j < lastCollidingObjects.size(); j++) {
			Object* objectB = lastCollidingObjects[j];

			std::vector<StaticObject*>::const_iterator start = collideList.begin();
			std::vector<StaticObject*>::const_iterator end = collideList.end();
			std::vector<StaticObject*>::const_iterator it = std::find(start, end, objectB);
			bool found = it != end;
			if(!found) {
				objectB->removeCurrentlyColliding(object); //will remove dynamic objects that might be still be colliding, but its okay since they will be re-added later if they are still colliding
				object->removeCurrentlyColliding(objectB);
			}
		}
	}

	//collision detection (dynamic objects)
	for(std::size_t i = 0; i < movingObjects.size(); i++) {
		MovingObject* objectA = movingObjects[i];

		//dynamic objects
		for(std::size_t j = 0; j < movingObjects.size(); j++) {
			MovingObject* objectB = movingObjects[j];

			if(i == j) continue; //skip collision on self

			bool colliding = objectA->isColliding(*objectB);
			if(colliding) {
				objectA->addCurrentlyColliding(objectB);
			}
			/*else if(objectA->isCurrentlyColliding(objectB)) { //will never happen
				objectA->removeCurrentlyColliding(objectB);
			}*/
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
