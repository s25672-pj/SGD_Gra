//
// Created by Malak on 22.03.2024.
//

#ifndef CYBERDRUNK_COLLISIONMANAGER_H
#define CYBERDRUNK_COLLISIONMANAGER_H


#include "TestObject.h"
#include <SDL.h>
#include <vector>
#include "Item.h"
#include "Game.h"
#include <cmath>
#include "vector2.h"

class CollisionManager {
public:
    static void checkCollisions(TestObject * obj1, double deltaTime) {

//        for (auto& obj : TestObject::registry) {
//            obj->test = false;
//        }

        if (!obj1->getCollider()) return;

        for (auto& obj2 : TestObject::registry) {
            if (obj1 == obj2 || obj1->getName() == obj2->getName() || !obj2->getCollider()) continue;

            auto & collider1 = obj1->getCollider();
            auto & collider2 = obj2->getCollider();

            CollisionResult result = collider1->checkCollision(*collider2);
            if (result.collided) {
                obj1->test = true;
                obj1->onCollide(obj2);


                if(collider1->isPhysicsObject && collider2->isPhysicsObject){
                    double interpolationDuration = 0.25;


                    Vector2 direction = collider2->getOrigin() - collider1->getOrigin();


                    auto distance = collider1->getOrigin().distance(collider2->getOrigin());

                    if(!collider1->isStaticObject){
                        auto normalized = direction.normalized();

                        Vector2 destination = (normalized * distance) + collider1->getOrigin();

                        auto nextOrigin = Vector2::lerp(collider1->getOrigin(), destination, deltaTime);


                        if (result.overlapX != 0) {
                            obj1->addPosition(collider1->getOrigin().x - nextOrigin.x, 0);
                        }
                        //poniższa logika powoduje wytracenie prędkości dla obiektów 1 i 2 jeżeli dochodzi do kolizji lądując na niższym obiekcie lub uderzając w obiekt powyżej.
                        //logika jest wykonywana nawet podczas kolizji z colliderem który nie jest oznaczony jak physicsObject (bool w klasie collider)
                        if (result.overlapY != 0) {
                            if (obj1->velocityY <= 0 && collider1.get() == result.topCollider){
                                obj1->velocityY = 0;
                                obj1->isGrounded = true;
                            }
                            else if(obj1->velocityY > 0 && collider1.get() != result.topCollider){
                                obj1->velocityY = 0;
                            }
                            obj1->addPosition(0, collider1->getOrigin().y - nextOrigin.y);
                        }
                    }
                }
            }
        }
    }

};


#endif //CYBERDRUNK_COLLISIONMANAGER_H
