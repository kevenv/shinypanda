#ifndef SPE_OBJECT_H
#define SPE_OBJECT_H

#include <vector>

namespace spe
{

class Object
{
protected:
    const char* _name;
    bool _solid;
    bool _harmful;
	std::vector<Object*> _currentlyCollidingObjects; //TODO: VERY inefficient, but good enough for now

public:
    Object(const char* name = "");
	virtual ~Object() {}

	virtual void collide(Object& obj) {}

	inline const char* getName() const { return _name; }

    inline bool isSolid() const { return _solid; }
    inline void setSolid(bool solid) {_solid = solid; }
    inline bool isHarmful() const { return _harmful; }
    inline void setHarmful(bool harmful) {_harmful = harmful; }

	bool isCurrentlyColliding(const Object* object) const;
	inline bool isCurrentlyColliding() const { return _currentlyCollidingObjects.size() > 0; }

	const std::vector<Object*>& getCurrentlyCollidingObjects() { return _currentlyCollidingObjects; }

	void addCurrentlyColliding(Object* object);
	void removeCurrentlyColliding(const Object* object);
	void clearCurrentlyColliding();
};

}

#endif
