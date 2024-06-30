#include "TestObject.h"
#include <cmath>
#include "BoxCollider.h"
#include "Game.h"
#include "Camera.h"
#include "globals.h"
#include <algorithm>
std::vector<TestObject *> TestObject::registry;


TestObject::~TestObject()
{
    auto it = std::find(registry.begin(), registry.end(), this);
    if (it != registry.end()) {
        registry.erase(it);
    }
}

CollisionResult TestObject::checkCollisionWith(const TestObject& other) const {
    return collider->checkCollision(*other.collider);
}

void TestObject::setTtl(double value) {
    this->ttl = value;
}

void TestObject::setVelocity(double x, double y) {
    setVelocityX(x);
    setVelocityY(y);
}

void TestObject::setVelocityX(double value) {
    this->velocityX = value;
}

void TestObject::setVelocityY(double value) {
    this->velocityY = value;
}

void TestObject::moveX(double x) {
    this->x_pos = x;
}

void TestObject::moveY(double y) {
    this->y_pos = y;
}

void TestObject::update(double deltaTime) {

    this->velocityY = std::clamp(this->velocityY, -666.0, 666.0 );
    this->velocityX = std::clamp(this->velocityX, -1000.0 , 1000.0);

    GameObject::update(deltaTime);
    if (collider != nullptr)
    {
        collider->position.x = x_pos - x_origin;
        collider->position.y = y_pos;
        collider->size.width = width;
        collider->size.height = height;;
    }

    deltaTime *= timeMultiplier;

    if (ttl > 0) {
        life += deltaTime;
    }
    //niewłaściwe usuwanie pointera
    //TODO: Sprwadź keyword delete oraz stwórz logikę odpowiedzialną za usuwanie "martwych" obiektów
    if (life > ttl) {
        this->markedToDelete = true;
        return;
    }

    double previousY = y_pos;

    velocityX += -velocityX * this->frictionStrenght;


   if(!isGrounded){
       velocityY += gravity * deltaTime * 2;
   }


    if(!isLocked){
        x_pos += velocityX * deltaTime * 10;
        y_pos += velocityY * deltaTime * 10;
    }

  if (y_pos <= 0) {
      if (previousY != 0) {
          //on land do smth
      }
      y_pos = 0;
      velocityY = 0.0;
      isJumping = false;
  }

}

void TestObject::render() {
  GameObject::render();

  if(this->collider != nullptr)
  {
      if (test)
      {
          SDL_SetRenderDrawColor(Game::getRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
      } else {
          SDL_SetRenderDrawColor(Game::getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
      }

      SDL_Rect destRect = {
              static_cast<int>(-Camera::x + x_pos) - x_origin + Game::getWidth() / 2,
              static_cast<int>(Camera::y - y_pos) - y_origin + Game::getHeight() / 2,
              static_cast<int>(width),
              static_cast<int>(height)
      };
      SDL_RenderDrawRect(Game::getRenderer(), &destRect);
  }

  if (name == "Player")
  {
      //SDL_SetRenderDrawColor(Game::getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
      //SDL_RenderDrawLine(Game::getRenderer(), Mouse::gameToScreen(x_pos, y_pos).first, Mouse::gameToScreen(x_pos, y_pos).second - 12, Mouse::getScreenX(),  Mouse::getScreenY());
  }
}

void TestObject::setTexture(SDL_Texture* texture) {
    this->texture = texture;
}
void TestObject::setPosition(double x, double y) {
    this->x_pos = x;
    this->y_pos = y;
}

void TestObject::onCollide(TestObject *) {

}

void TestObject::addVelocityX(double value) {
    this->velocityX += value;
}

void TestObject::addVelocityY(double value) {
    this->velocityY += value;
}

void TestObject::addPosition(double x, double y) {
    this->x_pos += x;
    this->y_pos += y;
}

