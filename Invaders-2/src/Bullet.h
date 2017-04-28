/*
 * Bullet.h
 *
 *  Created on: Apr 9, 2017
 *      Author: Daniel
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "Sprite.h"

#include <memory>

namespace proj {

class Bullet : virtual public Sprite {
public:
    /**
      * Creates a Bullet of the given subclass of bullet.
      */
    static std::shared_ptr<Bullet> createBullet(/**Determines whether bullet comes from player or enemy*/
                               bool isFriendly,
                                /**X position of bullet*/ double x,
                                /**Y position of bullet*/ double y,
                                /**Speed of bullet*/ double speed,
                                /**Damage of bullet*/ int damage,
                                /**Angle of the bullet*/ int angle);

    /**
      * Determines whether bullet is from player or not.
      */
    bool isFriendly();

    /**
      * Determines the damage of this bullet.
      */
    int getDamage();

    /**
      * Returns the image index of this bullet.
      */
    virtual int getImageIndex();

protected:
    /**
      * Default constructor for a Bullet.
      */
	Bullet(/**Determines whether bullet comes from player or enemy*/bool isFriendly,
        /**X position of bullet*/double x,
        /**Y position of bullet*/double y,
        /**Damage of bullet*/ int damage,
        /**Angle of the bullet*/ int angle);

	/**
	  * Determines whether this bullet damages players or enemies. True means it damages enemies.
	  */
    bool isFriendly_;

    /**
      * Represents the damage done by this bullet.
      */
    int damage_;

};
}



#endif /* BULLET_H_ */
