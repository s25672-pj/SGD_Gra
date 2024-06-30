#include "PauseMenu.h"
#include "Button.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Camera.h"

std::vector<PauseMenu *> PauseMenu::registry;

void PauseMenu::render() {
    if (isHidden) return;
    TestObject::render();
}

void PauseMenu::setPosition(double x, double y) {
    this->y_pos = y;
    this->x_pos = x;
}

PauseMenu::~PauseMenu()
{
    auto it = std::find(registry.begin(), registry.end(), this);
    if (it != registry.end()) {
        registry.erase(it);
    }
}

void PauseMenu::hide() {
    isHidden = true;
}

void PauseMenu::show() {
    isHidden = false;
}
