
#include "Dimension.h"

namespace spe
{

Dimension::Dimension():
	_loaded(false)
{

}

Dimension::~Dimension()
{
	for (std::size_t i = 0; i < _parallaxLayers.size(); ++i) {
		delete _parallaxLayers[i];
	}
}

}