//
// Created by christopher on 15/07/19.
//

#include "Vec2.h"
#include "Vec3.h"

Vec2::Vec2(int x, int y)
        : x_(x), y_(y) { }

Vec2::operator Vec3() const {
    return {this->x_, this->y_, 0};
}

bool Vec2::operator==(const Vec2 &rhs) const {
    return x_ == rhs.x_ &&
           y_ == rhs.y_;
}

bool Vec2::operator!=(const Vec2 &rhs) const {
    return !(rhs == *this);
}

Vec2 Vec2::operator+(const Vec2 &rhs) {
    return {x_ + rhs.x_, y_ + rhs.y_};
}

Vec2 Vec2::operator-(const Vec2 &rhs) {
    return {x_ - rhs.x_, y_ - rhs.y_};
}

Vec2 Vec2::operator*(int scalar) {
    return {x_ * scalar, y_ * scalar};
}

int Vec2::getX() const {
    return x_;
}

void Vec2::setX(int x) {
    Vec2::x_ = x;
}

int Vec2::getY() const {
    return y_;
}

void Vec2::setY(int y) {
    Vec2::y_ = y;
}

Vec2 Vec2::withX(int x) const {
    return {x, this->y_};
}

Vec2 Vec2::withY(int y) const {
    return {this->x_, y};
}

String Vec2::toString() const
{
    return (String) "Vec2(" + x_ + ", " + y_ + ")";
}

Vec2::operator String() const {
    return this->toString();
}
