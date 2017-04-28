/*
 * Created by Daniel Lawrence.
 * Represents a powerful bullet.
 */
#ifndef LASER_CANNON_H_INCLUDED
#define LASER_CANNON_H_INCLUDED

#include "Bullet.h"
#include <memory>

namespace proj {
class Laser_Cannon : public Bullet {
public:
    /**
      * Moves the laser.
      */
    virtual void move_sprite() override;

    /**
      * Creates a Laser when called.
      */
    static std::shared_ptr<Laser_Cannon> createBullet(/**Determines whether it is friendly to the player*/ bool isFriendly,
                 /**Determines x coordinate of it*/ double x,
                 /**Determines y coordinate of it*/ double y,
                 /**Determines velocity of bullet*/ double speed,
                 /**Damage the bullet does*/ int damage,
                 /**Angle the bullet travels*/int angle);

protected:
    /**
      * Creates a laser cannon with given info.
      */
    Laser_Cannon(/**Determines whether it is friendly to the player*/ bool isFriendly,
                 /**Determines x coordinate of it*/ double x,
                 /**Determines y coordinate of it*/ double y,
                 /**Determines velocity of bullet*/ double velocity,
                 /**Damage of the bullet*/ int damage,
                 /**Angle the bullet travels*/int angle);
};
}

#endif // LASER_CANNON_H_INCLUDED
