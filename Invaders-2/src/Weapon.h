/*
 * Weapon.h
 *
 *  Created on: Apr 8, 2017
 *      Author: Daniel
 *  Weapons are what create specific bullets.
 *  Players and enemies have different weapons.
 *  Weapons are what create bullets.
 */

#ifndef WEAPON_H_
#define WEAPON_H_

#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "Bullet.h"

namespace proj {
template <typename T>
class Weapon {
public:
    static_assert(std::is_base_of<Bullet, T>::value, "Value must be of type Bullet");
	/**
	 * Creates a weapon with a specific amount of damage and fire rate.
	 */
	Weapon(/**Name of the weapon*/ std::string name,
			/**Damage weapon does*/ int damage,
			/**Fire rate*/ int fire_rate) {
        this->damage_ = damage;
        this->fire_rate_ = fire_rate;
        this->name_ = name;
    }

	/**
	 * Destructor for the Weapon class.
	 */
	virtual ~Weapon(){};

	/**
	 * Updates the weapon, changing the cool-down depending on whether an
	 * attempt to fire the weapon was sent.
	 */
	virtual void update(){
        if (this->cool_down_ > 0) {
            cool_down_ --;
        }
        if (name_ == "Cannon") {
            //std::cout << cool_down_ << std::endl;
        }
    }

	/**
	 * Returns the name of this weapon.
	 */
	virtual std::string getName(){
        return this->name_;
    }


	/**
	  * Returns the damage this weapon does.
	  */
    virtual int getDamage() {
        return damage_;
    }

    /**
      * Returns the fire rate on this weapon.
      */
    virtual int getFireRate(){
        return fire_rate_;
    }

	/**
	 * Fires the weapon if request is sent and it's possible
	 */
	virtual void fire(std::vector<std::shared_ptr<Bullet>>& bullets, double x, double y, double speed, int angle) {
        if (this->cool_down_ <= 0) {
            std::shared_ptr<T> b = T::createBullet(isPlayer_, x, y, speed, damage_, angle);
            bullets.push_back(b);
            cool_down_ = fire_rate_;
        }
	}

protected:
	/**
	 * Fire rate of weapon.
	 */
	int fire_rate_;

	/**
	 * Time until next shot is possible for weapon.
	 */
	int cool_down_ = 0;

	/**
	 * Damage of weapon.
	 */
	int damage_;

	/**
	 * Name of the weapon.
	 */
	std::string name_;

	/**
	  * Determines whether player or enemy is using this weapon.
	  */
    bool isPlayer_ = false;
};

}


#endif /* WEAPON_H_ */
