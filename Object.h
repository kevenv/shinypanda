
#ifndef SPE_OBJECT_H
#define SPE_OBJECT_H

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
    bool _inReal; /**< \brief Whether the object exist in the Real World or not.
                    This variable does nothing if _collidable is false and _transparent is true. */
    bool _inDream; /**< \brief Whether the object exist in the Dream World or not.
                    This variable does nothing if _collidable is false and _transparent is true. */

public:
	Object() {}

    /**
    Main constructor of the class.

    @param[in] name Name of the object.
    @param[in] inDream,inReal If the object is in the Dream/Real World or not.
    @param[in] solid If the object can't be passed through.
    */
    Object(const char* name, bool inDream = true, bool inReal = true, bool solid = true);

    /**
    Destructor.

    Free all ressources attached to the object.
    */
	virtual ~Object() {}

    /**
    Tells whether the object is solid or not.

    @return True if the object is solid, false otherwise.
    */
    inline bool isSolid() { return _solid; }
    /**
    Tells whether the object exists in the Real World.

    @return True if the object is in the Real World, false otherwise.
    */
    inline bool isInReal() { return _inReal; }
    /**
    Tells whether the object exists in the Dream World.

    @return True if the object is in the Dream World, false otherwise.
    */
    inline bool isInDream() { return _inDream; }
    /**
    Get the name of the object.

    The name of the Object is given at initialization to the constructor and never changes.

    @return the name of the object.
    */
    inline const char* getName() { return _name; }
};

}

#endif
