//
// Created by christopher on 15/07/19.
//

#pragma once

#include <Arduino.h>

class Vec2;

class Vec3 {
public:
    Vec3(int x, int y, int z);

    operator Vec2() const;

    bool operator==(const Vec3 &rhs) const;
    bool operator!=(const Vec3 &rhs) const;

    Vec3 operator+(const Vec3 &rhs);
    Vec3 operator-(const Vec3 &rhs);
    Vec3 operator*(int scalar);

    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
    int getZ() const;
    void setZ(int z);

    Vec3 withX(int x) const;
    Vec3 withY(int y) const;
    Vec3 withZ(int z) const;

    String toString() const;
    operator String() const;

private:
    int x_, y_, z_;
};



