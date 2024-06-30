//
// Created by Heniu on 25.06.2024.
//

#ifndef CYBERDRUNK2137_VECTOR2_H
#define CYBERDRUNK2137_VECTOR2_H

#include <iostream>
#include <cmath>

class Vector2 {
public:
    // Members
    union {
        struct {
            double x;
            double y;
        };
        struct {
            double width;
            double height;
        };
    };
//    double x, y;

    // Constructors
    Vector2();
    Vector2(double x, double y);

    // Operator overloads
    Vector2 operator+(const Vector2& other) const ;

    Vector2 operator-(const Vector2& other) const;

    Vector2 operator*(double scalar) const;

    Vector2 operator/(double scalar) const ;

    Vector2& operator+=(const Vector2& other) ;
    Vector2& operator-=(const Vector2& other);

    Vector2& operator*=(double scalar) ;

    Vector2& operator/=(double scalar) ;

    bool operator==(const Vector2& other) const ;

    bool operator!=(const Vector2& other) const ;

    // Other methods
    double length() const ;

    double dot(const Vector2& other) const;

    Vector2 normalized() const;

    double distance(const Vector2& other) const;

    Vector2 abs() const;

    static Vector2 lerp(Vector2 A, Vector2 B, double T);

    void print() const;

};





#endif //CYBERDRUNK2137_VECTOR2_H
