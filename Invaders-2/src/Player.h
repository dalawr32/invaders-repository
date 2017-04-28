/*
 * Player.h
 *
 *  Created on: Apr 7, 2017
 *      Author: Daniel
 *  This class represents the user controlled
 *  ship, ie the player ship. This class does
 *  NOT contain the control ability for the player.
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Weapon.h"
#include "Ship.h"
#include <tr1/memory>


namespace proj {
class Player : public virtual Ship {
public:
	/**
	 * Creates a player with specified weapon and maximum health.
	 */
	Player(/**The weapon the player has*/std::shared_ptr<Weapon<Bullet>> weapon,
			/**The maximum player health*/int maxHealth);

    /**
      * From Sprite.h, returns that this Player is a Player.
      */
    virtual bool isPlayer() override {
        return true;
    }

    /**
      * From Sprite.h, prevents player from moving past the boundaries.
      */
    virtual void setX(/**The position to be set*/double x) override;

    /**
      * From Sprite.h, caps the speed the player can move at.
      */
    virtual void set_X_Speed(/**The new speed*/double speed) override;

    /**
      * Changes the health of the player.
      */
    virtual void changeHealth(/**New health value*/int health) override;


    /**
      * Moves and updates the player on tick.
      */
    virtual void move_sprite() override;

    /**
      *  Returns the index of this sprite's image's location.
      */
    virtual int getImageIndex();

private:
    /**
      * Determines how much time until the player can be damaged again.
      */
    int invulnerable_time = 0;
};
}



#endif /* PLAYER_H_ */
