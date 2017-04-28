/*
 * Enemy.cpp
 *
 *  Created on: Apr 8, 2017
 *      Author: Daniel
 */


#include "Enemy.h"

#include "Ship.h"
#include "Sprite.h"

#include <functional>
#include <iostream>
#include <memory>
#include <mutex>

using namespace std;
using namespace proj;

Enemy::Enemy(){}

Enemy::Enemy(shared_ptr<Weapon<Bullet>> weapon,
             int health,
             const function<void(shared_ptr<Player> p, Enemy* e)> change,
             int difficulty)
: Ship(weapon, health) {
	this->position_change_ = change;
	this->difficulty_ = difficulty;
	this->time_alive_ = 0;
}

Enemy::Enemy(shared_ptr<Weapon<Bullet>> weapon,
             int health,
             const function<void(shared_ptr<Player> p, Enemy* e)> change,
             double start_x, double start_y, int difficulty)
: Ship(weapon, health, start_x, start_y) {
    setX(start_x);
    setY(start_y);
    position_change_ = change;
    difficulty_ = difficulty;
    time_alive_ = 0;
}

int Enemy::getTime() {
	return this->time_alive_;
}

void Enemy::update(shared_ptr<Player> player, vector<shared_ptr<Bullet>>& bullets) {
    int oldY = this->getY();
	position_change_(player, this);
	this->Sprite::move_sprite();
	int newY = this->getY();
	this->setY(newY);
	if (weapon_) {
        weapon_->update();
	}
	time_alive_++;
}

int Enemy::getDifficulty() {
    return difficulty_;
}
