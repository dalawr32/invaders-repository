/**
  * Created by Daniel Lawrence.
  */

#include "Basic_Shooter.h"
#include "Enemy.h"
#include "Touch.h"
#include "Player.h"
#include "Repeater.h"
#include "Weapon.h"

#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

using namespace proj;
using namespace std;

Basic_Shooter::Basic_Shooter(int health,
                             int damage,
                             function<void(shared_ptr<Player> p, Enemy* e)> position_change,
                             double start_x,
                             double start_y)
: Enemy(make_shared<Repeater>(Repeater(damage, false)), health, position_change, start_x, start_y, 10) {
    if (weapon_) {
        //Make sure weapon was properly initialized.
    }
    else {
        weapon_ = make_shared<Repeater>(Repeater(damage, false));
    }
}

void Basic_Shooter::update(shared_ptr<Player> player, vector<shared_ptr<Bullet>>& bullets) {
    this->Enemy::update(player, bullets);
    this->fire(bullets, 10);
}

int Basic_Shooter::getImageIndex() {
    return 4;
}
