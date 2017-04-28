/*
 * Ship.cpp
 *
 *  Created on: Apr 8, 2017
 *      Author: Daniel
 */


#include "Ship.h"

#include "Sprite.h"
#include "Weapon.h"
#include "Bullet.h"

#include <memory>
#include <vector>

using namespace proj;
using namespace std;

Ship::Ship() : Sprite(0, 0, 30, 30) {
    weapon_ = shared_ptr<Weapon<Bullet>>();
    health_ = 50;
    maxHealth_ = 50;
}

Ship::Ship(shared_ptr<Weapon<Bullet>> weapon, int health)
: Sprite(0.0, 0.0, 30, 30),
weapon_(weapon), health_(health), maxHealth_(health) {
}

Ship::Ship(shared_ptr<Weapon<Bullet>> weapon, int health, double start_x, double start_y)
: Sprite(start_x, start_y, 30, 30),
weapon_(weapon), health_(health), maxHealth_(health) {}

int Ship::getHealth() const noexcept {
	return this->health_;
}

int Ship::getMaxHealth() const noexcept {
	return this->maxHealth_;
}

void Ship::changeHealth(int health) {
	this->health_ = health;
}

void Ship::changeMaxHealth(int maxHealth) {
	this->maxHealth_ = maxHealth;
}

void Ship::fire(vector<shared_ptr<Bullet>>& bullets, double speed) {
    if (weapon_) {
        weapon_->fire(bullets, getX() + getWidth()/2, getY() - getHeight()/2, speed, this->getAngle());
    }
}
