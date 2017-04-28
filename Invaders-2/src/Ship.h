/*
 * Ship.h
 *
 *  Created on: Apr 7, 2017
 *      Author: Daniel
 *  Represents any ship, player or enemy,
 *  that could be in the game.
 */

#ifndef SHIP_H_
#define SHIP_H_

#include "Sprite.h"
#include "Weapon.h"
#include "Bullet.h"

#include <vector>
#include <memory>

namespace proj {

class Ship : virtual public Sprite {
public:

	/**
	 * Returns the health of this Ship.
	 */
	virtual int getHealth() const noexcept;

	/**
	 * Returns the max health of this ship.
	 */
	virtual int getMaxHealth() const noexcept;

	/**
	 * Changes the current health by the specified amount.
	 */
	virtual void changeHealth(/**The new amount of health*/int amount);

	/**
	 * Changes the maximum health to the specified amount.
	 */
	virtual void changeMaxHealth/**The new maximum health*/(int amount);

	/**
	  * Fires the weapon for this Ship.
	  */
    virtual void fire(/**The bullets in the world.*/
                      std::vector<std::shared_ptr<Bullet>>& bullets,
                      /**Speed of bullet*/double speed);

protected:
    /**
      * Creates a ship with default values.
      */
    Ship();

	/**
	 * Creates a ship at the origin. Primarily for testing.
	 */
	Ship(/**The weapon this ship is equipped with**/std::shared_ptr<Weapon<Bullet>> weapon,
			/**The health this ship has.**/int health);

    /**
	 * Creates a ship, while allowing for specification of a position..
	 */
	Ship(/**The weapon this ship is equipped with**/std::shared_ptr<Weapon<Bullet>> weapon,
			/**The health this ship has.**/int health,
			/**Starting x position*/double start_x,
			/**Starting y position*/double start_y);

	/**
	 * The current health of this Ship.
	 */
	int health_;

	/**
	 * The maximimum health of this Ship.
	 */
	int maxHealth_;

	/**
	 * The weapon this Ship uses.
	 */
	std::shared_ptr<Weapon<Bullet>> weapon_;
};

}




#endif /* SHIP_H_ */
