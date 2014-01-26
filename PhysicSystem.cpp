
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

	//collision detection (dynamic objects)
	const std::vector<MovingObject*>& movingObjects = map.getMovingObjects();

	for(std::size_t i = 0; i < movingObjects.size(); i++) {
		MovingObject* objectA = movingObjects[i];

		for(std::size_t j = 0; j < movingObjects.size(); j++) {
			MovingObject* objectB = movingObjects[j];

			if(i == j) continue; //skip collision on self

			bool colliding = objectA->isColliding(*objectB);

			if(colliding) {
				objectA->addCurrentlyColliding(objectB);
			}
			else if(objectA->isCurrentlyColliding(objectB)) {
				objectA->removeCurrentlyColliding(objectB);
			}
		}
	}

	//collision detection (static object)
	int sizeX = map.getTileMaps()->getSizeX();
	int sizeY = map.getTileMaps()->getSizeY();
	StaticObject*** rawMap = map.getPlaygroundMap();

	for(std::size_t i = 0; i < movingObjects.size(); i++) {
		MovingObject* object = movingObjects[i];

		/*std::vector<StaticObject*> collideList = isColliding(object, world);
		if(!collideList.empty()) {

			for(int i = 0; i < collideList.size(); i++) {
				StaticObject* staticObject = collideList[i];

				if(!object->isCurrentlyColliding(staticObject)) {
					staticObject->addCurrentlyColliding(object);
					object->addCurrentlyColliding(staticObject);
				}
			}
		}*/

		//else remove currently colliding for other in list of this object

		//check map
		for(int y = 0; y < sizeY; y++) {
			for(int x = 0; x < sizeX; x++) {
				StaticObject* staticObject = rawMap[y][x];

				if(isColliding(object, staticObject, world)) {
					staticObject->addCurrentlyColliding(object);
					object->addCurrentlyColliding(staticObject);
				}
				else if(staticObject->isCurrentlyColliding(object)){
					staticObject->removeCurrentlyColliding(object);
					object->removeCurrentlyColliding(staticObject);
				}
			}
		}
	}
}
/*
AABB PhysicSystem::isColliding(const MovingObject* movingObject, World& world) const
{
	float posX = movingObject->getPosition().x;
	float posY = movingObject->getPosition().y;
	int objW = movingObject->getWidth();
	int objH = movingObject->getHeight();

	int x = world.positionToTileCoords(posX);
	int y = world.positionToTileCoords(posY);
	int w = world.positionToTileCoords(objW);
	int h = world.positionToTileCoords(objH);

	StaticObject*** rawMap = world.getCurrentMap().getPlaygroundMap();
	for(; y < h; y++) {
		for(; x < w; x++) {
			StaticObject* staticObject = rawMap[y][x];

			if(staticObject->isSolid()) break;
		}
	}

	AABB box(x, y, w, h);
	return box;
}*/

std::vector<StaticObject*> PhysicSystem::isColliding(const MovingObject* movingObject, World& world) const
{
	std::vector<StaticObject*> collideList;
	Dimension& map = world.getCurrentMap();
	StaticObject*** rawMap = world.getCurrentMap().getPlaygroundMap();
	int x = world.positionToTileCoords(movingObject->getPosition().x);
	int y = world.positionToTileCoords(movingObject->getPosition().y);
	int w = world.positionToTileCoords(movingObject->getWidth());
	int h = world.positionToTileCoords(movingObject->getHeight());

	StaticObject* staticObject = nullptr;
	if(map.inRange(x,y)) {
		staticObject = rawMap[y][x];
		if(isColliding(x, y, staticObject, world)) {
			collideList.push_back(staticObject);
		}
	}
	if(map.inRange(x+w,y)) {
		staticObject = rawMap[y][x + w];
		if(isColliding(x+w, y, staticObject, world)) {
			collideList.push_back(staticObject);
		}
	}
	if(map.inRange(x,y+h)) {
		staticObject = rawMap[y + h][x];
		if(isColliding(x, y+h, staticObject, world)) {
			collideList.push_back(staticObject);
		}
	}
	if(map.inRange(x+w,y+h)) {
		staticObject = rawMap[y + h][x + w];
		if(isColliding(x+w, y+h, staticObject, world)) {
			collideList.push_back(staticObject);
		}
	}
	return collideList;
}

bool PhysicSystem::isColliding(const MovingObject* movingObject, const StaticObject* staticObject, const World& world) const
{
	float posX = movingObject->getPosition().x;
	float posY = movingObject->getPosition().y;
	int gridX = staticObject->getGridX();
	int gridY = staticObject->getGridY();
	int tileX, tileY;
	world.positionToTileCoords(posX, posY, tileX, tileY);

	if(tileX == gridX && tileY == gridY && staticObject->isSolid()) {
		return true;
	}
	else {
		return false;
	}
}

bool PhysicSystem::isColliding(int x, int y, const StaticObject* staticObject, const World& world) const
{
	int gridX = staticObject->getGridX();
	int gridY = staticObject->getGridY();

	if(x == gridX && y == gridY && staticObject->isSolid()) {
		return true;
	}
	else {
		return false;
	}
}

}