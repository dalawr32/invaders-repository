/*
 * Player.cpp
 *
 *  Created on: Apr 8, 2017
 *      Author: Daniel
 */



#include "Sprite.h"
#include "Ship.h"
#include "Player.h"
#include <iostream>


using namespace proj;
using namespace std;

Player::Player(shared_ptr<Weapon<Bullet>> weapon, int maxHealth)
: Ship(weapon, maxHealth) {
    setY(670);
    setAngle(0);
}

void Player::setX(double x) {
    //If the player goes past the leftmost part, return them to the left edge.
    if (x < 0) {
        x = 0;
        set_X_Speed(0);
    }
    //If the player goes past the rightmost part, return them to the right edge.
    if (x > 670) {
        x = 670;
        set_X_Speed(0);
    }
    //Do the call for the Super class.
    Sprite::setX(x);
}

void Player::set_X_Speed(double dx) {
    if (dx > 5) {
        dx = 5;
    }
    else if (dx < -5) {
        dx = -5;
    }
    Sprite::set_X_Speed(dx);
}

void Player::changeHealth(int health) {
    int oldHealth = getHealth();
    if (invulnerable_time <= 0) {
        Ship::changeHealth(health);
    }
    if (health < oldHealth) {
        invulnerable_time = 50;
    }
}

void Player::move_sprite() {
    if (invulnerable_time > 0) {
        invulnerable_time --;
    }
    weapon_->update();
    Sprite::move_sprite();
}

int Player::getImageIndex() {
    return 0;
}
