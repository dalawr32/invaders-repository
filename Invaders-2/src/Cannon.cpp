

#include "Cannon.h"

#include "Weapon.h"

#include "Bullet.h"

#include "Laser_Cannon.h"

using namespace proj;
using namespace std;

Cannon::Cannon(int damage, bool isPlayer)
: Weapon<Laser_Cannon>("Cannon", damage, 100) {
    isPlayer_ = isPlayer;
    cool_down_ = fire_rate_;
}
