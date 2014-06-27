
#ifndef SPE_OBJECT_H
#define SPE_OBJECT_H

#include <vector>

namespace spe
{
/**
    @class Object Object.h "Object.h"
    @brief An object in the map.

    This is an abstract class that represents all the possible objects in a map.
*/

class Object
{
protected:
    const char* _name; ///< Name of the object.
    bool _solid; ///< Whether the object if tangible or not. If false, we can pass through it.
    bool _player; ///< If the object is a player.
    bool _harmful; ///< \brief Whether the object kills the player on touch or not.
    bool _inReal; /**< \brief Whether the object exist in the Real World or not.
                    This variable does nothing if _collidable is false. */
    bool _inDream; /**< \brief Whether the object exist in the Dream World or not.
                    This variable does nothing if _collidable is false. */
	std::vector<Object*> _currentlyCollidingObjects;//TODO: VERY inefficient, but good enough for now

public:

    /**
    Main constructor of the class.

    @param[in] name Name of the object.
    */
    Object(const char* name = "");

    /**
    Destructor.

    Free all ressources attached to the object.
    */
	virtual ~Object() {}

    /**
    Tells whether the object is solid or not.

    @return True if the object is solid, false otherwise.
    */
    inline bool isSolid() const { return _solid; }
    /**
    @param[in] solid If the object can't be passed through.
    */
    inline void setSolid(bool solid) {_solid = solid; }
    /**
    Tells whether the object is a player object or not.

    @return True if the object is a player, false otherwise.
    */
    inline bool isPlayer() const { return _player; }
    /**
    @param[in] player If the object is a player.
    */
    inline void setPlayer(bool player) {_player = player; }
    /**
    Tells whether the object kills the player on touch or not.

    @return True if the object is harmful to the player, false otherwise.
    */
    inline bool isHarmful() const { return _harmful; }
    /**
    @param[in] harmful If the object is harmful to the player.
    */
    inline void setHarmful(bool harmful) {_harmful = harmful; }
    /**
    Tells whether the object exists in the Real World.

    @return True if the object is in the Real World, false otherwise.
    */
    inline bool isInReal() const { return _inReal; }
    /**
    @param[in] inReal If the object is in the Real World or not.
    */
    inline void setInReal(bool inReal) {_inReal = inReal; }
    /**
    Tells whether the object exists in the Dream World.

    @return True if the object is in the Dream World, false otherwise.
    */
    inline bool isInDream() const { return _inDream; }
    /**
    @param[in] inDream If the object is in the Dream World or not.
    */
    inline void setInDream(bool inDream) {_inDream = inDream; }
    /**
    Get the name of the object.

    The name of the Object is given at initialization to the constructor and never changes.

    @return the name of the object.
    */
    inline const char* getName() const { return _name; }

	bool isCurrentlyColliding(const Object* object) const;

	inline bool isCurrentlyColliding() const { return _currentlyCollidingObjects.size() > 0; }

	void addCurrentlyColliding(Object* object);

	void removeCurrentlyColliding(const Object* object);

	void clearCurrentlyColliding();

	std::vector<Object*>& accessCurrentlyCollidingObjects() { return _currentlyCollidingObjects; }
	const std::vector<Object*>& getCurrentlyCollidingObjects() { return _currentlyCollidingObjects; }

    /**
    Handle the effects on this object from being collided by an object obj.

    When overriding this method, you should call the method from the base class.

    @param[in] obj Object colliding with.
    */
	virtual void collide(Object& obj) {}
};

}

#endif
