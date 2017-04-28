/**
*   Created by Daniel Lawrence.
*   Represents another basic type of enemy for the game,
*   one that flies in a predefined line and shoots in a straight line.
*/

#ifndef BASIC_SHOOTER_H_INCLUDED
#define BASIC_SHOOTER_H_INCLUDED

#include "Enemy.h"
#include "Player.h"
#include <memory>
#include <vector>

namespace proj {
class Basic_Shooter : virtual public Enemy {
public:
    /**
      * Creates a Basic Shooter.
      */
    Basic_Shooter(/**The health this enemy has.*/int health,
                  /**The damage this enemy does*/ int damage,
                /**The function guiding enemy movement*/
                std::function<void(std::shared_ptr<Player> p, Enemy* e)> position_change,
                /**The starting x position*/double start_x,
                /**The starting y position*/ double start_y);


    /**
      * Overrides the Basic Shooter function in Enemy.h to damage players on touch.
      */
    virtual void update(std::shared_ptr<Player> p, std::vector<std::shared_ptr<Bullet>>& bullets) override;

    /**
      *  Returns the index of this sprite's image's location.
      */
    virtual int getImageIndex() override;
};
}

#endif // BASIC_SHOOTER_H_INCLUDED
