/*
 * World.h
 *
 *  Created on: Apr 8, 2017
 *      Author: Daniel
 */

#ifndef WORLD_H_
#define WORLD_H_


#include <vector>
#include <memory>
#include <map>
#include <functional>
#include <random>

#include "Player.h"
#include "Enemy.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Spark.h"

namespace proj {
class World {
public:
	/**
	 * Creates a world with a given difficulty.
	 */
	World(/**Represents the difficulty of the world*/int difficulty = 100);

	/**
	 * Destructs a world.
	 */
	~World(){};

	/**
	 * Updates the world.
	 */
	void update();

	/**
	 * Determines whether the world is continuing. If true, no.
	 */
	bool isOver();

	/**
	  * Returns the player.
	  */
    std::shared_ptr<Player> getPlayer() noexcept;

    /**
      * Returns a list of all active enemies.
      */
    std::vector<std::shared_ptr<Enemy>> getEnemies() noexcept;

    /**
      * Returns a list of all active bullets.
      */
    std::vector<std::shared_ptr<Bullet>> getBullets() noexcept;

    /**
      * Returns a list of pointers to sparks.
      */
    std::vector<std::shared_ptr<Spark>> getSparks() noexcept;

    /**
      * Sets the bullets to the given list.
      */
    void setBullets(/**List of bullets to be passed*/ std::vector<std::shared_ptr<Bullet>> bullets);

protected:
    /**
      * Creates the map of all functions that guide enemy movement.
      */
    void init();

    /**
      * Creates new enemies when the number of enemies draws thin.
      */
    std::shared_ptr<Enemy> createEnemy(/**The difficulty increase*/int difficulty_spike);

private:
	/**
	 * Represents the player.
	 */
	std::shared_ptr<Player> player_;

	/**
	 * Contains all the enemies alive in the game.
	 */
	std::vector<std::shared_ptr<Enemy>> enemies_;

	/**
	 * Contains all the bullets currently on the game world.
	 */
	std::vector<std::shared_ptr<Bullet>> bullets_;

	/**
	  * Contains any sparks created by hitting players or enemies.
	  */
    std::vector<std::shared_ptr<Spark>> sparks_;

	/**
	 * Represents the difficulty i.e. the maximum value of enemy difficulty
	 * scores at a time on the game.
	 */
	int difficulty_ = 80;

	/**
	  * Determines if the game is over.
	  */
    bool isOver_ = false;

    /**
      * Map of all possible functions that could guide enemy movement. Initialized with init();
      */
    std::map<int, std::function<void(std::shared_ptr<Player> player, Enemy* e)>> movementMap_;

    /**
      * Map of possible enemies that can be created. Initialized with init();
      */
    std::map<int, std::function<std::shared_ptr<Enemy>(int health,
                          int damage,
                          int x,
                          int y,
                          const std::function<void(std::shared_ptr<Player> player, Enemy* e)>fun)>> enemyMap_;

    /**
      * Engines for generating possible values for enemies.
      */
    std::mt19937 engine_width_;

    std::mt19937 engine_height_;

    std::mt19937 engine_fun_;

    std::mt19937 engine_type_;

    /**
      *
      */
    std::uniform_int_distribution<int> width_possible_;

    std::uniform_int_distribution<int> height_possible_;

    std::uniform_int_distribution<int> fun_possible_;

};
}


#endif /* WORLD_H_ */
