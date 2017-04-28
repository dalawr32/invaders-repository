/**
  * Created by Daniel.
  * Contains all the methods from Repeater.h.
  */


#include "Repeater.h"
#include "Bullet.h"
#include "Weapon.h"

#include <string>

using namespace proj;
using namespace std;

Repeater::Repeater(int damage, bool isPlayer)
: Weapon("Repeater", damage, 25) {
    if (!isPlayer) {
        this->fire_rate_ = 125;
    }
    this->isPlayer_ = isPlayer;
}
