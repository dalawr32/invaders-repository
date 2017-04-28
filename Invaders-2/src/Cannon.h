/*
 * Created by Daniel Lawrence.
 * This weapon is for creating powerful Laser Cannons.
 */
#ifndef CANNON_H_INCLUDED
#define CANNON_H_INCLUDED

#include "Weapon.h"
#include "Laser_Cannon.h"
namespace proj {
class Cannon : public Weapon<Laser_Cannon> {
public:
    /**Creates a cannon*/
    Cannon(/**Represents the damage of the cannon*/int damage,
           /**Represents whether the cannon is player-controlled*/bool isPlayer);
};
}


#endif // CANNON_H_INCLUDED
