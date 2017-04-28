/*
 * Sprite.cpp
 *
 *  Created on: Apr 7, 2017
 *      Author: Daniel
 */


#include "Sprite.h"

#include <math.h>
#include <iostream>

using namespace std;
using namespace proj;

Sprite::Sprite() {
    x_ = 0.0;
    y_ = 0.0;
    width_ = 25;
    height_ = 30;
}

Sprite::Sprite(double x, double y, int width, int height) : x_(x), y_(y), width_(width), height_(height) {}

double Sprite::getX() const noexcept {
	return this->x_;
}

double Sprite::getY() const noexcept {
	return this->y_;
}

int Sprite::getWidth() const noexcept {
	return this->width_;
}

int Sprite::getHeight() const noexcept {
	return this->height_;
}

void Sprite::setWidth(int width) {
    width_ = width;
}

void Sprite::setHeight(int height) {
    height_ = height ;
}

void Sprite::setX(double x) {
	this->x_ = x;
}

void Sprite::setY(double y) {
	this->y_ = y;
}

double Sprite::get_X_Speed() noexcept {
	return this->x_speed_;
}

double Sprite::get_Y_Speed() noexcept {
	return this->y_speed_;
}

void Sprite::set_X_Speed(double speed) {
	this->x_speed_ = speed;
}

void Sprite::set_Y_Speed(double speed) {
	this->y_speed_ = speed;
}

double Sprite::getSpeed() noexcept {
	return sqrt(pow(this->x_speed_, 2) + pow(this->y_speed_, 2));
}

int Sprite::getAngle() const noexcept {
    return angle_;
}

void Sprite::setAngle(int angle) noexcept {
    while (angle > 180) {
        angle = angle - 360;
    }
    while (angle < -180) {
        angle = angle + 360;
    }
    //We keep reducing the angle so it can't theoretically become too large in bits.
    this->angle_ = angle;
}

void Sprite::move_sprite() {
    setX(getX() + get_X_Speed());
    setY(getY() + get_Y_Speed());
}

bool Sprite::isColliding(const Sprite& other) noexcept {
	return (this->x_ < other.x_ + other.width_)
			and (this->x_ + this->width_ > other.x_)
			and (this->y_ < other.y_ + other.height_)
			and (this->y_ + this->height_ > other.y_);
}

bool Sprite::isPlayer() {
    return false;
}

bool Sprite::isEnemy() {
    return false;
}

int Sprite::getImageIndex() {
    throw exception();
}
