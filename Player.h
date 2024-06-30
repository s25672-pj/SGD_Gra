//
// Created by Heniu on 22.06.2024.
//

#ifndef CYBERDRUNK2137_PLAYER_H
#define CYBERDRUNK2137_PLAYER_H

#include "MobObject.h"


class Player : public MobObject{
public:
    void onCollide(TestObject *);
    void update(double deltaTime) override;

    bool colided = false;

    Player(
            std::string name = "TestObject",
    double x = 0.0,
    double y = 0.0,
            SDL_Texture* texture = nullptr,
    int x_origin = 0,
    int y_origin = 0,
    int totalFrames = 1,
    int numberOfAnimations = 1
    );


};


#endif //CYBERDRUNK2137_PLAYER_H


//TODO: memory leak może być przez brak destruktora wirtualnego