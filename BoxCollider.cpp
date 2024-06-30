#include "BoxCollider.h"

CollisionResult BoxCollider::checkCollision(const BoxCollider& other) const {
//    double dx = (x + width / 2) - (other.x + other.width / 2);
//    double dy = (y + height / 2) - (other.y + other.height / 2);

    Vector2 originDiff = this->getOrigin() - other.getOrigin();


//    double overlapX = (width / 2 + other.width / 2) - std::abs(dx);
//    double overlapY = (height / 2 + other.height / 2) - std::abs(dy);

    Vector2 overlap = (this->size + other.size)/2 - originDiff.abs();



    if (overlap.x > 0 && overlap.y > 0) {
            return {true, originDiff.x < 0 ? -overlap.x : overlap.x, originDiff.y < 0 ? -overlap.y : overlap.y, this->position.y > other.position.y ? this : & other};
    }
    return {false, 0, 0, this->position.y > other.position.y ? this : & other};
}

Vector2 BoxCollider::getOrigin() const{
    return this->position + this->size / 2;
}

//double BoxCollider::originX() {
//    return width/2 + x;
//}
//
//double BoxCollider::originY() {
//    return height/2 + y;
//}

BoxCollider::BoxCollider(Vector2 position, Vector2 size)
        : position(position), size(size) {
}

