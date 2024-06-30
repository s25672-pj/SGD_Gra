//
// Created by Heniu on 25.06.2024.
//

#include "vector2.h"

    // Constructors
    Vector2::Vector2() : x(0), y(0) {}
    Vector2::Vector2(double x, double y) : x(x), y(y) {}

    // Operator overloads
    Vector2 Vector2::operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 Vector2::operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 Vector2::operator*(double scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 Vector2::operator/(double scalar) const {
        if (scalar == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return Vector2(x / scalar, y / scalar);
    }

    Vector2& Vector2::operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2& Vector2::operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2& Vector2::operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2& Vector2::operator/=(double scalar) {
        if (scalar == 0) {
            throw std::invalid_argument("Division by zero");
        }
        x /= scalar;
        y /= scalar;
        return *this;
    }

    bool Vector2::operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }

    bool Vector2::operator!=(const Vector2& other) const {
        return !(*this == other);
    }

    // Other methods
    double Vector2::length() const {
        return std::sqrt(x * x + y * y);
    }

    double Vector2::dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }

    Vector2 Vector2::normalized() const {
        double len = length();
        if (len == 0) {
            throw std::invalid_argument("Cannot normalize zero-length vector");
        }
        return Vector2(x / len, y / len);
    }

    double Vector2::distance(const Vector2& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    Vector2 Vector2::abs() const {
        return Vector2(std::abs(this->x), std::abs(this->y));
    }

    Vector2 Vector2::lerp(Vector2 A, Vector2 B, double T){
        auto X = std::lerp(A.x, B.x, T);
        auto Y = std::lerp(A.y, B.y ,T);

        return Vector2(X, Y);
    }

    void Vector2::print() const {
        std::cout << "x: "<< this->x << " y: "<< this->y << std::endl;
    }


