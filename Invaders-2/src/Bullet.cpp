/**
  * Created by Daniel Lawrence.
  * Represents the instantiation of the Bullet
  * class from Bullet.h.
  */

#include "Bullet.h"
#include "Sprite.h"

#include <memory>
#include <cmath>
#include <iostream>

using namespace std;
using namespace proj;

Bullet::Bullet(bool isFriendly, double x, double y, int damage, int angle) : Sprite(x, y, 3, 10) {
    this->isFriendly_ = isFriendly;
    this->damage_ = damage;
    setAngle(angle);
}

shared_ptr<Bullet> Bullet::createBullet(bool isFriendly, double x, double y,
                            double speed, int damage, int angle) {
    shared_ptr<Bullet> b = make_shared<Bullet>(Bullet(isFriendly, x, y, damage, angle));
    b->set_X_Speed(speed * sin(-angle / 57.3));
    b->set_Y_Speed(speed * cos(angle / 57.3));
    b->setAngle(angle);
    return b;
}

bool Bullet::isFriendly() {
    return isFriendly_;
}

int Bullet::getDamage() {
    return damage_;
}

int Bullet::getImageIndex() {
    if (isFriendly()) {
        return 2;
    }
    else {
        return 3;
    }
}
