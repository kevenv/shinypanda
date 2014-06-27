#ifndef SPE_DIMENSION_H
#define SPE_DIMENSION_H

#include <vector>
#include "TileMap.h"

#define SPE_NB_LAYERS 3

namespace spe
{

class MovingObject;
class AnimatedTile;
class ParallaxLayer;

enum class LAYER
{
	FOREGROUND,
	PLAYGROUND,
	BACKGROUND
};

class Dimension
{
public:
    Dimension();
    ~Dimension();

	inline const std::vector<MovingObject*>& getMovingObjects() const { return _movingObjects; }
	inline std::vector<MovingObject*>& accessMovingObjects() { return _movingObjects; }

	inline const std::vector<ParallaxLayer*>& getParallaxLayers() const { return _parallaxLayers; }
	inline std::vector<ParallaxLayer*>& accessParallaxLayers() { return _parallaxLayers; }

	inline const TileMap* getTileMaps() const { return _maps; }
	inline TileMap* accessTileMaps() { return _maps; }

	StaticObject*** getPlaygroundMap() { return _maps[(int)LAYER::PLAYGROUND].accessData(); }

	inline int getSizeX() const { return _sizeX; }
	inline int getSizeY() const { return _sizeY; }
	inline void setSizeX(int sizeX) { _sizeX = sizeX; }
	inline void setSizeY(int sizeY) { _sizeY = sizeY; }

	inline bool inRange(int x, int y) const
	{
		return x >= 0 && x < _sizeX && y >= 0 && y < _sizeY;
	}

	inline bool isLoaded() const { return _loaded; }
	inline void setLoaded(bool loaded) { _loaded = loaded; }

private:
	TileMap _maps[SPE_NB_LAYERS];
	std::vector<ParallaxLayer*> _parallaxLayers;
    int _sizeX;
    int _sizeY;
	bool _loaded;

    std::vector<MovingObject*> _movingObjects;
    std::vector<AnimatedTile*> _animatedTiles;
};

}

#endif
