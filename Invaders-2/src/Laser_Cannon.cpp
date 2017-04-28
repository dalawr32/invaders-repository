/*
 * Created by Daniel Lawrence.
 * Represents the instantiation of the Laser_Cannon header.
 */

 #include "Laser_Cannon.h"
 #include "Bullet.h"
 #include <memory>
 #include <cmath>
 #include <iostream>

 using namespace std;
 using namespace proj;


Laser_Cannon::Laser_Cannon(bool isFriendly, double x, double y, double speed, int damage, int angle)
: Bullet(isFriendly, x, y, damage, angle) {
    setX(x);
    setY(y);
    set_X_Speed(speed * sin(-angle / 57.3));
    set_Y_Speed(speed * cos(angle / 57.3));
}

shared_ptr<Laser_Cannon> Laser_Cannon::createBullet(bool isFriendly, double x, double y, double speed, int damage, int angle) {
    return make_shared<Laser_Cannon>(Laser_Cannon(isFriendly, x, y, speed, damage, angle));
}

void Laser_Cannon::move_sprite() {
    Sprite::move_sprite();
    if (this->getHeight() < 700) {
        this->setHeight(getHeight() + 50);
    }
}
