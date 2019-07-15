//
// Created by christopher on 15/07/19.
//

#include "Vec3.h"
#include "Vec2.h"

Vec3::Vec3(int x, int y, int z)
 : x_(x), y_(y), z_(z) { }

Vec3::operator Vec2() const {
    return {this->x_, this->y_};
}

bool Vec3::operator==(const Vec3 &rhs) const {
    return x_ == rhs.x_ &&
           y_ == rhs.y_ &&
           z_ == rhs.z_;
}

bool Vec3::operator!=(const Vec3 &rhs) const {
    return !(rhs == *this);
}

Vec3 Vec3::operator+(const Vec3 &rhs) {
    return {x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_};
}

Vec3 Vec3::operator-(const Vec3 &rhs) {
    return {x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_};
}

Vec3 Vec3::operator*(int scalar) {
    return {x_ * scalar, y_ * scalar, z_ * scalar};
}

int Vec3::getX() const {
    return x_;
}

void Vec3::setX(int x) {
    Vec3::x_ = x;
}

int Vec3::getY() const {
    return y_;
}

void Vec3::setY(int y) {
    Vec3::y_ = y;
}

int Vec3::getZ() const {
    return z_;
}

void Vec3::setZ(int z) {
    Vec3::z_ = z;
}

Vec3 Vec3::withX(int x) const {
    return {x, this->y_, this->z_};
}

Vec3 Vec3::withY(int y) const {
    return {this->x_, y, this->z_};
}

Vec3 Vec3::withZ(int z) const {
    return {this->x_, this->y_, z};
}

String Vec3::toString() const
{
    return (String) "Vec3(" + x_ + ", " + y_ + ", " + z_ + ")";
}

Vec3::operator String() const {
    return this->toString();
}
