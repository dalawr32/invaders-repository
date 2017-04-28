/**
*   Created by Daniel Lawrence.
*   Represents the basic type of enemy for the game,
*   one that flies in a predefined line.
*/

#ifndef BASIC_ENEMY_H_INCLUDED
#define BASIC_ENEMY_H_INCLUDED

#include "Enemy.h"
#include "Player.h"
#include <memory>
#include <vector>

namespace proj {
class Basic_Enemy : virtual public Enemy {
public:
    /**
      * Creates a basic enemy with given health. This is primarily for testing.
      *
      */
    Basic_Enemy(/**The health this enemy has.*/int health,
                /**The function guiding enemy movement*/
                std::function<void(std::shared_ptr<Player> p, Enemy* e)> position_change);


    /**
      * Creates an overload constructor for a basic enemy. This one allows for specification of starting position.
      */
    Basic_Enemy(/**The health this enemy has.*/int health,
                /**The function guiding enemy movement*/
                std::function<void(std::shared_ptr<Player> p, Enemy* e)> position_change,
                /**The starting x position*/double start_x,
                /**The starting y position*/ double start_y);


    /**
      * Overrides the Basic Enemy function in Enemy.h to damage players on touch.
      */
    virtual void update(std::shared_ptr<Player> p, std::vector<std::shared_ptr<Bullet>>& bullets) override;

    /**
      *  Returns the index of this sprite's image's location.
      */
    virtual int getImageIndex() override;
};

}

#endif // BASIC_ENEMY_H_INCLUDED
