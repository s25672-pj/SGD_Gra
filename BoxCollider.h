#ifndef CYBERDRUNK_BOXCOLLIDER_H
#define CYBERDRUNK_BOXCOLLIDER_H

#include "GameObject.h"
#include "vector2.h"
class BoxCollider;
struct CollisionResult {
    bool collided;
    double overlapX, overlapY;
    const BoxCollider * topCollider;
};

class BoxCollider {
public:

    Vector2 position;
    Vector2 size;

    bool isPhysicsObject = false;
    bool isStaticObject = false;

//    double originX();
//    double originY();
    Vector2 getOrigin() const;

    BoxCollider(Vector2 position, Vector2 size);
    CollisionResult checkCollision(const BoxCollider& other) const;
};


#endif //CYBERDRUNK_BOXCOLLIDER_H
