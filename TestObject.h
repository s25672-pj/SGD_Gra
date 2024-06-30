#ifndef CYBERDRUNK_TESTOBJECT_H
#define CYBERDRUNK_TESTOBJECT_H

#include "GameObject.h"
#include "BoxCollider.h"
#include <string>
#include <SDL.h>
#include <memory>
#include <utility>
#include <any>
#include <unordered_map>

class TestObject : public GameObject {

public:
    static std::vector<TestObject*> registry;

    double velocityX, velocityY;
    double gravity;
    double ttl;
    double life;
    double frictionStrenght = 0.1;

    bool isJumping;
    bool isLocked = false;
    bool test;
    bool isGrounded = false;
    bool markedToDelete = false;


    TestObject(
            std::string name = "TestObject",
            double x = 0.0,
            double y = 0.0,
            SDL_Texture* texture = nullptr,
            int x_origin = 0,
            int y_origin = 0,
            int totalFrames = 1,
            int numberOfAnimations = 1,
            bool initCollider = true
    ) : GameObject(std::move(name), x, y, texture, x_origin, y_origin, totalFrames, numberOfAnimations),
    velocityX(0.0),
    velocityY(0.0),
    gravity(-10),
    ttl(0),
    life(0),
    isJumping(false),
    test(true) {
            if(initCollider ){
                this->collider = std::make_unique<BoxCollider>(Vector2(x, y), Vector2(width, height));
            }

            registry.push_back(this);
    }

    ~TestObject() override;

    void lockInPlace(){
        isLocked = true;
    }

    void unlock(){
        isLocked = false;
    }

    std::unique_ptr<BoxCollider>& getCollider() {
        return collider;
    }

    [[nodiscard]] CollisionResult checkCollisionWith(const TestObject& other) const;

    void setTtl(double ttl);
    void setVelocity(double x, double y);
    void setVelocityX(double value);
    void setVelocityY(double value);
    void addVelocityX(double value);
    void addVelocityY(double value);

    TestObject& operator=(TestObject&& other) noexcept {
        if (this != &other) {
            GameObject::operator=(std::move(other));
            collider = std::move(other.collider);
        }
        return *this;
    }

    void moveX(double x);
    void moveY(double y);
//    void jump();
    void update(double deltaTime) override;
    void render() override;
    void setTexture(SDL_Texture* texture);
    void setPosition(double x, double y);
    void addPosition(double x, double y);

    std::unique_ptr<BoxCollider> collider;

    virtual void onCollide(TestObject *);

protected:
    std::unordered_map<std::string, std::any> dataVariables;

public:
    template<class T>
    T getValueByKey(std::string key) {
        std::any newDataVariable = dataVariables[key];

        T anyNewVariable = std::any_cast<T>(newDataVariable);

        return anyNewVariable;
    }

    template<class T>
    void setValueByKey(std::string key, T value){
        auto tValue = std::make_any<T>(value);
        dataVariables[key] = tValue;
    }

};
#endif //CYBERDRUNK_TESTOBJECT_H
