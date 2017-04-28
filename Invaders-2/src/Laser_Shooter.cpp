/*
 * Created by Daniel Lawrence.
 * Instantiates the Laser_Shooter header.
 */

#include "Laser_Shooter.h"
#include "Weapon.h"
#include "Enemy.h"
#include "Cannon.h"
#include "Repeater.h"
#include "Weapon.h"
#include "Player.h"
#include "Bullet.h"
#include <memory>
#include <functional>
#include <vector>
#include <iostream>

using namespace proj;
using namespace std;

Laser_Shooter::Laser_Shooter(int health,
                             int damage,
                             const function<void(shared_ptr<Player> player, Enemy* e)> position_change,
                             double x, double y) {
    position_change_ = position_change;
    changeHealth(health);
    changeMaxHealth(health);
    setX(x);
    setY(y);
    setWidth(50);
    setHeight(50);
    weapon_ = make_shared<Cannon>(Cannon(damage, false));
}

void Laser_Shooter::update(shared_ptr<Player> player, vector<shared_ptr<Bullet>>& bullets) {
    if (time_alive_ < 400) {
        Enemy::update(player, bullets);
    }
    else {
        time_alive_++;
        if (time_alive_ > 600) {
            time_alive_ = 0;
        }
        if (time_alive_ == 0) {
            weapon_->fire(bullets, this->getX(), this->getY(), 30, getAngle());
        }
    }
    weapon_->update();
    //cout << "Shooter time alive" << time_alive_;
}

int Laser_Shooter::getImageIndex() {
    return 7;
}
