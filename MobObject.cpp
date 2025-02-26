#include "MobObject.h"
#include "Mouse.h"
#include <algorithm>
#include <cmath>
#include <iostream>

std::vector<MobObject *> MobObject::registry;

MobObject::MobObject(std::string name,
                     double x,
                     double y,
                     SDL_Texture* texture,
                     int x_origin,
                     int y_origin,
                     int totalFrames,
                     int numberOfAnimations)
        : TestObject(std::move(name), x, y, texture, x_origin, y_origin, totalFrames, numberOfAnimations)
        {
    currentWeapon = new Item(0,"dupa",0,{"w1.wav","w2.wav", "w3.wav"});
    registry.push_back(this);
    if(this->name == "Player"){
        this->height = 27;
        this->width = 19;
    }
// this->collider jest inicjalizowany w klasie bazowej
//    this->collider = std::make_unique<BoxCollider>(x,y, this->width, this->height);
}

MobObject::~MobObject()
{
    auto it = std::find(registry.begin(), registry.end(), this);
    if (it != registry.end()) {
        registry.erase(it);
    }
}

void MobObject::jump() {
    if (!isJumping) {
        addVelocityY(this->jumpStrenght);
        isJumping = true;

    }
}

void MobObject::moveLeft() {
    flip = true;
    addVelocityX(-MovementSpeed );
    isRunning = true;
}

void MobObject::moveRight() {
    flip = false;
    addVelocityX(MovementSpeed );
    isRunning = true;
}

void MobObject::attack()
{
    if (!isAttacking)
    {
        if(currentWeapon)
        {
            currentWeapon->use();
        }
        isAttacking = true;
    }
}

double calculateDistance(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

void MobObject::attackMelee() {
    // logika później
    Mix_Chunk* soundMelee = nullptr;
    soundMelee = ResourceManager::loadSound("walkaWrecz1.mp3");
    if (soundMelee != nullptr) {
        Mix_PlayChannel(-1, soundMelee, 0);
    }
    if (Game::enemy) {
        double distance = calculateDistance(this->x_pos, this->y_pos, Game::enemy->getX(), Game::enemy->getY());
        double meleeRange = 40.0; // Zakładany zasięg walki wręcz

        if (distance <= meleeRange) {
            Game::enemy->despawn();
            Game::enemy.reset();
            std::cout << "Enemy despawned" << std::endl;
        } else {
            std::cout << "Enemy is out of range: " << distance << std::endl;
        }
    }
}
void MobObject::granade() {
    Mix_Chunk *soundGranate = nullptr;
    soundGranate = ResourceManager::loadSound("granatRzutEksplozja.mp3");
    if (soundGranate != nullptr) {
        Mix_PlayChannel(-1, soundGranate, 0);
    }
}
void MobObject::update(double deltaTime) {
    TestObject::update(deltaTime);

    deltaTime *= timeMultiplier;

    if(invisibilityTime>0){
        invisibilityTime -=1;
    }

    if(invisibilityTime<=0){
        invisibilityTime=0;
        canGetDamage = true;
    }

    if (isAttacking)
    {
        changeAnimation(1);
        totalFrames = 8;
        shotTime += deltaTime;

        if (shotTime >= 1.0 / attackSpeed)
        {
            shotTime = 0;
            TestObject *b = new TestObject("Effect", getX()- 13, getY() + 16,
                                           ResourceManager::loadTexture("star.png"), 0, 0, 1,1, false);
            auto dd = Mouse::screenToGame(getX(), getY());

            double dx = Mouse::getGameX() - getX() - 13 ;
            double dy = Mouse::getGameY() - (getY() + 16);


            double magnitude = sqrt(dx * dx + dy * dy);

            dx /= magnitude;
            dy /= magnitude;

            b->setVelocity(dx*480.0, dy*480.0);
            b->setTtl(3);
            b->gravity = -50;
        }

        attackTime += deltaTime;

        if (attackTime >= 1)
        {
            attackTime = 0;
            isAttacking = false;
        }
    }
    if(abs(velocityX) <= 0.5 )
    {
        isRunning = false;
    }

    if (isRunning && !isAttacking)
    {
        totalFrames = 12;
        changeAnimation(0);
    }

    if (!isRunning && !isAttacking )
    {
        totalFrames = 1;
        currentAnimation = 2;
        currentFrame = 0;
    }

    if (isJumping)
    {
        totalFrames = 1;
        currentAnimation = 0;
        currentFrame = 8;
    }

    double previousY = y_pos;

    if (y_pos <= 0){
        isGrounded = true;
        y_pos = 0;
    }
    if (isGrounded) {
        if (previousY != 0) {
            shotTime = 0;
            TestObject *b = new TestObject("Effect", getX()- 13, getY() + 16,ResourceManager::loadTexture("star.png"), 0, 0, 1,1, false);
            //auto dd = Mouse::screenToGame(getX(), getY());
            double dx = Mouse::getGameX() - getX() - 13 ;
            double dy = Mouse::getGameY() - (getY() + 16);

            double magnitude = sqrt(dx * dx + dy * dy);

            dx /= magnitude;
            dy /= magnitude;

            b->setVelocity(dx*480.0, dy*480.0);
            b->setTtl(3);
            b->gravity = -50;
        }
        velocityY = 0.0;
        isJumping = false;
    }
}

void MobObject::render() {
    TestObject::render();
}


void MobObject::getDamage(int damage) {
    if(this->canGetDamage&&this->life>0){
        life-=1;
        canGetDamage = false;
        invisibilityTime = 100;
    }
}
