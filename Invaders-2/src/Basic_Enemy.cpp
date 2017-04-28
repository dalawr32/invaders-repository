/**
  * Created by Daniel Lawrence.
  */

#include "Basic_Enemy.h"
#include "Enemy.h"
#include "Touch.h"
#include "Player.h"

#include <functional>
#include <iostream>
#include <memory>

using namespace proj;
using namespace std;

Basic_Enemy::Basic_Enemy(int health, function<void(shared_ptr<Player> p, Enemy* e)> position_change)
: Enemy(shared_ptr<Weapon<Bullet>>(),
        health,
        position_change,
        10){
}

Basic_Enemy::Basic_Enemy(int health, function<void(shared_ptr<Player> p, Enemy* e)> position_change,
                         double start_x, double start_y)
: Enemy(shared_ptr<Weapon<Bullet>>(), health, position_change, start_x, start_y, 10) {}


 void Basic_Enemy::update(shared_ptr<Player> p, vector<shared_ptr<Bullet>>& bullets) {
    this->Enemy::update(p, bullets);
    if (this->isColliding(*p)) {
        p->changeHealth(p->getHealth() - 30);
    }
}

int Basic_Enemy::getImageIndex() {
    return 1;
}
