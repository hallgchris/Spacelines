//
// Created by christopher on 15/07/19.
//

#pragma once

#include <Arduino.h>

class Vec3;

class Vec2 {
public:
    Vec2(int x, int y);

    operator Vec3() const;

    bool operator==(const Vec2 &rhs) const;
    bool operator!=(const Vec2 &rhs) const;

    Vec2 operator+(const Vec2 &rhs);
    Vec2 operator-(const Vec2 &rhs);
    Vec2 operator*(int scalar);

    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);

    Vec2 withX(int x) const;
    Vec2 withY(int y) const;

    String toString() const;
    operator String() const;

private:
    int x_, y_;
};
