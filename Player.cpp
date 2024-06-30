//
// Created by Heniu on 22.06.2024.
//

#include "Player.h"
#include "globals.h"
#include "Game.h"
    void Player::onCollide(TestObject * otter) {

        auto next = getValueByKey<double>("nextKnockbackTime");

        if(next > Globals::curTime){
            return;
        }

        if(otter -> getName() == "spikes" ){
            this->addVelocityY(10);
            colided = true;
            auto cooldown = getValueByKey<double>("knockbackCooldown");
            setValueByKey("nextKnockbackTime", Globals::curTime + cooldown);

            Game::hitPlayer(1);
        }

        if(otter -> getName() == "enemy" ){
            this->addVelocityY(10);
            colided = true;
            auto cooldown = getValueByKey<double>("knockbackCooldown");
            setValueByKey("nextKnockbackTime", Globals::curTime + cooldown);

            Game::hitPlayer(1);
        }


    }
        Player::Player(std::string name,
                double x,
                double y,
                SDL_Texture* texture,
                int x_origin,
                int y_origin,
                int totalFrames,
                int numberOfAnimations)
        : MobObject(std::move(name), x, y, texture, x_origin, y_origin, totalFrames, numberOfAnimations)
        {
            this->setValueByKey("knockbackCooldown", 0.25);
            this->setValueByKey("nextKnockbackTime", 0.0);
            this->frictionStrenght = 0.3;
        }

void Player::update(double deltaTime) {
    MobObject::update(deltaTime);
}
