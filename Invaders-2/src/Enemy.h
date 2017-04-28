/*
 * Enemy.h
 *
 *  Created on: Apr 8, 2017
 *      Author: Daniel
 *  Represents the enemies, the computer controlled
 *  ships the player must defeat. Enemies are
 *  controlled using equations that set their
 *  location based on time alive or player
 *  movement, allowing for a range of different
 *  types.
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "Player.h"
#include "Ship.h"

#include <memory>
#include <functional>
#include <mutex>
#include <vector>

namespace proj {
class Enemy : virtual public Ship {
public:
	/**
	 * Gets the time this enemy has been alive.
	 */
	virtual int getTime();

	/**
     * Gets the difficulty of this enemy.
     */
    virtual int getDifficulty();

	/**
	 * Updates the enemy every tick, using the position_change field.
	 */
	virtual void update(/** The player*/ std::shared_ptr<Player> p,
                     /**The bullets*/ std::vector<std::shared_ptr<Bullet>>& bullets);

	/**
	  * Returns whether the given sprite is an enemy.
	  */
	virtual bool isEnemy() override {
        return true;
	}

protected:
    /**
      * Constructs an empty enemy.
      */
    Enemy();

	/**
	 * Constructs an enemy.
	 */
	Enemy(/**Weapon enemy uses*/std::shared_ptr<Weapon<Bullet>> w,
			/**Health of the enemy*/int health,
			/**Function that determines movement and behavior*/
			const std::function<void(std::shared_ptr<Player> p, Enemy* e)> position_change,
            /**Represents the difficulty of this enemy*/
            int difficulty);


    /**
	 * Constructs an enemy, allowing for specification of position.
	 */
	Enemy(/**Weapon enemy uses*/std::shared_ptr<Weapon<Bullet>> w,
			/**Health of the enemy*/int health,
			/**Function that determines movement and behavior*/
			const std::function<void(std::shared_ptr<Player> p, Enemy* e)> position_change,
            /**Starting x position*/double start_x,
            /**Starting y position*/double start_y,
            /**Represents the difficulty of this enemy*/
            int difficulty);
	/**
	 * Represents how long it's been alive.
	 */
	int time_alive_ = 0;

	/**
	 * The function changing the position based on player and time.
	 */
	std::function<void(std::shared_ptr<Player> p, Enemy* e)> position_change_;

	/**
     * Represents the difficulty of this enemy.
     */
    int difficulty_;

private:
    /**
      * Lock we'll use for locking the player.
      */
    //std::mutex lock_;
};
}



#endif /* ENEMY_H_ */
