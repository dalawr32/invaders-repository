/*
 * Created by Daniel Lawrence.
 * Utilizes the Cannon to fire lasers.
 */

#ifndef LASER_SHOOTER_H_INCLUDED
#define LASER_SHOOTER_H_INCLUDED

#include "Enemy.h"
#include "Cannon.h"
#include <memory>
#include <functional>

namespace proj {
class Laser_Shooter : public Enemy {
public:
    /**
      * Creates a Laser Shooter with given health.
      */
    Laser_Shooter(/**Health of shooter*/int health,
                  /**Damage done by shooter*/int damage,
                  /**function guiding movement*/
                  const std::function<void(std::shared_ptr<Player> player, Enemy* enemy)> position_change,
                  /**Starting x*/ double x,
                  /**Starting y*/ double y);

    /**
      * Updates the enemy on-tick.
      */
    void update(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Bullet>>& bullets) override;

    /**
      * Returns the index of the image.
      */
    int getImageIndex() override;
private:
    /**
      * Represents the cannon.
      */
    std::shared_ptr<Cannon> weapon_;
};
}


#endif // LASER_SHOOTER_H_INCLUDED
