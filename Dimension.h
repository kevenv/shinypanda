#ifndef SPE_DIMENSION_H
#define SPE_DIMENSION_H

#include <vector>
#include "TileMap.h"

#define SPE_NB_LAYERS 3

namespace spe
{

class World;
class RenderSystem;
class MovingObject;
class AnimatedTile;
class ParallaxLayer;

class Dimension
{
	friend class World;
	friend class RenderSystem;

public:
    Dimension();
    ~Dimension();

private:
	TileMap _map[SPE_NB_LAYERS];
	std::vector<ParallaxLayer*> _parallaxLayers;
    int _sizeX;
    int _sizeY;

    std::vector<MovingObject*> _movingObjects;
    std::vector<AnimatedTile*> _animatedTiles;
};

}

#endif